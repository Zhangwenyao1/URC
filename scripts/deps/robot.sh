#!/bin/bash

# Exit on error
#set -e

sudo apt-get install ros-kinetic-rosserial-arduino ros-kinetic-rosserial-python \ 
                     nethogs \ # network bandwidth monitor
                     v4l-utils # find out which /dev/video* is which using v4l2-ctl --list-devices


# TODO: Add Installing RTIMULib section from  http://www.jetsonhacks.com/2015/07/01/bosch-imu-under-ros-on-nvidia-jetson-tk1/


wstool set usb_cam -y --git https://github.com/bosch-ros-pkg/usb_cam.git
if [[ $1 == "y" ]]; then
 wstool set zed_ros_wrapper -y --git https://github.com/stereolabs/zed-ros-wrapper.git
fi
wstool set robot_localization -y --git https://github.com/cra-ros-pkg/robot_localization
wstool set rtimulib_ros -y --git https://github.com/romainreignier/rtimulib_ros

