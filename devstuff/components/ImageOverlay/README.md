### Start code

```
python overlay_scale_and_compass.py _image_topic:=/usb_cam1/image_raw/compressed
```

### Publish fake bearing messages

```
rostopic pub /gps/heading std_msgs/Float32 180

# or

while true; do rostopic pub /gps/heading std_msgs/Float32 `date +%s | tail -c 4` -1; done
```

### Publish fake scale messages

```
rostopic pub /science/scale std_msgs/Float32 3.2

# or

while true; do rostopic pub /science/scale std_msgs/Float32 `date +%s | tail -c 4` -1; done
```

### View output

```
rqt_image_view /science/overlay/compressed
```
