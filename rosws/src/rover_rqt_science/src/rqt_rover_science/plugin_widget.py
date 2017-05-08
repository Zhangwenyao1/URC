import os
import rospkg

import rospy
import rover_science.msg
import rover_science.srv
from python_qt_binding import loadUi
from python_qt_binding.QtCore import Signal, Slot
from python_qt_binding.QtWidgets import QWidget, QInputDialog

from .take_dialog import TakeMeasurementsDialog
from .inner_widget import InnerWidget


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
        self.take_measurement = rospy.ServiceProxy("/science/sci/take_measurement", rover_science.srv.TakeMeasurement)
        self.retake_measurement = rospy.ServiceProxy("/science/sci/update_measurement", rover_science.srv.UpdateMeasurement)
        self.change_site_name = rospy.ServiceProxy("/science/sci/change_site_name", rover_science.srv.SiteNameChange)
        self.addSitePushButton.clicked.connect(self.new_site_click)
        self.removeSitePushButton.clicked.connect(self.remove_site_click)
        self.listWidget.currentRowChanged.connect(self.selected_change)
        self.takeMeasurementPushButton.clicked.connect(self.new_measurement_clicked)
        self.renamePushButton.clicked.connect(self.rename_clicked)
        self.last_site_data = None

        context.add_widget(self)

    @Slot(rover_science.msg.Sites)
    def new_data(self, msg):
        """

        :type msg: rover_science.msg.Sites
        """
        currRow = self.listWidget.currentRow()
        self.listWidget.clear() # clear the site list
        self.last_site_data = msg
        for i, site in enumerate(msg.sites):
            site = site # type: rover_science.msg.Site
            self.listWidget.addItem(site.site_name)
        if currRow == -1:
            return
        elif currRow < len(self.last_site_data.sites):
            self.listWidget.setCurrentRow(currRow)
        else:
            return

    @Slot()
    def new_measurement_clicked(self):
        if self.listWidget.currentRow() == -1:
            return
        else:
            b, ok = self._get_take_bifield()
            if not ok:
                return
            msg = rover_science.srv.TakeMeasurementRequest()
            msg.site_id = self.listWidget.currentRow()
            msg.measurements_to_take = b
            self.take_measurement(msg)

    @Slot(int, int)
    def retake_measurement_clicked(self, mid, sid):
        b, ok = self._get_take_bifield()
        if not ok:
            return
        msg = rover_science.srv.UpdateMeasurementRequest()
        msg.site_id = sid
        msg.measurements_to_retake = b
        msg.measurement_id = mid
        self.retake_measurement(msg)

    # noinspection PyMethodMayBeStatic
    def _get_take_bifield(self):
        dialog = TakeMeasurementsDialog()
        ok = bool(dialog.exec_())
        b = 0
        b |= rover_science.msg.Measurement.HAS_PH * int(dialog.phCheckBox.isChecked())
        b |= rover_science.msg.Measurement.HAS_TEMP * int(dialog.tempCheckBox.isChecked())
        b |= rover_science.msg.Measurement.HAS_HUMIDITY * int(dialog.humidCheckBox.isChecked())
        return b, ok

    def _setup_tab_view_page(self, sid, mid):
        tabContent = InnerWidget(mid, sid)
        tabContent.mesaurementLabel.setText("<html><head/><body><p><span style=\" font-size:14pt; "
                                            "font-weight:600;\">Measurement {}</span></p></body></html>".format(mid+1))
        measurement = self.last_site_data.sites[sid].measurements[mid]  # type: rover_science.msg.Measurement
        tabContent.latitudeLabel.setText("Latitude: {}".format(measurement.location.latitude))
        tabContent.longitudeLabel.setText("Longitude: {}".format(measurement.location.longitude))
        tabContent.altitudeLabel.setText("Altitude: {}".format(measurement.location.altitude))
        if measurement.data_completeness & measurement.HAS_PH == measurement.HAS_PH:
            tabContent.phLabel.setText("PH: {}".format(measurement.ph))
        if measurement.data_completeness & measurement.HAS_TEMP == measurement.HAS_TEMP:
            tabContent.tempLabel.setText("Temperature: {}".format(measurement.temp))
        if measurement.data_completeness & measurement.HAS_HUMIDITY == measurement.HAS_HUMIDITY:
            tabContent.humidityLabel.setText("Humidity: {}".format(measurement.humidity))
        tabContent.retake.connect(self.retake_measurement_clicked)
        self.tabWidget.addTab(tabContent, "Measurement {}".format(mid+1))

    @Slot()
    def rename_clicked(self):
        if self.listWidget.currentRow() == -1:
            return
        else:
            input_text, ok = QInputDialog.getText(self, "New site name", "New name of the site: ")
            if ok:
                msg = rover_science.srv.SiteNameChangeRequest()
                msg.site_name = input_text
                msg.site_id = self.listWidget.currentRow()
                self.change_site_name(msg)

    @Slot(int)
    def selected_change(self, newSelected):
        if newSelected == -1:
            self.tabWidget.clear()
            return
        else:
            self.tabWidget.clear()
            for j in range(len(self.last_site_data.sites[newSelected].measurements)):
                self._setup_tab_view_page(newSelected, j)

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

    def shutdown(self):
        self.sites_subscriber.unregister()
        self.add_site.close()
        self.remove_site.close()
