# generated from rosidl_generator_py/resource/_idl.py.em
# with input from teleoperation_msg_ros2:msg/VrPose.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'head_position'
# Member 'head_quaternion'
# Member 'left_position'
# Member 'left_quaternion'
# Member 'right_position'
# Member 'right_quaternion'
# Member 'left_j4j6_cmd'
# Member 'right_j4j6_cmd'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VrPose(type):
    """Metaclass of message 'VrPose'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('teleoperation_msg_ros2')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'teleoperation_msg_ros2.msg.VrPose')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vr_pose
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vr_pose
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vr_pose
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vr_pose
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vr_pose

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VrPose(metaclass=Metaclass_VrPose):
    """Message class 'VrPose'."""

    __slots__ = [
        '_header',
        '_power',
        '_head_position',
        '_head_quaternion',
        '_left_position',
        '_left_quaternion',
        '_left_gripper_close',
        '_right_position',
        '_right_quaternion',
        '_right_gripper_close',
        '_left_j4j6_cmd',
        '_right_j4j6_cmd',
        '_left_disconnect_pressed',
        '_right_disconnect_pressed',
        '_control_mode',
        '_manipulation_mode',
        '_waist_right',
        '_waist_left',
        '_tilt_forward',
        '_tilt_backward',
        '_torso_up',
        '_torso_down',
        '_torso_forward',
        '_torso_backward',
        '_x_vel',
        '_y_vel',
        '_angular_vel',
        '_breakpoint',
        '_exception',
        '_need_reset_to_init',
        '_engage_by_operator',
        '_disengage_by_operator',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'power': 'boolean',
        'head_position': 'sequence<float>',
        'head_quaternion': 'sequence<float>',
        'left_position': 'sequence<float>',
        'left_quaternion': 'sequence<float>',
        'left_gripper_close': 'boolean',
        'right_position': 'sequence<float>',
        'right_quaternion': 'sequence<float>',
        'right_gripper_close': 'boolean',
        'left_j4j6_cmd': 'sequence<float>',
        'right_j4j6_cmd': 'sequence<float>',
        'left_disconnect_pressed': 'boolean',
        'right_disconnect_pressed': 'boolean',
        'control_mode': 'int8',
        'manipulation_mode': 'int8',
        'waist_right': 'boolean',
        'waist_left': 'boolean',
        'tilt_forward': 'boolean',
        'tilt_backward': 'boolean',
        'torso_up': 'boolean',
        'torso_down': 'boolean',
        'torso_forward': 'boolean',
        'torso_backward': 'boolean',
        'x_vel': 'float',
        'y_vel': 'float',
        'angular_vel': 'float',
        'breakpoint': 'boolean',
        'exception': 'boolean',
        'need_reset_to_init': 'boolean',
        'engage_by_operator': 'boolean',
        'disengage_by_operator': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.power = kwargs.get('power', bool())
        self.head_position = array.array('f', kwargs.get('head_position', []))
        self.head_quaternion = array.array('f', kwargs.get('head_quaternion', []))
        self.left_position = array.array('f', kwargs.get('left_position', []))
        self.left_quaternion = array.array('f', kwargs.get('left_quaternion', []))
        self.left_gripper_close = kwargs.get('left_gripper_close', bool())
        self.right_position = array.array('f', kwargs.get('right_position', []))
        self.right_quaternion = array.array('f', kwargs.get('right_quaternion', []))
        self.right_gripper_close = kwargs.get('right_gripper_close', bool())
        self.left_j4j6_cmd = array.array('f', kwargs.get('left_j4j6_cmd', []))
        self.right_j4j6_cmd = array.array('f', kwargs.get('right_j4j6_cmd', []))
        self.left_disconnect_pressed = kwargs.get('left_disconnect_pressed', bool())
        self.right_disconnect_pressed = kwargs.get('right_disconnect_pressed', bool())
        self.control_mode = kwargs.get('control_mode', int())
        self.manipulation_mode = kwargs.get('manipulation_mode', int())
        self.waist_right = kwargs.get('waist_right', bool())
        self.waist_left = kwargs.get('waist_left', bool())
        self.tilt_forward = kwargs.get('tilt_forward', bool())
        self.tilt_backward = kwargs.get('tilt_backward', bool())
        self.torso_up = kwargs.get('torso_up', bool())
        self.torso_down = kwargs.get('torso_down', bool())
        self.torso_forward = kwargs.get('torso_forward', bool())
        self.torso_backward = kwargs.get('torso_backward', bool())
        self.x_vel = kwargs.get('x_vel', float())
        self.y_vel = kwargs.get('y_vel', float())
        self.angular_vel = kwargs.get('angular_vel', float())
        self.breakpoint = kwargs.get('breakpoint', bool())
        self.exception = kwargs.get('exception', bool())
        self.need_reset_to_init = kwargs.get('need_reset_to_init', bool())
        self.engage_by_operator = kwargs.get('engage_by_operator', bool())
        self.disengage_by_operator = kwargs.get('disengage_by_operator', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.power != other.power:
            return False
        if self.head_position != other.head_position:
            return False
        if self.head_quaternion != other.head_quaternion:
            return False
        if self.left_position != other.left_position:
            return False
        if self.left_quaternion != other.left_quaternion:
            return False
        if self.left_gripper_close != other.left_gripper_close:
            return False
        if self.right_position != other.right_position:
            return False
        if self.right_quaternion != other.right_quaternion:
            return False
        if self.right_gripper_close != other.right_gripper_close:
            return False
        if self.left_j4j6_cmd != other.left_j4j6_cmd:
            return False
        if self.right_j4j6_cmd != other.right_j4j6_cmd:
            return False
        if self.left_disconnect_pressed != other.left_disconnect_pressed:
            return False
        if self.right_disconnect_pressed != other.right_disconnect_pressed:
            return False
        if self.control_mode != other.control_mode:
            return False
        if self.manipulation_mode != other.manipulation_mode:
            return False
        if self.waist_right != other.waist_right:
            return False
        if self.waist_left != other.waist_left:
            return False
        if self.tilt_forward != other.tilt_forward:
            return False
        if self.tilt_backward != other.tilt_backward:
            return False
        if self.torso_up != other.torso_up:
            return False
        if self.torso_down != other.torso_down:
            return False
        if self.torso_forward != other.torso_forward:
            return False
        if self.torso_backward != other.torso_backward:
            return False
        if self.x_vel != other.x_vel:
            return False
        if self.y_vel != other.y_vel:
            return False
        if self.angular_vel != other.angular_vel:
            return False
        if self.breakpoint != other.breakpoint:
            return False
        if self.exception != other.exception:
            return False
        if self.need_reset_to_init != other.need_reset_to_init:
            return False
        if self.engage_by_operator != other.engage_by_operator:
            return False
        if self.disengage_by_operator != other.disengage_by_operator:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def power(self):
        """Message field 'power'."""
        return self._power

    @power.setter
    def power(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'power' field must be of type 'bool'"
        self._power = value

    @builtins.property
    def head_position(self):
        """Message field 'head_position'."""
        return self._head_position

    @head_position.setter
    def head_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'head_position' array.array() must have the type code of 'f'"
            self._head_position = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'head_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._head_position = array.array('f', value)

    @builtins.property
    def head_quaternion(self):
        """Message field 'head_quaternion'."""
        return self._head_quaternion

    @head_quaternion.setter
    def head_quaternion(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'head_quaternion' array.array() must have the type code of 'f'"
            self._head_quaternion = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'head_quaternion' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._head_quaternion = array.array('f', value)

    @builtins.property
    def left_position(self):
        """Message field 'left_position'."""
        return self._left_position

    @left_position.setter
    def left_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'left_position' array.array() must have the type code of 'f'"
            self._left_position = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'left_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._left_position = array.array('f', value)

    @builtins.property
    def left_quaternion(self):
        """Message field 'left_quaternion'."""
        return self._left_quaternion

    @left_quaternion.setter
    def left_quaternion(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'left_quaternion' array.array() must have the type code of 'f'"
            self._left_quaternion = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'left_quaternion' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._left_quaternion = array.array('f', value)

    @builtins.property
    def left_gripper_close(self):
        """Message field 'left_gripper_close'."""
        return self._left_gripper_close

    @left_gripper_close.setter
    def left_gripper_close(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'left_gripper_close' field must be of type 'bool'"
        self._left_gripper_close = value

    @builtins.property
    def right_position(self):
        """Message field 'right_position'."""
        return self._right_position

    @right_position.setter
    def right_position(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'right_position' array.array() must have the type code of 'f'"
            self._right_position = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'right_position' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._right_position = array.array('f', value)

    @builtins.property
    def right_quaternion(self):
        """Message field 'right_quaternion'."""
        return self._right_quaternion

    @right_quaternion.setter
    def right_quaternion(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'right_quaternion' array.array() must have the type code of 'f'"
            self._right_quaternion = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'right_quaternion' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._right_quaternion = array.array('f', value)

    @builtins.property
    def right_gripper_close(self):
        """Message field 'right_gripper_close'."""
        return self._right_gripper_close

    @right_gripper_close.setter
    def right_gripper_close(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'right_gripper_close' field must be of type 'bool'"
        self._right_gripper_close = value

    @builtins.property
    def left_j4j6_cmd(self):
        """Message field 'left_j4j6_cmd'."""
        return self._left_j4j6_cmd

    @left_j4j6_cmd.setter
    def left_j4j6_cmd(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'left_j4j6_cmd' array.array() must have the type code of 'f'"
            self._left_j4j6_cmd = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'left_j4j6_cmd' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._left_j4j6_cmd = array.array('f', value)

    @builtins.property
    def right_j4j6_cmd(self):
        """Message field 'right_j4j6_cmd'."""
        return self._right_j4j6_cmd

    @right_j4j6_cmd.setter
    def right_j4j6_cmd(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'right_j4j6_cmd' array.array() must have the type code of 'f'"
            self._right_j4j6_cmd = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'right_j4j6_cmd' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._right_j4j6_cmd = array.array('f', value)

    @builtins.property
    def left_disconnect_pressed(self):
        """Message field 'left_disconnect_pressed'."""
        return self._left_disconnect_pressed

    @left_disconnect_pressed.setter
    def left_disconnect_pressed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'left_disconnect_pressed' field must be of type 'bool'"
        self._left_disconnect_pressed = value

    @builtins.property
    def right_disconnect_pressed(self):
        """Message field 'right_disconnect_pressed'."""
        return self._right_disconnect_pressed

    @right_disconnect_pressed.setter
    def right_disconnect_pressed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'right_disconnect_pressed' field must be of type 'bool'"
        self._right_disconnect_pressed = value

    @builtins.property
    def control_mode(self):
        """Message field 'control_mode'."""
        return self._control_mode

    @control_mode.setter
    def control_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'control_mode' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'control_mode' field must be an integer in [-128, 127]"
        self._control_mode = value

    @builtins.property
    def manipulation_mode(self):
        """Message field 'manipulation_mode'."""
        return self._manipulation_mode

    @manipulation_mode.setter
    def manipulation_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'manipulation_mode' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'manipulation_mode' field must be an integer in [-128, 127]"
        self._manipulation_mode = value

    @builtins.property
    def waist_right(self):
        """Message field 'waist_right'."""
        return self._waist_right

    @waist_right.setter
    def waist_right(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'waist_right' field must be of type 'bool'"
        self._waist_right = value

    @builtins.property
    def waist_left(self):
        """Message field 'waist_left'."""
        return self._waist_left

    @waist_left.setter
    def waist_left(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'waist_left' field must be of type 'bool'"
        self._waist_left = value

    @builtins.property
    def tilt_forward(self):
        """Message field 'tilt_forward'."""
        return self._tilt_forward

    @tilt_forward.setter
    def tilt_forward(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'tilt_forward' field must be of type 'bool'"
        self._tilt_forward = value

    @builtins.property
    def tilt_backward(self):
        """Message field 'tilt_backward'."""
        return self._tilt_backward

    @tilt_backward.setter
    def tilt_backward(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'tilt_backward' field must be of type 'bool'"
        self._tilt_backward = value

    @builtins.property
    def torso_up(self):
        """Message field 'torso_up'."""
        return self._torso_up

    @torso_up.setter
    def torso_up(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'torso_up' field must be of type 'bool'"
        self._torso_up = value

    @builtins.property
    def torso_down(self):
        """Message field 'torso_down'."""
        return self._torso_down

    @torso_down.setter
    def torso_down(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'torso_down' field must be of type 'bool'"
        self._torso_down = value

    @builtins.property
    def torso_forward(self):
        """Message field 'torso_forward'."""
        return self._torso_forward

    @torso_forward.setter
    def torso_forward(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'torso_forward' field must be of type 'bool'"
        self._torso_forward = value

    @builtins.property
    def torso_backward(self):
        """Message field 'torso_backward'."""
        return self._torso_backward

    @torso_backward.setter
    def torso_backward(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'torso_backward' field must be of type 'bool'"
        self._torso_backward = value

    @builtins.property
    def x_vel(self):
        """Message field 'x_vel'."""
        return self._x_vel

    @x_vel.setter
    def x_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'x_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._x_vel = value

    @builtins.property
    def y_vel(self):
        """Message field 'y_vel'."""
        return self._y_vel

    @y_vel.setter
    def y_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'y_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._y_vel = value

    @builtins.property
    def angular_vel(self):
        """Message field 'angular_vel'."""
        return self._angular_vel

    @angular_vel.setter
    def angular_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'angular_vel' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'angular_vel' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._angular_vel = value

    @builtins.property  # noqa: A003
    def breakpoint(self):  # noqa: A003
        """Message field 'breakpoint'."""
        return self._breakpoint

    @breakpoint.setter  # noqa: A003
    def breakpoint(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'breakpoint' field must be of type 'bool'"
        self._breakpoint = value

    @builtins.property
    def exception(self):
        """Message field 'exception'."""
        return self._exception

    @exception.setter
    def exception(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'exception' field must be of type 'bool'"
        self._exception = value

    @builtins.property
    def need_reset_to_init(self):
        """Message field 'need_reset_to_init'."""
        return self._need_reset_to_init

    @need_reset_to_init.setter
    def need_reset_to_init(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'need_reset_to_init' field must be of type 'bool'"
        self._need_reset_to_init = value

    @builtins.property
    def engage_by_operator(self):
        """Message field 'engage_by_operator'."""
        return self._engage_by_operator

    @engage_by_operator.setter
    def engage_by_operator(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'engage_by_operator' field must be of type 'bool'"
        self._engage_by_operator = value

    @builtins.property
    def disengage_by_operator(self):
        """Message field 'disengage_by_operator'."""
        return self._disengage_by_operator

    @disengage_by_operator.setter
    def disengage_by_operator(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'disengage_by_operator' field must be of type 'bool'"
        self._disengage_by_operator = value
