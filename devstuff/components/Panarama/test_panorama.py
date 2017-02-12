#!/usr/bin/env python
import time
import rospy
import cv2
import imutils

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

rospy.init_node('PanoramaTestPublisher', anonymous=True)
topic = 'camera/compressed'
camera_compressed = rospy.Publisher(topic, CompressedImage, queue_size=20)

frame1 = cv2.imread('scottsdale_left_01.png')
frame2 = cv2.imread('scottsdale_right_01.png')

frame1 = imutils.resize(frame1, width=400)
frame2 = imutils.resize(frame2, width=400)


if frame1 == None or frame2 == None:
  rospy.loginfo("image failed to open")
  exit(1)

# msg_frame_compressed = CvBridge().cv2_to_compressed_imgmsg(frame1)
# rospy.loginfo("Publishing to topic %s" % topic)
# camera_compressed.publish(msg_frame_compressed)

# time.sleep(3)

msg_frame_compressed = CvBridge().cv2_to_compressed_imgmsg(frame2)
rospy.loginfo("Publishing to topic %s" % topic)
camera_compressed.publish(msg_frame_compressed)

