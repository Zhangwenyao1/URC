#!/usr/bin/env python
import serial
import struct
import std_msgs.msg
import rospy
import time

s = serial.Serial(port="/dev/ttyUSB0", baudrate=38400)
print" ADSAADFDFA2"
rospy.init_node("science_serial")
sensor_names = ("ph", "humid", "temp")
pub = {n: rospy.Publisher("/science/" + name, std_msgs.msg.Float32, queue_size=10) for n, name in zip((0, 1, 2), sensor_names)}

print" ADSAADFDFA"

while not rospy.is_shutdown():
    if s.in_waiting < 1:
        time.sleep(0.33)
        print("test")
    else:
        t = s.read(1)
        if ord(t) in (0, 1, 2):
            v = struct.unpack("<f", s.read(4))[0]
            print "[+] Data {} Value {}".format(sensor_names[ord(t)], v)
            pub[ord(t)].publish(v)
        else:
            print "[!] Bad data!"
