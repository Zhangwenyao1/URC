#!/bin/bash

# Exit on error
set -e

echo "Installing deps"
./deps/common.sh

echo "Setting up ROS workspace, if this fails make sure you have ros sourced and are in the root directory!"
source /opt/ros/kinetic/setup.bash
catkin_init_workspace rosws/src
cd rosws/src

echo "Getting wstool deps"
wstool update

echo "Building ros workspace for the first time"
cd ..
catkin_make

echo "source `pwd`/rosws/devel/setup.sh" >> ~/.bashrc
source ./rosws/devel/setup.sh

cd ..
echo "Done!"



