# URC

## Prerequisites

- Jetson TX1 mobile computing platform
-  ZED depth camera
- Ubuntu 16.04 ARM 64-bit (preferably this version to closely match the Jetson TX1)
- ROS Kinetic

## Installation
### Software dependencies
#### For Joystick
```
sudo apt-get install ros-indigo-joy
# more info: http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick
```

#### For Arduino Development
```
sudo apt-get install ros-indigo-rosserial-arduino
sudo apt-get install ros-indigo-rosserial
# more info: http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick
```

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
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
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
roscore
# in another terminal
source ~/catkin_ws/devel/setup.bash
rosrun r3ros talker.py
```

# Editing robot model (URDF format)

To use our robot with many standard ROS tools, we need to write down a model of the robot’s kinematics. That is, we need to describe the physical configuration of the robot, such as how many wheels it has, where they are placed, and which directions they turn in. This information will be used by rviz to visualize the state of the robot, by gazebo to simulate it, and by systems like the navigation stack to make it drive around the world in a purposeful manner.
In ROS, we represent robot models in an XML format called Unified Robot Description Format (URDF) This format is designed to represent a wide variety of robots, from a two wheeled toy to a walking humanoid.

```bash
cd ~/catkin_ws/src/URC/urdf
./open_model.sh robot.urdf
```
