#!/usr/bin/env python
import rospy
import std_msgs.msg
import serial
import struct

rospy.init_node("ya")
s = serial.Serial(port="/dev/ttyACM0", baudrate=9600)
ip = rospy.Publisher("/motIN", std_msgs.msg.Float32, queue_size=5)
op = rospy.Publisher("/motOUT", std_msgs.msg.Float32, queue_size=5)
sep = rospy.Publisher("/motSET", std_msgs.msg.Float32, queue_size=5)


def wait_for_serial_message():
    while True:
        if rospy.is_shutdown():
            exit(0)
        elif s.in_waiting < 14:
            pass
        else:
            if s.read() != '\x04':
                continue
            else:
                s.read()
                i = struct.unpack("<f", s.read(4))[0]
                o = struct.unpack("<f", s.read(4))[0]
                se = struct.unpack("<f", s.read(4))[0]
                ip.publish(i)
                op.publish(o)
                sep.publish(se)
                break


while not rospy.is_shutdown():
    wait_for_serial_message()
