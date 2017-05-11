#!/usr/bin/python

import rospy
import geometry_msgs.msg
import serial
import struct
import rover_drive.msg

cmode = False


def transmit_if(t):
    global cmode
    if cmode == t:
        return
    else:
        theSerial.write("\x00" if not t else "\x01")
        cmode = t


def on_new_twist(data):
    transmit_if(False)
    dat = "\x02" + struct.pack("<ff", data.linear.x/5.7, (-data.angular.z)/5.777)
    theSerial.write(dat)


def on_new_tank(data):
    transmit_if(True)
    dat = "\x02" + struct.pack("<ff", data.left, data.right)
    theSerial.write(dat)

theSerial = serial.Serial()
theSerial.port = "/dev/ttyACM0"
theSerial.open()

rospy.init_node("twist_sender")
subscriber = rospy.Subscriber("/cmd_vel", geometry_msgs.msg.Twist, on_new_twist, queue_size=15)
subscriver = rospy.Subscriber("/cmd_vel_tank", rover_drive.msg.Tank, on_new_tank, queue_size=15)
rospy.spin()
