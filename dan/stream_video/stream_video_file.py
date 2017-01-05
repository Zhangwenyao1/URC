#!/usr/bin/env python
import time
import rospy
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage

import cv2
from cv_bridge import CvBridge, CvBridgeError

def camera():
  rospy.loginfo("starting...")
  rospy.init_node('VideoPublisher', anonymous=True)
  camera = rospy.Publisher('camera', Image)
  camera_compressed = rospy.Publisher('camera/compressed', CompressedImage)
  rate = rospy.Rate(24) # 24hz
  cap = cv2.VideoCapture('/home/ubuntu/dan/catkin_ws/src/beginner_tutorials/src/output.avi')
  #cap = cv2.VideoCapture(0) # open first camera device

  if not cap.isOpened():
    rospy.loginfo("capture is not open :(")

  while not rospy.is_shutdown() and cap.isOpened():
    rospy.loginfo("sending frame...")
    ret, frame = cap.read()

    if cv2.waitKey(1) & 0xFF == ord('q'):
      rospy.logwarn("breaking...")
      break
    if not ret:
      rospy.logwarn("something wrong opening frame")
      break

    msg_frame = CvBridge().cv2_to_imgmsg(frame, encoding='bgr8')
    msg_frame_compressed = CvBridge().cv2_to_compressed_imgmsg(frame)
    camera.publish(msg_frame)
    camera_compressed.publish(msg_frame_compressed)
    rate.sleep()

  cap.release()

if __name__ == '__main__':
  try:
    camera()
  except rospy.ROSInterruptException:
    pass
