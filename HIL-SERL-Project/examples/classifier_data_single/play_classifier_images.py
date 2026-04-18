import os
import re
import glob
import pickle as pkl
import cv2
import numpy as np


BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATA_DIR = BASE_DIR

IMAGE_KEYS = ["left_wrist_rgb", "head_rgb", "right_wrist_rgb"]
SHOW_SIZE = (256, 256)

# success: prefix_200_success_images_2026-04-18_20-47-17.pkl
SUCCESS_PATTERN = re.compile(
    r"^(?P<prefix>.+?)_(?P<count>\d+)_success_images_(?P<timestamp>\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2})\.pkl$"
)

# failure 兼容两种格式：
# 1) prefix_failure_images_timestamp.pkl
# 2) prefix_7810_failure_images_timestamp.pkl
FAILURE_PATTERN = re.compile(
    r"^(?P<prefix>.+?)(?:_(?P<count>\d+))?_failure_images_(?P<timestamp>\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2})\.pkl$"
)


def load_pkl(path: str):
    with open(path, "rb") as f:
        return pkl.load(f)


def parse_file_info(path: str):
    filename = os.path.basename(path)

    m = SUCCESS_PATTERN.match(filename)
    if m:
        return {
            "kind": "success",
            "prefix": m.group("prefix"),
            "timestamp": m.group("timestamp"),
            "count": int(m.group("count")),
            "path": path,
            "filename": filename,
        }

    m = FAILURE_PATTERN.match(filename)
    if m:
        count = m.group("count")
        return {
            "kind": "failure",
            "prefix": m.group("prefix"),
            "timestamp": m.group("timestamp"),
            "count": int(count) if count is not None else None,
            "path": path,
            "filename": filename,
        }

    return None


def build_groups():
    """
    把 success / failure 文件按 (prefix, timestamp) 配成一组。
    兼容：
      galaxea_usb_insertion_single_200_success_images_2026-04-18_20-47-17.pkl
      galaxea_usb_insertion_single_7810_failure_images_2026-04-18_20-47-17.pkl

    也兼容旧式 failure：
      galaxea_usb_insertion_single_failure_images_2026-04-18_20-47-17.pkl
    """
    all_files = glob.glob(os.path.join(DATA_DIR, "*.pkl"))
    groups = {}

    for path in all_files:
        info = parse_file_info(path)
        if info is None:
            continue

        key = (info["prefix"], info["timestamp"])
        if key not in groups:
            groups[key] = {
                "prefix": info["prefix"],
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
    group_list.sort(key=lambda x: (x["prefix"], x["timestamp"]), reverse=True)
    return group_list


def extract_images(obs_or_transition):
    """
    兼容两种格式：
    1) transition["observations"][key]
    2) transition["observations"]["images"][key]
    """
    if "observations" in obs_or_transition:
        obs = obs_or_transition["observations"]
    else:
        obs = obs_or_transition

    if isinstance(obs, dict) and "images" in obs:
        img_dict = obs["images"]
    else:
        img_dict = obs

    frames = []
    for key in IMAGE_KEYS:
        if key not in img_dict:
            blank = np.zeros((SHOW_SIZE[1], SHOW_SIZE[0], 3), dtype=np.uint8)
            frames.append(blank)
            continue

        img = np.asarray(img_dict[key])

        while img.ndim > 3:
            img = img[-1]

        if img.dtype != np.uint8:
            img = np.clip(img, 0, 255).astype(np.uint8)

        # RGB -> BGR
        img = img[..., ::-1]
        img = cv2.resize(img, SHOW_SIZE)
        frames.append(img)

    return frames


def make_canvas(sample, mode_name: str, idx: int, total: int, group_info: dict, group_idx: int, group_total: int):
    frames = extract_images(sample)
    if not frames:
        blank = np.zeros((SHOW_SIZE[1], SHOW_SIZE[0], 3), dtype=np.uint8)
        frames = [blank, blank, blank]

    canvas = np.concatenate(frames, axis=1)

    line1 = f"[{group_idx + 1}/{group_total}] {group_info['prefix']} | {group_info['timestamp']}"
    line2 = f"{mode_name.upper()} | sample {idx + 1}/{total}"
    line3 = "A/D: prev/next | S/F: success/failure | Q/E: prev/next group | ESC: quit"

    current_file = group_info["success_filename"] if mode_name == "success" else group_info["failure_filename"]
    if current_file is None:
        current_file = f"No {mode_name} file"

    cv2.putText(canvas, line1, (20, 28), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2, cv2.LINE_AA)
    cv2.putText(canvas, line2, (20, 58), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 0), 2, cv2.LINE_AA)
    cv2.putText(canvas, current_file, (20, 88), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 255, 255), 1, cv2.LINE_AA)
    cv2.putText(canvas, line3, (20, canvas.shape[0] - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1, cv2.LINE_AA)

    return canvas


def load_group_data(group_info):
    success_data = load_pkl(group_info["success_path"]) if group_info["success_path"] else []
    failure_data = load_pkl(group_info["failure_path"]) if group_info["failure_path"] else []
    return success_data, failure_data


def main():
    groups = build_groups()
    if not groups:
        raise FileNotFoundError("classifier_data_single 目录下没有找到可配对的 success/failure pkl 文件。")

    print("找到的数据组：")
    for i, g in enumerate(groups):
        print(f"[{i}] prefix={g['prefix']} | timestamp={g['timestamp']}")
        print(f"    success: {g['success_filename']}")
        print(f"    failure: {g['failure_filename']}")

    group_idx = 0
    group_info = groups[group_idx]
    success_data, failure_data = load_group_data(group_info)

    mode = "success" if len(success_data) > 0 else "failure"
    index = 0

    cv2.namedWindow("classifier viewer", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("classifier viewer", 1400, 420)

    while True:
        group_info = groups[group_idx]

        if mode == "success":
            data = success_data
        else:
            data = failure_data

        if not data:
            canvas = np.zeros((SHOW_SIZE[1], SHOW_SIZE[0] * 3, 3), dtype=np.uint8)
            msg = f"No {mode} data in this group"
            cv2.putText(canvas, msg, (30, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2, cv2.LINE_AA)
            cv2.putText(
                canvas,
                f"group={group_info['prefix']} | {group_info['timestamp']}",
                (30, 100),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (255, 255, 255),
                1,
                cv2.LINE_AA,
            )
        else:
            index = max(0, min(index, len(data) - 1))
            canvas = make_canvas(
                data[index],
                mode,
                index,
                len(data),
                group_info,
                group_idx,
                len(groups),
            )

        cv2.imshow("classifier viewer", canvas)
        key = cv2.waitKey(0) & 0xFF

        if key == 27:  # ESC
            break
        elif key == ord("d"):
            index += 1
        elif key == ord("a"):
            index -= 1
        elif key == ord("s"):
            mode = "success"
            index = 0
        elif key == ord("f"):
            mode = "failure"
            index = 0
        elif key == ord("q"):
            group_idx = (group_idx - 1) % len(groups)
            group_info = groups[group_idx]
            success_data, failure_data = load_group_data(group_info)
            mode = "success" if len(success_data) > 0 else "failure"
            index = 0
        elif key == ord("e"):
            group_idx = (group_idx + 1) % len(groups)
            group_info = groups[group_idx]
            success_data, failure_data = load_group_data(group_info)
            mode = "success" if len(success_data) > 0 else "failure"
            index = 0

    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()