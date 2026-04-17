// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from teleoperation_msg_ros2:srv/SwitchControlModeVR.idl
// generated code does not contain a copyright notice

#ifndef TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__FUNCTIONS_H_
#define TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "teleoperation_msg_ros2/msg/rosidl_generator_c__visibility_control.h"

#include "teleoperation_msg_ros2/srv/detail/switch_control_mode_vr__struct.h"

/// Initialize srv/SwitchControlModeVR message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request
 * )) before or use
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg);

/// Finalize srv/SwitchControlModeVR message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg);

/// Create srv/SwitchControlModeVR message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__create();

/// Destroy srv/SwitchControlModeVR message.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * msg);

/// Check for srv/SwitchControlModeVR message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * rhs);

/// Copy a srv/SwitchControlModeVR message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request * output);

/// Initialize array of srv/SwitchControlModeVR messages.
/**
 * It allocates the memory for the number of elements and calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array, size_t size);

/// Finalize array of srv/SwitchControlModeVR messages.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array);

/// Create array of srv/SwitchControlModeVR messages.
/**
 * It allocates the memory for the array and calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__create(size_t size);

/// Destroy array of srv/SwitchControlModeVR messages.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * array);

/// Check for srv/SwitchControlModeVR message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * rhs);

/// Copy an array of srv/SwitchControlModeVR messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Request__Sequence * output);

/// Initialize srv/SwitchControlModeVR message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response
 * )) before or use
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg);

/// Finalize srv/SwitchControlModeVR message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg);

/// Create srv/SwitchControlModeVR message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__create();

/// Destroy srv/SwitchControlModeVR message.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * msg);

/// Check for srv/SwitchControlModeVR message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * rhs);

/// Copy a srv/SwitchControlModeVR message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response * output);

/// Initialize array of srv/SwitchControlModeVR messages.
/**
 * It allocates the memory for the number of elements and calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__init(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array, size_t size);

/// Finalize array of srv/SwitchControlModeVR messages.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__fini(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array);

/// Create array of srv/SwitchControlModeVR messages.
/**
 * It allocates the memory for the array and calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence *
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__create(size_t size);

/// Destroy array of srv/SwitchControlModeVR messages.
/**
 * It calls
 * teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
void
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__destroy(teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * array);

/// Check for srv/SwitchControlModeVR message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__are_equal(const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * lhs, const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * rhs);

/// Copy an array of srv/SwitchControlModeVR messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_teleoperation_msg_ros2
bool
teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence__copy(
  const teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * input,
  teleoperation_msg_ros2__srv__SwitchControlModeVR_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TELEOPERATION_MSG_ROS2__SRV__DETAIL__SWITCH_CONTROL_MODE_VR__FUNCTIONS_H_
