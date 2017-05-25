#!/usr/bin/env python
import click
import rospy

from geometry_msgs.msg import PointStamped
from visualization_msgs.msg import Marker


class PointToMarker():
    def __init__(self):
        self.marker_publisher = rospy.Publisher('marker', Marker, queue_size=10)
        self.scale = 1.0

    def publish_marker(self, point):
        marker = Marker()
        marker.header.frame_id = 'map'
        marker.header.stamp = rospy.get_rostime()
        marker.ns = 'map' # Namespace to place this object in
        marker.id = 0 # object ID
        marker.type = 1 # cube
        marker.action = 0 # add
        marker.lifetime = rospy.Duration(0)
        marker.pose.position = point.point
        marker.pose.orientation.x = 0
        marker.pose.orientation.y = 0
        marker.pose.orientation.z = 0
        marker.pose.orientation.w = 1.0
        marker.scale.x = 1.0 * self.scale
        marker.scale.y = 1.0 * self.scale
        marker.scale.z = 2.0 * self.scale
        marker.color.r = 1.0
        marker.color.g = 1.0
        marker.color.b = 0.0
        marker.color.a = 1.0
        self.marker_publisher.publish(marker)
        rospy.loginfo('Published marker at (%.3f, %.3f, %.3f)(x,y,z).' % (point.point.x, point.point.y, point.point.z))

@click.command()
@click.option('--scale', prompt='Marker size (m)', help='Marker size (m)')
def main(scale):
    MarkerController = PointToMarker()
    MarkerController.scale = float(scale)
    rospy.init_node('point_to_marker')
    rospy.Subscriber('point_to_marker', PointStamped, MarkerController.publish_marker)
    rospy.spin()

if __name__ == '__main__':
    main()