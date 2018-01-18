

# Team R3 Rover for URC 2017

**For additional documentation please see: https://github.com/danielsnider/ros-rover or our [book chapter documentation](https://github.com/danielsnider/ros-rover/raw/master/Book%20Chapter%20-%20University%20Rover%20Challenge%20Tutorials%20and%20Control%20System%20Survey.pdf).**

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



## Usage and layout

### The wiki
The wiki contains a lot more information than this file. Go check it out!

### Layout
The layout of this repo is like this:

| Path | What it is |
| --- | --: |
| `rosws/` | The main ros workspace |
| `rosws/src` | All the catkin packages, NOT all the nodes |
| `rosws/.gitignore` | A simple gitignore to keep per-system directories out of the repo |
| `microcontroller/` | All of the microcontroller (arduino) related things, grouped by device. |
| `scripts/` | Various useful scripts to use this repo for maximum productivity! |
| `devstuff/` | General other stuff that you want to put on git. The original git repo is copied here as well. |

### First clone
When you first clone this, you will want to run `scripts/setup_firsttime.sh` from the root directory. It will then setup everything.

### Arduino things
If you want to update one arduino, go into its directory, and use the command `$ pio run --target upload`. On the TX1, however, we know where all the arduinos are plugged in and a script (coming soon) will auto-update all of them.

### Build everything
Use the script `scripts/build.sh`. If a build fails, it will ask you if you want to continue.

## More documentation?
If we need more, or you just want to say something, you can use slack, or put it in the wiki for this repo. I might put a page about what to put in a package soon.

## P.S
Don't be a litterbug, keep general development... stuff in the `devstuff/` folder, and keep the structured code in the right directory!

## Network IP Addresses (private network)

**Device**|**IP**|**Username**|**Password**
:-----:|:-----:|:-----:|:-----:
Rocket M2 UBNT-ROBOT|192.168.137.2|ubnt|robotrobot
Rocket M2 UBNT-BASESTATION|192.168.137.3|ubnt|robotrobot
Jetson TX1 (old)|192.168.137.212|ubuntu|ubuntu
Jetson TX1 (old) VPN|192.168.255.10 |ubuntu|ubuntu
Jetson TX1 (new)|192.168.137.213|ubuntu|ubuntu
Jeston TX1 (new) VPN|192.168.255.18|ubuntu|ubuntu
TP-link 1|192.168.0.254|admin|admin
TP-link 2|192.168.0.253|admin|admin
Daniel's Laptop|192.167.137.10| |
Gabe's laptop|192.167.137.22| | 
