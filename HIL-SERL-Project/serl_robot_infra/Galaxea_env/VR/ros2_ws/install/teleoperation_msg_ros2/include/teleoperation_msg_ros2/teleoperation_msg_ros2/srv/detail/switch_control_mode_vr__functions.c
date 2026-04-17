// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice
#include "teleoperation_msg_ros2/srv/detail/switch_control_mode_vr__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg)
{
  if (!msg) {
    return false;
  }
  // use_vr_mode
  return true;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg)
{
  if (!msg) {
    return;
  }
  // use_vr_mode
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // use_vr_mode
  if (lhs->use_vr_mode != rhs->use_vr_mode) {
    return false;
  }
  return true;
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // use_vr_mode
  output->use_vr_mode = input->use_vr_mode;
  return true;
}

teleoperation_msg_ros2__srv__SwitchControlModeVR_Request *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Request *)allocator.allocate(sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request));
  bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * data = NULL;

  if (size) {
    data = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Request *)allocator.zero_allocate(size, sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(&data[i - 1]);
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
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array)
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
      teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(&array->data[i]);
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

teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence *)allocator.allocate(sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * data =
      (teleoperation_msg_ros2__srv__SwitchControlModeVR_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(msg);
    return false;
  }
  return true;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

teleoperation_msg_ros2__srv__SwitchControlModeVR_Response *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Response *)allocator.allocate(sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response));
  bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * data = NULL;

  if (size) {
    data = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Response *)allocator.zero_allocate(size, sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(&data[i - 1]);
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
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array)
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
      teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(&array->data[i]);
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

teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array = (teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence *)allocator.allocate(sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * data =
      (teleoperation_msg_ros2__srv__SwitchControlModeVR_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
