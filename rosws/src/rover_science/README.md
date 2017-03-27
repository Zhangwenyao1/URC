
# Tips

To publish a fake temperature data to ROS:

```
rostopic pub /temp std_msgs/Float32 1
```

To save data to files prefixed with a description use the _description parameter:

```
rosrun rover_science save_temp.py _description:=site1
```
