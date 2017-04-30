#!/usr/bin/python
import sys
import rospy

from std_msgs.msg import Float32
from datetime import datetime


def save_humidity():
  rospy.init_node('save_humidity', anonymous=True)
  description = None

  if rospy.has_param('~description'):
    description = rospy.get_param('~description')

  data = rospy.wait_for_message('humidity', Float32)
  humidity = data.data

  time_now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
  filename = '%s_humidity.txt' % time_now
  if description:
    filename = '%s_%s' %(description, filename)
  f = open(filename, 'w')
  f.write('Relative humidity: %s%\n' % str(humidity))
  f.close()

  rospy.loginfo("Saved relative humidity reading %s% to file '%s'" % (humidity, filename))

if __name__ == '__main__':
  save_humidity()
