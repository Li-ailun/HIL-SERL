// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "teleoperation_msg_ros2/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace teleoperation_msg_ros2
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
cdr_serialize(
  const teleoperation_msg_ros2::msg::VrPose & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  teleoperation_msg_ros2::msg::VrPose & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
get_serialized_size(
  const teleoperation_msg_ros2::msg::VrPose & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
max_serialized_size_VrPose(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace teleoperation_msg_ros2

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, teleoperation_msg_ros2, msg, VrPose)();

#ifdef __cplusplus
}
#endif

#endif  // TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
