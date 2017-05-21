#!/usr/bin/python
import rospy
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist
import std_msgs.msg
import rover_drive.msg

mode = False
s = 160/2

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

    global s

    if data.buttons[5]:
        s -= 5
    if data.buttons[4]:
        s += 5
    if data.buttons[2]:
        s = 160/2

    pub3.publish(s)


rospy.init_node("joystick_teleoperation")
sub = rospy.Subscriber("joy", Joy, on_joy_data)
pub = rospy.Publisher("cmd_vel_mux/teleoperation", Twist, queue_size=1)
pub2 = rospy.Publisher("cmd_vel_tank", rover_drive.msg.Tank, queue_size=1)
pub3 = rospy.Publisher("zed_servo", std_msgs.msg.Float32, queue_size=1)
rospy.spin()
