import rospy

from nav_msgs.msg import Odometry

odom_out = Odometry()


def callback(data):
    odom_out.pose = data.pose
    odom_out.pose.covariance[0] = -1
    odom_out.pose.covariance[7] = -1
    odom_out.pose.covariance[14] = -1
    odom_out.pose.covariance[21] = -1
    odom_out.pose.covariance[28] = -1
    odom_out.pose.covariance[35] = -1
    odom_out.twist = data.twist
    odom_out.twist.covariance[0] = -1
    odom_out.twist.covariance[7] = -1
    odom_out.twist.covariance[14] = -1
    odom_out.twist.covariance[21] = -1
    odom_out.twist.covariance[28] = -1
    odom_out.twist.covariance[35] = -1
    pub.publish(odom_out)

pub = rospy.Publisher("/zed/odom_fixed", Odometry, queue_size=10)
sub = rospy.Subscriber("/zed/odom", Odometry, callback=callback)

rospy.init_node("odom_fixer_zed")
while True:
    rospy.spin()
