<<<<<<< HEAD
dan@ubuntu:~/catkin_ws/src/URC/r3ros/arm-urdf
=======
# Arm Basics

This code is based on (and explained in detail) Chapter 8 (page 389) of the ROS book "[Programming Robots with ROS](https://drive.google.com/drive/folders/0B0R9maYs7LgsVWpIOThTR1pVcTQ)".

## Dependencies

Before running the code below you will need to install some dependencies. Run this in bash.

```bash
cd ~/catkin_ws/src/URC/r3ros/arm-urdf
./install_dependencies.sh
```

## Unified Robot Description Format (URDF)

The ```arm.urdf``` file describes the arm model for ROS.

## View Arm Model in RViz

To open rviz with the arm model run the following in bash.

```bash
roslaunch urdf_tutorial display.launch model:=arm.urdf gui:=True
```

## Simulate Robot Arm Model in Gazebo

To open Gazebo with the arm model run the following in bash.

```bash
roslaunch r3ros arm.launch
```

## Move by sending command to the arm_controller node

```bash
rostopic pub /arm_controller/command trajectory_msgs/JointTrajectory '{joint_names: ["hip", "shoulder", "elbow", "wrist"], points: [{positions: [0.1, -0.5, 0.5, 0.75], time_from_start: [1.0, 0.0]}]}'
```
>>>>>>> origin
