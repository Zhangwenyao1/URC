#!/usr/bin/env python
import rospy
import sensor_msgs.msg
import serial
import struct
import genpy
from cStringIO import StringIO

rospy.init_node("yay_900mhz_recv")
dev = rospy.get_param("~dev")
s = serial.Serial(port=dev)

st = struct.Struct("<BBBBH")
ss = int(st.size)
V = {1: sensor_msgs.msg.CompressedImage}
P = {1: "/900mhz/image/compressed"}

for i in P:
    P[i] = rospy.Publisher(P[i], V[i], queue_size=5)


def search():
    if s.in_waiting >= ss:
        try:
            d = st.unpack(s.read(ss))
            # print d
            if not (d[0] == d[1] == d[2] == d[3]):
                return
            elif d[0] not in P:
                return
            else:
                sss = d[4]
                dbuffer = StringIO()
                a = 0
                while a < sss:
                    remain = sss - a
                    ddd = min(s.in_waiting, remain)
                    dbuffer.write(s.read(ddd))
                    a += ddd
                dser = dbuffer.getvalue()
                msg = V[d[0]]()
                msg.deserialize(dser)
                # print msg
                P[d[0]].publish(msg)
        except struct.error:
            return
        except KeyError:
            return
        except genpy.message.DeserializationError:
            return

while not rospy.is_shutdown():
    search()