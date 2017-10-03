#!/usr/bin/env python3

import sys

from PyQt5.QtWidgets import *
from PyQt5 import uic
from connect import *
#import pdb
#from PyQt5 import QtGui, QtCore

form_class = uic.loadUiType("ui.ui")[0]

class MyWindow(QMainWindow, form_class):

    fileName = ""

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.show_file_open)
        self.pushButton_2.clicked.connect(self.telnet_connect)


    def show_file_open(self):
        fname = QFileDialog.getOpenFileName(self)
        self.fileName = fname[0]
        self.lineEdit.setText(fname[0])
        return 0

    def telnet_connect(self):
        telnet = Tel.main(self.fileName)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = MyWindow()
    myWindow.show()
    app.exec_()
