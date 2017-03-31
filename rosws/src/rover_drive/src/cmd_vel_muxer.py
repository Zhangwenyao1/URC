#!/usr/bin/python
import rospy
import geometry_msgs.msg

auto_timeout = 0
dt = 0

rospy.init_node("cmd_vel_mux")
pub = rospy.Publisher("cmd_vel", geometry_msgs.msg.Twist, queue_size=10)


def on_auto_data(data):
    data = data # type: geometry_msgs.msg.Twist
    global auto_timeout, dt
    dtt = rospy.Time(0) - dt
    dt = rospy.Time(0)
    auto_timeout -= dtt
    if auto_timeout <= 0:
        auto_timeout = 0
        pub.publish(data)


def on_human_data(data):
    global auto_timeout, dt
    dt = rospy.Time(0)
    auto_timeout = 5
    pub.publish(data)


s1 = rospy.Subscriber("cmd_vel_mux/move_base", geometry_msgs.msg.Twist, callback=on_auto_data)
s2 = rospy.Subscriber("cmd_vel_mux/teleoperation", geometry_msgs.msg.Twist, callback=on_human_data)
rospy.spin()
