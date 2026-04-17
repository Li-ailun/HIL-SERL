// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_H_
#define TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SwitchControlModeVR in the package teleoperation_msg_ros2.
typedef struct teleoperation_msg_ros2__srv__SwitchControlModeVR_Request
{
  bool use_vr_mode;
} teleoperation_msg_ros2__srv__SwitchControlModeVR_Request;

// Struct for a sequence of teleoperation_msg_ros2__srv__SwitchControlModeVR_Request.
typedef struct teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence
{
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SwitchControlModeVR in the package teleoperation_msg_ros2.
typedef struct teleoperation_msg_ros2__srv__SwitchControlModeVR_Response
{
  bool success;
  rosidl_runtime_c__String message;
} teleoperation_msg_ros2__srv__SwitchControlModeVR_Response;

// Struct for a sequence of teleoperation_msg_ros2__srv__SwitchControlModeVR_Response.
typedef struct teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence
{
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_H_
