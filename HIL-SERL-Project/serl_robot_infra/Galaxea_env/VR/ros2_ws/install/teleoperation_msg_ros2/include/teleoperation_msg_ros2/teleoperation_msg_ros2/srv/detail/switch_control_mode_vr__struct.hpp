// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_HPP_
#define TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Request __attribute__((deprecated))
#else
# define DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Request __declspec(deprecated)
#endif

namespace teleoperation_msg_ros2
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SwitchControlModeVR_Request_
{
  using Type = SwitchControlModeVR_Request_<ContainerAllocator>;

  explicit SwitchControlModeVR_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->use_vr_mode = false;
    }
  }

  explicit SwitchControlModeVR_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->use_vr_mode = false;
    }
  }

  // field types and members
  using _use_vr_mode_type =
    bool;
  _use_vr_mode_type use_vr_mode;

  // setters for named parameter idiom
  Type & set__use_vr_mode(
    const bool & _arg)
  {
    this->use_vr_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Request
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Request
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SwitchControlModeVR_Request_ & other) const
  {
    if (this->use_vr_mode != other.use_vr_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const SwitchControlModeVR_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SwitchControlModeVR_Request_

// alias to use template instance with default allocator
using SwitchControlModeVR_Request =
  teleoperation_msg_ros2::srv::SwitchControlModeVR_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace teleoperation_msg_ros2


#ifndef _WIN32
# define DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Response __attribute__((deprecated))
#else
# define DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Response __declspec(deprecated)
#endif

namespace teleoperation_msg_ros2
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SwitchControlModeVR_Response_
{
  using Type = SwitchControlModeVR_Response_<ContainerAllocator>;

  explicit SwitchControlModeVR_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SwitchControlModeVR_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Response
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__teleoperation_msg_ros2__srv__SwitchControlModeVR_Response
    std::shared_ptr<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SwitchControlModeVR_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SwitchControlModeVR_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SwitchControlModeVR_Response_

// alias to use template instance with default allocator
using SwitchControlModeVR_Response =
  teleoperation_msg_ros2::srv::SwitchControlModeVR_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace teleoperation_msg_ros2

namespace teleoperation_msg_ros2
{

namespace srv
{

struct SwitchControlModeVR
{
  using Request = teleoperation_msg_ros2::srv::SwitchControlModeVR_Request;
  using Response = teleoperation_msg_ros2::srv::SwitchControlModeVR_Response;
};

}  // namespace srv

}  // namespace teleoperation_msg_ros2

#endif  // TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__STRUCT_HPP_
