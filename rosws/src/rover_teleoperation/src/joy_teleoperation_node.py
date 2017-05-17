#!/usr/bin/python
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist
import rover_drive.msg

mode = False

def on_joy_data(data):
    global mode
    """

    :type data: Joy
    """
    if data.buttons[1]: # B button on xbox 360 controller
        mode = not mode

    if not mode:
        msg = Twist()
        msg.linear.x = data.axes[1]
        msg.angular.z = data.axes[0]
        pub.publish(msg)
    else:
        msg = rover_drive.msg.Tank()
        msg.left = data.axes[1]
        msg.right = data.axes[4]
        pub2.publish(msg)


rospy.init_node("joystick_teleoperation")
sub = rospy.Subscriber("joy", Joy, on_joy_data)
pub = rospy.Publisher("cmd_vel_mux/teleoperation", Twist, queue_size=1)
pub2 = rospy.Publisher("cmd_vel_tank", rover_drive.msg.Tank, queue_size=1)
rospy.spin()
