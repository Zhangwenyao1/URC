#!/bin/bash

# Exit on error
#set -e

sudo apt-get install ros-kinetic-rosserial-arduino ros-kinetic-rosserial-python
wstool set usb_cam -y --git https://github.com/bosch-ros-pkg/usb_cam.git
if [[ $1 == "y" ]]; then
 wstool set zed_ros_wrapper -y --git https://github.com/stereolabs/zed-ros-wrapper.git
fi

