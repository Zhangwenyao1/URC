#!/usr/bin/env python
import rospy
import cv2

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

def camera():
  rospy.init_node('VideoPublisher', anonymous=True)

  topic = "camera/compressed"
  camera_id = 0 # find number using $ v4l2-ctl --list-devices
  
  camera_compressed = rospy.Publisher(topic, CompressedImage, queue_size=1)
  rospy.loginfo("Publishing to topic %s" % topic)

  rate = rospy.Rate(10)
  cap = cv2.VideoCapture(camera_id)

  # ZED Supported Resolutions: 
  # 4416 x 1242 (@ 15 fps)
  # 3840 x 1080 (@ 30 fps)
  # 2560 x 720 (@ 60 fps)
  # 1344 x 376 (1@ 00 fps)
  cap.set(3, 4416)
  cap.set(4, 1242)

  if not cap.isOpened():
    rospy.loginfo("capture is not open :(")
    exit(1)

  while not rospy.is_shutdown() and cap.isOpened():
    ret, frame = cap.read()

    rospy.loginfo("sending frame...")
    height, width, channels = frame.shape
    rospy.loginfo("frame size: %s %s %s" % (height, width, channels) )

    if cv2.waitKey(1) & 0xFF == ord('q'):
      rospy.logwarn("breaking...")
      break
    if not ret:
      rospy.logwarn("something wrong opening frame")
      break

    msg_frame_compressed = CvBridge().cv2_to_compressed_imgmsg(frame)
    camera_compressed.publish(msg_frame_compressed)
    rate.sleep()

  cap.release()

if __name__ == '__main__':
  try:
    camera()
  except rospy.ROSInterruptException:
    pass
