# R3 ROS Workspace

## Launch ALL components (best usage pattern)

On the rover:
```bash
$ cd URC/
$ mux
```

On the teleoperator's computer:

```bash
$ cd URC/devstuff/dan/
$ mux
```

For more information about our use of tmux see section 16.1 [here](https://github.com/danielsnider/ros-rover/raw/master/Book%20Chapter%20-%20University%20Rover%20Challenge%20Tutorials%20and%20Control%20System%20Survey.pdf).

## Launch individual components

#### GPS
```bash
$ roslaunch rover gps.launch
# Output topic
$ rostopic echo gps/fix
```

#### IMU
```bash
$ roslaunch rtimulib_ros rtimulib_ros.launch
# View output
rostopic echo imu/data
$ ~/RTIMULib/Linux/build-RTIMULibDemoGL-Desktop-Debug/Output/RTIMULibDemoGL # Graphical vizualization
```


#### rtabmap
```bash
$ roslaunch rover_rtabmap_config navigation.launch
# View output
$ roslaunch rover_rtabmap_config mapping_rviz.launch
```

#### Overlay scale and bearing
```bash
$ python ~/URC/devstuff/components/ImageOverlay/overlay_scale_and_compass.py
# View output
$ rqt_image_view /science/overlay/compressed
```

#### RAMSBOT
1. Plug in the joystick to your computer
2. `laptop$ source ./URC/scripts/set_robot_as_ROS_master.sh`
3. Roslaunch the joy_teleoperation node where you have the joystick connected by USB
```bash
laptop$ roslaunch teleoperation joy_teleoperation.launch
```
4. Roslaunch the ramsbot_test.launch on the TX1 where the arduino connects to the motors
```bash
tx1$ roslaunch rover_drive ramsbot_test.launch
# View output
$ rostopic echo cmd_vel
```

#### Temperature Sensor
```bash
$ rosrun rover_science save_temp.py _description:=site1
# View output
$ cat *_temperature.txt
```
#### pH Sensor
```bash
$ rosrun rover_science save_ph.py _description:=site1
# View output
$ cat *_ph.txt
```

#### All USB Cameras
```bash
$ roslaunch rover usb_cameras.launch
# View output
rqt --perspective-file URC/devstuff/dan/gui_configs/rqt_all_cameras.perspective
```

#### ZED Camera
```bash
$ roslaunch rover zed_up.launch
# View output: there are many ways...
1) video stream: usq rqt or rviz
2) point cloud: use rviz
3) odometry: use rviz
```


Welcome to
_______ _______ _______  ______ _______ ______ 
|______ |       |_____| |_____/ |_____| |_____]
______| |_____  |     | |    \_ |     | |_____]

Scarab Canada Advanced Robotics And Bionics

