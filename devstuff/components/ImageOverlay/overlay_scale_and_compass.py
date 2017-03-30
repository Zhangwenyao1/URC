# Authors: Marcey and Daniel
#

import sys
import cv2
import rospy
import numpy as np

from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge, CvBridgeError

from std_msgs.msg import Float32

# Default settings
scale_text = 0
bearing_rotation = 0

img = cv2.imread("mars.jpg", -1)
if img == None:
  img = np.zeros((700,1000,3),dtype=np.uint8)


def image_callback(data):
  global img
  img = data.data

def bearing_callback(data):
  global bearing_rotation
  bearing_rotation = data.data

def scale_callback(data):
  global scale_text
  scale_text = data.data

def overlay_telemetry(scale_img, compass_img):
  # Get global data that callbacks can change anytime
  global img
  global scale_text
  global bearing_rotation

  # Overlay scale image (with transparency support)
  x_offset= 10
  y_offset= img.shape[0]-120
  for c in range(0,3):
      # sudo code explaination: img[where the overlay is going to be placed] = (overlay_image[all pixcels] * transparency) + (original_image * transparency)
      img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] = scale_img[:,:] * (scale_img[:,:]/255.0) + img[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] * (1.0 - scale_img[:,:]/255.0)

  # Rotate compass based on bearing
  num_rows, num_cols = compass_img.shape[:2]
  rotation_matrix = cv2.getRotationMatrix2D((int(num_rows/2), int(num_cols/2)),bearing_rotation,1)
  compass_img_rotation = cv2.warpAffine(compass_img, rotation_matrix, (num_cols, num_rows))

  # Warp compass in 3D so it looks like its pointing into the image
  compass_width = int(compass_img_rotation.shape[1])
  compass_height = int(compass_img_rotation.shape[0])
  img1_square_corners = np.float32([[0,0], [compass_height,0], [compass_height,compass_width],[0,compass_width]])
  img2_quad_corners = np.float32([[153,0], [429,0], [600,286], [0,286]]) # TODO: Set this sizes properly using a scale factor and image size (NOT static)
  h, mask = cv2.findHomography(img1_square_corners, img2_quad_corners)
  compass_img = cv2.warpPerspective(compass_img_rotation, h, (600,286))

  # Overlay compass image (with transparency support)
  compass_width = int(compass_img.shape[1])
  compass_height = int(compass_img.shape[0])
  x_offset= img.shape[1] - compass_width -10
  y_offset= img.shape[0] - compass_height - 10
  for c in range(0,3):
      # sudo code explaination: img[where the overlay is going to be placed] = (overlay_image[all pixcels] * transparency) + (original_image * transparency)
      img[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] = compass_img[:,:,c] * (compass_img[:,:,3]/255.0) + img[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] * (1.0 - compass_img[:,:,3]/255.0)

  # Set text overlay near scale_img indicating the scale value
  font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX = 3
  scale_text_pretty = "%s cm" % scale_text
  cv2.putText(img, scale_text_pretty, (20,img.shape[0]-20), font,1,(0,0,255), 2, cv2.LINE_AA)

  # cv2.imshow("Image", img)
  # cv2.waitKey(0)
  # cv2.destroyAllWindo()

  return img


if __name__ == '__main__':
  compass_filename = "compass.png"
  scale_filename = "scale.png"

  scale_img = cv2.imread(scale_filename, -1)
  if scale_img == None:
    rospy.logerr("ERROR image file didn't load: %s" % scale_img)
    exit(1)

  compass_img = cv2.imread(compass_filename, -1)
  if compass_img == None:
    rospy.logerr("ERROR image file didn't load: %s" % compass_img)
    exit(1)

  rospy.init_node('overlay_scale_and_compass', anonymous=True)
  overlay_publisher = rospy.Publisher('/science/overlay/compressed', CompressedImage, queue_size=1)

  # Get an image from ROS
  image_topic = "camera/compressed"
  if rospy.has_param('~image_topic'):
    image_topic = rospy.get_param('~image_topic')
  else:
    rospy.logwarn("image topic not provided; using %s" % image_topic)
  rospy.Subscriber(image_topic, CompressedImage, image_callback)

  # Get a compass bearing from ROS
  bearing_topic = "/science/bearing"
  if rospy.has_param('~bearing_topic'):
    bearing_topic = rospy.get_param('~bearing_topic')
  else:
    rospy.logwarn("bearing topic not provided; using %s" % bearing_topic)
  rospy.Subscriber(bearing_topic, Float32, bearing_callback)

  # Get scale size from ROS
  scale_topic = "/science/scale"
  if rospy.has_param('~scale_topic'):
    scale_topic = rospy.get_param('~scale_topic')
  else:
    rospy.logwarn("scale topic not provided; using %s" % scale_topic)
  rospy.Subscriber(scale_topic, Float32, scale_callback)

  rate = rospy.Rate(10) # 10hz
  while not rospy.is_shutdown():
    img = overlay_telemetry(scale_img, compass_img)
    compressed_image = CvBridge().cv2_to_compressed_imgmsg(img)
    overlay_publisher.publish(compressed_image)
    rate.sleep()
