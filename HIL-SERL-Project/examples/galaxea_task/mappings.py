#它只是把实验名映射到 usb_pick_insertion等任务/config.py 里的训练配置类。
from .usb_pick_insertion.config import GalaxeaUSBTrainConfig

CONFIG_MAPPING = {
    "galaxea_usb_insertion": GalaxeaUSBTrainConfig,
}

