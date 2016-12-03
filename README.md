# URC

## Prerequisites

- Jetson TX1 mobile computing platform
-  ZED depth camera
- Ubuntu 16.04 ARM 64-bit (preferably this version to closely match the Jetson TX1)
- ROS Kinetic

## Installation
### Create a workspace
Create your workspace by following the standard convention:

```bash
source /opt/ros/kinetic/setup.bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ~/catkin_ws
catkin_make
source ~/catkin_ws/devel/setup.bash
echo $ROS_PACKAGE_PATH # should contain your catkin_ws workspace
```

To make R3's URC code part of your workspace, follow these steps (assuming your workspace is setup following the standard conventions):

```bash
cd ~/catkin_ws/src
git clone git@github.com:teamr3/URC.git
cd ~/catkin_ws
catkin_make
```

(Optional: Only set this when using the Jetson TX1.) Set environment variables for ros networking:

```bash
export ROS_MASTER_URI=http://tegra-ubuntu.mshome.net:11311/
export ROS_IP=`hostname -I`
echo 'export ROS_MASTER_URI=http://tegra-ubuntu.mshome.net:11311/' >> ~/.bashrc
echo 'export ROS_IP=`hostname -I`' >> ~/.bashrc
```

# Run

```bash
source ~/catkin_ws/devel/setup.bash
rosrun r3ros talker.py
```

