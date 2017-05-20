#! /usr/bin/env python
import sys
import rospy
import cv2
# import image_transport

from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


pub = rospy.Publisher('/low_res', Image, queue_size=1)
def streamer(data):
    img = CvBridge().imgmsg_to_cv2(data, desired_encoding="mono8")

    # resize img to at least 400 wide
    scale_factor = 100.0/img.shape[1]
    img = cv2.resize(img, (int(scale_factor*img.shape[1]), int(scale_factor*img.shape[0])), interpolation = cv2.INTER_CUBIC)

    img = CvBridge().cv2_to_imgmsg(img)
    pub.publish(img)

if __name__ == '__main__':
  try:
    rospy.init_node('low_res_stream')
    # TODO: BUFFERING NOT WORKING
    rospy.Subscriber('/usb_cam/image_raw', Image, streamer, queue_size=1)
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
