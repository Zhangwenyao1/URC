# R3 ROS Workspace

## Launch ALL components (not actually working, someone could write this)
```bash
$ tmuxinator ...
# Less preferred method (everything runs in one terminal, harder to debug)
$ roslaunch rover robot.launch
```

## Launch individual components

#### GPS
```bash
$ rosrun nmea_navsat_driver nmea_serial_driver _port:=/dev/ttyTHS2 _baud:=9600
# Output topic
$ rostopic echo fix
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
2. `source ./URC/scripts/set_robot_as_ROS_master.sh`
3. Roslaunch the joy_teleoperation node where you have the joystick connected by USB
```bash
$ roslaunch teleoperation joy_teleoperation.launch
```
4. Roslaunch the ramsbot_test.launch on the TX1 where the arduino connects to the motors
```bash
$ roslaunch rover_drive ramsbot_test.launch
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

#### Don't forget to source setup.bash
```
$ source ~/URC/rosws/devel/setup.bash
```

