#!/bin/bash

# Exit on error
set -e

# MISC
sudo apt-get update
sudo apt-get install vim git tmux tcpdump arduino python-pip
pip install wstool

# ROS
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full python-rosinstall
if [ ! -e "/etc/ros/rosdep/sources.list.d/20-default.list" ]; then
	sudo rosdep init
fi
rosdep update

sudo apt-get install ros-kinetic-rosserial-arduino ros-kinetic-rosserial
