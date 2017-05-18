import os
import rospkg

import actionlib
import rospy
import rover_panorama.msg
import rover_science.msg
import rover_science.srv
from python_qt_binding import loadUi
from python_qt_binding.QtCore import Signal, Slot
from python_qt_binding.QtWidgets import QWidget
from python_qt_binding.QtGui import QPixmap


class PluginWidget(QWidget):
    pstate_signal = Signal(rover_panorama.msg.PanoState)
    progreeeeeees = Signal(rover_panorama.msg.PanoramaFeedback)
    finiiiiiished = Signal(rover_panorama.msg.PanoramaResult)
    sstate_signal = Signal(dict)

    def __init__(self):
        super(PluginWidget, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'pano.ui')
        loadUi(ui_file, self)
        self.files = {}
        self.science_mark = -1
        self.pixmaps = {}
        self.sites = {}

        self.mark_pano = rospy.ServiceProxy("/science/sci/mark_panorama", rover_science.srv.MarkPano)
        self.panorama = actionlib.SimpleActionClient("/science/panorama/stitch_panorama", rover_panorama.msg.PanoramaAction)

        def state_sub(s):
            self.pstate_signal.emit(s)

        self._state_sub = rospy.Subscriber("/science/panorama/pano_state", rover_panorama.msg.PanoState, callback=state_sub)

        def science_sub(s):
            self.sstate_signal.emit([x.site_name for x in s.sites])

        self._sstate_sub = rospy.Subscriber("/science/sites", rover_science.msg.Sites, callback=science_sub)

    def feedback(self, f):
        self.progreeeeeees.emit(f)

    def goal(self, f, r):
        self.finiiiiiished.emit(r)

    @Slot(dict)
    def new_state(self, l):
        self.sites = l

    @Slot(rover_panorama.msg.PanoState)
    def new_pano_state(self, msg):
        self.listWidget.clear()
        self.files = {}
        self.pixmaps = {}
        j = 0
        for i in msg.in_transfer:
            self.tableWidget.setItem(j, 0, i)
            self.tableWidget.setItem(j, 1, "Transferred")
            j += 1
        for i in msg.transferred:
            self.tableWidget.setItem(j, 0, i)
            self.tableWidget.setItem(j, 1, "Transferring")
            self.files[j] = i
            self.pixmaps[j] = QPixmap(i)
            j += 1

    @Slot(int)
    def new_selected(self, r):
        if r in self.files:
            pmap = self.pixmaps[r]
            self.label.pixmap = pmap
            self.label.text = ""
        else:
            self.label.pixmap = None
            self.label.text = "File does not exist yet"

    @Slot(rover_panorama.msg.PanoramaFeedback)
    def new_feedback(self, msg):
        c = self.progressBar.maximum - msg.commandsToGo
        self.progressBar.value = c

    @Slot(rover_panorama.msg.PanoramaGoal)
    def goal(self, msg):
        request = rover_science.srv.MarkPanoRequest()
        request.mark_flags = request.HAS_PANO
        request.pano_location = msg.resultFilenameSmall
        self.mark_pano(request)

    @Slot()
    def push_button(self):

