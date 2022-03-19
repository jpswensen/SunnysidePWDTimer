from PyQt5 import QtWidgets, uic, QtCore, QtSerialPort
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from sys import platform

from pwdtimer_communications import *

class CommDialog(QDialog):
    def __init__(self, client, parent=None):
        QDialog.__init__(self, parent)
        uic.loadUi("commdialog.ui",self)

        self.client = client

        self.portList = QtSerialPort.QSerialPortInfo.availablePorts()        
        print(self.portList)

        for port in self.portList:
            self.portComboBox.addItem(port.portName())

        self.serialConnectButton.clicked.connect(self.on_serial_connect)
        self.networkConnectButton.clicked.connect(self.on_network_connect)

    def on_network_connect(self):
        pass
        host = self.hostLineEdit.text()
        port = int(self.portLineEdit.text())
        self.client.connect_wifi(host,port)

    def on_serial_connect(self):
        selected_port_idx = self.portComboBox.currentIndex()
        selected_port = self.portList[selected_port_idx]

        full_port_name = selected_port.portName()
        if platform == "linux" or platform == "linux2" or platform == "darwin":
            full_port_name = "/dev/" + full_port_name
        
        self.client.connect_serial(full_port_name)        


