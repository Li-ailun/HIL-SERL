// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__TRAITS_HPP_
#define TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleoperation_msg_ros2/srv/detail/switch_control_mode_vr__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace teleoperation_msg_ros2
{

namespace srv
{

inline void to_flow_style_yaml(
  const SwitchControlModeVR_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: use_vr_mode
  {
    out << "use_vr_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.use_vr_mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SwitchControlModeVR_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: use_vr_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_vr_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.use_vr_mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SwitchControlModeVR_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace teleoperation_msg_ros2

namespace rosidl_generator_traits
{

[[deprecated("use teleoperation_msg_ros2::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const teleoperation_msg_ros2::srv::SwitchControlModeVR_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleoperation_msg_ros2::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleoperation_msg_ros2::srv::to_yaml() instead")]]
inline std::string to_yaml(const teleoperation_msg_ros2::srv::SwitchControlModeVR_Request & msg)
{
  return teleoperation_msg_ros2::srv::to_yaml(msg);
}

template<>
inline const char * data_type<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>()
{
  return "teleoperation_msg_ros2::srv::SwitchControlModeVR_Request";
}

template<>
inline const char * name<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>()
{
  return "teleoperation_msg_ros2/srv/SwitchControlModeVR_Request";
}

template<>
struct has_fixed_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace teleoperation_msg_ros2
{

namespace srv
{

inline void to_flow_style_yaml(
  const SwitchControlModeVR_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SwitchControlModeVR_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SwitchControlModeVR_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace teleoperation_msg_ros2

namespace rosidl_generator_traits
{

[[deprecated("use teleoperation_msg_ros2::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const teleoperation_msg_ros2::srv::SwitchControlModeVR_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleoperation_msg_ros2::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleoperation_msg_ros2::srv::to_yaml() instead")]]
inline std::string to_yaml(const teleoperation_msg_ros2::srv::SwitchControlModeVR_Response & msg)
{
  return teleoperation_msg_ros2::srv::to_yaml(msg);
}

template<>
inline const char * data_type<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>()
{
  return "teleoperation_msg_ros2::srv::SwitchControlModeVR_Response";
}

template<>
inline const char * name<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>()
{
  return "teleoperation_msg_ros2/srv/SwitchControlModeVR_Response";
}

template<>
struct has_fixed_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<teleoperation_msg_ros2::srv::SwitchControlModeVR>()
{
  return "teleoperation_msg_ros2::srv::SwitchControlModeVR";
}

template<>
inline const char * name<teleoperation_msg_ros2::srv::SwitchControlModeVR>()
{
  return "teleoperation_msg_ros2/srv/SwitchControlModeVR";
}

template<>
struct has_fixed_size<teleoperation_msg_ros2::srv::SwitchControlModeVR>
  : std::integral_constant<
    bool,
    has_fixed_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>::value &&
    has_fixed_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>::value
  >
{
};

template<>
struct has_bounded_size<teleoperation_msg_ros2::srv::SwitchControlModeVR>
  : std::integral_constant<
    bool,
    has_bounded_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>::value &&
    has_bounded_size<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>::value
  >
{
};

template<>
struct is_service<teleoperation_msg_ros2::srv::SwitchControlModeVR>
  : std::true_type
{
};

template<>
struct is_service_request<teleoperation_msg_ros2::srv::SwitchControlModeVR_Request>
  : std::true_type
{
};

template<>
struct is_service_response<teleoperation_msg_ros2::srv::SwitchControlModeVR_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__TRAITS_HPP_
