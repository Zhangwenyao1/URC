#!/usr/bin/env python
# Authors: Marcey and Daniel
#
import sys
import cv2
import rospy
import click
import numpy as np

from std_msgs.msg import Float32
from sensor_msgs.msg import CompressedImage, Image
from cv_bridge import CvBridge, CvBridgeError

# Global variables
# TODO(Dan): do proper multitheading data sharing with a class?
scale_text = 0
bearing_rotation = 0
img = np.zeros((700,1000,3),dtype=np.uint8)

def image_callback(data):
  global img
  img_cv = CvBridge().compressed_imgmsg_to_cv2(data)

  # resize img to at least 1000 high
  scale_factor = 1000.0/img.shape[0]
  img = cv2.resize(img_cv, (int(scale_factor*img.shape[1]), int(scale_factor*img.shape[0])), interpolation = cv2.INTER_CUBIC)

def bearing_callback(data):
  global bearing_rotation
  bearing_rotation = data.data

def scale_callback(data):
  global scale_text
  scale_text = data.data

def overlay_telemetry(scale_img, compass_img, heading=None, scale=None, output_file=False):
  # Get global data that callbacks can change anytime
  global img
  global scale_text
  global bearing_rotation
  im_out = img.copy()

  if heading:
    bearing_rotation = heading
  if scale:
    scale_text = scale

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
  x_offset = im_out.shape[1] / 2 - scale_img.shape[1] / 2 # center width position
  y_offset = im_out.shape[0] - compass_height - 1 # near bottom
  for c in range(0,3):
      # pseudo code explaination: im_out[where the overlay is going to be placed] = (overlay_image[all pixcels] * transparency) + (original_image * transparency)
      im_out[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] = compass_img[:,:,c] * (compass_img[:,:,3]/255.0) + im_out[y_offset:y_offset+compass_img.shape[0], x_offset:x_offset+compass_img.shape[1], c] * (1.0 - compass_img[:,:,3]/255.0)



  # Overlay scale image (with transparency support)
  x_offset = im_out.shape[1] / 2 - scale_img.shape[1] / 2 # center width position
  y_offset = im_out.shape[0] / 2 # # center height position
  for c in range(0,3):
      # pseudo code explaination: im_out[where the overlay is going to be placed] = (overlay_image[all pixcels] * transparency) + (original_image * transparency)
      im_out[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] = scale_img[:,:,c] * (scale_img[:,:,3]/255.0) + im_out[y_offset:y_offset+scale_img.shape[0], x_offset:x_offset+scale_img.shape[1], c] * (1.0 - scale_img[:,:,3]/255.0)

  # Set text overlay near scale_img indicating the scale value
  font = 3
  scale = 1
  thick = 2
  line_type = 4
  color = (255,255,255)
  scale_text_pretty = "%s cm" % scale_text
  cv2.putText(im_out, "0", (x_offset-25,y_offset+16), font, scale, color, thick, line_type)
  cv2.putText(im_out, scale_text_pretty, (x_offset+scale_img.shape[1]+5,y_offset+16), font, scale, color, thick, line_type)

  # cv2.imshow("Image", im_out)
  # cv2.waitKey(0)
  # cv2.destroyAllWindo()

  return im_out


@click.command()
@click.option('--once', is_flag=True, help='Only perform overlay once instead of infinite loop')
@click.option('--output-file', default=False, help='Save to file rather than publish over ROS')
@click.option('--image', default=False, help='Input image file')
@click.option('--heading', default=False, type=float)
@click.option('--scale', default=False, type=float)
def main(once, output_file, image, heading, scale):
  rospy.init_node('overlay_scale_and_compass')
  if not output_file:
    overlay_publisher = rospy.Publisher('/science/overlay/compressed', CompressedImage, queue_size=1)
  compass_filename = "compass.png"
  scale_filename = "scale.png"

  # Load scale image
  scale_img = cv2.imread(scale_filename, -1)
  if scale_img == None:
    rospy.logerr("ERROR image file didn't load: %s" % scale_img)
    exit(1)
  # # resize img to at least 600 wide
  scale_factor = 600.0/scale_img.shape[1]
  scale_img = cv2.resize(scale_img, (int(scale_factor*scale_img.shape[1]), int(scale_factor*scale_img.shape[0])), interpolation = cv2.INTER_CUBIC)

  # Load compass image
  compass_img = cv2.imread(compass_filename, -1)
  if compass_img == None:
    rospy.logerr("ERROR image file didn't load: %s" % compass_img)
    exit(1)

  if not image:
    rospy.Subscriber(rospy.get_param('~image_topic', '/camera/rgb_fixed/compressed'), CompressedImage, image_callback)
  else:
    global img
    img = cv2.imread(image, -1)
    if img == None:
      rospy.logerr("ERROR image file didn't load: %s" % image)
      exit(1)
  if not heading:
    rospy.Subscriber(rospy.get_param('~bearing_topic','/gps/heading'), Float32, bearing_callback)
  if not scale:
    rospy.Subscriber(rospy.get_param('~scale_topic', '/science/scale'), Float32, scale_callback)

  rate = rospy.Rate(10) # 10hz
  while not rospy.is_shutdown():
    img = overlay_telemetry(scale_img, compass_img, heading=heading, scale=scale, output_file=output_file)
    if output_file:
      cv2.imwrite(output_file,img)
    else:
      compressed_image = CvBridge().cv2_to_compressed_imgmsg(img)
      overlay_publisher.publish(compressed_image)
    if once:
      return
    rate.sleep()

if __name__ == '__main__':
  main()
