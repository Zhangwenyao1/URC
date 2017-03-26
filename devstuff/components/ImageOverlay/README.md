Talk to Daniel about this code

### Start code

```
python overlay_scale_and_compass.py
```

### Publish fake bearing messages

```
do rostopic pub /science/bearing std_msgs/Float32 `date +%s | tail -c 4` -1; done
```

### View output

```
rqt_image_view /science/overlay/compressed
```

