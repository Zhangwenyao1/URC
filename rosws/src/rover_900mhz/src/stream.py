#!/usr/bin/env python
import rospy
import serial
import sensor_msgs.msg
from cStringIO import StringIO
import struct
import Queue
import threading

rospy.init_node("yay_900mhz_publish")
dev = rospy.get_param("~dev")
s = serial.Serial(port=dev,baudrate=57600)
# s.open()

st = struct.Struct("<H")
db = Queue.Queue()


def r():
    while True:
        a = db.get()
        s.write(a)
	while not s.cts:
		print "WAIT"
		pass

a = threading.Thread(target=r, name="hi")
a.start()


def gen_serialize(i):
    msg_head = chr(i) * 4

    def serialize(msg):
        si = StringIO()
        si.write(msg_head)
        s2 = StringIO()
        msg.serialize(s2)
        si.write(st.pack(len(s2.getvalue())))
        si.write(s2.getvalue())
        a = si.getvalue()
        db.put(a)
    return serialize

import theora_image_transport.msg

im_i_in = rospy.Subscriber(rospy.get_param("~image"), sensor_msgs.msg.CompressedImage, gen_serialize(1))
rospy.spin()
