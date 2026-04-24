#!/usr/bin/env python3
import os
import sys
import re
import glob
import argparse
import pickle as pkl
from typing import Any, Dict, List, Optional, Tuple

import cv2
import numpy as np


# ============================================================
# 路径
# ============================================================

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

# 当前脚本通常在：
# HIL-SERL-Project/examples/classifier_data_single/play_classifier_images.py
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, "..", ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)


# ============================================================
# 尝试读取任务 config.classifier_keys
# ============================================================

def try_get_config_classifier_keys():
    try:
        from examples.galaxea_task.usb_pick_insertion_single.config import env_config
        keys = list(getattr(env_config, "classifier_keys", []))
        if keys:
            return keys
    except Exception:
        pass
    return None


# ============================================================
# 文件名解析
# ============================================================

TIMESTAMP_RE = r"\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2}"

# 兼容新旧格式：
#
# 新格式：
#   prefix_200_success_images_left_wrist_rgb_2026-04-24_12-00-00.pkl
#   prefix_4075_failure_images_left_wrist_rgb_2026-04-24_12-00-00.pkl
#
# 旧格式：
#   prefix_200_success_images_2026-04-24_12-00-00.pkl
#   prefix_4075_failure_images_2026-04-24_12-00-00.pkl
#   prefix_failure_images_2026-04-24_12-00-00.pkl
#
FILE_PATTERN = re.compile(
    rf"^(?P<prefix>.+?)(?:_(?P<count>\d+))?_(?P<kind>success|failure)_images"
    rf"(?:_(?P<keytag>.*?))?_(?P<timestamp>{TIMESTAMP_RE})\.pkl$"
)


def parse_file_info(path: str) -> Optional[Dict[str, Any]]:
    filename = os.path.basename(path)
    m = FILE_PATTERN.match(filename)
    if not m:
        return None

    count = m.group("count")
    keytag = m.group("keytag")

    # 旧格式没有 keytag
    if keytag is None or keytag == "":
        keytag = "no-keytag"

    return {
        "kind": m.group("kind"),
        "prefix": m.group("prefix"),
        "timestamp": m.group("timestamp"),
        "keytag": keytag,
        "count": int(count) if count is not None else None,
        "path": path,
        "filename": filename,
    }


def build_groups(data_dir: str):
    """
    按 (prefix, keytag, timestamp) 分组。
    不强制 success/failure 必须同时存在；这样即使只有 success 或只有 failure 也能打开看。
    """
    all_files = sorted(glob.glob(os.path.join(data_dir, "*.pkl")))

    groups: Dict[Tuple[str, str, str], Dict[str, Any]] = {}
    unmatched = []

    for path in all_files:
        info = parse_file_info(path)
        if info is None:
            unmatched.append(path)
            continue

        key = (info["prefix"], info["keytag"], info["timestamp"])
        if key not in groups:
            groups[key] = {
                "prefix": info["prefix"],
                "keytag": info["keytag"],
                "timestamp": info["timestamp"],
                "success_path": None,
                "failure_path": None,
                "success_filename": None,
                "failure_filename": None,
                "success_count_tag": None,
                "failure_count_tag": None,
            }

        if info["kind"] == "success":
            groups[key]["success_path"] = info["path"]
            groups[key]["success_filename"] = info["filename"]
            groups[key]["success_count_tag"] = info["count"]
        else:
            groups[key]["failure_path"] = info["path"]
            groups[key]["failure_filename"] = info["filename"]
            groups[key]["failure_count_tag"] = info["count"]

    group_list = list(groups.values())

    # 新的排前面
    group_list.sort(
        key=lambda x: (x["timestamp"], x["prefix"], x["keytag"]),
        reverse=True,
    )

    return group_list, unmatched


def load_pkl(path: str):
    with open(path, "rb") as f:
        return pkl.load(f)


def load_group_data(group_info: Dict[str, Any]):
    success_data = load_pkl(group_info["success_path"]) if group_info["success_path"] else []
    failure_data = load_pkl(group_info["failure_path"]) if group_info["failure_path"] else []
    return success_data, failure_data


# ============================================================
# image key 解析
# ============================================================

def parse_image_keys(raw: str):
    """
    raw:
      config -> 使用 env_config.classifier_keys
      all    -> 自动显示样本里所有图像 key
      a,b,c  -> 指定 key
    """
    raw = str(raw).strip()

    if raw.lower() in ("config", "__config__", ""):
        keys = try_get_config_classifier_keys()
        if keys:
            return keys
        return ["left_wrist_rgb"]

    if raw.lower() in ("all", "*"):
        return "all"

    return [x.strip() for x in raw.split(",") if x.strip()]


def get_obs_from_sample(sample: Any):
    if isinstance(sample, dict) and "observations" in sample:
        return sample["observations"]
    return sample


def get_img_dict_from_obs(obs: Any):
    if isinstance(obs, dict) and "images" in obs and isinstance(obs["images"], dict):
        return obs["images"]
    return obs


def infer_image_keys_from_sample(sample: Any):
    obs = get_obs_from_sample(sample)
    img_dict = get_img_dict_from_obs(obs)

    if not isinstance(img_dict, dict):
        return []

    keys = []
    for k, v in img_dict.items():
        try:
            arr = np.asarray(v)
            if arr.ndim >= 3:
                keys.append(k)
        except Exception:
            pass

    # 常用顺序优先
    preferred_order = ["left_wrist_rgb", "head_rgb", "right_wrist_rgb"]
    ordered = [k for k in preferred_order if k in keys]
    ordered += [k for k in keys if k not in ordered]
    return ordered


# ============================================================
# 图像处理
# ============================================================

def unwrap_image(img: Any):
    arr = np.asarray(img)

    # 常见：
    # (1, H, W, C) -> (H, W, C)
    # (B, 1, H, W, C) -> 取最后一帧
    while arr.ndim > 3:
        if arr.shape[0] == 1:
            arr = arr[0]
        else:
            arr = arr[-1]

    return arr


def to_bgr_uint8(img: Any, show_size: Tuple[int, int]):
    arr = unwrap_image(img)

    if arr.ndim == 2:
        arr = np.repeat(arr[..., None], 3, axis=-1)

    if arr.ndim != 3:
        blank = np.zeros((show_size[1], show_size[0], 3), dtype=np.uint8)
        return blank

    if arr.shape[-1] == 1:
        arr = np.repeat(arr, 3, axis=-1)

    if arr.shape[-1] > 3:
        arr = arr[..., :3]

    if arr.dtype != np.uint8:
        arr = np.clip(arr, 0, 255).astype(np.uint8)

    # 数据默认按 RGB 保存，OpenCV 显示需要 BGR
    if arr.shape[-1] == 3:
        arr = arr[..., ::-1]

    arr = cv2.resize(arr, show_size)
    return arr


def blank_frame(show_size: Tuple[int, int], text: str):
    frame = np.zeros((show_size[1], show_size[0], 3), dtype=np.uint8)
    cv2.putText(
        frame,
        text,
        (10, show_size[1] // 2),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.55,
        (0, 0, 255),
        1,
        cv2.LINE_AA,
    )
    return frame


def extract_frames(sample: Any, image_keys, show_size: Tuple[int, int]):
    obs = get_obs_from_sample(sample)
    img_dict = get_img_dict_from_obs(obs)

    if image_keys == "all":
        keys = infer_image_keys_from_sample(sample)
    else:
        keys = list(image_keys)

    if not keys:
        keys = ["left_wrist_rgb"]

    frames = []

    for key in keys:
        if not isinstance(img_dict, dict) or key not in img_dict:
            frame = blank_frame(show_size, f"missing: {key}")
        else:
            frame = to_bgr_uint8(img_dict[key], show_size)

        # 图像左上角写 key
        cv2.rectangle(frame, (0, 0), (show_size[0], 26), (0, 0, 0), -1)
        cv2.putText(
            frame,
            key,
            (8, 18),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.55,
            (0, 255, 255),
            1,
            cv2.LINE_AA,
        )
        frames.append(frame)

    return frames, keys


def transition_summary(sample: Any):
    if not isinstance(sample, dict):
        return ""

    reward = sample.get("rewards", sample.get("reward", None))
    done = sample.get("dones", sample.get("done", None))
    mask = sample.get("masks", sample.get("mask", None))
    action = sample.get("actions", None)

    parts = []

    if reward is not None:
        try:
            parts.append(f"reward={float(np.asarray(reward).reshape(-1)[0]):.3f}")
        except Exception:
            parts.append(f"reward={reward}")

    if done is not None:
        try:
            parts.append(f"done={bool(np.asarray(done).reshape(-1)[0])}")
        except Exception:
            parts.append(f"done={done}")

    if mask is not None:
        try:
            parts.append(f"mask={float(np.asarray(mask).reshape(-1)[0]):.3f}")
        except Exception:
            parts.append(f"mask={mask}")

    if action is not None:
        try:
            a = np.asarray(action).reshape(-1)
            if a.size > 0:
                parts.append(f"action_dim={a.size}")
                parts.append(f"action_absmax={float(np.max(np.abs(a))):.3f}")
        except Exception:
            pass

    return " | ".join(parts)


# ============================================================
# 画布
# ============================================================

def make_canvas(
    sample,
    mode_name: str,
    idx: int,
    total: int,
    group_info: dict,
    group_idx: int,
    group_total: int,
    image_keys,
    show_size: Tuple[int, int],
):
    frames, used_keys = extract_frames(sample, image_keys, show_size)

    if not frames:
        frames = [blank_frame(show_size, "no image")]

    image_row = np.concatenate(frames, axis=1)

    header_h = 115
    footer_h = 45
    canvas_h = header_h + image_row.shape[0] + footer_h
    canvas_w = image_row.shape[1]

    canvas = np.zeros((canvas_h, canvas_w, 3), dtype=np.uint8)

    canvas[header_h:header_h + image_row.shape[0], :, :] = image_row

    current_file = group_info["success_filename"] if mode_name == "success" else group_info["failure_filename"]
    if current_file is None:
        current_file = f"No {mode_name} file in this group"

    line1 = f"[group {group_idx + 1}/{group_total}] prefix={group_info['prefix']} | keytag={group_info['keytag']}"
    line2 = f"timestamp={group_info['timestamp']} | mode={mode_name.upper()} | sample {idx + 1}/{total}"
    line3 = f"file={current_file}"
    line4 = f"image_keys={used_keys}"
    line5 = transition_summary(sample)

    cv2.putText(canvas, line1, (15, 24), cv2.FONT_HERSHEY_SIMPLEX, 0.58, (0, 255, 0), 1, cv2.LINE_AA)
    cv2.putText(canvas, line2, (15, 48), cv2.FONT_HERSHEY_SIMPLEX, 0.58, (255, 255, 0), 1, cv2.LINE_AA)
    cv2.putText(canvas, line3, (15, 72), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (255, 255, 255), 1, cv2.LINE_AA)
    cv2.putText(canvas, line4, (15, 94), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (200, 200, 200), 1, cv2.LINE_AA)

    if line5:
        cv2.putText(canvas, line5, (15, canvas_h - 48), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (180, 255, 180), 1, cv2.LINE_AA)

    help_line = "A/D: prev/next | J/K: +/-10 | S/F: success/failure | Q/E: group | R: reload | ESC: quit"
    cv2.putText(canvas, help_line, (15, canvas_h - 16), cv2.FONT_HERSHEY_SIMPLEX, 0.48, (255, 255, 255), 1, cv2.LINE_AA)

    return canvas


# ============================================================
# 主逻辑
# ============================================================

def print_groups(groups, unmatched):
    if groups:
        print("找到的数据组：")
        for i, g in enumerate(groups):
            print(f"[{i}] prefix={g['prefix']} | keytag={g['keytag']} | timestamp={g['timestamp']}")
            print(f"    success: {g['success_filename']}")
            print(f"    failure: {g['failure_filename']}")
    else:
        print("没有找到可识别的数据组。")

    if unmatched:
        print("\n以下 pkl 文件没有匹配到 success/failure 命名规则：")
        for p in unmatched:
            print(f"    {os.path.basename(p)}")


def choose_initial_mode(success_data, failure_data, requested_mode):
    if requested_mode == "success" and len(success_data) > 0:
        return "success"
    if requested_mode == "failure" and len(failure_data) > 0:
        return "failure"

    if len(success_data) > 0:
        return "success"
    if len(failure_data) > 0:
        return "failure"

    return requested_mode


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--dir",
        type=str,
        default=SCRIPT_DIR,
        help="classifier_data_single 数据目录。默认是脚本所在目录。",
    )
    parser.add_argument(
        "--image_keys",
        type=str,
        default="config",
        help="显示哪些图像。默认 config=env_config.classifier_keys；也可 left_wrist_rgb 或 all。",
    )
    parser.add_argument(
        "--show_size",
        type=int,
        default=384,
        help="每路图像显示边长，默认 384。",
    )
    parser.add_argument(
        "--start_mode",
        type=str,
        default="success",
        choices=["success", "failure"],
        help="默认先看 success 还是 failure。",
    )
    args = parser.parse_args()

    data_dir = os.path.abspath(args.dir)
    image_keys = parse_image_keys(args.image_keys)
    show_size = (args.show_size, args.show_size)

    print("=" * 100)
    print("Reward Classifier Image Viewer")
    print("=" * 100)
    print(f"data_dir      : {data_dir}")
    print(f"image_keys    : {image_keys}")
    print(f"show_size     : {show_size}")
    print("=" * 100)

    groups, unmatched = build_groups(data_dir)
    print_groups(groups, unmatched)

    if not groups:
        raise FileNotFoundError(
            f"{data_dir} 下没有找到可识别的 success/failure pkl 文件。\n"
            "请确认文件名类似：\n"
            "  exp_200_success_images_left_wrist_rgb_2026-04-24_12-00-00.pkl\n"
            "  exp_4000_failure_images_left_wrist_rgb_2026-04-24_12-00-00.pkl"
        )

    group_idx = 0
    success_data, failure_data = load_group_data(groups[group_idx])
    mode = choose_initial_mode(success_data, failure_data, args.start_mode)
    index = 0

    cv2.namedWindow("classifier viewer", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("classifier viewer", 1400, 700)

    while True:
        group_info = groups[group_idx]

        data = success_data if mode == "success" else failure_data
        total = len(data)

        if total == 0:
            canvas = np.zeros((360, 900, 3), dtype=np.uint8)
            msg1 = f"No {mode} data in this group"
            msg2 = f"group={group_info['prefix']} | keytag={group_info['keytag']} | {group_info['timestamp']}"
            msg3 = "S/F switch mode | Q/E switch group | R reload | ESC quit"
            cv2.putText(canvas, msg1, (30, 70), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2, cv2.LINE_AA)
            cv2.putText(canvas, msg2, (30, 120), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1, cv2.LINE_AA)
            cv2.putText(canvas, msg3, (30, 170), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1, cv2.LINE_AA)
        else:
            index = max(0, min(index, total - 1))
            canvas = make_canvas(
                data[index],
                mode,
                index,
                total,
                group_info,
                group_idx,
                len(groups),
                image_keys,
                show_size,
            )

        cv2.imshow("classifier viewer", canvas)
        key = cv2.waitKey(0) & 0xFF

        if key == 27:  # ESC
            break

        elif key == ord("d"):
            index += 1

        elif key == ord("a"):
            index -= 1

        elif key == ord("k"):
            index += 10

        elif key == ord("j"):
            index -= 10

        elif key == ord("s"):
            mode = "success"
            index = 0

        elif key == ord("f"):
            mode = "failure"
            index = 0

        elif key == ord("q"):
            group_idx = (group_idx - 1) % len(groups)
            success_data, failure_data = load_group_data(groups[group_idx])
            mode = choose_initial_mode(success_data, failure_data, mode)
            index = 0

        elif key == ord("e"):
            group_idx = (group_idx + 1) % len(groups)
            success_data, failure_data = load_group_data(groups[group_idx])
            mode = choose_initial_mode(success_data, failure_data, mode)
            index = 0

        elif key == ord("r"):
            groups, unmatched = build_groups(data_dir)
            print_groups(groups, unmatched)
            if not groups:
                print("reload 后没有找到数据组。")
                continue
            group_idx = min(group_idx, len(groups) - 1)
            success_data, failure_data = load_group_data(groups[group_idx])
            mode = choose_initial_mode(success_data, failure_data, mode)
            index = 0

        # 防止越界
        data = success_data if mode == "success" else failure_data
        if data:
            index = max(0, min(index, len(data) - 1))
        else:
            index = 0

    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()