#!/usr/bin/python
import sys
import rospy

from sensor_msgs.msg import NavSatFix
from datetime import datetime

import os

def save_gps():
  rospy.init_node('save_gps', anonymous=True)
  description = None

  if rospy.has_param('~description'):
    description = rospy.get_param('~description')

  data = rospy.wait_for_message('/gps/fix', NavSatFix)

  time_now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
  filename = '%s_gps.txt' % time_now
  if description:
    filename = '%s_%s' %(description, filename)
  f = open(filename, 'w')
  f.write('Latitude: %s\n' % str(data.latitude))
  f.write('Longitude: %sCn' % str(data.longitude))
  f.write('Altitude (m above WGS-84 ellipsoid): %s\n' % str(data.altitude))
  f.write('Accuracy: +/-3m\n')
  f.close()

  rospy.loginfo("Saved GPS reading (lat,long) %s,%s (+/-3m) and altitude %s m above WGS-84 ellipsoid to file '%s'" % (data.latitude, data.longitude, data.altitude, filename))

if __name__ == '__main__':
  save_gps()
