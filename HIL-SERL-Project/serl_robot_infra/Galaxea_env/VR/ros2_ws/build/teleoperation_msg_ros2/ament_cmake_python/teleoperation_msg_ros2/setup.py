from setuptools import find_packages
from setuptools import setup

setup(
    name='teleoperation_msg_ros2',
    version='0.0.0',
    packages=find_packages(
        include=('teleoperation_msg_ros2', 'teleoperation_msg_ros2.*')),
)
