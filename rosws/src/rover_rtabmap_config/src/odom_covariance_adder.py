#!/usr/bin/python
import rospy

from nav_msgs.msg import Odometry

odom_out = Odometry()


def callback(data):
    odom_out = data
    c_hack = list(odom_out.pose.covariance)
    c_hack[0] = -1
    c_hack[7] = -1
    c_hack[14] = -1
    c_hack[21] = -1
    c_hack[28] = -1
    c_hack[35] = -1
    odom_out.pose.covariance = tuple(c_hack)
    c_hack = list(odom_out.twist.covariance)
    c_hack[0] = -1
    c_hack[7] = -1
    c_hack[14] = -1
    c_hack[21] = -1
    c_hack[28] = -1
    c_hack[35] = -1
    odom_out.twist.covariance = tuple(c_hack)
    pub.publish(odom_out)

rospy.init_node("odom_fixer_zed")
pub = rospy.Publisher("/zed/odom_fixed", Odometry, queue_size=10)
sub = rospy.Subscriber("/zed/odom", Odometry, callback=callback)

while True:
    rospy.spin()
