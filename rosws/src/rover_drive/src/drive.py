#!/usr/bin/python

import rospy
import geometry_msgs.msg
import serial
import struct
import rover_drive.msg

cmode = False


def transmit_if(t):
    global cmode
    if theSerial.in_waiting > 0:
        rospy.logwarn("Data in serial buffer, but the driveduino shouldn't be giving me any...")
    if cmode == t:
        return
    else:
        theSerial.write(b"\x00" if not t else b"\x01")
        cmode = t


def on_new_twist(data):
    transmit_if(False)
    dat = bytes(b"\x02") + struct.pack("<ff", -data.linear.x, (-data.angular.z))
    theSerial.write(dat)


def on_new_tank(data):
    transmit_if(True)
    dat = "\x02" + struct.pack("<ff", -data.left, -data.right)
    theSerial.write(dat)
    pass

theSerial = serial.Serial(baudrate=9600)
theSerial.port = "/dev/ttyACM0"
theSerial.open()

rospy.init_node("twist_sender")
subscriber = rospy.Subscriber("/cmd_vel", geometry_msgs.msg.Twist, on_new_twist, queue_size=15)
subscriver = rospy.Subscriber("/cmd_vel_tank", rover_drive.msg.Tank, on_new_tank, queue_size=15)
rospy.spin()
