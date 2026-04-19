import os
import glob
import pickle as pkl
import numpy as np

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# 设成 None 就自动取最新 pkl；也可以手动写死某个文件
PKL_PATH = None


def find_latest_demo_pkl():
    pkl_files = glob.glob(os.path.join(BASE_DIR, "*.pkl"))
    if not pkl_files:
        raise FileNotFoundError(f"在 {BASE_DIR} 下没有找到任何 .pkl 文件")
    return max(pkl_files, key=os.path.getmtime)


def summarize_array(name, arr, max_items=12):
    arr = np.asarray(arr)
    flat = arr.reshape(-1)
    preview = flat[:max_items]
    print(f"{name}: shape={arr.shape}, dtype={arr.dtype}, preview={preview}")


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
    print("observations 类型:", type(obs))

    # ---------------------------
    # state 检查
    # ---------------------------
    if "state" in obs:
        print("\n===== observations['state'] 检查 =====")
        state = obs["state"]
        print("type(obs['state']):", type(state))

        if isinstance(state, dict):
            print("state 是 dict，keys 如下：")
            print(list(state.keys()))
            for k, v in state.items():
                summarize_array(f"state['{k}']", v)
        else:
            summarize_array("state", state)

            state_arr = np.asarray(state)
            last_dim = state_arr.shape[-1] if state_arr.ndim > 0 else 1

            if last_dim == 8:
                print("✅ 很像单臂 proprio（通常 = 7维 ee pose + 1维 gripper）")
            elif last_dim == 16:
                print("⚠️ 很像双臂 proprio（通常 = 左右臂 pose/gripper 拼接）")
            else:
                print(f"ℹ️ state 最后一维 = {last_dim}，不是最常见的 8 或 16，需要继续结合 config 判断。")

    # ---------------------------
    # images 检查
    # ---------------------------
    image_keys = ["head_rgb", "left_wrist_rgb", "right_wrist_rgb"]
    print("\n===== 图像检查 =====")
    for k in image_keys:
        if k in obs:
            summarize_array(k, obs[k], max_items=3)
        elif "images" in obs and k in obs["images"]:
            summarize_array(f"images['{k}']", obs["images"][k], max_items=3)
        else:
            print(f"{k}: 不存在")

    # ---------------------------
    # action 检查
    # ---------------------------
    print("\n===== actions 检查 =====")
    act = np.asarray(first["actions"]).reshape(-1)
    print("actions shape:", act.shape)
    print("actions value:", act)

    if act.shape[0] == 7:
        print("✅ 这是单臂动作格式，通常是 [dx, dy, dz, droll, dpitch, dyaw, gripper]")
        print(f"最后一维 gripper = {act[6]:.6f}")
    elif act.shape[0] == 14:
        print("⚠️ 这是双臂动作格式")
    else:
        print("ℹ️ 动作维度不是常见的 7 或 14")

    # ---------------------------
    # infos 检查
    # ---------------------------
    print("\n===== infos 检查 =====")
    infos = first.get("infos", {})
    print("type(infos):", type(infos))
    if isinstance(infos, dict):
        print("infos keys:", list(infos.keys()))
    else:
        print(infos)

    # ---------------------------
    # 全文件统计
    # ---------------------------
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

    # 抽样前 5 条
    print("\n===== 抽样前 5 条 actions =====")
    for i in range(min(5, len(data))):
        a = np.asarray(data[i]["actions"]).reshape(-1)
        print(f"[{i}] shape={a.shape}, action={a}")


if __name__ == "__main__":
    main()