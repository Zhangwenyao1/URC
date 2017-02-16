#!/bin/bash

# Exit on error
#set -e

sudo apt-get install ros-kinetic-rosserial-arduino ros-kinetic-rosserial-python \ 
                     nethogs \ # network bandwidth monitor
                     v4l-utils # find out which /dev/video* is which using v4l2-ctl --list-devices
wstool set usb_cam -y --git https://github.com/bosch-ros-pkg/usb_cam.git
if [[ $1 == "y" ]]; then
 wstool set zed_ros_wrapper -y --git https://github.com/stereolabs/zed-ros-wrapper.git
fi

