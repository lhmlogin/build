#!/usr/bin/python3

from imp_process_full_py3 import MyApp
from PyQt5 import QtWidgets
import sys

app = QtWidgets.QApplication(sys.argv)
window = MyApp()
window.show()
window.move((QtWidgets.QApplication.desktop().width() - window.width())/2,(QtWidgets.QApplication.desktop().height() - window.height())/2)
sys.exit(app.exec_())