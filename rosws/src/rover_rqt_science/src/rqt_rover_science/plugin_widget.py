import os
import time

import rospy
import rospkg

from python_qt_binding import loadUi
from python_qt_binding.QtCore import Qt, Signal, Slot
from python_qt_binding.QtWidgets import QWidget, QLineEdit, QInputDialog
import rover_science.msg
import rover_science.srv


class ScienceWidget(QWidget):
    refresh_data = Signal(rover_science.msg.Sites)

    def __init__(self, context):
        super(ScienceWidget, self).__init__()
        ui_file = os.path.join(rospkg.RosPack().get_path('rover_rqt_science'), 'resource', 'plugin.ui')
        loadUi(ui_file, self)

        self.refresh_data.connect(self.new_data)

        def sites_subscriber(msg):
            self.refresh_data.emit(msg)

        self.sites_subscriber = rospy.Subscriber("/science/sites", rover_science.msg.Sites, callback=sites_subscriber,
                                                 queue_size=5)

        self.add_site = rospy.ServiceProxy("/science/sci/new_site", rover_science.srv.NewSite)
        self.remove_site = rospy.ServiceProxy("/science/sci/delete_site", rover_science.srv.DeleteSite)
        self.addSitePushButton.clicked.connect(self.new_site_click)
        self.removeSitePushButton.clicked.connect(self.remove_site_click)
        context.add_widget(self)

    @Slot(rover_science.msg.Sites)
    def new_data(self, msg):
        """

        :type msg: rover_science.msg.Sites
        """
        self.listWidget.clear() # clear the site list
        for site in msg.sites:
            site = site # type: rover_science.msg.Site
            self.listWidget.addItem(site.site_name)

    @Slot()
    def new_site_click(self):
        input_text, ok = QInputDialog.getText(self, "New site name", "Name of the new site: ")
        if ok:
            msg = rover_science.srv.NewSiteRequest()
            msg.site_name = input_text
            self.add_site(msg)

    @Slot()
    def remove_site_click(self):
        site_id = self.listWidget.currentRow()
        if site_id == -1:
            return
        else:
            msg = rover_science.srv.DeleteSiteRequest()
            msg.site_id = site_id
            self.remove_site(msg)
