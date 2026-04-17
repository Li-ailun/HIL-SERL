// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "teleoperation_msg_ros2/msg/detail/vr_pose__rosidl_typesupport_introspection_c.h"
#include "teleoperation_msg_ros2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__functions.h"
#include "teleoperation_msg_ros2/msg/detail/vr_pose__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `head_position`
// Member `head_quaternion`
// Member `left_position`
// Member `left_quaternion`
// Member `right_position`
// Member `right_quaternion`
// Member `left_j4j6_cmd`
// Member `right_j4j6_cmd`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  teleoperation_msg_ros2__msg__VrPose__init(message_memory);
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_fini_function(void * message_memory)
{
  teleoperation_msg_ros2__msg__VrPose__fini(message_memory);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__head_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__head_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__head_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__head_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__head_quaternion(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_quaternion(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_quaternion(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__head_quaternion(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_quaternion(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__head_quaternion(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_quaternion(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__head_quaternion(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_quaternion(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_quaternion(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_quaternion(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_quaternion(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_quaternion(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_quaternion(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_quaternion(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_quaternion(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_quaternion(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_quaternion(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_quaternion(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_quaternion(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_quaternion(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_quaternion(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_quaternion(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_quaternion(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_j4j6_cmd(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_j4j6_cmd(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_j4j6_cmd(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_j4j6_cmd(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_j4j6_cmd(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_j4j6_cmd(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_j4j6_cmd(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_j4j6_cmd(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_j4j6_cmd(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_j4j6_cmd(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_j4j6_cmd(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_j4j6_cmd(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_j4j6_cmd(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_j4j6_cmd(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_j4j6_cmd(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_j4j6_cmd(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_member_array[32] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "power",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, power),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "head_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, head_position),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__head_position,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_position,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_position,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__head_position,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__head_position,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__head_position  // resize(index) function pointer
  },
  {
    "head_quaternion",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, head_quaternion),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__head_quaternion,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__head_quaternion,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__head_quaternion,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__head_quaternion,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__head_quaternion,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__head_quaternion  // resize(index) function pointer
  },
  {
    "left_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, left_position),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_position,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_position,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_position,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_position,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_position,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_position  // resize(index) function pointer
  },
  {
    "left_quaternion",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, left_quaternion),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_quaternion,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_quaternion,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_quaternion,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_quaternion,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_quaternion,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_quaternion  // resize(index) function pointer
  },
  {
    "left_gripper_close",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, left_gripper_close),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, right_position),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_position,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_position,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_position,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_position,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_position,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_position  // resize(index) function pointer
  },
  {
    "right_quaternion",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, right_quaternion),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_quaternion,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_quaternion,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_quaternion,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_quaternion,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_quaternion,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_quaternion  // resize(index) function pointer
  },
  {
    "right_gripper_close",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, right_gripper_close),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_j4j6_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, left_j4j6_cmd),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__left_j4j6_cmd,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__left_j4j6_cmd,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__left_j4j6_cmd,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__left_j4j6_cmd,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__left_j4j6_cmd,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__left_j4j6_cmd  // resize(index) function pointer
  },
  {
    "right_j4j6_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, right_j4j6_cmd),  // bytes offset in struct
    NULL,  // default value
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__size_function__VrPose__right_j4j6_cmd,  // size() function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_const_function__VrPose__right_j4j6_cmd,  // get_const(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__get_function__VrPose__right_j4j6_cmd,  // get(index) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__fetch_function__VrPose__right_j4j6_cmd,  // fetch(index, &value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__assign_function__VrPose__right_j4j6_cmd,  // assign(index, value) function pointer
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__resize_function__VrPose__right_j4j6_cmd  // resize(index) function pointer
  },
  {
    "left_disconnect_pressed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, left_disconnect_pressed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_disconnect_pressed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, right_disconnect_pressed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "control_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, control_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "manipulation_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, manipulation_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waist_right",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, waist_right),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waist_left",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, waist_left),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tilt_forward",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, tilt_forward),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tilt_backward",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, tilt_backward),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torso_up",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, torso_up),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torso_down",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, torso_down),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torso_forward",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, torso_forward),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "torso_backward",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, torso_backward),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, x_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, y_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angular_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, angular_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "breakpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, breakpoint),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "exception",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, exception),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "need_reset_to_init",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, need_reset_to_init),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "engage_by_operator",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, engage_by_operator),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "disengage_by_operator",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(teleoperation_msg_ros2__msg__VrPose, disengage_by_operator),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_members = {
  "teleoperation_msg_ros2__msg",  // message namespace
  "VrPose",  // message name
  32,  // number of fields
  sizeof(teleoperation_msg_ros2__msg__VrPose),
  teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_member_array,  // message members
  teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_init_function,  // function to initialize message memory (memory has to be allocated)
  teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_type_support_handle = {
  0,
  &teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_teleoperation_msg_ros2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, teleoperation_msg_ros2, msg, VrPose)() {
  teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_type_support_handle.typesupport_identifier) {
    teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &teleoperation_msg_ros2__msg__VrPose__rosidl_typesupport_introspection_c__VrPose_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
