# cd ~/HIL-SERL/HIL-SERL-Project/examples
# python demo_data_single/replay_demo_actions.py

# 你先建议用：

# DRY_RUN = True

# 跑一次，先不动机器人，只验证 demo 文件里：

# actions
# observations -> next_observations 反推 action

# 是否一致。

# 然后再改成：

# DRY_RUN = False

# 真机回放。真机回放前一定确认：

# 1. reset 后位置和录制 demo 初始位置一致；
# 2. VR 手柄不要处于 VR 接管模式；
# 3. wrapper 不要把你的 replay action 覆盖成 intervene_action；
# 4. 夹爪和物体初始状态尽量和录制时一致。
# 5,回放 demos 时，不应该把 demo 里的 action 先乘 POS_SCALE/ROT_SCALE 再传给 env.step()。
#    因为 demos / buffer 里保存的 action[:6] 已经是归一化动作，env.step(action) 
#    内部会按 config 的 POS_SCALE/ROT_SCALE 把它变成真实末端增量执行。

# 修改config后必须重新录制demos，录制完demos再修改config的缩放不可行
# 


"""
replay_demo_gripper_diagnostics.py

用途：
  在播放 demo action 的同时，重点诊断夹爪链路。

它会记录：
  1. demo 里的 action[6]：close(-1) / hold(0) / open(+1)
  2. env.step(action) 前后的真实 gripper feedback
  3. env.unwrapped._last_hw_gripper_cmd 的 right/left 记忆值
  4. reward / done / truncated
  5. refresh_obs_after_sleep 是否成功

适用场景：
  - 你确认独立 gripper 测试正常，但播放 demo 时夹爪仍然“要闭合又张开”
  - 需要判断是 demo action 发了 open、hold memory 变了、外部 publisher 覆盖，还是成功后脚本继续播放造成移动

注意：
  - demo 里的 action[:6] 是归一化动作，不要在脚本外部乘 POS_SCALE / ROT_SCALE。
  - 本脚本不会修改 demo、env、train_rlpd。
  - 第一次可设 DRY_RUN=True；真机诊断设 DRY_RUN=False。
"""

import os
import sys
import glob
import time
import csv
import pickle as pkl
from typing import Any, Dict, List, Optional, Tuple

import numpy as np


# =============================================================================
# 0. 你主要改这里
# =============================================================================

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if not os.path.exists(os.path.join(PROJECT_ROOT, "examples")):
    PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))
if PROJECT_ROOT not in sys.path:
    sys.path.append(PROJECT_ROOT)

from examples.galaxea_task.usb_pick_insertion_single.config import env_config


# demo 路径：目录、单个 pkl、或 glob 都可以。
DEMO_PATH = "./demo_data_single"
DEMO_FILE_INDEX = 0

START_TRANSITION = 0
MAX_STEPS = None  # 建议第一次真机诊断先设 130，只覆盖 close 附近；确认后再 None。

DRY_RUN = False

# 每步 env.step(action) 后等待多久再刷新 live obs。
# 夹爪执行比 EE 慢，建议 0.12~0.30。
STEP_SLEEP_SEC = 0.20
REFRESH_OBS_AFTER_SLEEP = True

WAIT_ENTER_BEFORE_REPLAY = True
FORCE_SCRIPT_MODE = True
USE_CLASSIFIER = False

CLIP_ACTION_FOR_SAFETY = True
QUANTIZE_GRIPPER_FOR_SAFETY = True

# 成功 / 终止后是否停止继续播放。
# replay 诊断时建议打开，避免 reward=1 / done=True 后仍然继续移动。
STOP_ON_REWARD = True
STOP_ON_DONE = True
STOP_ON_TRUNCATED = True

# 如果你只是想看完整 demo 后续动作，可临时设 False。
PRINT_EVERY = 1

SAVE_CSV = True
CSV_PATH = "./demo_replay_gripper_diagnostics.csv"

# 夹爪 feedback 判定阈值，和 env/config 保持一致。
HW_CLOSE_MAX = 30.0
HW_OPEN_MIN = 70.0

# legacy demo 没有 metadata 时，用手动 scale 做离线提示。
# 本脚本不做动作转换，只打印检查。
MANUAL_DEMO_POS_SCALE = 0.018
MANUAL_DEMO_ROT_SCALE = 0.05
MANUAL_DEMO_HZ = 15

STRICT_SCALE_FOR_LIVE_REPLAY = True


# =============================================================================
# 1. demo / metadata
# =============================================================================

def sorted_pkl_files(path: str) -> List[str]:
    if os.path.isdir(path):
        files = sorted(glob.glob(os.path.join(path, "*.pkl")))
    else:
        files = sorted(glob.glob(path))
    files = [f for f in files if f.endswith(".pkl")]
    if not files:
        raise FileNotFoundError(f"没有找到 pkl 文件: {path}")
    return files


def load_demo_payload(path: str, file_index: int) -> Tuple[str, List[Dict[str, Any]], Dict[str, Any], str]:
    files = sorted_pkl_files(path)
    if file_index < 0 or file_index >= len(files):
        raise IndexError(f"DEMO_FILE_INDEX={file_index} 越界，共找到 {len(files)} 个 pkl 文件。")

    file_path = files[file_index]
    with open(file_path, "rb") as f:
        data = pkl.load(f)

    if isinstance(data, dict) and "transitions" in data:
        transitions = data["transitions"]
        metadata = data.get("metadata", {}) or {}
        fmt = "dict_with_metadata" if metadata else "dict_without_metadata"
    elif isinstance(data, list):
        transitions = data
        metadata = {}
        fmt = "legacy_list"
    else:
        raise ValueError(f"无法识别 pkl 格式: type={type(data)}")

    if len(transitions) == 0:
        raise ValueError(f"pkl 为空: {file_path}")

    return file_path, transitions, metadata, fmt


def get_metadata_float(metadata: Dict[str, Any], *keys: str) -> Optional[float]:
    for key in keys:
        if key in metadata and metadata[key] is not None:
            try:
                return float(metadata[key])
            except Exception:
                pass
    return None


def get_config_value(env, name: str, default: float) -> float:
    try:
        base = env.unwrapped
        cfg = getattr(base, "config", None)
        if cfg is not None and hasattr(cfg, name):
            return float(getattr(cfg, name))
        if hasattr(base, name):
            return float(getattr(base, name))
    except Exception:
        pass

    # env_config 是 TrainingConfig，实际 POS_SCALE 通常在硬件 env_cfg 里；
    # 这里仅兜底。
    if hasattr(env_config, name):
        return float(getattr(env_config, name))

    return float(default)


def resolve_demo_scales(metadata: Dict[str, Any], current_pos: float, current_rot: float, current_hz: float):
    meta_pos = get_metadata_float(metadata, "pos_scale", "POS_SCALE")
    meta_rot = get_metadata_float(metadata, "rot_scale", "ROT_SCALE")
    meta_hz = get_metadata_float(metadata, "hz", "HZ")

    if meta_pos is not None and meta_rot is not None:
        return meta_pos, meta_rot, meta_hz if meta_hz is not None else current_hz, "metadata"

    if MANUAL_DEMO_POS_SCALE is not None and MANUAL_DEMO_ROT_SCALE is not None:
        return (
            float(MANUAL_DEMO_POS_SCALE),
            float(MANUAL_DEMO_ROT_SCALE),
            float(MANUAL_DEMO_HZ) if MANUAL_DEMO_HZ is not None else current_hz,
            "manual",
        )

    return current_pos, current_rot, current_hz, "current_config_fallback"


def scales_match(a: float, b: float, atol: float = 1e-9) -> bool:
    return abs(float(a) - float(b)) <= atol


def check_scale_consistency(demo_pos, demo_rot, current_pos, current_rot, source, dry_run):
    print("=" * 100)
    print("Scale 检查")
    print("=" * 100)
    print(f"demo scale source : {source}")
    print(f"demo POS_SCALE    : {demo_pos}")
    print(f"demo ROT_SCALE    : {demo_rot}")
    print(f"current POS_SCALE : {current_pos}")
    print(f"current ROT_SCALE : {current_rot}")

    if scales_match(demo_pos, current_pos) and scales_match(demo_rot, current_rot):
        print("✅ demo scale 和当前 config scale 一致。")
        return

    print("⚠️ demo scale 和当前 config scale 不一致。")
    if not dry_run and STRICT_SCALE_FOR_LIVE_REPLAY:
        raise RuntimeError("真机回放被阻止：demo scale 和当前 config scale 不一致。")


# =============================================================================
# 2. observation / gripper 工具
# =============================================================================

def to_1d_array(x) -> Optional[np.ndarray]:
    try:
        arr = np.asarray(x, dtype=np.float32).reshape(-1)
        if arr.size == 0:
            return None
        return arr
    except Exception:
        return None


def extract_gripper_feedback(obs: Dict[str, Any], arm_side: str = "right") -> Optional[float]:
    if obs is None or not isinstance(obs, dict) or "state" not in obs:
        return None

    state = obs["state"]

    if isinstance(state, dict):
        preferred_keys = []
        if arm_side == "right":
            preferred_keys.extend([
                "right_gripper",
                "state/right_gripper",
                "right/gripper",
                "gripper_right",
            ])
        else:
            preferred_keys.extend([
                "left_gripper",
                "state/left_gripper",
                "left/gripper",
                "gripper_left",
            ])

        preferred_keys.extend(["gripper", "gripper_pos", "gripper_position"])

        for key in preferred_keys:
            if key in state:
                arr = to_1d_array(state[key])
                if arr is not None:
                    return float(arr[-1])

        for key, value in state.items():
            if "gripper" in str(key).lower():
                arr = to_1d_array(value)
                if arr is not None:
                    return float(arr[-1])
        return None

    arr = to_1d_array(state)
    if arr is None:
        return None
    return float(arr[-1])


def classify_gripper_feedback(value: Optional[float]) -> str:
    if value is None:
        return "unknown"
    if value <= HW_CLOSE_MAX:
        return "closed"
    if value >= HW_OPEN_MIN:
        return "open"
    return "middle/unclear"


def describe_gripper_action(g: float) -> str:
    g = float(g)
    if g <= -0.5:
        return "close(-1)"
    if g >= 0.5:
        return "open(+1)"
    return "hold(0)"


def quantize_gripper(g: float) -> float:
    g = float(g)
    if g <= -0.5:
        return -1.0
    if g >= 0.5:
        return 1.0
    return 0.0


def get_env_gripper_memory(env) -> Optional[Dict[str, float]]:
    if env is None:
        return None
    try:
        base = env.unwrapped
        mem = getattr(base, "_last_hw_gripper_cmd", None)
        if isinstance(mem, dict):
            out = {}
            for k, v in mem.items():
                try:
                    out[str(k)] = float(v)
                except Exception:
                    pass
            return out
    except Exception:
        pass
    return None


def print_state_keys(obs: Dict[str, Any]) -> None:
    print("=" * 100)
    print("reset 后 observation state 检查")
    print("=" * 100)
    if obs is None or not isinstance(obs, dict) or "state" not in obs:
        print("⚠️ obs 中没有 state。")
        return

    state = obs["state"]
    if isinstance(state, dict):
        print(f"state keys: {list(state.keys())}")
        for k, v in state.items():
            if "gripper" in str(k).lower():
                arr = to_1d_array(v)
                print(f"  gripper-like key: {k}, value={None if arr is None else arr.tolist()}")
    else:
        arr = to_1d_array(state)
        print(f"state ndarray shape={None if arr is None else arr.shape}, value_head={None if arr is None else arr[:12].tolist()}")
        if arr is not None:
            print(f"  fallback gripper feedback = last dim = {float(arr[-1]):.3f}")


def refresh_obs_after_sleep(env, fallback_obs, sleep_sec: float):
    time.sleep(max(0.0, float(sleep_sec)))

    if not REFRESH_OBS_AFTER_SLEEP:
        return fallback_obs, False, "disabled_use_step_obs"

    try:
        base = env.unwrapped
        if hasattr(base, "_get_sync_obs"):
            fresh_obs = base._get_sync_obs()
            if fresh_obs is not None:
                return fresh_obs, True, "env.unwrapped._get_sync_obs"
    except Exception as e:
        print(f"⚠️ refresh obs failed: {e!r}")

    return fallback_obs, False, "fallback_step_obs"


def force_script_mode_if_possible(env) -> None:
    if not FORCE_SCRIPT_MODE or env is None:
        return

    print("🤖 尝试强制进入脚本/AI动作测试模式，避免 VRInterventionWrapper 覆盖 action...")

    current = env
    seen = set()
    while current is not None and id(current) not in seen:
        seen.add(id(current))

        if hasattr(current, "use_vr_mode"):
            try:
                current.use_vr_mode = False
                print(f"  - set {type(current).__name__}.use_vr_mode=False")
            except Exception as e:
                print(f"  - warning: set use_vr_mode failed: {e!r}")

        if hasattr(current, "_call_switch_service"):
            try:
                current._call_switch_service(False)
                print(f"  - call {type(current).__name__}._call_switch_service(False)")
            except Exception as e:
                print(f"  - warning: _call_switch_service(False) failed: {e!r}")

        current = getattr(current, "env", None)

    try:
        base = env.unwrapped
        if hasattr(base, "notify_script_control"):
            base.notify_script_control(True)
            print("  - call env.unwrapped.notify_script_control(True)")
    except Exception as e:
        print(f"  - warning: notify_script_control failed: {e!r}")

    print("✅ 已请求脚本/AI模式。请确认 VR 手柄/底层控制没有处于 VR 接管模式。")


def make_env():
    return env_config.get_environment(
        fake_env=False,
        save_video=False,
        classifier=USE_CLASSIFIER,
    )


# =============================================================================
# 3. transition / action
# =============================================================================

def get_transition_action(trans: Dict[str, Any]) -> np.ndarray:
    for key in ("actions", "action"):
        if key in trans:
            arr = np.asarray(trans[key], dtype=np.float32).reshape(-1)
            return arr
    raise KeyError("transition 中找不到 actions/action 字段。")


def prepare_action_for_step(raw_action: np.ndarray, action_space=None) -> Tuple[np.ndarray, bool]:
    action = np.asarray(raw_action, dtype=np.float32).reshape(-1).copy()
    before = action.copy()

    if CLIP_ACTION_FOR_SAFETY:
        if action_space is not None:
            try:
                low = np.asarray(action_space.low, dtype=np.float32).reshape(-1)
                high = np.asarray(action_space.high, dtype=np.float32).reshape(-1)
                if low.shape == action.shape and high.shape == action.shape:
                    action = np.clip(action, low, high)
                else:
                    action = np.clip(action, -1.0, 1.0)
            except Exception:
                action = np.clip(action, -1.0, 1.0)
        else:
            action = np.clip(action, -1.0, 1.0)

    if QUANTIZE_GRIPPER_FOR_SAFETY and action.size >= 7:
        action[6] = np.float32(quantize_gripper(float(action[6])))

    changed = not np.allclose(before, action, atol=1e-6)
    return action.astype(np.float32), bool(changed)


def info_has_intervention(info: Any) -> bool:
    if not isinstance(info, dict):
        return False
    keys = [
        "intervene_action",
        "intervention_action",
        "intervene",
        "intervened",
        "vr_intervention",
    ]
    for k in keys:
        if k in info:
            v = info[k]
            if isinstance(v, bool):
                return bool(v)
            if v is not None:
                return True
    return False


# =============================================================================
# 4. CSV / summary
# =============================================================================

def save_csv(rows: List[Dict[str, Any]]) -> None:
    if not SAVE_CSV or not rows:
        return
    fieldnames = list(rows[0].keys())
    with open(CSV_PATH, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)
    print(f"✅ CSV saved: {os.path.abspath(CSV_PATH)}")


def summarize_rows(rows: List[Dict[str, Any]]) -> None:
    print("=" * 100)
    print("Replay gripper diagnostics summary")
    print("=" * 100)
    print(f"rows: {len(rows)}")

    if not rows:
        return

    close_rows = [r for r in rows if float(r["action_6"]) <= -0.5]
    hold_rows = [r for r in rows if abs(float(r["action_6"])) < 0.5]
    open_rows = [r for r in rows if float(r["action_6"]) >= 0.5]

    print(f"gripper close/hold/open: {len(close_rows)} / {len(hold_rows)} / {len(open_rows)}")

    if close_rows:
        print("close action steps:", [r["global_step"] for r in close_rows[:20]], "..." if len(close_rows) > 20 else "")
    if open_rows:
        print("open action steps :", [r["global_step"] for r in open_rows[:20]], "..." if len(open_rows) > 20 else "")

    vals = []
    for r in rows:
        v = r.get("next_gripper_feedback", "")
        if v != "":
            vals.append(float(v))
    if vals:
        arr = np.asarray(vals, dtype=np.float32)
        print(f"feedback min/mean/max: {float(np.min(arr)):.3f} / {float(np.mean(arr)):.3f} / {float(np.max(arr)):.3f}")
        print(f"closed count <= {HW_CLOSE_MAX}: {int(np.sum(arr <= HW_CLOSE_MAX))}")
        print(f"open count   >= {HW_OPEN_MIN}: {int(np.sum(arr >= HW_OPEN_MIN))}")
        print(f"middle count           : {int(np.sum((arr > HW_CLOSE_MAX) & (arr < HW_OPEN_MIN)))}")

    # 找 close 后 20 步
    if close_rows:
        first_close = close_rows[0]["global_step"]
        win = [r for r in rows if first_close <= r["global_step"] <= first_close + 25]
        print("\nfirst close 附近窗口：")
        for r in win:
            print(
                f"  step={r['global_step']:04d}, a6={r['action_6_desc']}, "
                f"fb {r['prev_gripper_feedback']} -> {r['next_gripper_feedback']} "
                f"({r['next_gripper_state']}), "
                f"hw_right {r['prev_hw_gripper_cmd_right']} -> {r['next_hw_gripper_cmd_right']}, "
                f"reward={r['reward']}, done={r['done']}"
            )

    rewards = [r for r in rows if r.get("reward", "") not in ("", None) and float(r["reward"]) != 0.0]
    dones = [r for r in rows if bool(r.get("done", False))]
    truncs = [r for r in rows if bool(r.get("truncated", False))]

    if rewards:
        print(f"\nreward != 0 first step: {rewards[0]['global_step']}, reward={rewards[0]['reward']}")
    if dones:
        print(f"done=True first step: {dones[0]['global_step']}")
    if truncs:
        print(f"truncated=True first step: {truncs[0]['global_step']}")

    print("\n判断建议：")
    print("  1. 如果 action_6 没有 open(+1)，但 gripper feedback 回到 open，说明不是 demo 标签打开。")
    print("  2. 如果 hold 阶段 next_hw_gripper_cmd_right 保持 10，但 feedback 升到 70/80，怀疑外部 publisher 或底层夹爪保持。")
    print("  3. 如果 hold 阶段 next_hw_gripper_cmd_right 变成 80，说明 replay 链路中 hold memory 被改回 open。")
    print("  4. 如果 reward/done 后仍有 rows，建议启用 STOP_ON_REWARD/STOP_ON_DONE，避免成功后继续移动。")


# =============================================================================
# 5. main
# =============================================================================

def main():
    print("=" * 100)
    print("Demo Replay Gripper Diagnostics")
    print("=" * 100)
    print(f"DEMO_PATH                  : {DEMO_PATH}")
    print(f"DEMO_FILE_INDEX            : {DEMO_FILE_INDEX}")
    print(f"START_TRANSITION           : {START_TRANSITION}")
    print(f"MAX_STEPS                  : {MAX_STEPS}")
    print(f"DRY_RUN                    : {DRY_RUN}")
    print(f"STEP_SLEEP_SEC             : {STEP_SLEEP_SEC}")
    print(f"REFRESH_OBS_AFTER_SLEEP    : {REFRESH_OBS_AFTER_SLEEP}")
    print(f"FORCE_SCRIPT_MODE          : {FORCE_SCRIPT_MODE}")
    print(f"USE_CLASSIFIER             : {USE_CLASSIFIER}")
    print(f"STOP_ON_REWARD/DONE/TRUNC  : {STOP_ON_REWARD} / {STOP_ON_DONE} / {STOP_ON_TRUNCATED}")
    print(f"CSV_PATH                   : {CSV_PATH}")

    file_path, transitions, metadata, pkl_format = load_demo_payload(DEMO_PATH, DEMO_FILE_INDEX)
    print("=" * 100)
    print("Demo 文件")
    print("=" * 100)
    print(f"file: {file_path}")
    print(f"format: {pkl_format}")
    print(f"num transitions: {len(transitions)}")
    if metadata:
        print(f"metadata keys: {list(metadata.keys())}")

    env = None
    obs = None

    if DRY_RUN:
        current_pos, current_rot, current_hz = 0.018, 0.05, 15.0
        obs = {}
    else:
        print("\n🌍 正在创建真实环境...")
        env = make_env()

        current_pos = get_config_value(env, "POS_SCALE", 0.018)
        current_rot = get_config_value(env, "ROT_SCALE", 0.05)
        current_hz = get_config_value(env, "HZ", 15.0)

        print("\n🔄 正在 reset 环境...")
        obs, reset_info = env.reset()

        force_script_mode_if_possible(env)

        print_state_keys(obs)
        initial_feedback = extract_gripper_feedback(obs)
        print("=" * 100)
        print("初始 gripper feedback")
        print("=" * 100)
        print(f"initial gripper feedback: {initial_feedback} ({classify_gripper_feedback(initial_feedback)})")
        print(f"initial _last_hw_gripper_cmd: {get_env_gripper_memory(env)}")

    demo_pos, demo_rot, demo_hz, scale_source = resolve_demo_scales(
        metadata,
        current_pos,
        current_rot,
        current_hz,
    )
    check_scale_consistency(demo_pos, demo_rot, current_pos, current_rot, scale_source, DRY_RUN)

    end_transition = len(transitions)
    if MAX_STEPS is not None:
        end_transition = min(end_transition, START_TRANSITION + int(MAX_STEPS))

    selected = transitions[START_TRANSITION:end_transition]
    print("=" * 100)
    print("Replay 范围")
    print("=" * 100)
    print(f"selected transitions: {len(selected)}")
    print(f"global range: [{START_TRANSITION}, {end_transition})")

    if WAIT_ENTER_BEFORE_REPLAY and not DRY_RUN:
        input("确认机器人安全、夹爪附近无遮挡、VR 没有接管后，按 Enter 开始 replay 诊断...")

    rows: List[Dict[str, Any]] = []

    close_seen = 0
    open_seen = 0

    for local_i, trans in enumerate(selected):
        global_step = START_TRANSITION + local_i

        raw_action = get_transition_action(trans)
        raw_min = float(np.min(raw_action)) if raw_action.size else 0.0
        raw_max = float(np.max(raw_action)) if raw_action.size else 0.0

        action_space = None if env is None else getattr(env, "action_space", None)
        action, changed_by_safety = prepare_action_for_step(raw_action, action_space)

        if action.size < 7:
            raise ValueError(f"当前脚本期望 action 至少 7 维，但 step={global_step} action.shape={action.shape}")

        g = float(action[6])
        g_desc = describe_gripper_action(g)
        if g <= -0.5:
            close_seen += 1
        if g >= 0.5:
            open_seen += 1

        prev_feedback = extract_gripper_feedback(obs)
        prev_state = classify_gripper_feedback(prev_feedback)
        prev_mem = get_env_gripper_memory(env)

        if DRY_RUN:
            reward = None
            done = False
            truncated = False
            info = {}
            next_obs = obs
            refresh_success = False
            refresh_source = "dry_run"
            intervention_overrode_action = False
        else:
            step_obs, reward, done, truncated, info = env.step(action)
            intervention_overrode_action = info_has_intervention(info)
            next_obs, refresh_success, refresh_source = refresh_obs_after_sleep(env, step_obs, STEP_SLEEP_SEC)

        next_feedback = extract_gripper_feedback(next_obs)
        next_state = classify_gripper_feedback(next_feedback)
        next_mem = get_env_gripper_memory(env)

        delta_feedback = ""
        if prev_feedback is not None and next_feedback is not None:
            delta_feedback = float(next_feedback - prev_feedback)

        row = {
            "global_step": global_step,
            "local_step": local_i,
            "pkl_format": pkl_format,
            "demo_scale_source": scale_source,
            "demo_pos_scale": demo_pos,
            "demo_rot_scale": demo_rot,
            "current_pos_scale": current_pos,
            "current_rot_scale": current_rot,
            "raw_action_min": raw_min,
            "raw_action_max": raw_max,
            "action_changed_by_safety": bool(changed_by_safety),
            "intervention_overrode_action": bool(intervention_overrode_action),
            "action_0": float(action[0]),
            "action_1": float(action[1]),
            "action_2": float(action[2]),
            "action_3": float(action[3]),
            "action_4": float(action[4]),
            "action_5": float(action[5]),
            "action_6": float(action[6]),
            "action_6_desc": g_desc,
            "prev_gripper_feedback": "" if prev_feedback is None else float(prev_feedback),
            "next_gripper_feedback": "" if next_feedback is None else float(next_feedback),
            "delta_gripper_feedback": delta_feedback,
            "prev_gripper_state": prev_state,
            "next_gripper_state": next_state,
            "prev_hw_gripper_cmd_right": "" if not prev_mem or "right" not in prev_mem else float(prev_mem["right"]),
            "next_hw_gripper_cmd_right": "" if not next_mem or "right" not in next_mem else float(next_mem["right"]),
            "prev_hw_gripper_cmd_left": "" if not prev_mem or "left" not in prev_mem else float(prev_mem["left"]),
            "next_hw_gripper_cmd_left": "" if not next_mem or "left" not in next_mem else float(next_mem["left"]),
            "refresh_success": bool(refresh_success),
            "refresh_source": refresh_source,
            "reward": "" if reward is None else float(reward),
            "done": bool(done),
            "truncated": bool(truncated),
        }
        rows.append(row)

        should_print = (
            PRINT_EVERY is not None
            and PRINT_EVERY > 0
            and (local_i % PRINT_EVERY == 0)
        )

        # 夹爪事件附近强制打印
        if g_desc != "hold(0)":
            should_print = True

        # close 后 25 步内强制打印，方便观察闭合是否回弹
        if close_seen > 0 and close_seen <= 3:
            if len(rows) >= 2:
                first_close_step = next((r["global_step"] for r in rows if float(r["action_6"]) <= -0.5), None)
                if first_close_step is not None and global_step <= first_close_step + 25:
                    should_print = True

        if should_print:
            print("-" * 100)
            print(f"step {global_step} / local {local_i}")
            print(f"action[6]                  : {g_desc} ({g})")
            print(f"prev gripper feedback      : {prev_feedback} ({prev_state})")
            print(f"next gripper feedback      : {next_feedback} ({next_state})")
            print(f"delta gripper feedback     : {delta_feedback}")
            print(f"env _last_hw_gripper_cmd   : before={prev_mem}, after={next_mem}")
            print(f"intervention_overrode      : {intervention_overrode_action}")
            print(f"obs_refresh_success        : {refresh_success}, source={refresh_source}")
            print(f"reward={reward}, done={done}, truncated={truncated}")
            print("说明：obs_refresh_success=True 只表示刷新 observation 成功，不表示任务成功。")

        obs = next_obs

        if not DRY_RUN:
            if STOP_ON_REWARD and reward is not None and float(reward) != 0.0:
                print(f"✅ reward={reward} at step={global_step}，停止 replay，避免成功后继续移动。")
                break
            if STOP_ON_DONE and bool(done):
                print(f"✅ done=True at step={global_step}，停止 replay。")
                break
            if STOP_ON_TRUNCATED and bool(truncated):
                print(f"✅ truncated=True at step={global_step}，停止 replay。")
                break

    summarize_rows(rows)
    save_csv(rows)

    print("=" * 100)
    print("完成")
    print("=" * 100)


if __name__ == "__main__":
    main()




# """
# replay_demo_actions_standalone.py

# 只改回放脚本，不要求修改 demo 录制脚本、train_rlpd.py 或 GalaxeaArmEnv。

# 用途：
# 1. 读取旧格式 demo pkl: [transition, ...]
# 2. 兼容新格式 demo pkl: {"metadata": {...}, "transitions": [...]}
# 3. 按 demo 中保存的归一化 action 逐步 env.step(action) 回放。
# 4. DRY_RUN=True 时只做离线检查，不动机器人。
# 5. DRY_RUN=False 时真机回放，并在 env.step(action) 后先 sleep，再重新取 live obs 反推真实执行 delta。
# 6. 输出：
#    - demo action 本身
#    - action * 当前 POS_SCALE / ROT_SCALE 的理论命令增量
#    - demo 文件中 obs -> next_obs 反推 action
#    - live 真机 obs -> next_obs 反推 action
#    - normalized error
#    - 物理量 error：m / rad / degree

# 重要原则：
# - demo 里的 action[:6] 是归一化动作，不要在脚本外面乘 POS_SCALE / ROT_SCALE 再传给 env.step。
# - env.step(action) 内部会按当前 config.POS_SCALE / config.ROT_SCALE 执行动作。
# - 如果你改了 config.POS_SCALE / config.ROT_SCALE，必须重新录 demos；否则旧 demo action 的物理语义会变。
# - 本脚本不负责自动转换旧 demo action。scale 不一致时默认禁止真机回放。
# """

# import os
# import sys
# import glob
# import time
# import csv
# import pickle as pkl
# from datetime import datetime
# from typing import Any, Dict, List, Optional, Tuple

# import numpy as np
# from scipy.spatial.transform import Rotation as R


# # =============================================================================
# # 0. 你主要改这里
# # =============================================================================

# # 项目根目录：默认假设本脚本放在 examples/ 或 examples/demo_data_single/ 附近。
# PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
# if not os.path.exists(os.path.join(PROJECT_ROOT, "examples")):
#     PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))
# if PROJECT_ROOT not in sys.path:
#     sys.path.append(PROJECT_ROOT)

# # 单臂任务 config：你当前 single 任务用这个。
# from examples.galaxea_task.usb_pick_insertion_single.config import env_config


# # demo 路径：可以是目录、单个 pkl、glob。
# DEMO_PATH = "./demo_data_single"

# # 如果 DEMO_PATH 是目录或 glob，选择第几个 pkl 文件。
# DEMO_FILE_INDEX = 0

# # 从 demo 的第几条 transition 开始回放。
# START_TRANSITION = 0

# # 回放多少步。None 表示回放到 demo 结束。
# # 建议真机第一次先设成 10 或 20。
# MAX_STEPS = None

# # 安全默认：先离线检查，不动机器人。
# # 确认 demo_delta / scale / reset 都正常后，再改成 False。
# DRY_RUN = False#True

# # 每步 action 发出后，等待机器人跟随多久，再重新读取 live obs 计算 live delta。
# # 注意：新版脚本把 sleep 放在 live 反推之前。
# STEP_SLEEP_SEC = 0.12

# # sleep 后是否重新向底层取一次最新 observation。
# # True: 用 env.unwrapped._get_sync_obs() 刷新 live_next_obs。
# # False: 只用 env.step 返回的 next_obs。
# REFRESH_OBS_AFTER_SLEEP = True

# # 回放前是否等待你按回车。
# WAIT_ENTER_BEFORE_REPLAY = True

# # 是否打印初始 reset 位姿和 demo 首帧位姿对比。
# PRINT_INITIAL_POSE_COMPARE = True

# # 是否在 env 外层强制关闭 VR 接管状态。
# # 注意：最好物理手柄也切到脚本/AI模式，否则 VR callback 可能又切回去。
# FORCE_SCRIPT_MODE = True

# # 是否创建环境时启用 classifier。回放动作检查不需要 classifier，False 更快更干净。
# USE_CLASSIFIER = False

# # 安全处理 action。
# CLIP_ACTION_FOR_SAFETY = True
# QUANTIZE_GRIPPER_FOR_SAFETY = True

# # 保存 CSV。
# SAVE_CSV = True
# CSV_PATH = "./demo_replay_action_check_v2.csv"

# # 打印频率。
# PRINT_EVERY = 1

# # scale 检查：如果 demo 有 metadata 或你手动填了 MANUAL_DEMO_*，且和当前 config 不一致，默认禁止真机回放。
# STRICT_SCALE_FOR_LIVE_REPLAY = True

# # 旧 demo 没有 metadata 时，你可以手动填录制旧 demo 时使用的 scale。
# # 如果不填，就默认使用当前 config scale 做 demo 离线反推。
# # 例如旧 demo 是 POS_SCALE=0.01, ROT_SCALE=0.05 录的：
# # MANUAL_DEMO_POS_SCALE = 0.01
# # MANUAL_DEMO_ROT_SCALE = 0.05
# MANUAL_DEMO_POS_SCALE = 0.018
# MANUAL_DEMO_ROT_SCALE = 0.05
# MANUAL_DEMO_HZ = 15

# # 初始位姿误差报警阈值。
# INITIAL_POS_WARN_M = 0.02        # 2 cm
# INITIAL_ROT_WARN_RAD = 0.20      # 约 11.5 度

# # live error 报警阈值：同时看物理量和 normalized action。
# # 物理量更重要；normalized 在 ROT_SCALE 很小时会显得很大。
# LIVE_WARN_POS_ERR_M = 0.004                 # 4 mm
# LIVE_WARN_ROT_ERR_RAD = float(np.deg2rad(1.0))  # 1 degree
# LIVE_WARN_ACTION_ERR_NORM = 1.50

# # demo 离线误差报警阈值。
# DEMO_WARN_POS_ERR_M = 0.002                 # 2 mm
# DEMO_WARN_ROT_ERR_RAD = float(np.deg2rad(0.5))  # 0.5 degree
# DEMO_WARN_ACTION_ERR_NORM = 0.25


# # =============================================================================
# # 1. pkl / metadata 读取
# # =============================================================================

# def sorted_pkl_files(path: str) -> List[str]:
#     if os.path.isdir(path):
#         files = sorted(glob.glob(os.path.join(path, "*.pkl")))
#     else:
#         files = sorted(glob.glob(path))

#     files = [f for f in files if f.endswith(".pkl")]
#     if not files:
#         raise FileNotFoundError(f"没有找到 pkl 文件: {path}")
#     return files


# def load_demo_payload(path: str, file_index: int) -> Tuple[str, List[Dict[str, Any]], Dict[str, Any], str]:
#     """
#     兼容两种格式：
#       旧格式: [transition, ...]
#       新格式: {"metadata": {...}, "transitions": [...]}
#     """
#     files = sorted_pkl_files(path)

#     if file_index < 0 or file_index >= len(files):
#         raise IndexError(f"DEMO_FILE_INDEX={file_index} 越界，共找到 {len(files)} 个 pkl 文件。")

#     file_path = files[file_index]
#     with open(file_path, "rb") as f:
#         data = pkl.load(f)

#     if isinstance(data, dict) and "transitions" in data:
#         transitions = data["transitions"]
#         metadata = data.get("metadata", {}) or {}
#         fmt = "dict_with_metadata" if metadata else "dict_without_metadata"
#     elif isinstance(data, list):
#         transitions = data
#         metadata = {}
#         fmt = "legacy_list"
#     else:
#         raise ValueError(f"无法识别 pkl 格式: type={type(data)}")

#     if len(transitions) == 0:
#         raise ValueError(f"pkl 为空: {file_path}")

#     return file_path, transitions, metadata, fmt


# def get_metadata_float(metadata: Dict[str, Any], *keys: str) -> Optional[float]:
#     for key in keys:
#         if key in metadata and metadata[key] is not None:
#             try:
#                 return float(metadata[key])
#             except Exception:
#                 pass
#     return None


# def get_config_value(env, name: str, default: float) -> float:
#     """
#     优先从 env.unwrapped.config 读取 POS_SCALE / ROT_SCALE / HZ。
#     再从 env_config 读取。
#     最后 fallback 到 default。
#     """
#     try:
#         base_env = env.unwrapped
#         cfg = getattr(base_env, "config", None)
#         if cfg is not None and hasattr(cfg, name):
#             return float(getattr(cfg, name))
#         if hasattr(base_env, name):
#             return float(getattr(base_env, name))
#     except Exception:
#         pass

#     if hasattr(env_config, name):
#         return float(getattr(env_config, name))

#     return float(default)


# def resolve_demo_scales(
#     metadata: Dict[str, Any],
#     current_pos_scale: float,
#     current_rot_scale: float,
#     current_hz: float,
# ) -> Tuple[float, float, float, str]:
#     """
#     demo 离线反推使用哪个 scale：
#     1. 优先 pkl metadata
#     2. 其次手动 MANUAL_DEMO_*
#     3. 最后当前 config
#     """
#     meta_pos = get_metadata_float(metadata, "pos_scale", "POS_SCALE")
#     meta_rot = get_metadata_float(metadata, "rot_scale", "ROT_SCALE")
#     meta_hz = get_metadata_float(metadata, "hz", "HZ")

#     if meta_pos is not None and meta_rot is not None:
#         return meta_pos, meta_rot, meta_hz if meta_hz is not None else current_hz, "metadata"

#     if MANUAL_DEMO_POS_SCALE is not None and MANUAL_DEMO_ROT_SCALE is not None:
#         return (
#             float(MANUAL_DEMO_POS_SCALE),
#             float(MANUAL_DEMO_ROT_SCALE),
#             float(MANUAL_DEMO_HZ) if MANUAL_DEMO_HZ is not None else current_hz,
#             "manual",
#         )

#     return current_pos_scale, current_rot_scale, current_hz, "current_config_fallback"


# def scales_match(a: float, b: float, atol: float = 1e-9) -> bool:
#     return abs(float(a) - float(b)) <= atol


# def check_scale_consistency(
#     demo_pos_scale: float,
#     demo_rot_scale: float,
#     current_pos_scale: float,
#     current_rot_scale: float,
#     source: str,
#     dry_run: bool,
# ) -> None:
#     pos_ok = scales_match(demo_pos_scale, current_pos_scale)
#     rot_ok = scales_match(demo_rot_scale, current_rot_scale)

#     print("=" * 100)
#     print("Scale 检查")
#     print("=" * 100)
#     print(f"demo scale source : {source}")
#     print(f"demo POS_SCALE    : {demo_pos_scale}")
#     print(f"demo ROT_SCALE    : {demo_rot_scale}")
#     print(f"current POS_SCALE : {current_pos_scale}")
#     print(f"current ROT_SCALE : {current_rot_scale}")

#     if pos_ok and rot_ok:
#         print("✅ demo scale 和当前 config scale 一致。")
#         return

#     print("⚠️ demo scale 和当前 config scale 不一致。")
#     print("   这意味着 demo action 的物理语义和当前 env.step(action) 的物理语义不同。")
#     print("   如果你改了 POS_SCALE / ROT_SCALE，原则上必须重新录 demos。")

#     if not dry_run and STRICT_SCALE_FOR_LIVE_REPLAY:
#         raise RuntimeError(
#             "当前为真机回放 DRY_RUN=False，但 demo scale 和当前 config scale 不一致。\n"
#             "为了避免危险动作，脚本已停止。\n"
#             "解决方式：\n"
#             "1) 改回录 demo 时的 POS_SCALE / ROT_SCALE；或\n"
#             "2) 重新录 demos；或\n"
#             "3) 你确认风险后，把 STRICT_SCALE_FOR_LIVE_REPLAY=False。"
#         )


# # =============================================================================
# # 2. observation / pose 工具
# # =============================================================================

# def to_1d_array(x) -> Optional[np.ndarray]:
#     try:
#         arr = np.asarray(x, dtype=np.float32).reshape(-1)
#         if arr.size == 0:
#             return None
#         return arr
#     except Exception:
#         return None


# def extract_pose_from_state_dict(state: Dict[str, Any], arm_side: str = "right") -> Optional[np.ndarray]:
#     preferred_keys = []

#     if arm_side == "right":
#         preferred_keys.extend([
#             "right_ee_pose",
#             "right/tcp_pose",
#             "right_tcp_pose",
#             "state/right_ee_pose",
#             "state/right/tcp_pose",
#             "pose_ee_arm_right",
#         ])
#     else:
#         preferred_keys.extend([
#             "left_ee_pose",
#             "left/tcp_pose",
#             "left_tcp_pose",
#             "state/left_ee_pose",
#             "state/left/tcp_pose",
#             "pose_ee_arm_left",
#         ])

#     preferred_keys.extend([
#         "ee_pose",
#         "tcp_pose",
#         "pose_ee",
#     ])

#     for key in preferred_keys:
#         if key in state:
#             arr = to_1d_array(state[key])
#             if arr is not None and arr.size >= 6:
#                 return arr[:7] if arr.size >= 7 else arr[:6]

#     for key, value in state.items():
#         k = str(key).lower()
#         if ("pose" in k or "tcp" in k or "ee" in k) and "gripper" not in k:
#             arr = to_1d_array(value)
#             if arr is not None and arr.size >= 6:
#                 return arr[:7] if arr.size >= 7 else arr[:6]

#     return None


# def extract_ee_pose(obs: Dict[str, Any], arm_side: str = "right") -> Optional[np.ndarray]:
#     """
#     从 observation 中提取 EE pose。
#     兼容：
#       obs["state"] 是 dict
#       obs["state"] 是 array: [x,y,z,qx,qy,qz,qw,gripper]
#     """
#     if obs is None or not isinstance(obs, dict):
#         return None

#     if "state" not in obs:
#         return None

#     state = obs["state"]

#     if isinstance(state, dict):
#         return extract_pose_from_state_dict(state, arm_side=arm_side)

#     arr = to_1d_array(state)
#     if arr is None:
#         return None

#     if arr.size >= 7:
#         return arr[:7]
#     if arr.size >= 6:
#         return arr[:6]

#     return None


# def pose_to_pos_quat(pose: np.ndarray) -> Tuple[Optional[np.ndarray], Optional[np.ndarray]]:
#     """
#     支持：
#       7 维: xyz + quat(xyzw)
#       6 维: xyz + euler(xyz)
#     """
#     if pose is None:
#         return None, None

#     pose = np.asarray(pose, dtype=np.float32).reshape(-1)

#     if pose.size >= 7:
#         pos = pose[:3].astype(np.float32)
#         quat = pose[3:7].astype(np.float32)
#         norm = float(np.linalg.norm(quat))
#         if norm < 1e-8:
#             return None, None
#         quat = quat / norm
#         return pos, quat

#     if pose.size >= 6:
#         pos = pose[:3].astype(np.float32)
#         quat = R.from_euler("xyz", pose[3:6]).as_quat().astype(np.float32)
#         return pos, quat

#     return None, None


# def compute_delta_action_from_poses(
#     prev_pose: Optional[np.ndarray],
#     next_pose: Optional[np.ndarray],
#     pos_scale: float,
#     rot_scale: float,
#     clip: bool = False,
# ) -> Optional[np.ndarray]:
#     """
#     用 EE pose 差分反推 action[:6]：
#       action[:3] = (next_pos - prev_pos) / POS_SCALE
#       action[3:6] = rotvec(next_rot * prev_rot.inv()) / ROT_SCALE
#     """
#     if prev_pose is None or next_pose is None:
#         return None

#     prev_pos, prev_quat = pose_to_pos_quat(prev_pose)
#     next_pos, next_quat = pose_to_pos_quat(next_pose)

#     if prev_pos is None or next_pos is None or prev_quat is None or next_quat is None:
#         return None

#     try:
#         pos_delta = next_pos - prev_pos

#         prev_rot = R.from_quat(prev_quat)
#         next_rot = R.from_quat(next_quat)
#         rot_delta = (next_rot * prev_rot.inv()).as_rotvec().astype(np.float32)

#         a6 = np.zeros(6, dtype=np.float32)
#         a6[:3] = pos_delta / float(pos_scale)
#         a6[3:6] = rot_delta / float(rot_scale)

#         if clip:
#             a6 = np.clip(a6, -1.0, 1.0)

#         return a6.astype(np.float32)
#     except Exception:
#         return None


# def compute_real_delta_from_action(
#     action: np.ndarray,
#     pos_scale: float,
#     rot_scale: float,
# ) -> Tuple[np.ndarray, np.ndarray]:
#     """
#     normalized action -> 理论真实位移 / 旋转增量。
#     不要把这个 scaled action 再传给 env.step。
#     """
#     a = np.asarray(action, dtype=np.float32).reshape(-1)
#     pos_delta_m = a[:3] * float(pos_scale)
#     rot_delta_rad = a[3:6] * float(rot_scale)
#     return pos_delta_m.astype(np.float32), rot_delta_rad.astype(np.float32)


# def physical_delta_from_action6(
#     action6: np.ndarray,
#     pos_scale: float,
#     rot_scale: float,
# ) -> Tuple[np.ndarray, np.ndarray]:
#     a = np.asarray(action6, dtype=np.float32).reshape(-1)
#     pos_delta_m = a[:3] * float(pos_scale)
#     rot_delta_rad = a[3:6] * float(rot_scale)
#     return pos_delta_m.astype(np.float32), rot_delta_rad.astype(np.float32)


# # =============================================================================
# # 3. action / error 工具
# # =============================================================================

# def sanitize_action_for_replay(action: np.ndarray) -> Tuple[np.ndarray, bool]:
#     """
#     安全处理 action：
#       action[:6] 可选 clip 到 [-1,1]
#       action[6] 可选量化成 -1/0/+1
#     返回：clean_action, changed
#     """
#     a = np.asarray(action, dtype=np.float32).reshape(-1).copy()

#     if a.shape[0] != 7:
#         raise ValueError(f"当前脚本按单臂 7 维 action 写的，但收到 action shape={a.shape}")

#     before = a.copy()

#     if CLIP_ACTION_FOR_SAFETY:
#         a[:6] = np.clip(a[:6], -1.0, 1.0)

#     if QUANTIZE_GRIPPER_FOR_SAFETY:
#         g = float(a[6])
#         if g <= -0.5:
#             a[6] = -1.0
#         elif g >= 0.5:
#             a[6] = 1.0
#         else:
#             a[6] = 0.0

#     changed = bool(not np.allclose(before, a, atol=1e-6, rtol=1e-6))
#     return a.astype(np.float32), changed


# def describe_gripper(g: float) -> str:
#     g = float(g)
#     if g <= -0.5:
#         return "close(-1)"
#     if g >= 0.5:
#         return "open(+1)"
#     return "hold(0)"


# def max_abs_or_none(x: Optional[np.ndarray]) -> Optional[float]:
#     if x is None:
#         return None
#     return float(np.max(np.abs(np.asarray(x))))


# def deg(rad: float) -> float:
#     return float(np.rad2deg(rad))


# def compute_error_metrics(
#     expected_action6: np.ndarray,
#     measured_action6: Optional[np.ndarray],
#     pos_scale: float,
#     rot_scale: float,
# ) -> Dict[str, Any]:
#     """
#     同时返回 normalized error 和物理量 error。
#     expected_action6 / measured_action6 都是 normalized action[:6]。
#     """
#     out: Dict[str, Any] = {
#         "action_err_max": None,
#         "pos_err_max_m": None,
#         "rot_err_max_rad": None,
#         "rot_err_max_deg": None,
#         "pos_err_vec_m": None,
#         "rot_err_vec_rad": None,
#     }

#     if measured_action6 is None:
#         return out

#     expected_action6 = np.asarray(expected_action6, dtype=np.float32).reshape(6)
#     measured_action6 = np.asarray(measured_action6, dtype=np.float32).reshape(6)

#     action_err = measured_action6 - expected_action6
#     expected_pos_m, expected_rot_rad = physical_delta_from_action6(expected_action6, pos_scale, rot_scale)
#     measured_pos_m, measured_rot_rad = physical_delta_from_action6(measured_action6, pos_scale, rot_scale)

#     pos_err_vec_m = measured_pos_m - expected_pos_m
#     rot_err_vec_rad = measured_rot_rad - expected_rot_rad

#     rot_err_max_rad = float(np.max(np.abs(rot_err_vec_rad)))

#     out.update({
#         "action_err_max": float(np.max(np.abs(action_err))),
#         "pos_err_max_m": float(np.max(np.abs(pos_err_vec_m))),
#         "rot_err_max_rad": rot_err_max_rad,
#         "rot_err_max_deg": deg(rot_err_max_rad),
#         "pos_err_vec_m": pos_err_vec_m,
#         "rot_err_vec_rad": rot_err_vec_rad,
#     })
#     return out


# def is_live_warn(metrics: Dict[str, Any]) -> bool:
#     if metrics["action_err_max"] is None:
#         return False
#     return bool(
#         metrics["pos_err_max_m"] > LIVE_WARN_POS_ERR_M
#         or metrics["rot_err_max_rad"] > LIVE_WARN_ROT_ERR_RAD
#         or metrics["action_err_max"] > LIVE_WARN_ACTION_ERR_NORM
#     )


# def is_demo_warn(metrics: Dict[str, Any]) -> bool:
#     if metrics["action_err_max"] is None:
#         return False
#     return bool(
#         metrics["pos_err_max_m"] > DEMO_WARN_POS_ERR_M
#         or metrics["rot_err_max_rad"] > DEMO_WARN_ROT_ERR_RAD
#         or metrics["action_err_max"] > DEMO_WARN_ACTION_ERR_NORM
#     )


# # =============================================================================
# # 4. env / live 观测工具
# # =============================================================================

# def make_env():
#     env = env_config.get_environment(
#         fake_env=False,
#         save_video=False,
#         classifier=USE_CLASSIFIER,
#     )
#     return env


# def force_script_mode_if_possible(env) -> None:
#     """
#     尽量让 VRInterventionWrapper 不覆盖我们传入的 demo action。
#     最好你物理手柄也切到脚本/AI控制模式。
#     """
#     if not FORCE_SCRIPT_MODE:
#         return

#     print("🤖 尝试强制进入脚本/AI动作回放模式，避免 VRInterventionWrapper 覆盖 action...")

#     current = env
#     seen = set()

#     while current is not None and id(current) not in seen:
#         seen.add(id(current))

#         if hasattr(current, "use_vr_mode"):
#             try:
#                 current.use_vr_mode = False
#                 print(f"  - set {type(current).__name__}.use_vr_mode=False")
#             except Exception as e:
#                 print(f"  - warning: set use_vr_mode failed: {e!r}")

#         if hasattr(current, "_call_switch_service"):
#             try:
#                 current._call_switch_service(False)
#                 print(f"  - call {type(current).__name__}._call_switch_service(False)")
#             except Exception as e:
#                 print(f"  - warning: _call_switch_service(False) failed: {e!r}")

#         current = getattr(current, "env", None)

#     try:
#         base = env.unwrapped
#         if hasattr(base, "notify_script_control"):
#             base.notify_script_control(True)
#             print("  - call env.unwrapped.notify_script_control(True)")
#     except Exception as e:
#         print(f"  - warning: notify_script_control failed: {e!r}")

#     print("✅ 已请求脚本/AI模式。请确认 VR 手柄/底层控制没有处于 VR 接管模式。")


# def refresh_live_observation(env, fallback_obs: Dict[str, Any]) -> Tuple[Dict[str, Any], bool, str]:
#     """
#     env.step 后 sleep，再重新取最新 observation。
#     不修改 env 文件，直接调用 unwrapped._get_sync_obs()。
#     如果失败，就 fallback 到 env.step 返回的 next_obs。
#     """
#     if not REFRESH_OBS_AFTER_SLEEP:
#         return fallback_obs, False, "disabled"

#     try:
#         base = env.unwrapped
#         if hasattr(base, "_get_sync_obs"):
#             obs = base._get_sync_obs()
#             if obs is not None:
#                 return obs, True, "env.unwrapped._get_sync_obs"
#     except Exception as e:
#         return fallback_obs, False, f"refresh_failed:{e!r}"

#     return fallback_obs, False, "method_missing"


# def compare_initial_pose(
#     demo_obs: Dict[str, Any],
#     live_obs: Dict[str, Any],
#     pos_scale: float,
#     rot_scale: float,
# ) -> None:
#     demo_pose = extract_ee_pose(demo_obs)
#     live_pose = extract_ee_pose(live_obs)

#     if demo_pose is None or live_pose is None:
#         print("⚠️ 无法比较初始 EE pose：demo_pose 或 live_pose 提取失败。")
#         return

#     demo_pos, demo_quat = pose_to_pos_quat(demo_pose)
#     live_pos, live_quat = pose_to_pos_quat(live_pose)

#     if demo_pos is None or live_pos is None or demo_quat is None or live_quat is None:
#         print("⚠️ 无法比较初始 EE pose：pose_to_pos_quat 失败。")
#         return

#     pos_err = float(np.linalg.norm(live_pos - demo_pos))

#     try:
#         demo_rot = R.from_quat(demo_quat)
#         live_rot = R.from_quat(live_quat)
#         rot_err = float((live_rot * demo_rot.inv()).magnitude())
#     except Exception:
#         rot_err = float("nan")

#     print("=" * 100)
#     print("初始 reset 位姿对比")
#     print("=" * 100)
#     print(f"demo_pos: {np.round(demo_pos, 6).tolist()}")
#     print(f"live_pos: {np.round(live_pos, 6).tolist()}")
#     print(f"pos_err : {pos_err:.6f} m")
#     print(f"rot_err : {rot_err:.6f} rad = {deg(rot_err):.3f} deg")
#     print(f"pos_err / POS_SCALE: {pos_err / pos_scale:.3f}")
#     print(f"rot_err / ROT_SCALE: {rot_err / rot_scale:.3f}")

#     if pos_err > INITIAL_POS_WARN_M or (not np.isnan(rot_err) and rot_err > INITIAL_ROT_WARN_RAD):
#         print("⚠️ 初始 reset 和 demo 录制初始位姿差异较大，回放轨迹可能和录制时不一致。")
#     else:
#         print("✅ 初始 reset 和 demo 录制初始位姿比较接近。")


# # =============================================================================
# # 5. 打印 / CSV 工具
# # =============================================================================

# def safe_float(x: Any, default: Any = "") -> Any:
#     if x is None:
#         return default
#     try:
#         return float(x)
#     except Exception:
#         return default


# def add_vec_fields(row: Dict[str, Any], prefix: str, vec: Optional[np.ndarray], n: int) -> None:
#     if vec is None:
#         for i in range(n):
#             row[f"{prefix}_{i}"] = ""
#         return
#     arr = np.asarray(vec).reshape(-1)
#     for i in range(n):
#         row[f"{prefix}_{i}"] = float(arr[i]) if i < arr.size else ""


# def print_metrics(label: str, metrics: Dict[str, Any]) -> None:
#     if metrics["action_err_max"] is None:
#         print(f"{label}: N/A")
#         return
#     print(
#         f"{label}: "
#         f"norm_max={metrics['action_err_max']:.6f}, "
#         f"pos_max={metrics['pos_err_max_m']:.6f} m, "
#         f"rot_max={metrics['rot_err_max_rad']:.6f} rad ({metrics['rot_err_max_deg']:.3f} deg)"
#     )


# def summarize_numeric(rows: List[Dict[str, Any]], key: str) -> None:
#     vals = [r[key] for r in rows if key in r and r[key] != ""]
#     if not vals:
#         return
#     vals = np.asarray(vals, dtype=np.float64)
#     print(f"{key:32s}: mean={np.mean(vals):.6f}, max={np.max(vals):.6f}")


# # =============================================================================
# # 6. 主逻辑
# # =============================================================================

# def main():
#     file_path, transitions, metadata, fmt = load_demo_payload(DEMO_PATH, DEMO_FILE_INDEX)

#     print("=" * 100)
#     print("Demo Action Replay Standalone V2")
#     print("=" * 100)
#     print(f"DEMO_PATH       : {DEMO_PATH}")
#     print(f"selected file   : {file_path}")
#     print(f"pkl format      : {fmt}")
#     print(f"num transitions : {len(transitions)}")
#     print(f"START_TRANSITION: {START_TRANSITION}")
#     print(f"MAX_STEPS       : {MAX_STEPS}")
#     print(f"DRY_RUN         : {DRY_RUN}")
#     print(f"STEP_SLEEP_SEC  : {STEP_SLEEP_SEC}")
#     print(f"REFRESH_OBS     : {REFRESH_OBS_AFTER_SLEEP}")
#     print(f"CLIP_ACTION     : {CLIP_ACTION_FOR_SAFETY}")
#     print(f"QUANTIZE_GRIPPER: {QUANTIZE_GRIPPER_FOR_SAFETY}")

#     if metadata:
#         print("=" * 100)
#         print("Demo metadata")
#         print("=" * 100)
#         for k in sorted(metadata.keys()):
#             v = metadata[k]
#             if isinstance(v, np.ndarray):
#                 v = np.round(v, 6).tolist()
#             print(f"{k}: {v}")
#     else:
#         print("⚠️ 当前 demo pkl 没有 metadata。脚本会使用 MANUAL_DEMO_* 或当前 config scale 做离线检查。")

#     if START_TRANSITION < 0 or START_TRANSITION >= len(transitions):
#         raise IndexError(f"START_TRANSITION={START_TRANSITION} 越界。")

#     end = len(transitions) if MAX_STEPS is None else min(len(transitions), START_TRANSITION + int(MAX_STEPS))
#     selected = transitions[START_TRANSITION:end]

#     env = None
#     obs = None

#     if not DRY_RUN:
#         print("🌍 正在创建真实环境...")
#         env = make_env()

#         current_pos_scale = get_config_value(env, "POS_SCALE", 0.01)
#         current_rot_scale = get_config_value(env, "ROT_SCALE", 0.05)
#         current_hz = get_config_value(env, "HZ", 15.0)

#         demo_pos_scale, demo_rot_scale, demo_hz, demo_scale_source = resolve_demo_scales(
#             metadata,
#             current_pos_scale,
#             current_rot_scale,
#             current_hz,
#         )

#         print(f"✅ 从 config/env 读取当前缩放：POS_SCALE={current_pos_scale}, ROT_SCALE={current_rot_scale}, HZ={current_hz}")
#         check_scale_consistency(
#             demo_pos_scale,
#             demo_rot_scale,
#             current_pos_scale,
#             current_rot_scale,
#             demo_scale_source,
#             dry_run=False,
#         )

#         print("🔄 正在 reset 环境...")
#         obs, info = env.reset()
#         force_script_mode_if_possible(env)

#         if PRINT_INITIAL_POSE_COMPARE:
#             compare_initial_pose(
#                 selected[0].get("observations", None),
#                 obs,
#                 current_pos_scale,
#                 current_rot_scale,
#             )

#         if WAIT_ENTER_BEFORE_REPLAY:
#             input("确认机器人已经 reset 到和录制时一致，且处于脚本/AI控制模式后，按 Enter 开始回放...")
#     else:
#         current_pos_scale = float(getattr(env_config, "POS_SCALE", 0.01))
#         current_rot_scale = float(getattr(env_config, "ROT_SCALE", 0.05))
#         current_hz = float(getattr(env_config, "HZ", 15.0))

#         demo_pos_scale, demo_rot_scale, demo_hz, demo_scale_source = resolve_demo_scales(
#             metadata,
#             current_pos_scale,
#             current_rot_scale,
#             current_hz,
#         )

#         print(f"✅ DRY_RUN：从 env_config 读取当前缩放：POS_SCALE={current_pos_scale}, ROT_SCALE={current_rot_scale}, HZ={current_hz}")
#         check_scale_consistency(
#             demo_pos_scale,
#             demo_rot_scale,
#             current_pos_scale,
#             current_rot_scale,
#             demo_scale_source,
#             dry_run=True,
#         )

#     rows: List[Dict[str, Any]] = []

#     print("=" * 100)
#     print("开始回放 / 检查")
#     print("=" * 100)

#     changed_count = 0
#     missing_demo_delta_count = 0
#     missing_live_delta_count = 0
#     demo_warn_count = 0
#     live_warn_count = 0
#     intervention_override_count = 0
#     refresh_success_count = 0

#     for local_i, transition in enumerate(selected):
#         global_i = START_TRANSITION + local_i

#         if "actions" not in transition:
#             print(f"⚠️ transition {global_i} 没有 actions，跳过。")
#             continue

#         raw_action = np.asarray(transition["actions"], dtype=np.float32).reshape(-1)
#         action, changed = sanitize_action_for_replay(raw_action)
#         changed_count += int(changed)

#         # 当前 env 真机执行时的理论命令物理增量。
#         expected_pos_delta_m, expected_rot_delta_rad = compute_real_delta_from_action(
#             action,
#             current_pos_scale,
#             current_rot_scale,
#         )

#         # demo 文件内部 obs -> next_obs 反推。这里用 demo scale，不一定等于当前 config。
#         demo_prev_pose = extract_ee_pose(transition.get("observations", None))
#         demo_next_pose = extract_ee_pose(transition.get("next_observations", None))

#         demo_delta_action6 = compute_delta_action_from_poses(
#             demo_prev_pose,
#             demo_next_pose,
#             demo_pos_scale,
#             demo_rot_scale,
#             clip=False,
#         )

#         if demo_delta_action6 is None:
#             missing_demo_delta_count += 1

#         demo_metrics = compute_error_metrics(
#             action[:6],
#             demo_delta_action6,
#             demo_pos_scale,
#             demo_rot_scale,
#         )
#         if is_demo_warn(demo_metrics):
#             demo_warn_count += 1

#         live_delta_action6 = None
#         live_metrics = compute_error_metrics(action[:6], None, current_pos_scale, current_rot_scale)
#         live_reward = None
#         live_done = None
#         live_truncated = None
#         intervention_overrode_action = False
#         refresh_success = False
#         refresh_source = ""

#         if not DRY_RUN:
#             live_prev_pose = extract_ee_pose(obs)

#             # 关键：env.step(action) 传入的是归一化 action，不做额外 scale。
#             next_obs, reward, done, truncated, info = env.step(action)

#             # 如果 wrapper 返回 intervene_action，说明 VR/外部逻辑可能覆盖了 replay action。
#             if isinstance(info, dict) and "intervene_action" in info:
#                 intervention_overrode_action = True
#                 intervention_override_count += 1

#             # 关键改动：先等机器人跟随，再重新取 obs，然后反推 live delta。
#             if STEP_SLEEP_SEC > 0:
#                 time.sleep(STEP_SLEEP_SEC)

#             next_obs_for_measure, refresh_success, refresh_source = refresh_live_observation(env, next_obs)
#             refresh_success_count += int(refresh_success)

#             live_next_pose = extract_ee_pose(next_obs_for_measure)
#             live_delta_action6 = compute_delta_action_from_poses(
#                 live_prev_pose,
#                 live_next_pose,
#                 current_pos_scale,
#                 current_rot_scale,
#                 clip=False,
#             )

#             if live_delta_action6 is None:
#                 missing_live_delta_count += 1

#             live_metrics = compute_error_metrics(
#                 action[:6],
#                 live_delta_action6,
#                 current_pos_scale,
#                 current_rot_scale,
#             )
#             if is_live_warn(live_metrics):
#                 live_warn_count += 1

#             live_reward = reward
#             live_done = done
#             live_truncated = truncated
#             obs = next_obs_for_measure

#         if local_i % PRINT_EVERY == 0:
#             print("-" * 100)
#             print(f"step {global_i} / local {local_i}")
#             print(f"action[:6] normalized       : {np.round(action[:6], 4).tolist()}")
#             print(f"gripper action[6]           : {describe_gripper(action[6])}")
#             print(f"expected pos delta, current : {np.round(expected_pos_delta_m, 6).tolist()} m")
#             print(f"expected rot delta, current : {np.round(expected_rot_delta_rad, 6).tolist()} rad")

#             if demo_delta_action6 is not None:
#                 demo_pos_m, demo_rot_rad = physical_delta_from_action6(
#                     demo_delta_action6,
#                     demo_pos_scale,
#                     demo_rot_scale,
#                 )
#                 print(f"demo obs-delta action[:6]   : {np.round(demo_delta_action6, 4).tolist()}")
#                 print(f"demo obs-delta pos          : {np.round(demo_pos_m, 6).tolist()} m")
#                 print(f"demo obs-delta rot          : {np.round(demo_rot_rad, 6).tolist()} rad")
#                 print_metrics("demo error", demo_metrics)
#                 if is_demo_warn(demo_metrics):
#                     print("⚠️ demo 文件内 obs->next_obs 反推动作和保存 action 差异较大。")
#             else:
#                 print("demo obs-delta action[:6]   : N/A")

#             if not DRY_RUN:
#                 if live_delta_action6 is not None:
#                     live_pos_m, live_rot_rad = physical_delta_from_action6(
#                         live_delta_action6,
#                         current_pos_scale,
#                         current_rot_scale,
#                     )
#                     print(f"live obs-delta action[:6]   : {np.round(live_delta_action6, 4).tolist()}")
#                     print(f"live obs-delta pos          : {np.round(live_pos_m, 6).tolist()} m")
#                     print(f"live obs-delta rot          : {np.round(live_rot_rad, 6).tolist()} rad")
#                     print_metrics("live measured error", live_metrics)
#                     if is_live_warn(live_metrics):
#                         print("⚠️ live 实测运动和命令 action 差异较大。")
#                 else:
#                     print("live obs-delta action[:6]   : N/A")

#                 print(f"refresh_obs_after_sleep     : success={refresh_success}, source={refresh_source}")
#                 if intervention_overrode_action:
#                     print("⚠️ info 中出现 intervene_action，说明 replay action 可能被 VR/介入逻辑覆盖。")
#                 print(f"reward={live_reward}, done={live_done}, truncated={live_truncated}")

#         row: Dict[str, Any] = {
#             "global_step": global_i,
#             "local_step": local_i,
#             "pkl_format": fmt,
#             "demo_scale_source": demo_scale_source,
#             "demo_pos_scale": float(demo_pos_scale),
#             "demo_rot_scale": float(demo_rot_scale),
#             "current_pos_scale": float(current_pos_scale),
#             "current_rot_scale": float(current_rot_scale),
#             "raw_action_min": float(np.min(raw_action)),
#             "raw_action_max": float(np.max(raw_action)),
#             "action_changed_by_safety": bool(changed),
#             "intervention_overrode_action": bool(intervention_overrode_action),
#             "refresh_success": bool(refresh_success),
#             "refresh_source": refresh_source,
#             "expected_dx_m_current": float(expected_pos_delta_m[0]),
#             "expected_dy_m_current": float(expected_pos_delta_m[1]),
#             "expected_dz_m_current": float(expected_pos_delta_m[2]),
#             "expected_rx_rad_current": float(expected_rot_delta_rad[0]),
#             "expected_ry_rad_current": float(expected_rot_delta_rad[1]),
#             "expected_rz_rad_current": float(expected_rot_delta_rad[2]),
#             "demo_action_err_max": safe_float(demo_metrics["action_err_max"]),
#             "demo_pos_err_max_m": safe_float(demo_metrics["pos_err_max_m"]),
#             "demo_rot_err_max_rad": safe_float(demo_metrics["rot_err_max_rad"]),
#             "demo_rot_err_max_deg": safe_float(demo_metrics["rot_err_max_deg"]),
#             "live_action_err_max": safe_float(live_metrics["action_err_max"]),
#             "live_pos_err_max_m": safe_float(live_metrics["pos_err_max_m"]),
#             "live_rot_err_max_rad": safe_float(live_metrics["rot_err_max_rad"]),
#             "live_rot_err_max_deg": safe_float(live_metrics["rot_err_max_deg"]),
#             "live_reward": "" if live_reward is None else float(live_reward),
#             "live_done": "" if live_done is None else bool(live_done),
#             "live_truncated": "" if live_truncated is None else bool(live_truncated),
#         }

#         for j in range(7):
#             row[f"action_{j}"] = float(action[j])

#         add_vec_fields(row, "demo_delta_action", demo_delta_action6, 6)
#         add_vec_fields(row, "live_delta_action", live_delta_action6, 6)
#         add_vec_fields(row, "demo_pos_err_vec_m", demo_metrics["pos_err_vec_m"], 3)
#         add_vec_fields(row, "demo_rot_err_vec_rad", demo_metrics["rot_err_vec_rad"], 3)
#         add_vec_fields(row, "live_pos_err_vec_m", live_metrics["pos_err_vec_m"], 3)
#         add_vec_fields(row, "live_rot_err_vec_rad", live_metrics["rot_err_vec_rad"], 3)

#         rows.append(row)

#         if not DRY_RUN:
#             if live_done or live_truncated:
#                 print(f"✅ 环境在 step {global_i} 返回 done/truncated，停止回放。")
#                 break

#     print("=" * 100)
#     print("回放 / 检查总结")
#     print("=" * 100)
#     print(f"selected transitions        : {len(selected)}")
#     print(f"executed / checked rows     : {len(rows)}")
#     print(f"changed_by_safety           : {changed_count}")
#     print(f"missing_demo_delta_count    : {missing_demo_delta_count}")
#     print(f"missing_live_delta_count    : {missing_live_delta_count}")
#     print(f"demo_warn_count             : {demo_warn_count}")
#     print(f"live_warn_count             : {live_warn_count}")
#     print(f"intervention_override_count : {intervention_override_count}")
#     if not DRY_RUN:
#         print(f"refresh_success_count       : {refresh_success_count} / {len(rows)}")

#     if rows:
#         summarize_numeric(rows, "demo_action_err_max")
#         summarize_numeric(rows, "demo_pos_err_max_m")
#         summarize_numeric(rows, "demo_rot_err_max_rad")
#         summarize_numeric(rows, "demo_rot_err_max_deg")
#         summarize_numeric(rows, "live_action_err_max")
#         summarize_numeric(rows, "live_pos_err_max_m")
#         summarize_numeric(rows, "live_rot_err_max_rad")
#         summarize_numeric(rows, "live_rot_err_max_deg")

#         arr_actions = np.array([[r[f"action_{j}"] for j in range(7)] for r in rows], dtype=np.float32)
#         print(f"replay action[:6] absmax    : {float(np.max(np.abs(arr_actions[:, :6]))):.6f}")
#         print(
#             "gripper close/hold/open     : "
#             f"{int(np.sum(arr_actions[:, 6] < -0.5))} / "
#             f"{int(np.sum(np.abs(arr_actions[:, 6]) <= 0.5))} / "
#             f"{int(np.sum(arr_actions[:, 6] > 0.5))}"
#         )

#     if SAVE_CSV and rows:
#         fieldnames = list(rows[0].keys())
#         with open(CSV_PATH, "w", newline="") as f:
#             writer = csv.DictWriter(f, fieldnames=fieldnames)
#             writer.writeheader()
#             writer.writerows(rows)

#         print(f"✅ CSV saved: {os.path.abspath(CSV_PATH)}")

#     print("完成。")


# if __name__ == "__main__":
#     main()
