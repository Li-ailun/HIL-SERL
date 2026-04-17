// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleoperation_msg_ros2:msg/VrPose.idl
// generated code does not contain a copyright notice
#include "teleoperation_msg_ros2/msg/detail/vr_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `head_position`
// Member `head_quaternion`
// Member `left_position`
// Member `left_quaternion`
// Member `right_position`
// Member `right_quaternion`
// Member `left_j4j6_cmd`
// Member `right_j4j6_cmd`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
teleoperation_msg_ros2__msg__VrPose__init(teleoperation_msg_ros2__msg__VrPose * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // power
  // head_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->head_position, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // head_quaternion
  if (!rosidl_runtime_c__float__Sequence__init(&msg->head_quaternion, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // left_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->left_position, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // left_quaternion
  if (!rosidl_runtime_c__float__Sequence__init(&msg->left_quaternion, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // left_gripper_close
  // right_position
  if (!rosidl_runtime_c__float__Sequence__init(&msg->right_position, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // right_quaternion
  if (!rosidl_runtime_c__float__Sequence__init(&msg->right_quaternion, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // right_gripper_close
  // left_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__init(&msg->left_j4j6_cmd, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // right_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__init(&msg->right_j4j6_cmd, 0)) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
    return false;
  }
  // left_disconnect_pressed
  // right_disconnect_pressed
  // control_mode
  // manipulation_mode
  // waist_right
  // waist_left
  // tilt_forward
  // tilt_backward
  // torso_up
  // torso_down
  // torso_forward
  // torso_backward
  // x_vel
  // y_vel
  // angular_vel
  // breakpoint
  // exception
  // need_reset_to_init
  // engage_by_operator
  // disengage_by_operator
  return true;
}

void
teleoperation_msg_ros2__msg__VrPose__fini(teleoperation_msg_ros2__msg__VrPose * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // power
  // head_position
  rosidl_runtime_c__float__Sequence__fini(&msg->head_position);
  // head_quaternion
  rosidl_runtime_c__float__Sequence__fini(&msg->head_quaternion);
  // left_position
  rosidl_runtime_c__float__Sequence__fini(&msg->left_position);
  // left_quaternion
  rosidl_runtime_c__float__Sequence__fini(&msg->left_quaternion);
  // left_gripper_close
  // right_position
  rosidl_runtime_c__float__Sequence__fini(&msg->right_position);
  // right_quaternion
  rosidl_runtime_c__float__Sequence__fini(&msg->right_quaternion);
  // right_gripper_close
  // left_j4j6_cmd
  rosidl_runtime_c__float__Sequence__fini(&msg->left_j4j6_cmd);
  // right_j4j6_cmd
  rosidl_runtime_c__float__Sequence__fini(&msg->right_j4j6_cmd);
  // left_disconnect_pressed
  // right_disconnect_pressed
  // control_mode
  // manipulation_mode
  // waist_right
  // waist_left
  // tilt_forward
  // tilt_backward
  // torso_up
  // torso_down
  // torso_forward
  // torso_backward
  // x_vel
  // y_vel
  // angular_vel
  // breakpoint
  // exception
  // need_reset_to_init
  // engage_by_operator
  // disengage_by_operator
}

bool
teleoperation_msg_ros2__msg__VrPose__are_equal(const teleoperation_msg_ros2__msg__VrPose * lhs, const teleoperation_msg_ros2__msg__VrPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // power
  if (lhs->power != rhs->power) {
    return false;
  }
  // head_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->head_position), &(rhs->head_position)))
  {
    return false;
  }
  // head_quaternion
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->head_quaternion), &(rhs->head_quaternion)))
  {
    return false;
  }
  // left_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->left_position), &(rhs->left_position)))
  {
    return false;
  }
  // left_quaternion
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->left_quaternion), &(rhs->left_quaternion)))
  {
    return false;
  }
  // left_gripper_close
  if (lhs->left_gripper_close != rhs->left_gripper_close) {
    return false;
  }
  // right_position
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->right_position), &(rhs->right_position)))
  {
    return false;
  }
  // right_quaternion
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->right_quaternion), &(rhs->right_quaternion)))
  {
    return false;
  }
  // right_gripper_close
  if (lhs->right_gripper_close != rhs->right_gripper_close) {
    return false;
  }
  // left_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->left_j4j6_cmd), &(rhs->left_j4j6_cmd)))
  {
    return false;
  }
  // right_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->right_j4j6_cmd), &(rhs->right_j4j6_cmd)))
  {
    return false;
  }
  // left_disconnect_pressed
  if (lhs->left_disconnect_pressed != rhs->left_disconnect_pressed) {
    return false;
  }
  // right_disconnect_pressed
  if (lhs->right_disconnect_pressed != rhs->right_disconnect_pressed) {
    return false;
  }
  // control_mode
  if (lhs->control_mode != rhs->control_mode) {
    return false;
  }
  // manipulation_mode
  if (lhs->manipulation_mode != rhs->manipulation_mode) {
    return false;
  }
  // waist_right
  if (lhs->waist_right != rhs->waist_right) {
    return false;
  }
  // waist_left
  if (lhs->waist_left != rhs->waist_left) {
    return false;
  }
  // tilt_forward
  if (lhs->tilt_forward != rhs->tilt_forward) {
    return false;
  }
  // tilt_backward
  if (lhs->tilt_backward != rhs->tilt_backward) {
    return false;
  }
  // torso_up
  if (lhs->torso_up != rhs->torso_up) {
    return false;
  }
  // torso_down
  if (lhs->torso_down != rhs->torso_down) {
    return false;
  }
  // torso_forward
  if (lhs->torso_forward != rhs->torso_forward) {
    return false;
  }
  // torso_backward
  if (lhs->torso_backward != rhs->torso_backward) {
    return false;
  }
  // x_vel
  if (lhs->x_vel != rhs->x_vel) {
    return false;
  }
  // y_vel
  if (lhs->y_vel != rhs->y_vel) {
    return false;
  }
  // angular_vel
  if (lhs->angular_vel != rhs->angular_vel) {
    return false;
  }
  // breakpoint
  if (lhs->breakpoint != rhs->breakpoint) {
    return false;
  }
  // exception
  if (lhs->exception != rhs->exception) {
    return false;
  }
  // need_reset_to_init
  if (lhs->need_reset_to_init != rhs->need_reset_to_init) {
    return false;
  }
  // engage_by_operator
  if (lhs->engage_by_operator != rhs->engage_by_operator) {
    return false;
  }
  // disengage_by_operator
  if (lhs->disengage_by_operator != rhs->disengage_by_operator) {
    return false;
  }
  return true;
}

bool
teleoperation_msg_ros2__msg__VrPose__copy(
  const teleoperation_msg_ros2__msg__VrPose * input,
  teleoperation_msg_ros2__msg__VrPose * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // power
  output->power = input->power;
  // head_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->head_position), &(output->head_position)))
  {
    return false;
  }
  // head_quaternion
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->head_quaternion), &(output->head_quaternion)))
  {
    return false;
  }
  // left_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->left_position), &(output->left_position)))
  {
    return false;
  }
  // left_quaternion
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->left_quaternion), &(output->left_quaternion)))
  {
    return false;
  }
  // left_gripper_close
  output->left_gripper_close = input->left_gripper_close;
  // right_position
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->right_position), &(output->right_position)))
  {
    return false;
  }
  // right_quaternion
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->right_quaternion), &(output->right_quaternion)))
  {
    return false;
  }
  // right_gripper_close
  output->right_gripper_close = input->right_gripper_close;
  // left_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->left_j4j6_cmd), &(output->left_j4j6_cmd)))
  {
    return false;
  }
  // right_j4j6_cmd
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->right_j4j6_cmd), &(output->right_j4j6_cmd)))
  {
    return false;
  }
  // left_disconnect_pressed
  output->left_disconnect_pressed = input->left_disconnect_pressed;
  // right_disconnect_pressed
  output->right_disconnect_pressed = input->right_disconnect_pressed;
  // control_mode
  output->control_mode = input->control_mode;
  // manipulation_mode
  output->manipulation_mode = input->manipulation_mode;
  // waist_right
  output->waist_right = input->waist_right;
  // waist_left
  output->waist_left = input->waist_left;
  // tilt_forward
  output->tilt_forward = input->tilt_forward;
  // tilt_backward
  output->tilt_backward = input->tilt_backward;
  // torso_up
  output->torso_up = input->torso_up;
  // torso_down
  output->torso_down = input->torso_down;
  // torso_forward
  output->torso_forward = input->torso_forward;
  // torso_backward
  output->torso_backward = input->torso_backward;
  // x_vel
  output->x_vel = input->x_vel;
  // y_vel
  output->y_vel = input->y_vel;
  // angular_vel
  output->angular_vel = input->angular_vel;
  // breakpoint
  output->breakpoint = input->breakpoint;
  // exception
  output->exception = input->exception;
  // need_reset_to_init
  output->need_reset_to_init = input->need_reset_to_init;
  // engage_by_operator
  output->engage_by_operator = input->engage_by_operator;
  // disengage_by_operator
  output->disengage_by_operator = input->disengage_by_operator;
  return true;
}

teleoperation_msg_ros2__msg__VrPose *
teleoperation_msg_ros2__msg__VrPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__msg__VrPose * msg = (teleoperation_msg_ros2__msg__VrPose *)allocator.allocate(sizeof(teleoperation_msg_ros2__msg__VrPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleoperation_msg_ros2__msg__VrPose));
  bool success = teleoperation_msg_ros2__msg__VrPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleoperation_msg_ros2__msg__VrPose__destroy(teleoperation_msg_ros2__msg__VrPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleoperation_msg_ros2__msg__VrPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleoperation_msg_ros2__msg__VrPose__Sequence__init(teleoperation_msg_ros2__msg__VrPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__msg__VrPose * data = NULL;

  if (size) {
    data = (teleoperation_msg_ros2__msg__VrPose *)allocator.zero_allocate(size, sizeof(teleoperation_msg_ros2__msg__VrPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleoperation_msg_ros2__msg__VrPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleoperation_msg_ros2__msg__VrPose__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
teleoperation_msg_ros2__msg__VrPose__Sequence__fini(teleoperation_msg_ros2__msg__VrPose__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      teleoperation_msg_ros2__msg__VrPose__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

teleoperation_msg_ros2__msg__VrPose__Sequence *
teleoperation_msg_ros2__msg__VrPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__msg__VrPose__Sequence * array = (teleoperation_msg_ros2__msg__VrPose__Sequence *)allocator.allocate(sizeof(teleoperation_msg_ros2__msg__VrPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleoperation_msg_ros2__msg__VrPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleoperation_msg_ros2__msg__VrPose__Sequence__destroy(teleoperation_msg_ros2__msg__VrPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleoperation_msg_ros2__msg__VrPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleoperation_msg_ros2__msg__VrPose__Sequence__are_equal(const teleoperation_msg_ros2__msg__VrPose__Sequence * lhs, const teleoperation_msg_ros2__msg__VrPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleoperation_msg_ros2__msg__VrPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleoperation_msg_ros2__msg__VrPose__Sequence__copy(
  const teleoperation_msg_ros2__msg__VrPose__Sequence * input,
  teleoperation_msg_ros2__msg__VrPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleoperation_msg_ros2__msg__VrPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleoperation_msg_ros2__msg__VrPose * data =
      (teleoperation_msg_ros2__msg__VrPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleoperation_msg_ros2__msg__VrPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleoperation_msg_ros2__msg__VrPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleoperation_msg_ros2__msg__VrPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
