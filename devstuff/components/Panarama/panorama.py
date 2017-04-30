#!/usr/bin/env python
import cv2
import rospy
import argparse

from pyimagesearch.panorama import Stitcher
from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

def panorama():
  stitcher = Stitcher()
  br = CvBridge()
  rospy.init_node('panorama', anonymous=True)

  # Load parameters
  input_image_topic = "camera/compressed"
  if rospy.has_param('~input_image_topic'):
    input_image_topic = rospy.get_param('~input_image_topic')
    input_image_topic = '%s/compressed' % input_image_topic
  else:
    rospy.logwarn("input image topic not provided on param 'input_image_topic'; using %s" % input_image_topic)

  output_image_topic = "panorama/compressed"
  if rospy.has_param('~output_image_topic'):
    output_image_topic = rospy.get_param('~output_image_topic')
    output_image_topic = '%s/compressed' % output_image_topic
  else:
    rospy.logwarn("output image topic not provided on param 'output_image_topic'; using %s" % output_image_topic)

  num_segments = 2
  if rospy.has_param('~num_segments'):
    num_segments = rospy.get_param('~num_segments')
  else:
    rospy.logwarn("panorama number of segments not provided on param 'num_segments'; using %s" % num_segments)

  # Create publisher
  panorama_publisher = rospy.Publisher(output_image_topic, CompressedImage, queue_size=1)

  # Create panorama
  rospy.loginfo("Waiting for image on topic %s" % input_image_topic)
  imageA = rospy.wait_for_message(input_image_topic, CompressedImage)
  imageA = br.compressed_imgmsg_to_cv2(imageA)
  for n in range(1, num_segments):
    # move
    rospy.loginfo("Waiting for image on topic %s" % input_image_topic)
    imageB = rospy.wait_for_message(input_image_topic, CompressedImage)
    imageB = br.compressed_imgmsg_to_cv2(imageB)
    rospy.loginfo("Stitching...")
    (result, vis) = stitcher.stitch([imageA, imageB], showMatches=True)
    imageA = result

  # Show the images
  cv2.imshow("Image A", imageA)
  cv2.imshow("Image B", imageB)
  cv2.imshow("Keypoint Matches", vis)
  cv2.imshow("Result", result)
  cv2.waitKey(0)

  # Output panorama to file
  cv2.imwrite("output.jpg", result)
  # Publish panorama to ROS
  compressed_img_message = br.cv2_to_compressed_imgmsg(result)
  rospy.loginfo("Publishing panorama to topic %s" % output_image_topic)
  panorama_publisher.publish(compressed_img_message)


if __name__ == '__main__':
  try:
    panorama()
  except rospy.ROSInterruptException:
    pass


