#! /usr/bin/env python
import sys
import rospy
import cv2
# import image_transport

from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

def receiver(jpg_img):
    decimg = cv2.imdecode(jpg_img, 1)
    img = CvBridge().cv2_to_imgmsg(decimg,"bgr8")
    pub.publish(img)

pub = rospy.Publisher('/low_res', Image, queue_size=1)
def streamer(data):
    img = CvBridge().imgmsg_to_cv2(data, desired_encoding="mono8")
    print sys.getsizeof(img)

    # resize img to at least 400 wide
    scale_factor = 400.0/img.shape[1]
    img = cv2.resize(img, (int(scale_factor*img.shape[1]), int(scale_factor*img.shape[0])), interpolation = cv2.INTER_CUBIC)

    # cv2.imshow('image',img)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 8]
    result, jpg_img = cv2.imencode('.jpg', img, encode_param)

    receiver(jpg_img)


if __name__ == '__main__':
  try:
    rospy.init_node('low_res_stream')
    # TODO: BUFFERING NOT WORKING
    rospy.Subscriber('/usb_cam/image_raw', Image, streamer, queue_size=1)
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
