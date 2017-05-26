


# USAGE
# python stitch.py --first images/bryce_left_01.png --second images/bryce_right_01.png 

# import the necessary packages
from pyimagesearch.panorama import Stitcher
import argparse
import imutils
import cv2

# load the two images and resize them to have a width of 400 pixels
# (for faster processing)
cap = cv2.VideoCapture(0) # open first camera device

if not cap.isOpened():
  rospy.loginfo("capture is not open :(")
  return

ret, frame = cap.read()

  while not rospy.is_shutdown() and cap.isOpened():
    rospy.loginfo("sending frame...")
    ret, frame = cap.read()


# stitch the images together to create a panorama
stitcher = Stitcher()
(result, vis) = stitcher.stitch([imageA, imageB], showMatches=True)

# show the images
cv2.imshow("Image A", imageA)
cv2.imshow("Image B", imageB)
cv2.imshow("Keypoint Matches", vis)
cv2.imshow("Result", result)
cv2.waitKey(0)