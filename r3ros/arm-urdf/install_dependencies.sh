#!/bin/bash
if [ `rosversion -d` = 'indigo' ]; then
  sudo apt-get install ros-indigo-ros-controllers ros-indigo-youbot-gazebo-robot ros-indigo-youbot-gazebo-control ros-indigo-youbot-description ros-indigo-youbot-driver ros-indigo-youbot-driver-ros-interface ros-indigo-youbot-gazebo-worlds ros-indigo-youbot-simulation ros-indigo-gazebo-ros-control ros-indigo-effort-controllers ros-indigo-joint-state-controller ros-indigo-joint-trajectory-controller
fi
if [ `rosversion -d` = 'kinetic' ]; then
  sudo apt-get install ros-kinetic-ros-controllers ros-kinetic-youbot-gazebo-robot ros-kinetic-youbot-gazebo-control ros-kinetic-youbot-description ros-kinetic-youbot-driver ros-kinetic-youbot-driver-ros-interface ros-kinetic-youbot-gazebo-worlds ros-kinetic-youbot-simulation ros-kinetic-gazebo-ros-control ros-kinetic-effort-controllers ros-kinetic-joint-state-controller ros-kinetic-joint-trajectory-controller
fi