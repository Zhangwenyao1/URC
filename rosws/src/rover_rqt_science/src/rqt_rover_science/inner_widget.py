import os
import rospkg

from python_qt_binding import loadUi
from python_qt_binding.QtCore import Signal, Slot
from python_qt_binding.QtWidgets import QWidget


class InnerWidget(QWidget):
    retake = Signal(int, int)

    def __init__(self, mid, sid):
        super(InnerWidget, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'inner.ui')
        loadUi(ui_file, self)
        self._mid = mid
        self._sid = sid

        self.measurementsButton.clicked.connect(self.retakeClicked)

    @Slot()
    def retakeClicked(self):
        self.retake.emit(self._mid, self._sid)
