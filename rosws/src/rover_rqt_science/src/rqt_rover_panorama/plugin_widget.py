import os
import rospkg

import rospy
import rover_science.msg
import rover_science.srv
from python_qt_binding import loadUi
from python_qt_binding.QtCore import Signal, Slot
from python_qt_binding.QtWidgets import QWidget


class PluginWidget(QWidget):
    def __init__(self):
        super(PluginWidget, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'pano.ui')
        loadUi(ui_file, self)