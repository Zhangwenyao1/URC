#!/usr/bin/python
import sys
import rospy

from std_msgs.msg import Float32
from datetime import datetime


def save_ph():
  rospy.init_node('save_ph', anonymous=True)
  description = None

  if rospy.has_param('~description'):
    description = rospy.get_param('~description')

  data = rospy.wait_for_message('ph', Float32)
  ph = data.data

  time_now = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
  filename = '%s_pH.txt' % time_now
  if description:
    filename = '%s_%s' %(description, filename)
  f = open(filename, 'w')
  f.write('pherature: %sC\n' % str(ph))
  f.close()

  rospy.loginfo("Saved pH reading '%s' to file '%s'" % (ph, filename))

if __name__ == '__main__':
  save_ph()
