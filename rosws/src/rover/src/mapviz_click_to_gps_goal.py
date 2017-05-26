#!/usr/bin/env python
import click
import rospy
import subprocess

from geometry_msgs.msg import PointStamped


class GPSClickController():
    def __init__(self):
        self.executable = None

    def publish_gps_goal(self, point):
        rospy.loginfo('Publishing GPS goal to (%.3f, %.3f, %.3f)(lat, long, altitude).' % (point.point.x, point.point.y, point.point.z))
        subprocess.call('%s --lat %s --long %s' % (self.executable, point.point.y, point.point.x), shell=True)
        # import gps_goal
        # gps_goal.do_gps_goal(point.point.x, point.point.y) # not in use because you cannot create a new node (rospy.init_node()) twice in the same python script

@click.command()
@click.option('--executable', default='/home/dan/URC/rosws/src/rover/src/gps_goal.py')
def main(executable):
    ClickController = GPSClickController()
    ClickController.executable = executable
    rospy.init_node('clicked_gps')
    rospy.Subscriber('clicked_gps', PointStamped, ClickController.publish_gps_goal)
    rospy.spin()

if __name__ == '__main__':
    main()