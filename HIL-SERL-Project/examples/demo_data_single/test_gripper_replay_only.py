"""
test_gripper_replay_only.py

用途：
  用和 replay/actor 一样的 env.step(action) 链路，单独测试单臂夹爪动作。

核心测试：
  1) action[:6] = 0，只动 action[6]
  2) 连续发送 close(-1) 若干步
  3) 连续发送 hold(0) 若干步，检查是否保持闭合
  4) 连续发送 open(+1) 若干步
  5) 连续发送 hold(0) 若干步，检查是否保持张开

判断依据：
  - 打印每步 env.step 前后的真实 gripper feedback
  - 保存 CSV，方便看 feedback 是否真的从 open 区间变到 close 区间

注意：
  - 这个脚本不会修改你的 env / train / demo 文件。
  - 它只通过 env.step(action) 测试夹爪命令链路。
  - 当前默认 DRY_RUN=True，不会动真机。确认后改成 False。
"""

import os
import sys
import time
import csv
from typing import Any, Dict, Optional, Tuple, List

import numpy as np


# =============================================================================
# 0. 你主要改这里
# =============================================================================

# 项目根目录：默认假设脚本放在 examples/ 或 examples/inspect/ 附近。
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if not os.path.exists(os.path.join(PROJECT_ROOT, "examples")):
    PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.."))
if PROJECT_ROOT not in sys.path:
    sys.path.append(PROJECT_ROOT)

# 你的任务 config
from examples.galaxea_task.usb_pick_insertion_single.config import env_config


# 安全默认值：第一次建议 True，只打印动作序列，不创建真机 env。
DRY_RUN = False# True

# 是否等待人工按 Enter 再开始每个阶段。
WAIT_ENTER_BEFORE_EACH_PHASE = True

# 是否尝试强制 VR wrapper / 底层进入脚本/AI 模式。
FORCE_SCRIPT_MODE = True

# 是否创建 classifier wrapper。夹爪测试不需要 classifier。
USE_CLASSIFIER = False

# 每步之后等待多久再重新读取 gripper feedback。
# 夹爪执行通常比 EE pose 慢，建议 0.20~0.50。
STEP_SLEEP_SEC = 0.30

# 阶段之间额外等待。
PHASE_SLEEP_SEC = 1.0

# 单臂动作维度。你的当前任务是 7 维：6D EE delta + gripper event。
ACTION_DIM = 7

# 夹爪事件语义：
#   -1 -> close
#    0 -> hold
#   +1 -> open
CLOSE_ACTION = -1.0
HOLD_ACTION = 0.0
OPEN_ACTION = 1.0

# 每个阶段连续发送多少步。
# 如果你怀疑一帧 close 太短，先把 CLOSE_STEPS 设大一点。
CLOSE_STEPS = 20
HOLD_AFTER_CLOSE_STEPS = 15
OPEN_STEPS = 20
HOLD_AFTER_OPEN_STEPS = 15

# 真实 gripper feedback 判定阈值；和你 demo/gripper 逻辑保持一致。
HW_CLOSE_MAX = 30.0
HW_OPEN_MIN = 70.0

# CSV 保存
SAVE_CSV = True
CSV_PATH = "./gripper_replay_test.csv"

# 打印完整 obs state keys，帮助确认 gripper key 名称。
PRINT_STATE_KEYS_ON_RESET = True


# =============================================================================
# 1. 通用工具函数
# =============================================================================

def make_env():
    env = env_config.get_environment(
        fake_env=False,
        save_video=False,
        classifier=USE_CLASSIFIER,
    )
    return env


def to_1d_array(x) -> Optional[np.ndarray]:
    try:
        arr = np.asarray(x, dtype=np.float32).reshape(-1)
        if arr.size == 0:
            return None
        return arr
    except Exception:
        return None


def extract_gripper_feedback(obs: Dict[str, Any], arm_side: str = "right") -> Optional[float]:
    """
    从 observation 中提取真实 gripper feedback。

    兼容：
      1) obs["state"] 是 dict：right_gripper / left_gripper / gripper / 含 gripper 的 key
      2) obs["state"] 是 array：默认最后一维为 gripper
    """
    if obs is None or not isinstance(obs, dict):
        return None
    if "state" not in obs:
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

        preferred_keys.extend([
            "gripper",
            "gripper_pos",
            "gripper_position",
        ])

        for key in preferred_keys:
            if key in state:
                arr = to_1d_array(state[key])
                if arr is not None:
                    return float(arr[-1])

        # 兜底：找所有 key 名里带 gripper 的字段
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


def make_action(gripper_value: float) -> np.ndarray:
    action = np.zeros((ACTION_DIM,), dtype=np.float32)
    action[6] = np.float32(gripper_value)
    return action


def print_state_keys(obs: Dict[str, Any]) -> None:
    if obs is None or not isinstance(obs, dict) or "state" not in obs:
        print("⚠️ obs 中没有 state，无法打印 state keys。")
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
        print(f"state ndarray shape/value head: shape={None if arr is None else arr.shape}, value={None if arr is None else arr[:12].tolist()}")
        if arr is not None:
            print(f"  fallback gripper feedback = last dim = {float(arr[-1]):.3f}")


def refresh_obs_after_sleep(env, fallback_obs, sleep_sec: float) -> Tuple[Dict[str, Any], bool, str]:
    """
    sleep 后尽量重新读取最新真实 obs。
    如果 env.unwrapped._get_sync_obs 可用，就用它；否则使用 env.step 返回的 fallback_obs。
    """
    time.sleep(max(0.0, float(sleep_sec)))

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
    """
    尽量让 VRInterventionWrapper 不覆盖我们传入的 gripper action。
    最好你物理手柄也切到脚本/AI控制模式。
    """
    if not FORCE_SCRIPT_MODE:
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


def get_env_gripper_memory(env) -> Optional[Dict[str, float]]:
    """
    读取 GalaxeaArmEnv 内部 _last_hw_gripper_cmd，帮助判断 hold 是否保持到了正确硬件命令。
    """
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


def maybe_wait(msg: str) -> None:
    if WAIT_ENTER_BEFORE_EACH_PHASE:
        input(msg)


# =============================================================================
# 2. 测试执行逻辑
# =============================================================================

def run_phase(
    env,
    obs: Dict[str, Any],
    *,
    phase_name: str,
    gripper_action: float,
    num_steps: int,
    start_global_step: int,
    rows: List[Dict[str, Any]],
) -> Tuple[Dict[str, Any], int]:
    """
    连续发送同一个 gripper action。
    action[:6] 全 0，只测试夹爪。
    """
    print("=" * 100)
    print(f"阶段: {phase_name} | action[6]={describe_gripper_action(gripper_action)} | steps={num_steps}")
    print("=" * 100)

    action = make_action(gripper_action)

    for local_i in range(num_steps):
        global_step = start_global_step + local_i

        prev_feedback = extract_gripper_feedback(obs)
        prev_state = classify_gripper_feedback(prev_feedback)
        prev_memory = get_env_gripper_memory(env)

        if DRY_RUN:
            print(
                f"[DRY_RUN] step={global_step:04d}, phase={phase_name}, "
                f"would send action={action.tolist()}"
            )
            next_obs = obs
            reward = None
            done = False
            truncated = False
            refresh_success = False
            refresh_source = "dry_run"
        else:
            step_obs, reward, done, truncated, info = env.step(action)
            next_obs, refresh_success, refresh_source = refresh_obs_after_sleep(
                env,
                step_obs,
                STEP_SLEEP_SEC,
            )

        next_feedback = extract_gripper_feedback(next_obs)
        next_state = classify_gripper_feedback(next_feedback)
        next_memory = get_env_gripper_memory(env) if not DRY_RUN else None

        delta_feedback = None
        if prev_feedback is not None and next_feedback is not None:
            delta_feedback = next_feedback - prev_feedback

        print("-" * 100)
        print(f"step {global_step:04d} | phase={phase_name} | action[6]={describe_gripper_action(gripper_action)}")
        print(f"prev gripper feedback : {prev_feedback} ({prev_state})")
        print(f"next gripper feedback : {next_feedback} ({next_state})")
        print(f"delta feedback        : {delta_feedback}")
        print(f"refresh_obs_after_sleep: success={refresh_success}, source={refresh_source}")
        if prev_memory is not None or next_memory is not None:
            print(f"env _last_hw_gripper_cmd: before={prev_memory}, after={next_memory}")
        if not DRY_RUN:
            print(f"reward={reward}, done={done}, truncated={truncated}")

        rows.append({
            "global_step": global_step,
            "phase": phase_name,
            "action_0": float(action[0]),
            "action_1": float(action[1]),
            "action_2": float(action[2]),
            "action_3": float(action[3]),
            "action_4": float(action[4]),
            "action_5": float(action[5]),
            "action_6": float(action[6]),
            "action_6_desc": describe_gripper_action(gripper_action),
            "prev_gripper_feedback": "" if prev_feedback is None else float(prev_feedback),
            "next_gripper_feedback": "" if next_feedback is None else float(next_feedback),
            "delta_gripper_feedback": "" if delta_feedback is None else float(delta_feedback),
            "prev_gripper_state": prev_state,
            "next_gripper_state": next_state,
            "refresh_success": bool(refresh_success),
            "refresh_source": refresh_source,
            "prev_hw_gripper_cmd_right": "" if not prev_memory or "right" not in prev_memory else prev_memory["right"],
            "next_hw_gripper_cmd_right": "" if not next_memory or "right" not in next_memory else next_memory["right"],
            "prev_hw_gripper_cmd_left": "" if not prev_memory or "left" not in prev_memory else prev_memory["left"],
            "next_hw_gripper_cmd_left": "" if not next_memory or "left" not in next_memory else next_memory["left"],
            "reward": "" if reward is None else float(reward),
            "done": bool(done),
            "truncated": bool(truncated),
        })

        obs = next_obs

        if not DRY_RUN and (done or truncated):
            print(f"⚠️ env 在 phase={phase_name}, step={global_step} 返回 done/truncated，停止后续测试。")
            return obs, global_step + 1

    return obs, start_global_step + num_steps


def summarize_rows(rows: List[Dict[str, Any]]) -> None:
    print("=" * 100)
    print("夹爪测试总结")
    print("=" * 100)

    if not rows:
        print("没有 rows。")
        return

    feedback_values = []
    for r in rows:
        v = r.get("next_gripper_feedback", "")
        if v != "":
            feedback_values.append(float(v))

    print(f"total rows: {len(rows)}")
    if feedback_values:
        arr = np.asarray(feedback_values, dtype=np.float32)
        print(f"feedback min/mean/max: {float(np.min(arr)):.3f} / {float(np.mean(arr)):.3f} / {float(np.max(arr)):.3f}")
        print(f"closed count <= {HW_CLOSE_MAX}: {int(np.sum(arr <= HW_CLOSE_MAX))}")
        print(f"open count   >= {HW_OPEN_MIN}: {int(np.sum(arr >= HW_OPEN_MIN))}")
        print(f"middle count           : {int(np.sum((arr > HW_CLOSE_MAX) & (arr < HW_OPEN_MIN)))}")
    else:
        print("没有读取到任何 gripper feedback。")

    # 每个 phase 的最后一个 feedback
    phases = []
    for r in rows:
        if r["phase"] not in phases:
            phases.append(r["phase"])

    print("\n每个阶段最后一帧：")
    for ph in phases:
        ph_rows = [r for r in rows if r["phase"] == ph]
        last = ph_rows[-1]
        print(
            f"  {ph}: action={last['action_6_desc']}, "
            f"next_feedback={last['next_gripper_feedback']}, "
            f"state={last['next_gripper_state']}, "
            f"hw_cmd_right={last['next_hw_gripper_cmd_right']}"
        )

    print("\n判断建议：")
    print(f"  - close 阶段结束后 feedback 应该 <= {HW_CLOSE_MAX}，否则真实夹爪没有进入闭合区间。")
    print(f"  - open 阶段结束后 feedback 应该 >= {HW_OPEN_MIN}，否则真实夹爪没有进入张开区间。")
    print("  - 如果 _last_hw_gripper_cmd_right 变成 10 但 feedback 不变，说明 env 发出了闭合命令，但硬件/ROS/底层未执行或反馈未更新。")
    print("  - 如果 _last_hw_gripper_cmd_right 都没有变成 10，说明 action[6] 没有走到 env 的夹爪映射链路，或被 wrapper/VR 覆盖。")


def save_csv(rows: List[Dict[str, Any]]) -> None:
    if not SAVE_CSV or not rows:
        return
    fieldnames = list(rows[0].keys())
    with open(CSV_PATH, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)
    print(f"✅ CSV saved: {os.path.abspath(CSV_PATH)}")


def main():
    print("=" * 100)
    print("Gripper Replay-Path Test")
    print("=" * 100)
    print(f"DRY_RUN                     : {DRY_RUN}")
    print(f"FORCE_SCRIPT_MODE           : {FORCE_SCRIPT_MODE}")
    print(f"USE_CLASSIFIER              : {USE_CLASSIFIER}")
    print(f"STEP_SLEEP_SEC              : {STEP_SLEEP_SEC}")
    print(f"CLOSE_STEPS                 : {CLOSE_STEPS}")
    print(f"HOLD_AFTER_CLOSE_STEPS      : {HOLD_AFTER_CLOSE_STEPS}")
    print(f"OPEN_STEPS                  : {OPEN_STEPS}")
    print(f"HOLD_AFTER_OPEN_STEPS       : {HOLD_AFTER_OPEN_STEPS}")
    print(f"HW_CLOSE_MAX / HW_OPEN_MIN  : {HW_CLOSE_MAX} / {HW_OPEN_MIN}")

    env = None
    obs = None

    if DRY_RUN:
        print("\nDRY_RUN=True：不会创建真机环境，只打印将要发送的动作序列。")
        obs = {}
    else:
        print("\n🌍 正在创建真实环境...")
        env = make_env()

        print("🔄 正在 reset 环境...")
        obs, info = env.reset()

        force_script_mode_if_possible(env)

        if PRINT_STATE_KEYS_ON_RESET:
            print("=" * 100)
            print("reset 后 observation state 检查")
            print("=" * 100)
            print_state_keys(obs)

        initial_feedback = extract_gripper_feedback(obs)
        print("=" * 100)
        print("初始 gripper feedback")
        print("=" * 100)
        print(f"initial gripper feedback: {initial_feedback} ({classify_gripper_feedback(initial_feedback)})")
        print(f"initial _last_hw_gripper_cmd: {get_env_gripper_memory(env)}")

        input("确认机器人安全、夹爪附近无遮挡、VR 没有接管后，按 Enter 开始夹爪测试...")

    rows: List[Dict[str, Any]] = []
    global_step = 0

    maybe_wait("准备发送 CLOSE(-1) 连续命令，按 Enter 继续...")
    obs, global_step = run_phase(
        env,
        obs,
        phase_name="close_repeat",
        gripper_action=CLOSE_ACTION,
        num_steps=CLOSE_STEPS,
        start_global_step=global_step,
        rows=rows,
    )

    if not DRY_RUN:
        time.sleep(PHASE_SLEEP_SEC)

    maybe_wait("准备发送 HOLD(0) after close，按 Enter 继续...")
    obs, global_step = run_phase(
        env,
        obs,
        phase_name="hold_after_close",
        gripper_action=HOLD_ACTION,
        num_steps=HOLD_AFTER_CLOSE_STEPS,
        start_global_step=global_step,
        rows=rows,
    )

    if not DRY_RUN:
        time.sleep(PHASE_SLEEP_SEC)

    maybe_wait("准备发送 OPEN(+1) 连续命令，按 Enter 继续...")
    obs, global_step = run_phase(
        env,
        obs,
        phase_name="open_repeat",
        gripper_action=OPEN_ACTION,
        num_steps=OPEN_STEPS,
        start_global_step=global_step,
        rows=rows,
    )

    if not DRY_RUN:
        time.sleep(PHASE_SLEEP_SEC)

    maybe_wait("准备发送 HOLD(0) after open，按 Enter 继续...")
    obs, global_step = run_phase(
        env,
        obs,
        phase_name="hold_after_open",
        gripper_action=HOLD_ACTION,
        num_steps=HOLD_AFTER_OPEN_STEPS,
        start_global_step=global_step,
        rows=rows,
    )

    summarize_rows(rows)
    save_csv(rows)
    print("完成。")


if __name__ == "__main__":
    main()
