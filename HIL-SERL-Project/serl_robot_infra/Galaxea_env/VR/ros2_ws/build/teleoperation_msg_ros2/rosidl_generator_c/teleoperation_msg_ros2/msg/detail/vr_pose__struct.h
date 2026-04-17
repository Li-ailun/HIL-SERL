// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_H_
#define TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'head_position'
// Member 'head_quaternion'
// Member 'left_position'
// Member 'left_quaternion'
// Member 'right_position'
// Member 'right_quaternion'
// Member 'left_j4j6_cmd'
// Member 'right_j4j6_cmd'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/VrPose in the package teleoperation_msg_ros2.
typedef struct teleoperation_msg_ros2__msg__VrPose
{
  std_msgs__msg__Header header;
  bool power;
  rosidl_runtime_c__float__Sequence head_position;
  rosidl_runtime_c__float__Sequence head_quaternion;
  rosidl_runtime_c__float__Sequence left_position;
  rosidl_runtime_c__float__Sequence left_quaternion;
  bool left_gripper_close;
  rosidl_runtime_c__float__Sequence right_position;
  rosidl_runtime_c__float__Sequence right_quaternion;
  bool right_gripper_close;
  rosidl_runtime_c__float__Sequence left_j4j6_cmd;
  rosidl_runtime_c__float__Sequence right_j4j6_cmd;
  bool left_disconnect_pressed;
  bool right_disconnect_pressed;
  int8_t control_mode;
  int8_t manipulation_mode;
  bool waist_right;
  bool waist_left;
  bool tilt_forward;
  bool tilt_backward;
  bool torso_up;
  bool torso_down;
  bool torso_forward;
  bool torso_backward;
  float x_vel;
  float y_vel;
  float angular_vel;
  bool breakpoint;
  bool exception;
  bool need_reset_to_init;
  bool engage_by_operator;
  bool disengage_by_operator;
} teleoperation_msg_ros2__msg__VrPose;

// Struct for a sequence of teleoperation_msg_ros2__msg__VrPose.
typedef struct teleoperation_msg_ros2__msg__VrPose__Sequence
{
  teleoperation_msg_ros2__msg__VrPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleoperation_msg_ros2__msg__VrPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_H_
