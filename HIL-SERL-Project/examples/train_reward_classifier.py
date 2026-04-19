#训练奖励分类器
# 训练奖励分类器
#不需要要Ros2Bridge功能，
#只需要两样东西：
#（1）observation_space
#（2） action_space
#这两个东西从pkl 样本里直接推断出来


#cpu版本训练指令：
#JAX_PLATFORMS=cpu python train_reward_classifier.py --exp_name=galaxea_usb_insertion


# 训练奖励分类器
# 不需要 Ros2Bridge / 真机环境
# 只需要从 pkl 样本里推断：
# 1) observation_space
# 2) action_space

#环境：
#去掉导入env后（本脚本只有导入的env需要torch）
# 这个脚本本身原则上就不再需要 torch 了。你现在的离线训练脚本核心依赖是：
# JAX
# Flax
# Optax
# ReplayBuffer
# 你的 classifier 数据

#相对于官方，此次改动较大：
#区别：
# 1,官方脚本需要 env 接口，不等于需要真实环境；
#     我的旧代码真的在导入真实环境，即必须打开机器人+连接相机
# 2,官方加入动作为了：
#     （1）给每条样本补一个形状正确、dtype 正确的 action；
#     （2）让 buffer 接口满意；
#     （3）不是说这个 reward classifier 真要学动作。
#     （4）模型并没有把 actions 喂进分类器去算 loss。actions 
#     （5）主要只是为了让 transition 结构完整，能插入 ReplayBuffer。
#     我把 env.action_space.sample() 改成全零动作，对当前 reward classifier 训练基本没影响（因为新代码也没有真正训练动作）
import os
import sys
import glob
import pickle as pkl
import functools

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
SERL_LAUNCHER_ROOT = os.path.join(PROJECT_ROOT, "serl_launcher")

if PROJECT_ROOT not in sys.path:
    sys.path.insert(0, PROJECT_ROOT)
if SERL_LAUNCHER_ROOT not in sys.path:
    sys.path.insert(0, SERL_LAUNCHER_ROOT)

import jax
import jax.numpy as jnp
import jax.lax as lax
import flax.linen as nn
from flax import jax_utils
from flax.training import checkpoints
import numpy as np
import optax
from tqdm import tqdm
from absl import app, flags
from gymnasium import spaces

from serl_launcher.data.data_store import ReplayBuffer
from serl_launcher.utils.train_utils import concat_batches
from serl_launcher.vision.data_augmentations import batched_random_crop
from serl_launcher.networks.reward_classifier import create_classifier

from examples.galaxea_task.mappings import CONFIG_MAPPING


FLAGS = flags.FLAGS
flags.DEFINE_string("exp_name", None, "Name of experiment corresponding to folder.")
flags.DEFINE_integer("num_epochs", 150, "Number of training epochs.")
flags.DEFINE_integer("batch_size", 256, "Global batch size across all GPUs.")


def infer_space_from_value(x):
    """递归从样本值推断 gymnasium space。"""
    if isinstance(x, dict):
        return spaces.Dict({k: infer_space_from_value(v) for k, v in x.items()})

    arr = np.asarray(x)

    if arr.dtype == np.uint8:
        return spaces.Box(low=0, high=255, shape=arr.shape, dtype=np.uint8)
    elif np.issubdtype(arr.dtype, np.bool_):
        return spaces.Box(low=0, high=1, shape=arr.shape, dtype=np.bool_)
    elif np.issubdtype(arr.dtype, np.integer):
        return spaces.Box(
            low=np.iinfo(arr.dtype).min,
            high=np.iinfo(arr.dtype).max,
            shape=arr.shape,
            dtype=arr.dtype,
        )
    else:
        return spaces.Box(low=-np.inf, high=np.inf, shape=arr.shape, dtype=arr.dtype)


def build_spaces_from_dataset(success_paths, failure_paths):
    """从 success / failure pkl 中找一条样本，推断 observation_space 和 action_space。"""
    all_paths = list(success_paths) + list(failure_paths)
    if not all_paths:
        raise ValueError("classifier_data_single 目录下没有找到 success/failure pkl 文件")

    sample_transition = None
    for path in all_paths:
        with open(path, "rb") as f:
            data = pkl.load(f)
        if len(data) > 0:
            sample_transition = data[0]
            break

    if sample_transition is None:
        raise ValueError("所有 pkl 文件都是空的，无法推断 observation_space/action_space")

    observation_space = infer_space_from_value(sample_transition["observations"])
    action_space = infer_space_from_value(sample_transition["actions"])
    return observation_space, action_space


def shard_batch(batch, num_devices: int):
    """把全局 batch reshape 成 [n_devices, per_device_batch, ...]。"""
    def _shard(x):
        x = np.asarray(x)
        if x.shape[0] % num_devices != 0:
            raise ValueError(
                f"Batch 第一维 {x.shape[0]} 不能被设备数 {num_devices} 整除"
            )
        return x.reshape((num_devices, x.shape[0] // num_devices) + x.shape[1:])

    return jax.tree_util.tree_map(_shard, batch)


def tree_to_host_numpy(tree):
    """把 pytree 里的 jax.Array 全部转成 host numpy，便于 checkpoints.save_checkpoint。"""
    return jax.tree_util.tree_map(
        lambda x: np.asarray(jax.device_get(x)) if isinstance(x, (jax.Array, jnp.ndarray)) else x,
        tree,
    )


def main(_):
    assert FLAGS.exp_name in CONFIG_MAPPING, "Experiment folder not found."
    config = CONFIG_MAPPING[FLAGS.exp_name]()

    num_devices = jax.local_device_count()
    devices = jax.local_devices()

    if FLAGS.batch_size % num_devices != 0:
        raise ValueError(
            f"FLAGS.batch_size={FLAGS.batch_size} 必须能被设备数 num_devices={num_devices} 整除"
        )

    print(f"Using {num_devices} local devices: {devices}")
    print(f"Global batch size: {FLAGS.batch_size}")
    print(f"Per-device batch size: {FLAGS.batch_size // num_devices}")

    success_paths = glob.glob(os.path.join(os.getcwd(), "classifier_data_single", "*success*.pkl"))
    failure_paths = glob.glob(os.path.join(os.getcwd(), "classifier_data_single", "*failure*.pkl"))

    observation_space, action_space = build_spaces_from_dataset(success_paths, failure_paths)

    # -----------------------------
    # Positive buffer
    # -----------------------------
    pos_buffer = ReplayBuffer(
        observation_space,
        action_space,
        capacity=20000,
        include_label=True,
    )

    for path in success_paths:
        with open(path, "rb") as f:
            success_data = pkl.load(f)

        for trans in success_data:
            if "images" in trans["observations"].keys():
                continue

            trans = dict(trans)
            trans["labels"] = 1
            trans["actions"] = np.zeros_like(np.asarray(trans["actions"]), dtype=np.float32)
            pos_buffer.insert(trans)

    pos_iterator = pos_buffer.get_iterator(
        sample_args={"batch_size": FLAGS.batch_size // 2},
    )

    # -----------------------------
    # Negative buffer
    # -----------------------------
    neg_buffer = ReplayBuffer(
        observation_space,
        action_space,
        capacity=50000,
        include_label=True,
    )

    for path in failure_paths:
        with open(path, "rb") as f:
            failure_data = pkl.load(f)

        for trans in failure_data:
            if "images" in trans["observations"].keys():
                continue

            trans = dict(trans)
            trans["labels"] = 0
            trans["actions"] = np.zeros_like(np.asarray(trans["actions"]), dtype=np.float32)
            neg_buffer.insert(trans)

    neg_iterator = neg_buffer.get_iterator(
        sample_args={"batch_size": FLAGS.batch_size // 2},
    )

    print(f"failed buffer size: {len(neg_buffer)}")
    print(f"success buffer size: {len(pos_buffer)}")

    rng = jax.random.PRNGKey(0)
    rng, init_key = jax.random.split(rng)

    # 用一组未分片的 sample 初始化 classifier
    pos_sample = next(pos_iterator)
    neg_sample = next(neg_iterator)
    sample = concat_batches(pos_sample, neg_sample, axis=0)

    classifier = create_classifier(
        init_key,
        sample["observations"],
        config.classifier_keys,
    )

    # 复制到多 GPU
    classifier = jax_utils.replicate(classifier)

    def data_augmentation_fn(rng, observations):
        """这里输入是单个 device 上的 local batch，所以 num_batch_dims=1。"""
        for pixel_key in config.classifier_keys:
            rng, crop_key = jax.random.split(rng)
            observations = observations.copy(
                add_or_replace={
                    pixel_key: batched_random_crop(
                        observations[pixel_key],
                        crop_key,
                        padding=4,
                        num_batch_dims=1,
                    )
                }
            )
        return observations

    @functools.partial(jax.pmap, axis_name="devices")
    def train_step(state, batch, aug_key, dropout_key):
        obs = data_augmentation_fn(aug_key, batch["observations"])
        batch = batch.copy(add_or_replace={"observations": obs})

        def loss_fn(params):
            logits = state.apply_fn(
                {"params": params},
                batch["observations"],
                rngs={"dropout": dropout_key},
                train=True,
            )
            loss = optax.sigmoid_binary_cross_entropy(logits, batch["labels"]).mean()
            return loss, logits

        (loss, logits), grads = jax.value_and_grad(loss_fn, has_aux=True)(state.params)

        grads = lax.pmean(grads, axis_name="devices")
        loss = lax.pmean(loss, axis_name="devices")

        preds = (nn.sigmoid(logits) >= 0.5)
        acc = jnp.mean(preds == batch["labels"])
        acc = lax.pmean(acc, axis_name="devices")

        new_state = state.apply_gradients(grads=grads)
        return new_state, loss, acc

    for epoch in tqdm(range(FLAGS.num_epochs)):
        pos_sample = next(pos_iterator)
        neg_sample = next(neg_iterator)
        batch = concat_batches(pos_sample, neg_sample, axis=0)

        # labels -> float32, shape [B, 1]
        labels = np.asarray(batch["labels"], dtype=np.float32)[..., None]
        batch = batch.copy(add_or_replace={"labels": labels})

        # 分片到多 GPU
        batch = shard_batch(batch, num_devices)

        rng, aug_master_key = jax.random.split(rng)
        rng, dropout_master_key = jax.random.split(rng)

        aug_keys = jax.random.split(aug_master_key, num_devices)
        dropout_keys = jax.random.split(dropout_master_key, num_devices)

        classifier, train_loss, train_accuracy = train_step(
            classifier,
            batch,
            aug_keys,
            dropout_keys,
        )

        # pmap 返回每张卡一份相同标量，取第 0 张即可
        train_loss_scalar = float(jax.device_get(train_loss[0]))
        train_acc_scalar = float(jax.device_get(train_accuracy[0]))

        print(
            f"Epoch: {epoch + 1}, "
            f"Train Loss: {train_loss_scalar:.4f}, "
            f"Train Accuracy: {train_acc_scalar:.4f}"
        )

    # 关键：保存前先 unreplicate，再转成 host numpy
    classifier_to_save = jax_utils.unreplicate(classifier)
    classifier_to_save = tree_to_host_numpy(classifier_to_save)

    save_dir = os.path.join(os.getcwd(), "classifier_ckpt_single")
    os.makedirs(save_dir, exist_ok=True)

    checkpoints.save_checkpoint(
        save_dir,
        classifier_to_save,
        step=FLAGS.num_epochs,
        overwrite=True,
    )

    print(f"✅ classifier checkpoint 已保存到: {save_dir}")


if __name__ == "__main__":
    app.run(main)


