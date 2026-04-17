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

# 如果你已经把统一版底层 env 覆盖到 dual_galaxea_env.py，
# 这里既可以 import GalaxeaArmEnv，也可以继续 import GalaxeaDualArmEnv（因为我之前做了别名兼容）
from serl_robot_infra.Galaxea_env.envs.galaxea_arm_env import GalaxeaArmEnv


class GalaxeaUSBEnv(GalaxeaArmEnv):
    """
    星海图 USB 插拔单臂任务环境（当前按右臂单臂配置）。

    依赖前提：
    1. 底层 env 已经改成统一版，支持：
       - ARM_MODE = "single" / "dual"
       - ARM_SIDE = "left" / "right"
    2. config 中已经提供：
       - ARM_MODE = "single"
       - ARM_SIDE = "right"
       - RESET_POSE
    """

    def __init__(self, config=None, use_vr=True, **kwargs):
        if config is None:
            raise ValueError("GalaxeaUSBEnv 初始化失败：必须传入有效的 config")

        self.config = config
        self.use_vr = use_vr

        # 单臂 reset 位姿
        self.reset_pose = np.array(config.RESET_POSE, dtype=np.float32)

        # 只有 use_vr=True 时才会用到这些状态
        self.script_control_enabled = False
        self.script_control_switch_time = None

        super().__init__(config=config, **kwargs)

    def notify_script_control(self, enabled: bool):
        """
        由 VRInterventionWrapper 回调：
        mode=2 -> enabled=True
        mode=0 -> enabled=False
        """
        self.script_control_enabled = enabled
        self.script_control_switch_time = time.time() if enabled else None

    def _wait_until_script_control_ready(self, timeout: float = 15.0):
        start = time.time()
        while not self.script_control_enabled:
            if time.time() - start > timeout:
                raise TimeoutError(
                    "等待 Mode 2 超时：一直没有进入脚本控制模式(use_vr_mode=False)"
                )
            time.sleep(0.05)

    def _wait_extra_after_false(self, delay: float = 2.0):
        if self.script_control_switch_time is None:
            time.sleep(delay)
            return

        elapsed = time.time() - self.script_control_switch_time
        remain = delay - elapsed
        if remain > 0:
            print(f"⏳ 已进入脚本控制，额外等待 {remain:.2f}s 后开始复位...")
            time.sleep(remain)

    def _build_reset_target(self):
        reset_pose = self.reset_pose.copy()

        if getattr(self.config, "RANDOM_RESET", False):
            xy_range = float(self.config.RANDOM_XY_RANGE)
            reset_pose[:2] += np.random.uniform(-xy_range, xy_range, (2,))

        return reset_pose

    def go_to_reset(self):
        """
        两种模式：
        1) use_vr=True：保留 VR 模式切换复位逻辑
        2) use_vr=False：直接发送 ROS 复位轨迹，不等 VR
        """
        print("🤖 [USB Task Single Arm] 正在准备复位...")

        reset_pose = self._build_reset_target()

        if self.use_vr:
            print("💡 【请按 VR 手柄的 Mode 2 键】切到脚本控制模式（会发送 use_vr_mode=False）")
            self._wait_until_script_control_ready(timeout=15.0)
            self._wait_extra_after_false(delay=2.0)
            print("🤖 [USB Task Single Arm] 开始向底层发送复位坐标...")
        else:
            print("🤖 [USB Task Single Arm] 当前为无 VR 模式，直接发送复位轨迹...")

        # 统一 env 在 single 模式下提供 interpolate_move_single
        self.interpolate_move_single(reset_pose, timeout=3.0, gripper=1.0)
        time.sleep(0.5)

        print("✅ 单臂复位坐标发送完毕！")

        if self.use_vr:
            print("💡 【请按 VR 手柄的 Mode 0 键】重新夺回机械臂控制权，开始你的表演！")


class SingleGripperPenaltyWrapper(gym.Wrapper):
    """
    单臂夹爪惩罚 wrapper。

    单臂动作定义：
        action[0:6] = arm delta
        action[6]   = gripper command
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
        self.gripper_closed = None

    def reset(self, **kwargs):
        obs, info = self.env.reset(**kwargs)
        self.gripper_closed = None
        return obs, info

    def _update_one_side(self, cmd, prev_closed):
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

        # 单臂动作维度应为 7
        assert real_action.shape[0] == 7, f"动作维度异常，期望 7，实际是 {real_action.shape}"

        penalty_val, self.gripper_closed = self._update_one_side(real_action[6], self.gripper_closed)

        reward += penalty_val
        info["grasp_penalty"] = penalty_val

        return obs, reward, terminated, truncated, info