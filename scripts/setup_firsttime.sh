#!/bin/bash

# Setup ros, anything else will be added later.

echo "Installing deps"
./deps/common.sh

echo "Setting up ROS workspace!"
source /opt/ros/kinetic/setup.bash
catkin_init_workspace rosws/src
cd rosws

echo Setting up device specific deps...
echo You need to choose which set of dependencies you want to install.
echo "You can install all of them, the bare ones required for running the robot, everything but the zed wrapper, and ones for simply remote controlling the robot."
read -p "All/Robot/Zed/rEmote [arZe] " dep_set

case "${dep_set,,}" in
 "a") deps/full.shs
      ;;
 "r") deps/robot.sh
      ;;
 "e") deps/base_station.sh
      ;;
 "z")
   *)
      deps/full_no_zed.sh
      ;;
esac
wstool update

echo "Doing a build to get all required libs and dirs"
cd ..
echo "Done!"



