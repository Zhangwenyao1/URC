# R3 ROS Workspace

## Launch ALL components (empty for now, someone could write this)
```bash
roslaunch rover robot.launch
```

## Launch individual components

#### GPS
```bash
rosrun nmea_navsat_driver nmea_serial_driver _port:=/dev/ttyTHS2 _baud:=9600
```

#### IMU
```bash
roslaunch rtimulib_ros rtimulib_ros.launch
```


#### rtabmap
```bash
roslaunch rover_rtabmap_config navigation.launch
```

#### Overlay scale and bearing
```bash
python ~/URC/devstuff/components/ImageOverlay/overlay_scale_and_compass.py
```

#### RAMSBOT
```bash
roslaunch teleoperation joy_teleoperation.launch
roslaunch rover_drive ramsbot_test.launch
```

#### Temperature Sensor
```bash
rosrun rover_science save_temp.py _description:=site1
```
#### pH Sensor
```bash
rosrun rover_science save_ph.py _description:=site1
```

#### All USB Cameras
```bash
roslaunch rover usb_cameras.launch
```

#### ZED Camera
```bash
roslaunch rover zed_up.launch
```

#### Don't forget to source setup.bash
```
source ~/URC/rosws/devel/setup.bash
```

