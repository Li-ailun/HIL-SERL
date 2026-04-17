// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_HPP_
#define TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__teleoperation_msg_ros2__msg__VrPose __attribute__((deprecated))
#else
# define DEPRECATED__teleoperation_msg_ros2__msg__VrPose __declspec(deprecated)
#endif

namespace teleoperation_msg_ros2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VrPose_
{
  using Type = VrPose_<ContainerAllocator>;

  explicit VrPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->power = false;
      this->left_gripper_close = false;
      this->right_gripper_close = false;
      this->left_disconnect_pressed = false;
      this->right_disconnect_pressed = false;
      this->control_mode = 0;
      this->manipulation_mode = 0;
      this->waist_right = false;
      this->waist_left = false;
      this->tilt_forward = false;
      this->tilt_backward = false;
      this->torso_up = false;
      this->torso_down = false;
      this->torso_forward = false;
      this->torso_backward = false;
      this->x_vel = 0.0f;
      this->y_vel = 0.0f;
      this->angular_vel = 0.0f;
      this->breakpoint = false;
      this->exception = false;
      this->need_reset_to_init = false;
      this->engage_by_operator = false;
      this->disengage_by_operator = false;
    }
  }

  explicit VrPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->power = false;
      this->left_gripper_close = false;
      this->right_gripper_close = false;
      this->left_disconnect_pressed = false;
      this->right_disconnect_pressed = false;
      this->control_mode = 0;
      this->manipulation_mode = 0;
      this->waist_right = false;
      this->waist_left = false;
      this->tilt_forward = false;
      this->tilt_backward = false;
      this->torso_up = false;
      this->torso_down = false;
      this->torso_forward = false;
      this->torso_backward = false;
      this->x_vel = 0.0f;
      this->y_vel = 0.0f;
      this->angular_vel = 0.0f;
      this->breakpoint = false;
      this->exception = false;
      this->need_reset_to_init = false;
      this->engage_by_operator = false;
      this->disengage_by_operator = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _power_type =
    bool;
  _power_type power;
  using _head_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _head_position_type head_position;
  using _head_quaternion_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _head_quaternion_type head_quaternion;
  using _left_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _left_position_type left_position;
  using _left_quaternion_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _left_quaternion_type left_quaternion;
  using _left_gripper_close_type =
    bool;
  _left_gripper_close_type left_gripper_close;
  using _right_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _right_position_type right_position;
  using _right_quaternion_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _right_quaternion_type right_quaternion;
  using _right_gripper_close_type =
    bool;
  _right_gripper_close_type right_gripper_close;
  using _left_j4j6_cmd_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _left_j4j6_cmd_type left_j4j6_cmd;
  using _right_j4j6_cmd_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _right_j4j6_cmd_type right_j4j6_cmd;
  using _left_disconnect_pressed_type =
    bool;
  _left_disconnect_pressed_type left_disconnect_pressed;
  using _right_disconnect_pressed_type =
    bool;
  _right_disconnect_pressed_type right_disconnect_pressed;
  using _control_mode_type =
    int8_t;
  _control_mode_type control_mode;
  using _manipulation_mode_type =
    int8_t;
  _manipulation_mode_type manipulation_mode;
  using _waist_right_type =
    bool;
  _waist_right_type waist_right;
  using _waist_left_type =
    bool;
  _waist_left_type waist_left;
  using _tilt_forward_type =
    bool;
  _tilt_forward_type tilt_forward;
  using _tilt_backward_type =
    bool;
  _tilt_backward_type tilt_backward;
  using _torso_up_type =
    bool;
  _torso_up_type torso_up;
  using _torso_down_type =
    bool;
  _torso_down_type torso_down;
  using _torso_forward_type =
    bool;
  _torso_forward_type torso_forward;
  using _torso_backward_type =
    bool;
  _torso_backward_type torso_backward;
  using _x_vel_type =
    float;
  _x_vel_type x_vel;
  using _y_vel_type =
    float;
  _y_vel_type y_vel;
  using _angular_vel_type =
    float;
  _angular_vel_type angular_vel;
  using _breakpoint_type =
    bool;
  _breakpoint_type breakpoint;
  using _exception_type =
    bool;
  _exception_type exception;
  using _need_reset_to_init_type =
    bool;
  _need_reset_to_init_type need_reset_to_init;
  using _engage_by_operator_type =
    bool;
  _engage_by_operator_type engage_by_operator;
  using _disengage_by_operator_type =
    bool;
  _disengage_by_operator_type disengage_by_operator;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__power(
    const bool & _arg)
  {
    this->power = _arg;
    return *this;
  }
  Type & set__head_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->head_position = _arg;
    return *this;
  }
  Type & set__head_quaternion(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->head_quaternion = _arg;
    return *this;
  }
  Type & set__left_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->left_position = _arg;
    return *this;
  }
  Type & set__left_quaternion(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->left_quaternion = _arg;
    return *this;
  }
  Type & set__left_gripper_close(
    const bool & _arg)
  {
    this->left_gripper_close = _arg;
    return *this;
  }
  Type & set__right_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->right_position = _arg;
    return *this;
  }
  Type & set__right_quaternion(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->right_quaternion = _arg;
    return *this;
  }
  Type & set__right_gripper_close(
    const bool & _arg)
  {
    this->right_gripper_close = _arg;
    return *this;
  }
  Type & set__left_j4j6_cmd(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->left_j4j6_cmd = _arg;
    return *this;
  }
  Type & set__right_j4j6_cmd(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->right_j4j6_cmd = _arg;
    return *this;
  }
  Type & set__left_disconnect_pressed(
    const bool & _arg)
  {
    this->left_disconnect_pressed = _arg;
    return *this;
  }
  Type & set__right_disconnect_pressed(
    const bool & _arg)
  {
    this->right_disconnect_pressed = _arg;
    return *this;
  }
  Type & set__control_mode(
    const int8_t & _arg)
  {
    this->control_mode = _arg;
    return *this;
  }
  Type & set__manipulation_mode(
    const int8_t & _arg)
  {
    this->manipulation_mode = _arg;
    return *this;
  }
  Type & set__waist_right(
    const bool & _arg)
  {
    this->waist_right = _arg;
    return *this;
  }
  Type & set__waist_left(
    const bool & _arg)
  {
    this->waist_left = _arg;
    return *this;
  }
  Type & set__tilt_forward(
    const bool & _arg)
  {
    this->tilt_forward = _arg;
    return *this;
  }
  Type & set__tilt_backward(
    const bool & _arg)
  {
    this->tilt_backward = _arg;
    return *this;
  }
  Type & set__torso_up(
    const bool & _arg)
  {
    this->torso_up = _arg;
    return *this;
  }
  Type & set__torso_down(
    const bool & _arg)
  {
    this->torso_down = _arg;
    return *this;
  }
  Type & set__torso_forward(
    const bool & _arg)
  {
    this->torso_forward = _arg;
    return *this;
  }
  Type & set__torso_backward(
    const bool & _arg)
  {
    this->torso_backward = _arg;
    return *this;
  }
  Type & set__x_vel(
    const float & _arg)
  {
    this->x_vel = _arg;
    return *this;
  }
  Type & set__y_vel(
    const float & _arg)
  {
    this->y_vel = _arg;
    return *this;
  }
  Type & set__angular_vel(
    const float & _arg)
  {
    this->angular_vel = _arg;
    return *this;
  }
  Type & set__breakpoint(
    const bool & _arg)
  {
    this->breakpoint = _arg;
    return *this;
  }
  Type & set__exception(
    const bool & _arg)
  {
    this->exception = _arg;
    return *this;
  }
  Type & set__need_reset_to_init(
    const bool & _arg)
  {
    this->need_reset_to_init = _arg;
    return *this;
  }
  Type & set__engage_by_operator(
    const bool & _arg)
  {
    this->engage_by_operator = _arg;
    return *this;
  }
  Type & set__disengage_by_operator(
    const bool & _arg)
  {
    this->disengage_by_operator = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleoperation_msg_ros2__msg__VrPose
    std::shared_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleoperation_msg_ros2__msg__VrPose
    std::shared_ptr<teleoperation_msg_ros2::msg::VrPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VrPose_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->power != other.power) {
      return false;
    }
    if (this->head_position != other.head_position) {
      return false;
    }
    if (this->head_quaternion != other.head_quaternion) {
      return false;
    }
    if (this->left_position != other.left_position) {
      return false;
    }
    if (this->left_quaternion != other.left_quaternion) {
      return false;
    }
    if (this->left_gripper_close != other.left_gripper_close) {
      return false;
    }
    if (this->right_position != other.right_position) {
      return false;
    }
    if (this->right_quaternion != other.right_quaternion) {
      return false;
    }
    if (this->right_gripper_close != other.right_gripper_close) {
      return false;
    }
    if (this->left_j4j6_cmd != other.left_j4j6_cmd) {
      return false;
    }
    if (this->right_j4j6_cmd != other.right_j4j6_cmd) {
      return false;
    }
    if (this->left_disconnect_pressed != other.left_disconnect_pressed) {
      return false;
    }
    if (this->right_disconnect_pressed != other.right_disconnect_pressed) {
      return false;
    }
    if (this->control_mode != other.control_mode) {
      return false;
    }
    if (this->manipulation_mode != other.manipulation_mode) {
      return false;
    }
    if (this->waist_right != other.waist_right) {
      return false;
    }
    if (this->waist_left != other.waist_left) {
      return false;
    }
    if (this->tilt_forward != other.tilt_forward) {
      return false;
    }
    if (this->tilt_backward != other.tilt_backward) {
      return false;
    }
    if (this->torso_up != other.torso_up) {
      return false;
    }
    if (this->torso_down != other.torso_down) {
      return false;
    }
    if (this->torso_forward != other.torso_forward) {
      return false;
    }
    if (this->torso_backward != other.torso_backward) {
      return false;
    }
    if (this->x_vel != other.x_vel) {
      return false;
    }
    if (this->y_vel != other.y_vel) {
      return false;
    }
    if (this->angular_vel != other.angular_vel) {
      return false;
    }
    if (this->breakpoint != other.breakpoint) {
      return false;
    }
    if (this->exception != other.exception) {
      return false;
    }
    if (this->need_reset_to_init != other.need_reset_to_init) {
      return false;
    }
    if (this->engage_by_operator != other.engage_by_operator) {
      return false;
    }
    if (this->disengage_by_operator != other.disengage_by_operator) {
      return false;
    }
    return true;
  }
  bool operator!=(const VrPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VrPose_

// alias to use template instance with default allocator
using VrPose =
  teleoperation_msg_ros2::msg::VrPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace teleoperation_msg_ros2

#endif  // TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__STRUCT_HPP_
