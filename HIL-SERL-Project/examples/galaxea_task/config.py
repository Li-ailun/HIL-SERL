#统一接口规范
# 它的作用不是“直接控制某个具体任务”，而是规定：

# 所有任务配置类都应该有哪些通用超参数
# 所有任务配置类都必须实现哪些方法

# 比如官方这里规定了每个任务配置都要实现：

# get_environment(...)
# process_demos(...)

# 也就是说，它定义的是“任务配置长什么样”，不是“某个具体任务怎么做”。
# 你可以把它理解成一个模板或接口。

# galaxea_task/config.py

# 只保留成：

# DefaultTrainingConfig
# 抽象字段
# 抽象方法 get_environment()
# 抽象方法 process_demos()

"""
Galaxea Dual Arm Total Configuration for HIL-SERL
Author: Eren (Li-ailun)
Description: 替代官方 DefaultTrainingConfig，作为星海图项目的唯一全局基准配置。
"""

from abc import ABC, abstractmethod
from typing import List, Optional


class DefaultTrainingConfig(ABC):
    """Galaxea 任务配置抽象基类。"""

    # ==========================================
    # 1. 算法核心参数 (RL Hyperparameters)
    # ==========================================
    agent: str = "sac"
    max_traj_length: int = 100
    batch_size: int = 256
    cta_ratio: int = 2
    discount: float = 0.97

    # ==========================================
    # 2. 训练步数与日志规划 (Training & Logging Schedule)
    # ==========================================
    max_steps: int = 1_000_000
    replay_buffer_capacity: int = 200_000
    random_steps: int = 0
    training_starts: int = 100
    steps_per_update: int = 50

    log_period: int = 10
    eval_period: int = 2000
    checkpoint_period: int = 0
    buffer_period: int = 0

    eval_checkpoint_step: int = 0
    eval_n_trajs: int = 5
    demo_path: Optional[str] = None

    # ==========================================
    # 3. 视觉与状态配置 (Vision & Setup)
    # ==========================================
    image_keys: List[str] = []
    classifier_keys: List[str] = []
    proprio_keys: List[str] = []

    # "resnet" / "resnet-pretrained"
    encoder_type: str = "resnet-pretrained"

    # "single-arm-learned-gripper", "dual-arm-learned-gripper",
    # "single-arm-fixed-gripper", "dual-arm-fixed-gripper"
    setup_mode: str = "dual-arm-learned-gripper"

    # ==========================================
    # 4. 必须由具体任务实现的方法
    # ==========================================
    @abstractmethod
    def get_environment(self, fake_env: bool = False, save_video: bool = False, classifier: bool = False):
        """返回该任务对应的环境实例。"""
        raise NotImplementedError

    @abstractmethod
    def process_demos(self, demos):
        """对 demo 数据做任务级清洗/筛选。"""
        raise NotImplementedError