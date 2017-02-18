#!/bin/bash

# Joystick
sudo apt-get install ros-kinetic-joy

# MapViz
sudo apt-get install ros-kinetic-mapviz ros-kinetic-mapviz-plugins ros-kinetic-tilemap ros-kinet-multires-image

# Docker (needed for MapProxy for offline google maps for MapViz)
sudo apt-get install apt-transport-https ca-certificates
sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D
sudo touch /etc/apt/sources.list.d/docker.list
echo "deb https://apt.dockerproject.org/repo ubuntu-xenial main" > /etc/apt/sources.list.d/docker.list
sudo apt-get install linux-image-extra-$(uname -r)
sudo apt-get install docker-engine

# MoveIt (arm motion planning)
sudo apt-get install ros-kinetic-moveit ros-kinetic-ros-control ros-kinetic-ros-controllers ros-kinetic-gazebo-ros-control
