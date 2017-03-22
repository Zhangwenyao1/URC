#!/usr/bin/python

import rospy
import geometry_msgs.msg
import serial
import struct


def on_new_twist(data):
    dat = struct.pack("<ff", data.linear.x, data.angular.z)
    theSerial.write(dat)

theSerial = serial.Serial()

rospy.init_node("twist_sender")
subscriber = rospy.Subscriber("/cmd_vel", geometry_msgs.msg.Twist, on_new_twist, queue_size=10)
rospy.spin()