// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__BUILDER_HPP_
#define TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleoperation_msg_ros2/srv/detail/switch_control_mode_vr__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleoperation_msg_ros2
{

namespace srv
{

namespace builder
{

class Init_SwitchControlModeVR_Request_use_vr_mode
{
public:
  Init_SwitchControlModeVR_Request_use_vr_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::teleoperation_msg_ros2::srv::SwitchControlModeVR_Request use_vr_mode(::teleoperation_msg_ros2::srv::SwitchControlModeVR_Request::_use_vr_mode_type arg)
  {
    msg_.use_vr_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleoperation_msg_ros2::srv::SwitchControlModeVR_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>()
{
  return teleoperation_msg_ros2::srv::builder::Init_SwitchControlModeVR_Request_use_vr_mode();
}

}  // namespace teleoperation_msg_ros2


namespace teleoperation_msg_ros2
{

namespace srv
{

namespace builder
{

class Init_SwitchControlModeVR_Response_message
{
public:
  explicit Init_SwitchControlModeVR_Response_message(::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response & msg)
  : msg_(msg)
  {}
  ::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response message(::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response msg_;
};

class Init_SwitchControlModeVR_Response_success
{
public:
  Init_SwitchControlModeVR_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SwitchControlModeVR_Response_message success(::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SwitchControlModeVR_Response_message(msg_);
  }

private:
  ::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>()
{
  return teleoperation_msg_ros2::srv::builder::Init_SwitchControlModeVR_Response_success();
}

}  // namespace teleoperation_msg_ros2

#endif  // TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__BUILDER_HPP_
