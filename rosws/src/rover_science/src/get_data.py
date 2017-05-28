#!/usr/bin/env python
import serial
import struct
import std_msgs.msg
import rospy

s = serial.Serial(port="/dev/ttyUSB0",baudrate=38400)
rospy.init_node("ASDFASDFASDFASDF")
psb = {n: rospy.Publisher("/science/data{}".format(n), std_msgs.msg.Float32, queue_size=10) for n in (0, 1, 2)}

while True:
	if s.in_waiting < 1:
		continue
	else:
		t = s.read(1)
		if ord(t)  in (0, 1, 2):
			print "[+] Data {}".format(ord(t))
			v = struct.unpack("<f", s.read(4))[0]
			print "[+] Data Value{}".format(v)
			psb[ord(t)].publish(v)
		else:
			print "[!] Bad data!"



