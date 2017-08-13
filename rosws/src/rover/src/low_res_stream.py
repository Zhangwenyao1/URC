#! /usr/bin/env python
import sys
import rospy
import cv2

from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


pub = rospy.Publisher('/low_res', Image, queue_size=1)
def streamer(data):
    # Reduce bandwith by converting to image to greyscale
    img = CvBridge().imgmsg_to_cv2(data, desired_encoding="mono8")

    ## Make image smaller to reduce bandwith even more
    # resize img to at least 400 wide
    scale_factor = 400.0/img.shape[1]
    img = cv2.resize(img, (int(scale_factor*img.shape[1]), int(scale_factor*img.shape[0])), interpolation = cv2.INTER_CUBIC)

    img = CvBridge().cv2_to_imgmsg(img)
    pub.publish(img)

if __name__ == '__main__':
  try:
    rospy.init_node('low_res_stream')
    rospy.Subscriber('/usb_cam/image_raw', Image, streamer, queue_size=1)
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
