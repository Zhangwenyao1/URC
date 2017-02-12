#!/usr/bin/python
import sys
import rospy

from std_msgs.msg import Float32
from datetime import datetime

import os

def save_temp():
  rospy.init_node('save_temp', anonymous=True)
  description = None

  if rospy.has_param('~description'):
    description = rospy.get_param('~description')

  data = rospy.wait_for_message('temp', Float32)
  temp = data.data

  time_now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
  filename = '%s_temperature.txt' % time_now
  if description:
    filename = '%s_%s' %(description, filename)
  f = open(filename, 'w')
  f.write('temperature: %sC\n' % str(temp))
  f.close()

  rospy.loginfo("Saved temperature reading '%s' to file '%s'" % (temp, filename))

if __name__ == '__main__':
  save_temp()
