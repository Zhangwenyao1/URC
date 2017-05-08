import os
import rospkg

from python_qt_binding import loadUi
from python_qt_binding.QtCore import Signal, Slot
from python_qt_binding.QtWidgets import QWidget, QDialog


class TakeMeasurementsDialog(QDialog):
    def __init__(self):
        super(TakeMeasurementsDialog, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'chooseMeasurements.ui')
        loadUi(ui_file, self)
