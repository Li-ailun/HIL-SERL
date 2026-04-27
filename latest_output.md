下面把**当前完整数据流**重新捋一遍。你现在有两条主线：

```text
A. actor 自主控制时：
   网络输出归一化增量 action
   env 把 action 乘缩放，加到当前末端位姿上执行

B. VR 介入记录时：
   VR 底层真实控制机器人
   wrapper 用末端前后位姿差反推归一化 action
   保存到 info["intervene_action"]
```

这两条线是互逆的，所以训练语义是对齐的。

---

# 1. action 的定义

你的单臂 action 是 7 维：

```text
action[0:3] = xyz 位置归一化增量
action[3:6] = roll/pitch/yaw 或 rotvec 旋转归一化增量
action[6]   = 夹爪三值事件
```

其中：

```text
action[6] = -1  close event
action[6] =  0  hold / no-op
action[6] = +1  open event
```

前 6 维永远应该在：

```text
[-1, 1]
```

这不是末端绝对位置，不是 `/motion_control/pose_ee_arm_right` 的绝对值，也不是 VR 手柄绝对位姿。它表示：

```text
这一 step 末端应该移动多少个“动作单位”
```

---

# 2. 缩放是什么意思？

wrapper 里从 env/config 读取两个 scale：

```python
self.pos_scale = POS_SCALE，默认 0.01
self.rot_scale = ROT_SCALE，默认 0.05
```

代码里如果没有显式传，就会从底层 env/config 读取 `POS_SCALE` / `ROT_SCALE`，读不到才用默认 `0.01` / `0.05`。

含义是：

```text
POS_SCALE = 0.01
表示 action 位置维度的 1.0 对应真实末端 0.01 m，也就是 1 cm。

ROT_SCALE = 0.05
表示 action 旋转维度的 1.0 对应真实末端 0.05 rad，约 2.86°。
```

所以 actor 输出：

```text
action[:3] = [0.5, -0.2, 0.0]
```

实际位置增量就是：

```text
[0.5, -0.2, 0.0] * 0.01
= [0.005, -0.002, 0.0] m
= [5 mm, -2 mm, 0 mm]
```

如果 actor 输出：

```text
action[3:6] = [0.0, 0.0, 0.4]
```

实际旋转增量就是：

```text
[0.0, 0.0, 0.4] * 0.05
= [0.0, 0.0, 0.02] rad
```

---

# 3. actor 自主控制时的流程

actor 没有 VR 介入时，流程是：

```text
obs_t
  ↓
actor 网络
  ↓
policy_actions = 网络输出的归一化 action
  ↓
env.step(policy_actions)
  ↓
底层 env 根据当前真实末端位姿执行：
    target_pos = current_pos + policy_actions[:3] * POS_SCALE
    target_rot = delta_rot(policy_actions[3:6] * ROT_SCALE) * current_rot
  ↓
机器人运动
  ↓
得到 next_obs
  ↓
保存 transition
```

所以 actor 学的是：

```text
在当前图像 + 当前机器人状态下，下一步末端应该往哪个方向移动多少。
```

不是学绝对位置。

---

# 4. VR 介入时的流程

现在你明确不用 `/vr_pose` 的手柄位姿，因为手柄位姿漂移严重。wrapper 里也已经写明：`/vr_pose` 只用于 `control_mode` 和左右夹爪按钮，不再用 `/vr_pose` 的 position/quaternion 生成前 6 维动作。

VR 介入时实际流程是：

```text
进入 control_mode=0
  ↓
底层 VR 系统真实控制机器人运动
  ↓
wrapper 在 env.step 前保存 prev_ee_pose
  ↓
env.step(exec_action)
  ↓
wrapper 在 env.step 后读取 next_ee_pose
  ↓
用 next_ee_pose - prev_ee_pose 反推 action[:6]
  ↓
写入 info["intervene_action"]
  ↓
RLPD / demo 脚本保存这个 action
```

注意：VR 模式下传给 env.step 的 `exec_action` 只是占位动作，前 6 维是 0，夹爪维度带当前事件；真正要保存的 `intervene_action` 会在 step 后根据 EE feedback 反推。代码注释里也是这个意思。

---

# 5. VR 介入时位置增量怎么反推？

wrapper 先从 obs 里提取末端 pose。它支持 `right_ee_pose`、`right/tcp_pose`、`right_tcp_pose`、`pose_ee_arm_right`、`tcp_pose`、`ee_pose` 等 key；如果 `obs["state"]` 是数组，也会按 `[x,y,z,qx,qy,qz,qw,gripper]` 这类格式取前 7 维。

然后计算：

```python
pos_delta = next_pos - prev_pos
```

这是实际末端在一个 actor step 里移动了多少。

例如：

```text
prev_pos = [0.500, 0.100, 0.200]
next_pos = [0.504, 0.098, 0.200]
```

那么：

```text
pos_delta = [0.004, -0.002, 0.000] m
```

再除以 `POS_SCALE=0.01`：

```text
action[:3] = [0.004, -0.002, 0.000] / 0.01
           = [0.4, -0.2, 0.0]
```

这就是保存进 buffer 的归一化位置增量。

---

# 6. VR 介入时旋转增量怎么反推？

旋转不能直接用欧拉角相减。wrapper 里先把上一帧和下一帧 pose 转成四元数，然后转成 Rotation：

```python
prev_rot = R.from_quat(prev_quat)
next_rot = R.from_quat(next_quat)
```

然后计算相对旋转：

```python
rot_delta = (next_rot * prev_rot.inv()).as_rotvec()
```

代码注释里也写了执行语义：

```text
next_rot = delta_rot * prev_rot
所以 delta_rot = next_rot * prev_rot.inv()
```

然后：

```python
action[3:6] = rot_delta / ROT_SCALE
```

最后前 6 维统一 clip 到 `[-1, 1]`。

例如：

```text
这一 step 真实 yaw 增加了 0.01 rad
ROT_SCALE = 0.05
```

那么：

```text
action_yaw = 0.01 / 0.05 = 0.2
```

保存的旋转 action 就是 0.2。

---

# 7. 为什么要 clip 到 [-1, 1]？

因为策略网络的训练动作空间就是归一化动作空间：

```text
action[:6] ∈ [-1, 1]
```

如果某一步 VR 真实移动太大，例如：

```text
pos_delta = 0.02 m
POS_SCALE = 0.01
```

反推出来：

```text
action = 0.02 / 0.01 = 2.0
```

但网络动作空间不能保存 2.0，所以必须：

```text
clip(2.0, -1, 1) = 1.0
```

这就是为什么你后续 inspect 要看有没有大量 ±1。少量饱和可以接受，大量饱和说明 actor step 太慢、VR 速度太快，或者 scale 太小。

---

# 8. 夹爪是怎么记录的？

夹爪不靠末端 pose 反推，而是靠 `/vr_pose` 里的按钮状态做边沿事件。

逻辑是：

```text
上一帧没按 close，这一帧按下 close
  -> -1 close event

上一帧按着 close，这一帧松开 close
  -> +1 open event

其他情况
  -> 0 hold
```

代码里的 `_gripper_button_to_event()` 就是这个逻辑，而且第一帧只初始化按钮状态，不触发事件，避免切 mode 时误触发。

所以最终 VR 介入 action 是：

```text
action[:3] = 真实末端位置变化 / POS_SCALE
action[3:6] = 真实末端相对旋转 / ROT_SCALE
action[6] = 夹爪事件 -1/0/+1
```

---

# 9. info["intervene_action"] 是什么？

在 VR 模式下，wrapper 会在 step 后写：

```python
info["intervene_action"] = measured_action
```

其中 `measured_action` 就是刚才反推出的 7 维归一化动作。代码里在 `is_intervened` 时调用 `_compute_action_from_ee_delta()`，成功后把结果放进 `info["intervene_action"]`。

然后 RLPD actor 看到：

```text
if "intervene_action" in info:
    stored_actions = info.pop("intervene_action")
```

也就是说，VR 介入时保存的不是 actor 网络原本输出的动作，而是真实末端运动反推出来的人类介入动作。

---

# 10. 训练数据和执行语义为什么是对齐的？

这是最关键的闭环。

## actor 执行时

```text
actor action * scale -> 真实末端增量
```

例如：

```text
actor 输出 0.4
POS_SCALE=0.01
真实末端移动 0.004 m
```

## VR 记录时

```text
真实末端增量 / scale -> 保存 action
```

例如：

```text
真实末端移动 0.004 m
POS_SCALE=0.01
保存 action = 0.4
```

所以二者互为反运算：

```text
执行：
  action -> 真实运动

记录：
  真实运动 -> action
```

这就是为什么这个方案比 `/vr_pose` 手柄位姿可靠。你不需要校准漂移的手柄坐标，也不需要做 VR 坐标到机器人坐标的复杂映射；你直接用机器人真实末端反馈来反推训练动作。

---

# 11. 新 RLPD 网络更新流程和这个数据流的关系

你现在新生成的 RLPD 是官网式 episode 更新：

```text
一个 episode 内：
  不做周期性 client.update
  不后台频繁更新网络
  actor 连续 env.step
  VR 介入动作连续记录

episode 结束后：
  client.update()
  reset()
  reset 后等待新网络
  收到网络后再开始下一 episode 的动作输出
```

这个改动的目的不是改变 action 的数学定义，而是保证：

```text
VR 接管期间 actor 主循环尽量不断
x/1000000 连续增长
每个 env.step 都能形成一条 transition
```

这样 VR 期间：

```text
prev_ee_pose -> next_ee_pose
```

不会因为网络更新卡顿而跨很长时间，反推出的 action 也更稳定。

---

# 12. 最终一句话总结

你现在的完整设计是：

```text
actor 自主控制：
  网络输出归一化增量 action
  env 用 POS_SCALE / ROT_SCALE 把它变成真实末端增量执行

VR 介入记录：
  底层 VR 控制真实机器人
  wrapper 用真实末端前后位姿差反推真实增量
  再除以 POS_SCALE / ROT_SCALE 变回归一化 action
  写入 info["intervene_action"]
  RLPD 保存进 buffer 和 demo_buffer

夹爪：
  /vr_pose 只用于按钮事件
  -1 close，0 hold，+1 open
```

所以现在训练看到的所有 action 都是统一语义：

```text
机器人末端坐标系下的归一化一步增量动作
```

不是 VR 手柄坐标，不是绝对末端位姿。
