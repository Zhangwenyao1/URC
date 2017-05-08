#!/usr/bin/env python
import os
import rospy
import rospkg

from qt_gui.plugin import Plugin
from python_qt_binding import loadUi
from python_qt_binding.QtWidgets import QWidget
from python_qt_binding.QtCore import Signal, Slot
import rover_science.msg
from .plugin_widget import ScienceWidget


class SciencePlugin(Plugin):
    def __init__(self, context):
        super(SciencePlugin, self).__init__(context)
        self.setObjectName('SciencePlugin')
        self._widget = ScienceWidget(context)
        self._widget.setObjectName("SciencePluginUI")

        if context.serial_number() > 1:
            self._widget.setWindowTitle(self._widget.windowTitle() + (' (%d)' % context.serial_number()))

    def shutdown_plugin(self):
        self._widget.sites_subscriber.unregister()