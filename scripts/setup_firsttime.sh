#!/bin/bash

# Setup ros, anything else will be added later.

echo Installing deps
scripts/install_deps.sh

echo Setting up ROS workspace, if this fails make sure you have ros sourced and are in the root directory!

catkin_init_workspace rosws/src

cd rosws
echo Getting wstool deps
wstool update
echo Building ros workspace for the first time
catkin_make
cd ..

echo Done!

