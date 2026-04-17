// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__BUILDER_HPP_
#define TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace teleoperation_msg_ros2
{

namespace msg
{

namespace builder
{

class Init_VrPose_disengage_by_operator
{
public:
  explicit Init_VrPose_disengage_by_operator(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  ::teleoperation_msg_ros2::msg::VrPose disengage_by_operator(::teleoperation_msg_ros2::msg::VrPose::_disengage_by_operator_type arg)
  {
    msg_.disengage_by_operator = std::move(arg);
    return std::move(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_engage_by_operator
{
public:
  explicit Init_VrPose_engage_by_operator(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_disengage_by_operator engage_by_operator(::teleoperation_msg_ros2::msg::VrPose::_engage_by_operator_type arg)
  {
    msg_.engage_by_operator = std::move(arg);
    return Init_VrPose_disengage_by_operator(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_need_reset_to_init
{
public:
  explicit Init_VrPose_need_reset_to_init(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_engage_by_operator need_reset_to_init(::teleoperation_msg_ros2::msg::VrPose::_need_reset_to_init_type arg)
  {
    msg_.need_reset_to_init = std::move(arg);
    return Init_VrPose_engage_by_operator(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_exception
{
public:
  explicit Init_VrPose_exception(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_need_reset_to_init exception(::teleoperation_msg_ros2::msg::VrPose::_exception_type arg)
  {
    msg_.exception = std::move(arg);
    return Init_VrPose_need_reset_to_init(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_breakpoint
{
public:
  explicit Init_VrPose_breakpoint(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_exception breakpoint(::teleoperation_msg_ros2::msg::VrPose::_breakpoint_type arg)
  {
    msg_.breakpoint = std::move(arg);
    return Init_VrPose_exception(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_angular_vel
{
public:
  explicit Init_VrPose_angular_vel(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_breakpoint angular_vel(::teleoperation_msg_ros2::msg::VrPose::_angular_vel_type arg)
  {
    msg_.angular_vel = std::move(arg);
    return Init_VrPose_breakpoint(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_y_vel
{
public:
  explicit Init_VrPose_y_vel(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_angular_vel y_vel(::teleoperation_msg_ros2::msg::VrPose::_y_vel_type arg)
  {
    msg_.y_vel = std::move(arg);
    return Init_VrPose_angular_vel(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_x_vel
{
public:
  explicit Init_VrPose_x_vel(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_y_vel x_vel(::teleoperation_msg_ros2::msg::VrPose::_x_vel_type arg)
  {
    msg_.x_vel = std::move(arg);
    return Init_VrPose_y_vel(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_torso_backward
{
public:
  explicit Init_VrPose_torso_backward(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_x_vel torso_backward(::teleoperation_msg_ros2::msg::VrPose::_torso_backward_type arg)
  {
    msg_.torso_backward = std::move(arg);
    return Init_VrPose_x_vel(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_torso_forward
{
public:
  explicit Init_VrPose_torso_forward(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_torso_backward torso_forward(::teleoperation_msg_ros2::msg::VrPose::_torso_forward_type arg)
  {
    msg_.torso_forward = std::move(arg);
    return Init_VrPose_torso_backward(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_torso_down
{
public:
  explicit Init_VrPose_torso_down(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_torso_forward torso_down(::teleoperation_msg_ros2::msg::VrPose::_torso_down_type arg)
  {
    msg_.torso_down = std::move(arg);
    return Init_VrPose_torso_forward(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_torso_up
{
public:
  explicit Init_VrPose_torso_up(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_torso_down torso_up(::teleoperation_msg_ros2::msg::VrPose::_torso_up_type arg)
  {
    msg_.torso_up = std::move(arg);
    return Init_VrPose_torso_down(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_tilt_backward
{
public:
  explicit Init_VrPose_tilt_backward(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_torso_up tilt_backward(::teleoperation_msg_ros2::msg::VrPose::_tilt_backward_type arg)
  {
    msg_.tilt_backward = std::move(arg);
    return Init_VrPose_torso_up(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_tilt_forward
{
public:
  explicit Init_VrPose_tilt_forward(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_tilt_backward tilt_forward(::teleoperation_msg_ros2::msg::VrPose::_tilt_forward_type arg)
  {
    msg_.tilt_forward = std::move(arg);
    return Init_VrPose_tilt_backward(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_waist_left
{
public:
  explicit Init_VrPose_waist_left(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_tilt_forward waist_left(::teleoperation_msg_ros2::msg::VrPose::_waist_left_type arg)
  {
    msg_.waist_left = std::move(arg);
    return Init_VrPose_tilt_forward(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_waist_right
{
public:
  explicit Init_VrPose_waist_right(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_waist_left waist_right(::teleoperation_msg_ros2::msg::VrPose::_waist_right_type arg)
  {
    msg_.waist_right = std::move(arg);
    return Init_VrPose_waist_left(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_manipulation_mode
{
public:
  explicit Init_VrPose_manipulation_mode(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_waist_right manipulation_mode(::teleoperation_msg_ros2::msg::VrPose::_manipulation_mode_type arg)
  {
    msg_.manipulation_mode = std::move(arg);
    return Init_VrPose_waist_right(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_control_mode
{
public:
  explicit Init_VrPose_control_mode(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_manipulation_mode control_mode(::teleoperation_msg_ros2::msg::VrPose::_control_mode_type arg)
  {
    msg_.control_mode = std::move(arg);
    return Init_VrPose_manipulation_mode(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_right_disconnect_pressed
{
public:
  explicit Init_VrPose_right_disconnect_pressed(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_control_mode right_disconnect_pressed(::teleoperation_msg_ros2::msg::VrPose::_right_disconnect_pressed_type arg)
  {
    msg_.right_disconnect_pressed = std::move(arg);
    return Init_VrPose_control_mode(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_left_disconnect_pressed
{
public:
  explicit Init_VrPose_left_disconnect_pressed(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_right_disconnect_pressed left_disconnect_pressed(::teleoperation_msg_ros2::msg::VrPose::_left_disconnect_pressed_type arg)
  {
    msg_.left_disconnect_pressed = std::move(arg);
    return Init_VrPose_right_disconnect_pressed(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_right_j4j6_cmd
{
public:
  explicit Init_VrPose_right_j4j6_cmd(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_left_disconnect_pressed right_j4j6_cmd(::teleoperation_msg_ros2::msg::VrPose::_right_j4j6_cmd_type arg)
  {
    msg_.right_j4j6_cmd = std::move(arg);
    return Init_VrPose_left_disconnect_pressed(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_left_j4j6_cmd
{
public:
  explicit Init_VrPose_left_j4j6_cmd(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_right_j4j6_cmd left_j4j6_cmd(::teleoperation_msg_ros2::msg::VrPose::_left_j4j6_cmd_type arg)
  {
    msg_.left_j4j6_cmd = std::move(arg);
    return Init_VrPose_right_j4j6_cmd(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_right_gripper_close
{
public:
  explicit Init_VrPose_right_gripper_close(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_left_j4j6_cmd right_gripper_close(::teleoperation_msg_ros2::msg::VrPose::_right_gripper_close_type arg)
  {
    msg_.right_gripper_close = std::move(arg);
    return Init_VrPose_left_j4j6_cmd(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_right_quaternion
{
public:
  explicit Init_VrPose_right_quaternion(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_right_gripper_close right_quaternion(::teleoperation_msg_ros2::msg::VrPose::_right_quaternion_type arg)
  {
    msg_.right_quaternion = std::move(arg);
    return Init_VrPose_right_gripper_close(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_right_position
{
public:
  explicit Init_VrPose_right_position(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_right_quaternion right_position(::teleoperation_msg_ros2::msg::VrPose::_right_position_type arg)
  {
    msg_.right_position = std::move(arg);
    return Init_VrPose_right_quaternion(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_left_gripper_close
{
public:
  explicit Init_VrPose_left_gripper_close(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_right_position left_gripper_close(::teleoperation_msg_ros2::msg::VrPose::_left_gripper_close_type arg)
  {
    msg_.left_gripper_close = std::move(arg);
    return Init_VrPose_right_position(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_left_quaternion
{
public:
  explicit Init_VrPose_left_quaternion(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_left_gripper_close left_quaternion(::teleoperation_msg_ros2::msg::VrPose::_left_quaternion_type arg)
  {
    msg_.left_quaternion = std::move(arg);
    return Init_VrPose_left_gripper_close(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_left_position
{
public:
  explicit Init_VrPose_left_position(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_left_quaternion left_position(::teleoperation_msg_ros2::msg::VrPose::_left_position_type arg)
  {
    msg_.left_position = std::move(arg);
    return Init_VrPose_left_quaternion(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_head_quaternion
{
public:
  explicit Init_VrPose_head_quaternion(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_left_position head_quaternion(::teleoperation_msg_ros2::msg::VrPose::_head_quaternion_type arg)
  {
    msg_.head_quaternion = std::move(arg);
    return Init_VrPose_left_position(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_head_position
{
public:
  explicit Init_VrPose_head_position(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_head_quaternion head_position(::teleoperation_msg_ros2::msg::VrPose::_head_position_type arg)
  {
    msg_.head_position = std::move(arg);
    return Init_VrPose_head_quaternion(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_power
{
public:
  explicit Init_VrPose_power(::teleoperation_msg_ros2::msg::VrPose & msg)
  : msg_(msg)
  {}
  Init_VrPose_head_position power(::teleoperation_msg_ros2::msg::VrPose::_power_type arg)
  {
    msg_.power = std::move(arg);
    return Init_VrPose_head_position(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

class Init_VrPose_header
{
public:
  Init_VrPose_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VrPose_power header(::teleoperation_msg_ros2::msg::VrPose::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VrPose_power(msg_);
  }

private:
  ::teleoperation_msg_ros2::msg::VrPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::teleoperation_msg_ros2::msg::VrPose>()
{
  return teleoperation_msg_ros2::msg::builder::Init_VrPose_header();
}

}  // namespace teleoperation_msg_ros2

#endif  // TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__BUILDER_HPP_
