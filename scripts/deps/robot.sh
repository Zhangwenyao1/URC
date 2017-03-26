#!/bin/bash

# ROS apt repository
sudo sh -c 'echo "deb http://mirror.umd.edu/packages.ros.org/ros/ubuntu xenial main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update

sudo apt-get install ros-kinetic-rosserial-arduino \
                     ros-kinetic-rosserial-python \
                     ros-kinetic-rosserial \
                     ros-kinetic-joy \
                     ros-kinetic-rtabmap-ros \
                     ros-kinetic-navigation \
                     ros-kinetic-tf2-sensor-msgs \
                     ros-kinetic-perception \
                     ros-kinetic-desktop \
                     python-rosdep \
                     nethogs \
                     v4l-utils # find out which /dev/video* is which using v4l2-ctl --list-devices

# TODO: Add Installing RTIMULib section from  http://www.jetsonhacks.com/2015/07/01/bosch-imu-under-ros-on-nvidia-jetson-tk1/
sudo apt-get install cmake-curses-gui
git clone https://github.com/jetsonhacks/RTIMULib.git
cd RTIMULib
#Switch to the Linux directory
cd Linux
mkdir build
cd build
cmake .. 
ccmake ..
cmake .. 
make -j4
sudo make install
sudo ldconfig

sudo c_rehash /etc/ssl/certs # https://github.com/ros/rosdistro/issues/12894
sudo rosdept init
rosdep update

wstool set usb_cam -y --git https://github.com/bosch-ros-pkg/usb_cam.git
if [[ $1 == "y" ]]; then
 wstool set zed_ros_wrapper -y --git https://github.com/stereolabs/zed-ros-wrapper.git
fi
wstool set robot_localization -y --git https://github.com/cra-ros-pkg/robot_localization
wstool set rtimulib_ros -y --git https://github.com/romainreignier/rtimulib_ros

grep "source /opt/ros/kinetic/setup.bash"  ~/.bashrc || echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
