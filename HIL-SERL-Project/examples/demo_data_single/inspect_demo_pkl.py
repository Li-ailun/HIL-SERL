import os
import glob
import pickle as pkl
import numpy as np

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# 设成 None 就自动取最新 pkl；也可以手动写死某个文件名
PKL_PATH = None


def find_latest_demo_pkl():
    pkl_files = glob.glob(os.path.join(BASE_DIR, "*.pkl"))
    if not pkl_files:
        raise FileNotFoundError(f"在 {BASE_DIR} 下没有找到任何 .pkl 文件")
    return max(pkl_files, key=os.path.getmtime)


def main():
    path = PKL_PATH if PKL_PATH is not None else find_latest_demo_pkl()
    print(f"正在检查文件: {path}")

    with open(path, "rb") as f:
        data = pkl.load(f)

    print(f"\n总 transition 数: {len(data)}")
    if len(data) == 0:
        print("文件是空的。")
        return

    first = data[0]

    print("\n===== 顶层 keys =====")
    print(list(first.keys()))

    obs = first["observations"]
    print("\n===== observations 顶层 keys =====")
    print(list(obs.keys()))

    if "state" in obs:
        print("\n===== observations['state'] keys =====")
        print(list(obs["state"].keys()))
        for k, v in obs["state"].items():
            arr = np.asarray(v)
            print(f"  {k}: shape={arr.shape}, dtype={arr.dtype}, sample={arr}")

    if "images" in obs:
        print("\n===== observations['images'] keys =====")
        print(list(obs["images"].keys()))
        for k, v in obs["images"].items():
            arr = np.asarray(v)
            print(f"  {k}: shape={arr.shape}, dtype={arr.dtype}")

    act = np.asarray(first["actions"])
    print("\n===== 第一条 actions =====")
    print("shape:", act.shape)
    print("value:", act)

    if act.shape == (7,):
        print("\n推断：这是单臂动作。通常含义是：")
        print("  [dx, dy, dz, droll, dpitch, dyaw, gripper]")
        print("  其中最后一维一般是 gripper。")

    elif act.shape == (14,):
        print("\n推断：这是双臂动作。")

    print("\n===== infos keys（第一条）=====")
    infos = first.get("infos", {})
    if isinstance(infos, dict):
        print(list(infos.keys()))
    else:
        print(type(infos), infos)

    # 统计整份数据里 action 维度
    dims = {}
    done_count = 0
    static_count = 0

    for trans in data:
        a = np.asarray(trans["actions"]).reshape(-1)
        dims[a.shape[0]] = dims.get(a.shape[0], 0) + 1
        if bool(trans.get("dones", False)):
            done_count += 1
        if np.allclose(a, 0.0, atol=1e-8):
            static_count += 1

    print("\n===== 全文件统计 =====")
    print("action 维度分布:", dims)
    print("dones=True 数量:", done_count)
    print("静止动作数量:", static_count)

    # 再抽几条看看
    print("\n===== 抽样查看前 5 条 actions =====")
    for i in range(min(5, len(data))):
        a = np.asarray(data[i]["actions"]).reshape(-1)
        print(f"[{i}] shape={a.shape}, action={a}")

    # 检查是否含右臂字段
    print("\n===== 右臂字段检查 =====")
    state_keys = set(obs["state"].keys()) if "state" in obs else set()
    print("包含 right_ee_pose:", "right_ee_pose" in state_keys)
    print("包含 right_gripper:", "right_gripper" in state_keys)
    print("包含 left_ee_pose :", "left_ee_pose" in state_keys)
    print("包含 left_gripper :", "left_gripper" in state_keys)


if __name__ == "__main__":
    main()