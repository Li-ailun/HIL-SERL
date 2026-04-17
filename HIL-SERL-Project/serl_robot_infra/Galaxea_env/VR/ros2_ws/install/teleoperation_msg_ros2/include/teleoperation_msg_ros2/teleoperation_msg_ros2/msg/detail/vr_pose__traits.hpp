// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__TRAITS_HPP_
#define TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace teleoperation_msg_ros2
{

namespace msg
{

inline void to_flow_style_yaml(
  const VrPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: power
  {
    out << "power: ";
    rosidl_generator_traits::value_to_yaml(msg.power, out);
    out << ", ";
  }

  // member: head_position
  {
    if (msg.head_position.size() == 0) {
      out << "head_position: []";
    } else {
      out << "head_position: [";
      size_t pending_items = msg.head_position.size();
      for (auto item : msg.head_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: head_quaternion
  {
    if (msg.head_quaternion.size() == 0) {
      out << "head_quaternion: []";
    } else {
      out << "head_quaternion: [";
      size_t pending_items = msg.head_quaternion.size();
      for (auto item : msg.head_quaternion) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: left_position
  {
    if (msg.left_position.size() == 0) {
      out << "left_position: []";
    } else {
      out << "left_position: [";
      size_t pending_items = msg.left_position.size();
      for (auto item : msg.left_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: left_quaternion
  {
    if (msg.left_quaternion.size() == 0) {
      out << "left_quaternion: []";
    } else {
      out << "left_quaternion: [";
      size_t pending_items = msg.left_quaternion.size();
      for (auto item : msg.left_quaternion) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: left_gripper_close
  {
    out << "left_gripper_close: ";
    rosidl_generator_traits::value_to_yaml(msg.left_gripper_close, out);
    out << ", ";
  }

  // member: right_position
  {
    if (msg.right_position.size() == 0) {
      out << "right_position: []";
    } else {
      out << "right_position: [";
      size_t pending_items = msg.right_position.size();
      for (auto item : msg.right_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: right_quaternion
  {
    if (msg.right_quaternion.size() == 0) {
      out << "right_quaternion: []";
    } else {
      out << "right_quaternion: [";
      size_t pending_items = msg.right_quaternion.size();
      for (auto item : msg.right_quaternion) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: right_gripper_close
  {
    out << "right_gripper_close: ";
    rosidl_generator_traits::value_to_yaml(msg.right_gripper_close, out);
    out << ", ";
  }

  // member: left_j4j6_cmd
  {
    if (msg.left_j4j6_cmd.size() == 0) {
      out << "left_j4j6_cmd: []";
    } else {
      out << "left_j4j6_cmd: [";
      size_t pending_items = msg.left_j4j6_cmd.size();
      for (auto item : msg.left_j4j6_cmd) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: right_j4j6_cmd
  {
    if (msg.right_j4j6_cmd.size() == 0) {
      out << "right_j4j6_cmd: []";
    } else {
      out << "right_j4j6_cmd: [";
      size_t pending_items = msg.right_j4j6_cmd.size();
      for (auto item : msg.right_j4j6_cmd) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: left_disconnect_pressed
  {
    out << "left_disconnect_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.left_disconnect_pressed, out);
    out << ", ";
  }

  // member: right_disconnect_pressed
  {
    out << "right_disconnect_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.right_disconnect_pressed, out);
    out << ", ";
  }

  // member: control_mode
  {
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << ", ";
  }

  // member: manipulation_mode
  {
    out << "manipulation_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.manipulation_mode, out);
    out << ", ";
  }

  // member: waist_right
  {
    out << "waist_right: ";
    rosidl_generator_traits::value_to_yaml(msg.waist_right, out);
    out << ", ";
  }

  // member: waist_left
  {
    out << "waist_left: ";
    rosidl_generator_traits::value_to_yaml(msg.waist_left, out);
    out << ", ";
  }

  // member: tilt_forward
  {
    out << "tilt_forward: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_forward, out);
    out << ", ";
  }

  // member: tilt_backward
  {
    out << "tilt_backward: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_backward, out);
    out << ", ";
  }

  // member: torso_up
  {
    out << "torso_up: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_up, out);
    out << ", ";
  }

  // member: torso_down
  {
    out << "torso_down: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_down, out);
    out << ", ";
  }

  // member: torso_forward
  {
    out << "torso_forward: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_forward, out);
    out << ", ";
  }

  // member: torso_backward
  {
    out << "torso_backward: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_backward, out);
    out << ", ";
  }

  // member: x_vel
  {
    out << "x_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.x_vel, out);
    out << ", ";
  }

  // member: y_vel
  {
    out << "y_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.y_vel, out);
    out << ", ";
  }

  // member: angular_vel
  {
    out << "angular_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_vel, out);
    out << ", ";
  }

  // member: breakpoint
  {
    out << "breakpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.breakpoint, out);
    out << ", ";
  }

  // member: exception
  {
    out << "exception: ";
    rosidl_generator_traits::value_to_yaml(msg.exception, out);
    out << ", ";
  }

  // member: need_reset_to_init
  {
    out << "need_reset_to_init: ";
    rosidl_generator_traits::value_to_yaml(msg.need_reset_to_init, out);
    out << ", ";
  }

  // member: engage_by_operator
  {
    out << "engage_by_operator: ";
    rosidl_generator_traits::value_to_yaml(msg.engage_by_operator, out);
    out << ", ";
  }

  // member: disengage_by_operator
  {
    out << "disengage_by_operator: ";
    rosidl_generator_traits::value_to_yaml(msg.disengage_by_operator, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VrPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: power
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "power: ";
    rosidl_generator_traits::value_to_yaml(msg.power, out);
    out << "\n";
  }

  // member: head_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.head_position.size() == 0) {
      out << "head_position: []\n";
    } else {
      out << "head_position:\n";
      for (auto item : msg.head_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: head_quaternion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.head_quaternion.size() == 0) {
      out << "head_quaternion: []\n";
    } else {
      out << "head_quaternion:\n";
      for (auto item : msg.head_quaternion) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: left_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.left_position.size() == 0) {
      out << "left_position: []\n";
    } else {
      out << "left_position:\n";
      for (auto item : msg.left_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: left_quaternion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.left_quaternion.size() == 0) {
      out << "left_quaternion: []\n";
    } else {
      out << "left_quaternion:\n";
      for (auto item : msg.left_quaternion) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: left_gripper_close
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_gripper_close: ";
    rosidl_generator_traits::value_to_yaml(msg.left_gripper_close, out);
    out << "\n";
  }

  // member: right_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.right_position.size() == 0) {
      out << "right_position: []\n";
    } else {
      out << "right_position:\n";
      for (auto item : msg.right_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: right_quaternion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.right_quaternion.size() == 0) {
      out << "right_quaternion: []\n";
    } else {
      out << "right_quaternion:\n";
      for (auto item : msg.right_quaternion) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: right_gripper_close
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_gripper_close: ";
    rosidl_generator_traits::value_to_yaml(msg.right_gripper_close, out);
    out << "\n";
  }

  // member: left_j4j6_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.left_j4j6_cmd.size() == 0) {
      out << "left_j4j6_cmd: []\n";
    } else {
      out << "left_j4j6_cmd:\n";
      for (auto item : msg.left_j4j6_cmd) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: right_j4j6_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.right_j4j6_cmd.size() == 0) {
      out << "right_j4j6_cmd: []\n";
    } else {
      out << "right_j4j6_cmd:\n";
      for (auto item : msg.right_j4j6_cmd) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: left_disconnect_pressed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_disconnect_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.left_disconnect_pressed, out);
    out << "\n";
  }

  // member: right_disconnect_pressed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_disconnect_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.right_disconnect_pressed, out);
    out << "\n";
  }

  // member: control_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << "\n";
  }

  // member: manipulation_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manipulation_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.manipulation_mode, out);
    out << "\n";
  }

  // member: waist_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "waist_right: ";
    rosidl_generator_traits::value_to_yaml(msg.waist_right, out);
    out << "\n";
  }

  // member: waist_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "waist_left: ";
    rosidl_generator_traits::value_to_yaml(msg.waist_left, out);
    out << "\n";
  }

  // member: tilt_forward
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_forward: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_forward, out);
    out << "\n";
  }

  // member: tilt_backward
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt_backward: ";
    rosidl_generator_traits::value_to_yaml(msg.tilt_backward, out);
    out << "\n";
  }

  // member: torso_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torso_up: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_up, out);
    out << "\n";
  }

  // member: torso_down
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torso_down: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_down, out);
    out << "\n";
  }

  // member: torso_forward
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torso_forward: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_forward, out);
    out << "\n";
  }

  // member: torso_backward
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "torso_backward: ";
    rosidl_generator_traits::value_to_yaml(msg.torso_backward, out);
    out << "\n";
  }

  // member: x_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.x_vel, out);
    out << "\n";
  }

  // member: y_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.y_vel, out);
    out << "\n";
  }

  // member: angular_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_vel, out);
    out << "\n";
  }

  // member: breakpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "breakpoint: ";
    rosidl_generator_traits::value_to_yaml(msg.breakpoint, out);
    out << "\n";
  }

  // member: exception
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "exception: ";
    rosidl_generator_traits::value_to_yaml(msg.exception, out);
    out << "\n";
  }

  // member: need_reset_to_init
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "need_reset_to_init: ";
    rosidl_generator_traits::value_to_yaml(msg.need_reset_to_init, out);
    out << "\n";
  }

  // member: engage_by_operator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "engage_by_operator: ";
    rosidl_generator_traits::value_to_yaml(msg.engage_by_operator, out);
    out << "\n";
  }

  // member: disengage_by_operator
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "disengage_by_operator: ";
    rosidl_generator_traits::value_to_yaml(msg.disengage_by_operator, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VrPose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace teleoperation_msg_ros2

namespace rosidl_generator_traits
{

[[deprecated("use teleoperation_msg_ros2::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const teleoperation_msg_ros2::msg::VrPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  teleoperation_msg_ros2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use teleoperation_msg_ros2::msg::to_yaml() instead")]]
inline std::string to_yaml(const teleoperation_msg_ros2::msg::VrPose & msg)
{
  return teleoperation_msg_ros2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<teleoperation_msg_ros2::msg::VrPose>()
{
  return "teleoperation_msg_ros2::msg::VrPose";
}

template<>
inline const char * name<teleoperation_msg_ros2::msg::VrPose>()
{
  return "teleoperation_msg_ros2/msg/VrPose";
}

template<>
struct has_fixed_size<teleoperation_msg_ros2::msg::VrPose>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<teleoperation_msg_ros2::msg::VrPose>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<teleoperation_msg_ros2::msg::VrPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TELEOPERATION_MSG_ROS2__MSG__DETAIL__VR_POSE__TRAITS_HPP_
