// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice
#include "teleoperation_msg_ros2/msg/detail/vr_pose__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "teleoperation_msg_ros2/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.h"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // head_position, head_quaternion, left_j4j6_cmd, left_position, left_quaternion, right_j4j6_cmd, right_position, right_quaternion
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // head_position, head_quaternion, left_j4j6_cmd, left_position, left_quaternion, right_j4j6_cmd, right_position, right_quaternion
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleoperation_msg_ros2
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleoperation_msg_ros2
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_teleoperation_msg_ros2
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _VrPose__ros_msg_type = teleoperation_msg_ros2__msg__VrPose;

static bool _VrPose__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _VrPose__ros_msg_type * ros_message = static_cast<const _VrPose__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: power
  {
    cdr << (ros_message->power ? true : false);
  }

  // Field name: head_position
  {
    size_t size = ros_message->head_position.size;
    auto array_ptr = ros_message->head_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: head_quaternion
  {
    size_t size = ros_message->head_quaternion.size;
    auto array_ptr = ros_message->head_quaternion.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: left_position
  {
    size_t size = ros_message->left_position.size;
    auto array_ptr = ros_message->left_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: left_quaternion
  {
    size_t size = ros_message->left_quaternion.size;
    auto array_ptr = ros_message->left_quaternion.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: left_gripper_close
  {
    cdr << (ros_message->left_gripper_close ? true : false);
  }

  // Field name: right_position
  {
    size_t size = ros_message->right_position.size;
    auto array_ptr = ros_message->right_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: right_quaternion
  {
    size_t size = ros_message->right_quaternion.size;
    auto array_ptr = ros_message->right_quaternion.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: right_gripper_close
  {
    cdr << (ros_message->right_gripper_close ? true : false);
  }

  // Field name: left_j4j6_cmd
  {
    size_t size = ros_message->left_j4j6_cmd.size;
    auto array_ptr = ros_message->left_j4j6_cmd.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: right_j4j6_cmd
  {
    size_t size = ros_message->right_j4j6_cmd.size;
    auto array_ptr = ros_message->right_j4j6_cmd.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: left_disconnect_pressed
  {
    cdr << (ros_message->left_disconnect_pressed ? true : false);
  }

  // Field name: right_disconnect_pressed
  {
    cdr << (ros_message->right_disconnect_pressed ? true : false);
  }

  // Field name: control_mode
  {
    cdr << ros_message->control_mode;
  }

  // Field name: manipulation_mode
  {
    cdr << ros_message->manipulation_mode;
  }

  // Field name: waist_right
  {
    cdr << (ros_message->waist_right ? true : false);
  }

  // Field name: waist_left
  {
    cdr << (ros_message->waist_left ? true : false);
  }

  // Field name: tilt_forward
  {
    cdr << (ros_message->tilt_forward ? true : false);
  }

  // Field name: tilt_backward
  {
    cdr << (ros_message->tilt_backward ? true : false);
  }

  // Field name: torso_up
  {
    cdr << (ros_message->torso_up ? true : false);
  }

  // Field name: torso_down
  {
    cdr << (ros_message->torso_down ? true : false);
  }

  // Field name: torso_forward
  {
    cdr << (ros_message->torso_forward ? true : false);
  }

  // Field name: torso_backward
  {
    cdr << (ros_message->torso_backward ? true : false);
  }

  // Field name: x_vel
  {
    cdr << ros_message->x_vel;
  }

  // Field name: y_vel
  {
    cdr << ros_message->y_vel;
  }

  // Field name: angular_vel
  {
    cdr << ros_message->angular_vel;
  }

  // Field name: breakpoint
  {
    cdr << (ros_message->breakpoint ? true : false);
  }

  // Field name: exception
  {
    cdr << (ros_message->exception ? true : false);
  }

  // Field name: need_reset_to_init
  {
    cdr << (ros_message->need_reset_to_init ? true : false);
  }

  // Field name: engage_by_operator
  {
    cdr << (ros_message->engage_by_operator ? true : false);
  }

  // Field name: disengage_by_operator
  {
    cdr << (ros_message->disengage_by_operator ? true : false);
  }

  return true;
}

static bool _VrPose__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _VrPose__ros_msg_type * ros_message = static_cast<_VrPose__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: power
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->power = tmp ? true : false;
  }

  // Field name: head_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->head_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->head_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->head_position, size)) {
      fprintf(stderr, "failed to create array for field 'head_position'");
      return false;
    }
    auto array_ptr = ros_message->head_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: head_quaternion
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->head_quaternion.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->head_quaternion);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->head_quaternion, size)) {
      fprintf(stderr, "failed to create array for field 'head_quaternion'");
      return false;
    }
    auto array_ptr = ros_message->head_quaternion.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: left_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->left_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->left_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->left_position, size)) {
      fprintf(stderr, "failed to create array for field 'left_position'");
      return false;
    }
    auto array_ptr = ros_message->left_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: left_quaternion
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->left_quaternion.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->left_quaternion);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->left_quaternion, size)) {
      fprintf(stderr, "failed to create array for field 'left_quaternion'");
      return false;
    }
    auto array_ptr = ros_message->left_quaternion.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: left_gripper_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->left_gripper_close = tmp ? true : false;
  }

  // Field name: right_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->right_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->right_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->right_position, size)) {
      fprintf(stderr, "failed to create array for field 'right_position'");
      return false;
    }
    auto array_ptr = ros_message->right_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: right_quaternion
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->right_quaternion.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->right_quaternion);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->right_quaternion, size)) {
      fprintf(stderr, "failed to create array for field 'right_quaternion'");
      return false;
    }
    auto array_ptr = ros_message->right_quaternion.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: right_gripper_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->right_gripper_close = tmp ? true : false;
  }

  // Field name: left_j4j6_cmd
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->left_j4j6_cmd.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->left_j4j6_cmd);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->left_j4j6_cmd, size)) {
      fprintf(stderr, "failed to create array for field 'left_j4j6_cmd'");
      return false;
    }
    auto array_ptr = ros_message->left_j4j6_cmd.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: right_j4j6_cmd
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->right_j4j6_cmd.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->right_j4j6_cmd);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->right_j4j6_cmd, size)) {
      fprintf(stderr, "failed to create array for field 'right_j4j6_cmd'");
      return false;
    }
    auto array_ptr = ros_message->right_j4j6_cmd.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: left_disconnect_pressed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->left_disconnect_pressed = tmp ? true : false;
  }

  // Field name: right_disconnect_pressed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->right_disconnect_pressed = tmp ? true : false;
  }

  // Field name: control_mode
  {
    cdr >> ros_message->control_mode;
  }

  // Field name: manipulation_mode
  {
    cdr >> ros_message->manipulation_mode;
  }

  // Field name: waist_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->waist_right = tmp ? true : false;
  }

  // Field name: waist_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->waist_left = tmp ? true : false;
  }

  // Field name: tilt_forward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->tilt_forward = tmp ? true : false;
  }

  // Field name: tilt_backward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->tilt_backward = tmp ? true : false;
  }

  // Field name: torso_up
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->torso_up = tmp ? true : false;
  }

  // Field name: torso_down
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->torso_down = tmp ? true : false;
  }

  // Field name: torso_forward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->torso_forward = tmp ? true : false;
  }

  // Field name: torso_backward
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->torso_backward = tmp ? true : false;
  }

  // Field name: x_vel
  {
    cdr >> ros_message->x_vel;
  }

  // Field name: y_vel
  {
    cdr >> ros_message->y_vel;
  }

  // Field name: angular_vel
  {
    cdr >> ros_message->angular_vel;
  }

  // Field name: breakpoint
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->breakpoint = tmp ? true : false;
  }

  // Field name: exception
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->exception = tmp ? true : false;
  }

  // Field name: need_reset_to_init
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->need_reset_to_init = tmp ? true : false;
  }

  // Field name: engage_by_operator
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->engage_by_operator = tmp ? true : false;
  }

  // Field name: disengage_by_operator
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->disengage_by_operator = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleoperation_msg_ros2
size_t get_serialized_size_teleoperation_msg_ros2__msg__VrPose(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _VrPose__ros_msg_type * ros_message = static_cast<const _VrPose__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name power
  {
    size_t item_size = sizeof(ros_message->power);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name head_position
  {
    size_t array_size = ros_message->head_position.size;
    auto array_ptr = ros_message->head_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name head_quaternion
  {
    size_t array_size = ros_message->head_quaternion.size;
    auto array_ptr = ros_message->head_quaternion.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_position
  {
    size_t array_size = ros_message->left_position.size;
    auto array_ptr = ros_message->left_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_quaternion
  {
    size_t array_size = ros_message->left_quaternion.size;
    auto array_ptr = ros_message->left_quaternion.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_gripper_close
  {
    size_t item_size = sizeof(ros_message->left_gripper_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_position
  {
    size_t array_size = ros_message->right_position.size;
    auto array_ptr = ros_message->right_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_quaternion
  {
    size_t array_size = ros_message->right_quaternion.size;
    auto array_ptr = ros_message->right_quaternion.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_gripper_close
  {
    size_t item_size = sizeof(ros_message->right_gripper_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_j4j6_cmd
  {
    size_t array_size = ros_message->left_j4j6_cmd.size;
    auto array_ptr = ros_message->left_j4j6_cmd.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_j4j6_cmd
  {
    size_t array_size = ros_message->right_j4j6_cmd.size;
    auto array_ptr = ros_message->right_j4j6_cmd.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name left_disconnect_pressed
  {
    size_t item_size = sizeof(ros_message->left_disconnect_pressed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name right_disconnect_pressed
  {
    size_t item_size = sizeof(ros_message->right_disconnect_pressed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name control_mode
  {
    size_t item_size = sizeof(ros_message->control_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name manipulation_mode
  {
    size_t item_size = sizeof(ros_message->manipulation_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waist_right
  {
    size_t item_size = sizeof(ros_message->waist_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name waist_left
  {
    size_t item_size = sizeof(ros_message->waist_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tilt_forward
  {
    size_t item_size = sizeof(ros_message->tilt_forward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name tilt_backward
  {
    size_t item_size = sizeof(ros_message->tilt_backward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name torso_up
  {
    size_t item_size = sizeof(ros_message->torso_up);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name torso_down
  {
    size_t item_size = sizeof(ros_message->torso_down);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name torso_forward
  {
    size_t item_size = sizeof(ros_message->torso_forward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name torso_backward
  {
    size_t item_size = sizeof(ros_message->torso_backward);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name x_vel
  {
    size_t item_size = sizeof(ros_message->x_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name y_vel
  {
    size_t item_size = sizeof(ros_message->y_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name angular_vel
  {
    size_t item_size = sizeof(ros_message->angular_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name breakpoint
  {
    size_t item_size = sizeof(ros_message->breakpoint);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name exception
  {
    size_t item_size = sizeof(ros_message->exception);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name need_reset_to_init
  {
    size_t item_size = sizeof(ros_message->need_reset_to_init);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name engage_by_operator
  {
    size_t item_size = sizeof(ros_message->engage_by_operator);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name disengage_by_operator
  {
    size_t item_size = sizeof(ros_message->disengage_by_operator);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _VrPose__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_teleoperation_msg_ros2__msg__VrPose(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_teleoperation_msg_ros2
size_t max_serialized_size_teleoperation_msg_ros2__msg__VrPose(
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

  // member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: power
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: head_position
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
  // member: head_quaternion
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
  // member: left_position
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
  // member: left_quaternion
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
  // member: left_gripper_close
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: right_position
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
  // member: right_quaternion
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
  // member: right_gripper_close
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: left_j4j6_cmd
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
  // member: right_j4j6_cmd
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
  // member: left_disconnect_pressed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: right_disconnect_pressed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: control_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: manipulation_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: waist_right
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: waist_left
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: tilt_forward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: tilt_backward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: torso_up
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: torso_down
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: torso_forward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: torso_backward
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: x_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: y_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: angular_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: breakpoint
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: exception
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: need_reset_to_init
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: engage_by_operator
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: disengage_by_operator
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
    using DataType = teleoperation_msg_ros2__msg__VrPose;
    is_plain =
      (
      offsetof(DataType, disengage_by_operator) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _VrPose__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_teleoperation_msg_ros2__msg__VrPose(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_VrPose = {
  "teleoperation_msg_ros2::msg",
  "VrPose",
  _VrPose__cdr_serialize,
  _VrPose__cdr_deserialize,
  _VrPose__get_serialized_size,
  _VrPose__max_serialized_size
};

static rosidl_message_type_support_t _VrPose__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_VrPose,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, teleoperation_msg_ros2, msg, VrPose)() {
  return &_VrPose__type_support;
}

#if defined(__cplusplus)
}
#endif
