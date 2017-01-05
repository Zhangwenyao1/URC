#!/usr/bin/env python
import time
import rospy
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage

import cv2
from cv_bridge import CvBridge, CvBridgeError

# NOTE:
# THIS IS NOT WORKING

def camera():
  rospy.loginfo("starting...")
  rospy.init_node('VideoPublisher', anonymous=True)
  camera = rospy.Publisher('camera', Image)
  camera_compressed = rospy.Publisher('camera/compressed', CompressedImage)
  rate = rospy.Rate(24) # 24hz
  # from internet:
  #cap = cv2.VideoCapture('nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink')
  # from hamza: 
  cap = cv2.VideoCapture('nvcamerasrc fpsRange="30.0 30.0" ! video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)I420, framerate=(fraction)30/1 ! nvtee ! nvvidconv flip-method=2 ! video/x-raw(memory:NVMM), format=(string)I420 ! nvoverlaysink -e')

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
