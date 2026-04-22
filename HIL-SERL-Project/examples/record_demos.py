#录制专家轨迹，用于后续先bc再强化学习（人类在环监督或者无监督两种方式）

#该脚本的本质：（1）记录intervene_action（把供bc模仿学习的完美演示数据和共强化学习的人类介入数据都定义为intervene_action，这两个数据都保存仅专家池）
#           （2）所以即使这是录制脚本，也是依靠intervene_action信号记录数据的

#该脚本构成（高度模块化）
#（1）数据输入接口：无该内容，输入接口都在dual_galaxea_env.py里封装好了，只要dual_galaxea_env.py能正常收到需要的数据，则完成；
#（2）怎么录制：无该内容，录制控制都在wrappers.py里封装好了，此处录制的完整流程演示数据和wrappers.py的vr接管数据都被存入专家经验池（Demo Buffer））里
#（3）存放路径：存进 demo_data 文件夹
#（4）何时停止录制：
#       1,基于wrappers.py定义的mode0无人类介入，
                 #mode2人类介入的逻辑： 一旦切入 mode2，它就在这一帧的数据里挂上一个牌子（info["intervene_action"] = ...）。
                 #mode0时不记录，mode2后才记录
#       2,预设固定步长时间，超时自动停止录制
#       3,所以mode2提前结束任务，等待补偿结束，自动记录完美演示数据 

#总逻辑：
# dual_galaxea_env.py (底层)：负责和星海图的相机、机械臂打交道，把物理世界的声光电变成 NumPy 数组。
# wrappers.py (中层)：智能安检，负责监听你的 VR 手柄，把人类的动作替换进去，并贴上 intervene_action 的 VIP 标签。
# record_demos.py / train_rlpd.py (顶层)：数据分拣员。
#      只管看着 info 字典，看到有 VIP 标签的数据，就直接往专家经验池（Demo Buffer）里扔。
#      如果没有标签，就扔进在线探索池（Replay Buffer）。

# 默认 20 条成功 demo：
# python record_demos.py

# 限制每条最多 300 步：
# python record_demos.py --max_episode_steps=300

# 先少录几条测试：
# python record_demos.py --successes_needed=2 --max_episode_steps=200


#不过滤静止帧再保存demos（ros2 topic echo /motion_control/pose_ee_arm_right可以确认vr暂停后数值不会变化，所以可以视为静止帧 ）
#（可以回放录制的demos，看看动作是不是流畅的）

#录制的action【6】官方代表持续的张开/闭合命令，我们修改自己的情况，让其符合想闭合就显示一直闭合，想张开就一直张开的情况

##和官方一致
#不过滤静止帧，防止最后成功时被判定到静止帧范围从而demos不完整
#三值夹爪标签(可视化demos来判断是否准确实现）

import os
import sys
import time

# ==============================================================
# 像 actor 一样，先强制本地 CPU，避免 classifier=True 时本地环境炸
# ==============================================================
os.environ["JAX_PLATFORMS"] = "cpu"
os.environ["CUDA_VISIBLE_DEVICES"] = ""
os.environ["XLA_PYTHON_CLIENT_PREALLOCATE"] = "false"

from tqdm import tqdm
import numpy as np
import copy
import pickle as pkl
import datetime
from absl import app, flags

# ==============================================================
# 核心路径配置（确保模块可被正确导入）
# ==============================================================
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
if PROJECT_ROOT not in sys.path:
    sys.path.append(PROJECT_ROOT)

from examples.galaxea_task.usb_pick_insertion_single.config import env_config

# ==============================================================
# 命令行参数配置
# ==============================================================
FLAGS = flags.FLAGS
flags.DEFINE_string(
    "exp_name",
    "galaxea_usb_insertion_single",
    "Name of experiment corresponding to folder.",
)
flags.DEFINE_integer(
    "successes_needed",
    20,
    "Number of successful demos to collect.",
)
flags.DEFINE_integer(
    "max_episode_steps",
    650,
    "Maximum number of steps per demo episode before forcing truncation.",
)
flags.DEFINE_boolean(
    "classifier",
    True,
    "Whether to use reward classifier as the success/end signal.",
)
flags.DEFINE_boolean(
    "save_video",
    False,
    "Whether to save video during recording.",
)
flags.DEFINE_boolean(
    "manual_confirm_on_success",
    False,
    "Whether to manually confirm success even when classifier says succeed=True.",
)

# ==============================================================
# 夹爪反馈阈值
# ==============================================================
CLOSE_MAX = 30.0
OPEN_MIN = 70.0


def ask_success_from_terminal():
    while True:
        try:
            manual_rew = int(input("Success? (1/0): ").strip())
            if manual_rew in [0, 1]:
                return bool(manual_rew)
            print("❌ 请输入 1 或 0。")
        except ValueError:
            print("❌ 输入无效，请输入 1 或 0。")


def extract_gripper_feedback(obs):
    """
    从 obs["state"] 中提取夹爪反馈量程。
    兼容：
    1) state 是 dict，含 right_gripper / gripper
    2) state 是 ndarray，单臂常见最后一维为 gripper
    """
    if obs is None or "state" not in obs:
        return None

    state = obs["state"]

    if isinstance(state, dict):
        for key in [
            "right_gripper",
            "left_gripper",
            "gripper",
            "state/right_gripper",
            "state/left_gripper",
        ]:
            if key in state:
                arr = np.asarray(state[key]).reshape(-1)
                if arr.size > 0:
                    return float(arr[-1])

        for key, val in state.items():
            if "gripper" in str(key).lower():
                arr = np.asarray(val).reshape(-1)
                if arr.size > 0:
                    return float(arr[-1])

        return None

    arr = np.asarray(state)
    while arr.ndim > 1:
        arr = arr[-1]
    arr = arr.reshape(-1)
    if arr.size == 0:
        return None

    return float(arr[-1])


def infer_stable_gripper_state_from_feedback(
    gripper_feedback,
    prev_state,
    close_max=CLOSE_MAX,
    open_min=OPEN_MIN,
):
    """
    将反馈量程映射为稳定夹爪状态：
      -1 -> 当前稳定为闭合
      +1 -> 当前稳定为张开
      中间区 -> 保持上一稳定状态
    """
    if gripper_feedback is None:
        return prev_state

    x = float(gripper_feedback)

    if x <= close_max:
        return -1
    if x >= open_min:
        return +1

    return prev_state


def rewrite_gripper_action_to_official_style(
    action,
    obs,
    next_obs,
    prev_stable_state,
):
    """
    把夹爪最后一维改写成更接近官网的结构：
      -1 = close event
       0 = hold / no-op
      +1 = open event

    这里不是保存“当前夹爪状态”，而是保存“这一帧是否发生了开/关事件”。

    推断方式：
    1) 从 obs 与 next_obs 读取夹爪反馈量程
    2) 先推断前后两帧的稳定夹爪状态
    3) 若发生 OPEN->CLOSED，则记 -1
       若发生 CLOSED->OPEN，则记 +1
       否则记 0
    """
    action = np.asarray(action, dtype=np.float32).copy()

    if action.shape[0] != 7:
        return action, prev_stable_state

    prev_feedback = extract_gripper_feedback(obs)
    next_feedback = extract_gripper_feedback(next_obs)

    prev_state = infer_stable_gripper_state_from_feedback(
        prev_feedback,
        prev_stable_state,
    )
    next_state = infer_stable_gripper_state_from_feedback(
        next_feedback,
        prev_state,
    )

    gripper_event = 0.0
    if prev_state is not None and next_state is not None:
        if prev_state == +1 and next_state == -1:
            gripper_event = -1.0  # close
        elif prev_state == -1 and next_state == +1:
            gripper_event = +1.0  # open
        else:
            gripper_event = 0.0   # hold
    else:
        gripper_event = 0.0

    action[6] = np.float32(gripper_event)
    return action, next_state


def build_safe_idle_action(action_shape):
    """
    默认发给机器人的“安全空动作”：
    - 前 6 维全 0，不继续推动末端
    - 最后一维给安全夹爪保持值
    """
    safe_idle_action = np.zeros(action_shape, dtype=np.float32)
    if safe_idle_action.shape[0] == 7:
        # 正常 step 阶段默认持续给夹爪发送保持值
        safe_idle_action[6] = 80.0
    return safe_idle_action


def main(_):
    print(f"🚀 开始录制专家数据：{FLAGS.exp_name}")
    print(f"🧠 reward classifier: {'开启' if FLAGS.classifier else '关闭'}")
    print("📌 当前脚本策略：")
    print("   - classifier=True 时：成功由 reward ckpt 在成功瞬间触发。")
    print("   - max_episode_steps 只做失败/超时兜底。")
    print("   - 全程轨迹完整保留，不删除静止帧。")
    print("   - 夹爪最后一维改成官网风格三值动作：")
    print("       -1 -> close event")
    print("        0 -> hold / no-op")
    print("       +1 -> open event")
    print("   - 三值不是按钮原样存，而是由前后帧夹爪反馈量程变化推断。\n")

    env = env_config.get_environment(
        fake_env=False,
        save_video=FLAGS.save_video,
        classifier=FLAGS.classifier,
    )

    obs, info = env.reset()
    safe_idle_action = build_safe_idle_action(env.action_space.shape)

    print("✅ 环境重置完成，请戴上 VR 头显准备接管！")

    transitions = []
    success_count = 0
    success_needed = FLAGS.successes_needed
    max_episode_steps = FLAGS.max_episode_steps

    pbar = tqdm(total=success_needed, desc="成功收集的 Demo 数量")

    trajectory = []
    returns = 0.0
    episode_step = 0

    # 当前 episode 的稳定夹爪状态：
    #   -1 closed, +1 open, None unknown
    stable_gripper_state = None

    while success_count < success_needed:
        base_env = env.unwrapped

        # 非 reset 阶段，如果还在 Mode 2，就什么都不发，只等待切回 Mode 0
        if getattr(base_env, "script_control_enabled", False):
            time.sleep(0.05)
            continue

        # 默认执行固定“安全空动作”
        exec_action = safe_idle_action.copy()

        next_obs, rew, done, truncated, info = env.step(exec_action)
        returns += float(rew)
        episode_step += 1

        # ------------------------------------------------------
        # 记录逻辑：
        # - 有 VR 接管：记录 intervene_action
        # - 无 VR 接管：记录零动作/空闲帧
        # ------------------------------------------------------
        if "intervene_action" in info:
            raw_actions = np.asarray(info["intervene_action"], dtype=np.float32)
        else:
            raw_actions = np.zeros(env.action_space.shape, dtype=np.float32)

        # 改写夹爪最后一维为官网式三值动作
        actions, stable_gripper_state = rewrite_gripper_action_to_official_style(
            raw_actions,
            obs,
            next_obs,
            stable_gripper_state,
        )

        forced_timeout = False
        if episode_step >= max_episode_steps and not (done or truncated):
            forced_timeout = True
            truncated = True
            print(f"\n⏰ 达到最大录制时长：{max_episode_steps} 步，强制截断当前回合。")

        episode_end = bool(done or truncated)

        transition = copy.deepcopy(
            dict(
                observations=obs,
                actions=actions,
                next_observations=next_obs,
                rewards=float(rew),
                masks=1.0 - float(episode_end),
                dones=episode_end,
                infos=copy.deepcopy(info),
            )
        )

        trajectory.append(transition)

        pbar.set_description(
            f"成功 Demo 数: {success_count}/{success_needed} | "
            f"Return: {returns:.2f} | "
            f"Step: {episode_step}/{max_episode_steps}"
        )

        obs = next_obs

        if episode_end:
            print("\n🔄 回合结束。")
            print(f"   reward={rew}, done={done}, truncated={truncated}, forced_timeout={forced_timeout}")
            print(f"   info.succeed={info.get('succeed', None)}")

            if FLAGS.classifier:
                succeed = bool(info.get("succeed", False))
                if succeed and FLAGS.manual_confirm_on_success:
                    print("📝 classifier 判定成功，请人工确认本回合是否真的成功。")
                    succeed = ask_success_from_terminal()

                if len(trajectory) > 0:
                    trajectory[-1]["infos"] = copy.deepcopy(info)
                    trajectory[-1]["infos"]["succeed"] = succeed
                    trajectory[-1]["dones"] = True
                    trajectory[-1]["masks"] = 0.0
            else:
                print("📝 当前 classifier=False，使用人工判定 success / fail。")
                succeed = ask_success_from_terminal()

                if len(trajectory) > 0:
                    trajectory[-1]["infos"] = copy.deepcopy(info)
                    trajectory[-1]["infos"]["succeed"] = succeed
                    trajectory[-1]["rewards"] = float(succeed)
                    trajectory[-1]["dones"] = True
                    trajectory[-1]["masks"] = 0.0

            if succeed and len(trajectory) > 0:
                for trans in trajectory:
                    transitions.append(copy.deepcopy(trans))
                success_count += 1
                pbar.update(1)

                # 打印一下这一条里 gripper 三值统计，方便你核对结构
                traj_actions = np.asarray([t["actions"] for t in trajectory], dtype=np.float32)
                if traj_actions.ndim == 2 and traj_actions.shape[1] == 7:
                    g = traj_actions[:, 6]
                    n_close = int(np.sum(g < -0.5))
                    n_open = int(np.sum(g > 0.5))
                    n_hold = int(np.sum(np.abs(g) <= 0.5))
                    print(f"🎉 成功录制 1 条 Demo！当前累计成功条数: {success_count}")
                    print(f"📦 本条完整轨迹长度: {len(trajectory)}")
                    print(f"🤏 gripper统计: close={n_close}, hold={n_hold}, open={n_open}")
                else:
                    print(f"🎉 成功录制 1 条 Demo！当前累计成功条数: {success_count}")
                    print(f"📦 本条完整轨迹长度: {len(trajectory)}")
            else:
                print("❌ 当前回合失败，已丢弃该轨迹。")

            trajectory = []
            returns = 0.0
            episode_step = 0
            stable_gripper_state = None

            if success_count >= success_needed:
                break

            print("🔄 正在复位机器人...")
            obs, info = env.reset()
            safe_idle_action = build_safe_idle_action(env.action_space.shape)
            print("✅ 复位完成，可进行下一次演示。\n" + "-" * 40)

    save_dir = os.path.join(os.path.dirname(__file__), "demo_data_single")
    os.makedirs(save_dir, exist_ok=True)

    uuid = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    file_name = os.path.join(
        save_dir,
        f"{FLAGS.exp_name}_{success_needed}_demos_official_style_{uuid}.pkl",
    )

    with open(file_name, "wb") as f:
        pkl.dump(transitions, f)

    print(f"\n💾 恭喜！成功保存 {success_needed} 条 Demo 数据至 {file_name}")
    print(f"📊 总 transition 数量: {len(transitions)}")


if __name__ == "__main__":
    app.run(main)