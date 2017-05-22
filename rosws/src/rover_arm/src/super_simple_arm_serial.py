#!/usr/bin/python

import rospy
import sensor_msgs.msg
import serial
import struct

def on_new_joint(data):
    rospy.loginfo('Received joint positions %s'% data)
  # Execute arm position
    encoded_position = struct.pack("<fffffff",
                                    data.position[0],
                                    data.position[1],
                                    data.position[2],
                                    data.position[3],
                                    data.position[4],
                                    data.position[5],
                                    data.position[5],
                                    )
    theSerial.write(encoded_position)
    rospy.loginfo('Executed.')

theSerial = serial.Serial()
theSerial.port = "/dev/ttyACM0" # SET SERIAL DEVICE
theSerial.open()

rospy.init_node("joint_sender")
subscriber = rospy.Subscriber("/joint_states", sensor_msgs.msg.JointState, on_new_joint, queue_size=10)
rospy.spin()
