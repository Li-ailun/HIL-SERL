# 官方 wrapper.py 是“任务实体层”

# 你贴的官方 USBEnv(FrankaEnv) 里，放的都是和 USB 插拔这个任务本身强相关的东西，比如：

# init_cameras()：这个任务用哪些相机、怎么初始化
# reset()：这个任务开始前机械臂怎么走、夹爪怎么开合、怎么靠近目标
# interpolate_move()：这个任务用什么形式发运动命令
# go_to_reset()：这个任务的复位步骤
# GripperPenaltyWrapper：这个任务特有的惩罚逻辑

# 也就是说，官方 wrapper.py 的职责是：

# “这个任务在物理世界里到底怎么做”

# 不是训练参数，不是任务路由，而是任务动作和任务复位本身。

# 这个文件应该只保留“任务实体逻辑”：

# GalaxeaUSBEnv
# go_to_reset()
# 任务相关 reset() 特殊流程
# DualGripperPenaltyWrapper

# 不要让它再承担“总装环境”的职责。
# 也就是说，make_env() 这类函数最好最终不要在这里继续扩张。


import time
import numpy as np
import gymnasium as gym

from serl_robot_infra.Galaxea_env.envs.dual_galaxea_env import GalaxeaDualArmEnv


class GalaxeaUSBEnv(GalaxeaDualArmEnv):
    """星海图双臂 U 盘插拔专属环境。"""

    def __init__(self, config=None, **kwargs):
        self.config = config

        self.reset_l = np.array(config.RESET_L, dtype=np.float32)
        self.reset_r = np.array(config.RESET_R, dtype=np.float32)

        # 由 VRInterventionWrapper 在 mode=2 / mode=0 时更新
        self.script_control_enabled = False
        self.script_control_switch_time = None

        super().__init__(config=config, **kwargs)

    def notify_script_control(self, enabled: bool):
        """
        由 VRInterventionWrapper 回调：
        mode=2 -> enabled=True  （脚本/IK 接管）
        mode=0 -> enabled=False （VR 接管）
        """
        self.script_control_enabled = enabled
        self.script_control_switch_time = time.time() if enabled else None

    def _wait_until_script_control_ready(self, timeout: float = 15.0):
        """
        等待用户把手柄切到 Mode 2，直到 wrapper 已经发出 use_vr_mode=False。
        """
        start = time.time()
        while not self.script_control_enabled:
            if time.time() - start > timeout:
                raise TimeoutError(
                    "等待 Mode 2 超时：一直没有进入脚本控制模式(use_vr_mode=False)"
                )
            time.sleep(0.05)

    def _wait_extra_after_false(self, delay: float = 2.0):
        """
        当输出 false 后，再等 delay 秒，然后开始发复位轨迹。
        """
        if self.script_control_switch_time is None:
            time.sleep(delay)
            return

        elapsed = time.time() - self.script_control_switch_time
        remain = delay - elapsed
        if remain > 0:
            print(f"⏳ 已进入脚本控制，额外等待 {remain:.2f}s 后开始复位...")
            time.sleep(remain)

    def _build_reset_targets(self):
        """生成本次复位目标点，并按需加入随机扰动。"""
        reset_l = self.reset_l.copy()
        reset_r = self.reset_r.copy()

        if not hasattr(self.config, "RANDOM_RESET"):
            raise AttributeError("GalaxeaUSBEnv 初始化失败：缺少必需配置项 config.RANDOM_RESET")
        if not hasattr(self.config, "RANDOM_XY_RANGE"):
            raise AttributeError("GalaxeaUSBEnv 初始化失败：缺少必需配置项 config.RANDOM_XY_RANGE")

        if self.config.RANDOM_RESET:
            xy_range = float(self.config.RANDOM_XY_RANGE)
            reset_l[:2] += np.random.uniform(-xy_range, xy_range, (2,))
            reset_r[:2] += np.random.uniform(-xy_range, xy_range, (2,))

        return reset_l, reset_r

    def go_to_reset(self):
        """
        USB 任务复位逻辑：
        1. 提示用户切到 Mode 2
        2. 等待 wrapper 检测到 mode=2，并发出 use_vr_mode=False
        3. false 发出后，额外等待 2 秒
        4. 再开始发送复位轨迹
        """
        print("🤖 [USB Task] 正在准备复位...")
        print("💡 【请按 VR 手柄的 Mode 2 键】切到脚本控制模式（会发送 use_vr_mode=False）")

        self._wait_until_script_control_ready(timeout=15.0)
        self._wait_extra_after_false(delay=2.0)

        print("🤖 [USB Task] 开始向底层发送复位坐标...")

        reset_l, reset_r = self._build_reset_targets()
        self.interpolate_move(reset_l, reset_r, timeout=3.0)
        time.sleep(0.5)

        print("✅ 复位坐标发送完毕！")
        print("💡 【请按 VR 手柄的 Mode 0 键】重新夺回机械臂控制权，开始你的表演！")


class DualGripperPenaltyWrapper(gym.Wrapper):
    """
    双臂夹爪惩罚器（动作版）
    不依赖底层原始 obs 结构，避免被 SERLObsWrapper / ChunkingWrapper 搞崩。
    """

    def __init__(
        self,
        env,
        penalty: float = -0.02,
        close_thr: float = -0.5,
        open_thr: float = 0.5,
    ):
        super().__init__(env)
        self.penalty = penalty
        self.close_thr = close_thr
        self.open_thr = open_thr
        self.left_closed = None
        self.right_closed = None

    def reset(self, **kwargs):
        obs, info = self.env.reset(**kwargs)
        self.left_closed = None
        self.right_closed = None
        return obs, info

    def _update_one_side(self, cmd, prev_closed):
        """
        根据动作命令推断夹爪状态，并决定是否罚分。
        返回：
            penalty_delta, new_closed
        """
        penalty_delta = 0.0
        new_closed = prev_closed

        if cmd < self.close_thr:
            if prev_closed is False:
                penalty_delta += self.penalty
            new_closed = True
        elif cmd > self.open_thr:
            if prev_closed is True:
                penalty_delta += self.penalty
            new_closed = False

        return penalty_delta, new_closed

    def step(self, action):
        obs, reward, terminated, truncated, info = self.env.step(action)

        real_action = info.get("intervene_action", action)
        real_action = np.asarray(real_action, dtype=np.float32)

        penalty_val = 0.0
        left_delta, self.left_closed = self._update_one_side(real_action[6], self.left_closed)
        right_delta, self.right_closed = self._update_one_side(real_action[13], self.right_closed)

        penalty_val += left_delta + right_delta
        reward += penalty_val
        info["grasp_penalty"] = penalty_val

        return obs, reward, terminated, truncated, info


def make_env(reward_classifier_model=None, use_manual_reward=False):
    """
    兼容旧脚本入口。
    真正的环境装配已经迁移到 config.py 的 env_config.get_environment()。
    这里不再重复包装任何 wrapper，只做转发。
    """
    from examples.galaxea_task.usb_pick_insertion.config import env_config

    return env_config.get_environment(
        fake_env=False,
        save_video=False,
        classifier=False,
    )

# import numpy as np
# import time
# import gymnasium as gym

# from serl_robot_infra.Galaxea_env.envs.dual_galaxea_env import GalaxeaDualArmEnv
# from serl_robot_infra.Galaxea_env.envs.wrappers import VRInterventionWrapper


# class GalaxeaUSBEnv(GalaxeaDualArmEnv):
#     """星海图双臂 U 盘插拔专属环境"""

#     def __init__(self, config=None, **kwargs):
#         self.config = config

#         self.reset_l = getattr(
#             config,
#             "RESET_L",
#             np.array([0.2, -0.25, -0.3, 0.0, 0.0, 0.0, 1.0], dtype=np.float32),
#         )
#         self.reset_r = getattr(
#             config,
#             "RESET_R",
#             np.array([0.2, 0.25, -0.3, 0.0, 0.0, 0.0, 1.0], dtype=np.float32),
#         )

#         # 由 VRInterventionWrapper 在 mode=2 / mode=0 时更新
#         self.script_control_enabled = False
#         self.script_control_switch_time = None

#         super().__init__(config=config, **kwargs)

#     def notify_script_control(self, enabled: bool):
#         """
#         由 VRInterventionWrapper 回调：
#         mode=2 -> enabled=True  （脚本/IK 接管）
#         mode=0 -> enabled=False （VR 接管）
#         """
#         self.script_control_enabled = enabled
#         self.script_control_switch_time = time.time() if enabled else None

#     def _wait_until_script_control_ready(self, timeout=15.0):
#         """
#         等待用户把手柄切到 Mode 2，直到 wrapper 已经发出 use_vr_mode=False。
#         """
#         start = time.time()
#         while not self.script_control_enabled:
#             if time.time() - start > timeout:
#                 raise TimeoutError("等待 Mode 2 超时：一直没有进入脚本控制模式(use_vr_mode=False)")
#             time.sleep(0.05)

#     def _wait_extra_after_false(self, delay=2.0):
#         """
#         当输出 false 后，再等 2 秒，然后开始发复位轨迹。
#         """
#         if self.script_control_switch_time is None:
#             time.sleep(delay)
#             return

#         elapsed = time.time() - self.script_control_switch_time
#         remain = delay - elapsed
#         if remain > 0:
#             print(f"⏳ 已进入脚本控制，额外等待 {remain:.2f}s 后开始复位...")
#             time.sleep(remain)

#     def go_to_reset(self):
#         """
#         复位逻辑：
#         1. 提示用户切到 Mode 2
#         2. 等待 wrapper 检测到 mode=2，并发出 use_vr_mode=False
#         3. false 发出后，额外等待 2 秒
#         4. 再开始发送复位轨迹
#         """
#         print("🤖 [USB Task] 正在准备复位...")
#         print("💡 【请按 VR 手柄的 Mode 2 键】切到脚本控制模式（会发送 use_vr_mode=False）")

#         self._wait_until_script_control_ready(timeout=15.0)
#         self._wait_extra_after_false(delay=2.0)

#         print("🤖 [USB Task] 开始向底层发送复位坐标...")

#         reset_l = self.reset_l.copy()
#         reset_r = self.reset_r.copy()

#         if hasattr(self, "config") and getattr(self.config, "RANDOM_RESET", False):
#             xy_range = getattr(self.config, "RANDOM_XY_RANGE", 0.01)
#             reset_l[:2] += np.random.uniform(-xy_range, xy_range, (2,))
#             reset_r[:2] += np.random.uniform(-xy_range, xy_range, (2,))

#         self.interpolate_move(reset_l, reset_r, timeout=3.0)
#         time.sleep(0.5)

#         print("✅ 复位坐标发送完毕！")
#         print("💡 【请按 VR 手柄的 Mode 0 键】重新夺回机械臂控制权，开始你的表演！")


# class DualGripperPenaltyWrapper(gym.Wrapper):
#     """
#     双臂夹爪惩罚器（动作版）
#     不再依赖 obs['state']['left_gripper'] 这种原始字典结构，
#     避免被 SERLObsWrapper / ChunkingWrapper 搞崩。
#     """

#     def __init__(self, env, penalty=-0.02, close_thr=-0.5, open_thr=0.5):
#         super().__init__(env)
#         self.penalty = penalty
#         self.close_thr = close_thr
#         self.open_thr = open_thr
#         self.left_closed = None
#         self.right_closed = None

#     def reset(self, **kwargs):
#         obs, info = self.env.reset(**kwargs)
#         self.left_closed = None
#         self.right_closed = None
#         return obs, info

#     def _update_one_side(self, cmd, prev_closed):
#         """
#         根据动作命令推断夹爪状态，并决定是否罚分。
#         返回:
#           penalty_delta, new_closed
#         """
#         penalty_delta = 0.0
#         new_closed = prev_closed

#         if cmd < self.close_thr:
#             if prev_closed is False:
#                 penalty_delta += self.penalty
#             new_closed = True

#         elif cmd > self.open_thr:
#             if prev_closed is True:
#                 penalty_delta += self.penalty
#             new_closed = False

#         return penalty_delta, new_closed

#     def step(self, action):
#         obs, reward, terminated, truncated, info = self.env.step(action)

#         real_action = info.get("intervene_action", action)
#         real_action = np.asarray(real_action, dtype=np.float32)

#         penalty_val = 0.0
#         left_delta, self.left_closed = self._update_one_side(real_action[6], self.left_closed)
#         right_delta, self.right_closed = self._update_one_side(real_action[13], self.right_closed)

#         penalty_val += left_delta + right_delta
#         reward += penalty_val

#         info["grasp_penalty"] = penalty_val
#         return obs, reward, terminated, truncated, info


# def make_env(reward_classifier_model=None, use_manual_reward=False):
#     from examples.galaxea_task.usb_pick_insertion.config import env_config

#     env = env_config.get_environment(fake_env=False, classifier=False)
#     env = VRInterventionWrapper(env)
#     env = DualGripperPenaltyWrapper(env, penalty=-0.02)
#     return env


