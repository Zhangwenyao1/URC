#!/bin/bash

# Exit on error
set -e

wstool set usb_camera --git https://github.com/bosch-ros-pkg/usb_cam.git
if [ "$1" -eq "y" ]; then
 wstool set zed_ros_wrapper --git https://github.com/stereolabs/zed-ros-wrapper.git
fi

