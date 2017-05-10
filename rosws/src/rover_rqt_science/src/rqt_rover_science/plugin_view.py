#!/usr/bin/env python

from qt_gui.plugin import Plugin
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
        self._widget.shutdown()