import os
import time

import rospy
import rospkg

from python_qt_binding import loadUi
from python_qt_binding.QtCore import Qt
from python_qt_binding.QtGui import QWidget

class ScienceWidget(QWidget):
    def __init__(self, context):
        super(ScienceWidget, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'plugin.ui')
        loadUi(ui_file, self)