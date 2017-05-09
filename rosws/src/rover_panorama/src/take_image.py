#!/usr/bin/env python
# Takes images and saves them to disk with a requested filename in a parameter directory
# Useful for taking panoramas

import rospy
import cv2
from cv_bridge import CvBridge, CvBridgeError
import sensor_msgs.msg
import os
import rover_panorama.srv

rospy.init_node("image_taker")
the_bridge = CvBridge()

image_topic = rospy.get_param("~image_topic")
save_dir = rospy.get_param("~save_dir")

image_counter = 0


def take_picture(msg):
    global image_counter
    image = rospy.wait_for_message(image_topic, sensor_msgs.msg.Image, timeout=5)
    cv2image = the_bridge.imgmsg_to_cv2(image)
    pat = os.path.join(save_dir, "IMGROS_{}.png".format(image_counter))
    cv2.imwrite(pat, cv2image)
    image_counter += 1
    return rover_panorama.srv.TakeImageResponse(result=pat)


serv = rospy.Service("take_image", rover_panorama.srv.TakeImage, take_picture)
rospy.spin()