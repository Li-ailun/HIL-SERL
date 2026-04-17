// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice
#include "teleoperation_msg_ros2/msg/detail/vr_pose__rosidl_typesupport_fastrtps_cpp.hpp"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs


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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: power
  cdr << (ros_message.power ? true : false);
  // Member: head_position
  {
    cdr << ros_message.head_position;
  }
  // Member: head_quaternion
  {
    cdr << ros_message.head_quaternion;
  }
  // Member: left_position
  {
    cdr << ros_message.left_position;
  }
  // Member: left_quaternion
  {
    cdr << ros_message.left_quaternion;
  }
  // Member: left_gripper_close
  cdr << (ros_message.left_gripper_close ? true : false);
  // Member: right_position
  {
    cdr << ros_message.right_position;
  }
  // Member: right_quaternion
  {
    cdr << ros_message.right_quaternion;
  }
  // Member: right_gripper_close
  cdr << (ros_message.right_gripper_close ? true : false);
  // Member: left_j4j6_cmd
  {
    cdr << ros_message.left_j4j6_cmd;
  }
  // Member: right_j4j6_cmd
  {
    cdr << ros_message.right_j4j6_cmd;
  }
  // Member: left_disconnect_pressed
  cdr << (ros_message.left_disconnect_pressed ? true : false);
  // Member: right_disconnect_pressed
  cdr << (ros_message.right_disconnect_pressed ? true : false);
  // Member: control_mode
  cdr << ros_message.control_mode;
  // Member: manipulation_mode
  cdr << ros_message.manipulation_mode;
  // Member: waist_right
  cdr << (ros_message.waist_right ? true : false);
  // Member: waist_left
  cdr << (ros_message.waist_left ? true : false);
  // Member: tilt_forward
  cdr << (ros_message.tilt_forward ? true : false);
  // Member: tilt_backward
  cdr << (ros_message.tilt_backward ? true : false);
  // Member: torso_up
  cdr << (ros_message.torso_up ? true : false);
  // Member: torso_down
  cdr << (ros_message.torso_down ? true : false);
  // Member: torso_forward
  cdr << (ros_message.torso_forward ? true : false);
  // Member: torso_backward
  cdr << (ros_message.torso_backward ? true : false);
  // Member: x_vel
  cdr << ros_message.x_vel;
  // Member: y_vel
  cdr << ros_message.y_vel;
  // Member: angular_vel
  cdr << ros_message.angular_vel;
  // Member: breakpoint
  cdr << (ros_message.breakpoint ? true : false);
  // Member: exception
  cdr << (ros_message.exception ? true : false);
  // Member: need_reset_to_init
  cdr << (ros_message.need_reset_to_init ? true : false);
  // Member: engage_by_operator
  cdr << (ros_message.engage_by_operator ? true : false);
  // Member: disengage_by_operator
  cdr << (ros_message.disengage_by_operator ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  teleoperation_msg_ros2::msg::VrPose & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: power
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.power = tmp ? true : false;
  }

  // Member: head_position
  {
    cdr >> ros_message.head_position;
  }

  // Member: head_quaternion
  {
    cdr >> ros_message.head_quaternion;
  }

  // Member: left_position
  {
    cdr >> ros_message.left_position;
  }

  // Member: left_quaternion
  {
    cdr >> ros_message.left_quaternion;
  }

  // Member: left_gripper_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.left_gripper_close = tmp ? true : false;
  }

  // Member: right_position
  {
    cdr >> ros_message.right_position;
  }

  // Member: right_quaternion
  {
    cdr >> ros_message.right_quaternion;
  }

  // Member: right_gripper_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.right_gripper_close = tmp ? true : false;
  }

  // Member: left_j4j6_cmd
  {
    cdr >> ros_message.left_j4j6_cmd;
  }

  // Member: right_j4j6_cmd
  {
    cdr >> ros_message.right_j4j6_cmd;
  }

  // Member: left_disconnect_pressed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.left_disconnect_pressed = tmp ? true : false;
  }

  // Member: right_disconnect_pressed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.right_disconnect_pressed = tmp ? true : false;
  }

  // Member: control_mode
  cdr >> ros_message.control_mode;

  // Member: manipulation_mode
  cdr >> ros_message.manipulation_mode;

  // Member: waist_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.waist_right = tmp ? true : false;
  }

  // Member: waist_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.waist_left = tmp ? true : false;
  }

  // Member: tilt_forward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.tilt_forward = tmp ? true : false;
  }

  // Member: tilt_backward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.tilt_backward = tmp ? true : false;
  }

  // Member: torso_up
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.torso_up = tmp ? true : false;
  }

  // Member: torso_down
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.torso_down = tmp ? true : false;
  }

  // Member: torso_forward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.torso_forward = tmp ? true : false;
  }

  // Member: torso_backward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.torso_backward = tmp ? true : false;
  }

  // Member: x_vel
  cdr >> ros_message.x_vel;

  // Member: y_vel
  cdr >> ros_message.y_vel;

  // Member: angular_vel
  cdr >> ros_message.angular_vel;

  // Member: breakpoint
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.breakpoint = tmp ? true : false;
  }

  // Member: exception
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.exception = tmp ? true : false;
  }

  // Member: need_reset_to_init
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.need_reset_to_init = tmp ? true : false;
  }

  // Member: engage_by_operator
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.engage_by_operator = tmp ? true : false;
  }

  // Member: disengage_by_operator
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.disengage_by_operator = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
get_serialized_size(
  const teleoperation_msg_ros2::msg::VrPose & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: power
  {
    size_t item_size = sizeof(ros_message.power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: head_position
  {
    size_t array_size = ros_message.head_position.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.head_position[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: head_quaternion
  {
    size_t array_size = ros_message.head_quaternion.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.head_quaternion[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_position
  {
    size_t array_size = ros_message.left_position.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.left_position[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_quaternion
  {
    size_t array_size = ros_message.left_quaternion.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.left_quaternion[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_gripper_close
  {
    size_t item_size = sizeof(ros_message.left_gripper_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_position
  {
    size_t array_size = ros_message.right_position.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.right_position[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_quaternion
  {
    size_t array_size = ros_message.right_quaternion.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.right_quaternion[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_gripper_close
  {
    size_t item_size = sizeof(ros_message.right_gripper_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_j4j6_cmd
  {
    size_t array_size = ros_message.left_j4j6_cmd.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.left_j4j6_cmd[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_j4j6_cmd
  {
    size_t array_size = ros_message.right_j4j6_cmd.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.right_j4j6_cmd[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: left_disconnect_pressed
  {
    size_t item_size = sizeof(ros_message.left_disconnect_pressed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: right_disconnect_pressed
  {
    size_t item_size = sizeof(ros_message.right_disconnect_pressed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: control_mode
  {
    size_t item_size = sizeof(ros_message.control_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: manipulation_mode
  {
    size_t item_size = sizeof(ros_message.manipulation_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: waist_right
  {
    size_t item_size = sizeof(ros_message.waist_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: waist_left
  {
    size_t item_size = sizeof(ros_message.waist_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: tilt_forward
  {
    size_t item_size = sizeof(ros_message.tilt_forward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: tilt_backward
  {
    size_t item_size = sizeof(ros_message.tilt_backward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: torso_up
  {
    size_t item_size = sizeof(ros_message.torso_up);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: torso_down
  {
    size_t item_size = sizeof(ros_message.torso_down);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: torso_forward
  {
    size_t item_size = sizeof(ros_message.torso_forward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: torso_backward
  {
    size_t item_size = sizeof(ros_message.torso_backward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: x_vel
  {
    size_t item_size = sizeof(ros_message.x_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: y_vel
  {
    size_t item_size = sizeof(ros_message.y_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: angular_vel
  {
    size_t item_size = sizeof(ros_message.angular_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: breakpoint
  {
    size_t item_size = sizeof(ros_message.breakpoint);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: exception
  {
    size_t item_size = sizeof(ros_message.exception);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: need_reset_to_init
  {
    size_t item_size = sizeof(ros_message.need_reset_to_init);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: engage_by_operator
  {
    size_t item_size = sizeof(ros_message.engage_by_operator);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: disengage_by_operator
  {
    size_t item_size = sizeof(ros_message.disengage_by_operator);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_teleoperation_msg_ros2
max_serialized_size_VrPose(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: power
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: head_position
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: head_quaternion
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: left_position
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: left_quaternion
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: left_gripper_close
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: right_position
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: right_quaternion
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: right_gripper_close
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: left_j4j6_cmd
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: right_j4j6_cmd
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: left_disconnect_pressed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: right_disconnect_pressed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: control_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: manipulation_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: waist_right
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: waist_left
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: tilt_forward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: tilt_backward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: torso_up
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: torso_down
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: torso_forward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: torso_backward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: x_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: y_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: angular_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: breakpoint
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: exception
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: need_reset_to_init
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: engage_by_operator
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: disengage_by_operator
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = teleoperation_msg_ros2::msg::VrPose;
    is_plain =
      (
      offsetof(DataType, disengage_by_operator) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _VrPose__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const teleoperation_msg_ros2::msg::VrPose *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _VrPose__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<teleoperation_msg_ros2::msg::VrPose *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _VrPose__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const teleoperation_msg_ros2::msg::VrPose *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _VrPose__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_VrPose(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _VrPose__callbacks = {
  "teleoperation_msg_ros2::msg",
  "VrPose",
  _VrPose__cdr_serialize,
  _VrPose__cdr_deserialize,
  _VrPose__get_serialized_size,
  _VrPose__max_serialized_size
};

static rosidl_message_type_support_t _VrPose__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_VrPose__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace teleoperation_msg_ros2

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_teleoperation_msg_ros2
const rosidl_message_type_support_t *
get_message_type_support_handle<teleoperation_msg_ros2::msg::VrPose>()
{
  return &teleoperation_msg_ros2::msg::typesupport_fastrtps_cpp::_VrPose__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, teleoperation_msg_ros2, msg, VrPose)() {
  return &teleoperation_msg_ros2::msg::typesupport_fastrtps_cpp::_VrPose__handle;
}

#ifdef __cplusplus
}
#endif
