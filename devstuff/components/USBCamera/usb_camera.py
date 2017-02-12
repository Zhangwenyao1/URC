#!/usr/bin/env python
import rospy
import cv2

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

def camera():
  rospy.init_node('VideoPublisher', anonymous=True)

  topic = "camera/compressed"
  if rospy.has_param('~topic'):
    topic = rospy.get_param('~topic')
    topic = '%s/compressed' % topic
  else:
    rospy.logwarn("image topic not provided; using %s" % topic)

  camera_id = 0
  if rospy.has_param('~device_id'):
    camera_id = rospy.get_param('~device_id') #changed from ~camera_id to ~device_id to match launch file
  else:
    rospy.logwarn("image camera_id not provided; using %s" % camera_id)

  camera_compressed = rospy.Publisher(topic, CompressedImage, queue_size=1)
  rospy.loginfo("Publishing to topic %s" % topic)

  rate = rospy.Rate(10) # increase or decrease to get higher or lower frame rate. This modifies how many samples are sent per second
   cap = cv2.VideoCapture(camera_id) #the video capture refers to the video stream i believe. setting this to camera id should
    #make the capture occur from the camera streams.
  #cap = cv2.VideoCapture('/home/dan/output.avi')

  if not cap.isOpened():
    rospy.loginfo("capture is not open :(")
    exit(1)

  while not rospy.is_shutdown() and cap.isOpened():
    ret, frame = cap.read()
    rospy.loginfo("sending frame...")

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
