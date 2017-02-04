# Authors: Marcey and Daniel
#

import sys
import cv2
import rospy
import numpy as np

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError


def overlay_telemetry(img, bearing_rotation, scale_text):
  compass_filename = "compass.jpg"
  scale_filename = "scale.png"

  img = cv2.imread(img)
  if img == None:
    print "ERROR: img didn't load"
    exit(1)

  scale_img = cv2.imread(scale_filename, -1)
  if scale_img == None:
    print "ERROR: scale_img didn't load"
    exit(1)

  compass_img = cv2.imread(compass_filename, -1)
  if compass_img == None:
    print "ERROR: compass_img didn't load"
    exit(1)

  # cv2.imshow("Image", img)
  # cv2.waitKey(0)
  # cv2.destroyAllWindows()
  # cv2.imshow("Image", scale_img)
  # cv2.waitKey(0)
  # cv2.destroyAllWindows()
  # cv2.imshow("Image", compass_img)
  # cv2.waitKey(0)
  # cv2.destroyAllWindows()


  x_offset= 17
  y_offset= 68

  #for the scale
  for c in range(0,3):
      # overlay scale image (with transparency support)
      img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] = scale_img[:,:,c] * (scale_img[:,:,1.5]/255.0) + img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] * (1.0 - scale_img[:,:,1.5]/255.0)

  #compass rotation based on bearing_rotation
  compass_width = int(img.shape[1]*float(.4))
  compass_height = int(img.shape[0]*float(.4))

  x_offset= 0
  y_offset= 0

  compass_img_rotation = cv2.resize (compass_img,(compass_width, compass_height), interpolation = cv2.INTER_CUBIC)
  num_rows, num_cols = compass_img.shape[:2]
  rotation_matrix = cv2.getRotationMatrix2D((num_rows, num_cols),30,1)
  compass_img_rotation = cv2.warpAffine(compass_img, rotation_matrix, (num_cols, num_rows))

  # overlay compass image (with transparency support)
  for c in range(0,3):
      img[y_offset:y_offset+compass_img_rotation.shape[0], x_offset:x_offset+compass_img_rotation.shape[1], c] = compass_img_rotation[:,:,c] * (compass_img_rotation[:,:,1.5]/255.0) + img[y_offset:y_offset+compass_img_rotation.shape[0], x_offset:x_offset+compass_img_rotation.shape[1], c] * (1.0 - compass_img_rotation[:,:,1.5]/255.0)

  #text overlay on scale
  font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX = 3
  cv2.putText(img, scale_text, (459,680), font,0.6,(185,185,185), 2, cv2.CV_AA)

  cv2.imshow("Image", img)
  cv2.waitKey(0)
  cv2.destroyAllWindows()

  return img


  # subscribe to image publisher
  # create overlay
  # publish to new ROS image stream

if __name__ == '__main__':
  rospy.init_node('overlay_scale_and_compass', anonymous=True)
  overlay_publisher = rospy.Publisher('overlay_publish', CompressedImage, queue_size=1)

  # Get an image from ROS
  image_topic = "camera/compressed"
  if rospy.has_param('~image_topic'):
    image_topic = rospy.get_param('~image_topic')
  else:
    rospy.logwarn("image topic not provided; using %s" % image_topic)
  # img = rospy.wait_for_message(image_topic, CompressedImage)

  # Get a compass bearing from ROS
  bearing_topic = "bearing"
  if rospy.has_param('~bearing_topic'):
    bearing_topic = rospy.get_param('~bearing_topic')
  else:
    rospy.logwarn("bearing topic not provided; using %s" % bearing_topic)
  # bearing_rotation = rospy.wait_for_message(bearing_topic, CompressedImage)

  # Get scale size from ROS
  scale_topic = "scale"
  if rospy.has_param('~scale_topic'):
    scale_topic = rospy.get_param('~scale_topic')
  else:
    rospy.logwarn("scale topic not provided; using %s" % scale_topic)
  # scale = rospy.wait_for_message(scale_topic, CompressedImage)

  # overlay_telemetry(img, bearing_rotation, scale_text)
  img = overlay_telemetry("mars.jpg", 90, "scale_text")

  # Output resulting image to file
  cv2.imwrite("output.jpg", img)
  # Output resulting image to ROS
  compressed_image = CvBridge().cv2_to_compressed_imgmsg(img)
  overlay_publisher.publish(compressed_image)

