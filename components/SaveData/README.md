TODO
  Save GPS
  Save Image
  Compass direction / Scale
  Panorama
  Save sensor data


# Tips

To publish a fake temperature data to ROS:

```
rostopic pub /temp std_msgs/Float32 1
```

To save data to files prefixed with a description use the _description parameter:

```
rosrun urc save_temp.py _description:=site1
```