#!/usr/bin/python

import rospy
import geometry_msgs.msg
import serial
import struct


def on_new_twist(data):
    dat = struct.pack("<ff", data.linear.x/1.2, (-data.angular.z)/2)
    theSerial.write(dat)

theSerial = serial.Serial()
theSerial.port = "/dev/ttyACM0"
theSerial.open()

rospy.init_node("twist_sender")
subscriber = rospy.Subscriber("/cmd_vel", geometry_msgs.msg.Twist, on_new_twist, queue_size=10)
rospy.spin()
