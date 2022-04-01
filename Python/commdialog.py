from PyQt5 import QtWidgets, uic, QtCore, QtSerialPort
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from sys import platform

from resources import *
from pwdtimer_communications import *

class CommDialog(QDialog):
    def __init__(self, lanes, client, parent=None):
        QDialog.__init__(self, parent)
        uic.loadUi(resource_path('commdialog.ui'),self)

        self.lanes = lanes
        self.client = client

        self.laneCountLineEdit.setText(str(lanes))

        self.portList = QtSerialPort.QSerialPortInfo.availablePorts()        
        print(self.portList)

        idx = 0
        for K,port in enumerate(self.portList):
            self.portComboBox.addItem(port.portName())
            full_port_name = port.portName()
            if platform == "linux" or platform == "linux2" or platform == "darwin":
                full_port_name = "/dev/" + full_port_name
            if full_port_name == client.ser_port:
                idx = K
        self.portComboBox.setCurrentIndex(idx)

        self.serialConnectButton.clicked.connect(self.on_serial_connect)
        self.networkConnectButton.clicked.connect(self.on_network_connect)

        self.update_button_status()

    def update_button_status(self):
        if self.client.is_connected():
            if self.client.comm_mode == PWDTimerCommMode.SERIAL:
                self.serialConnectButton.setText("Disconnect")
                self.networkConnectButton.setEnabled(False)
            elif self.client.comm_mode == PWDTimerCommMode.NETWORK:
                self.networkConnectButton.setText("Disconnect")
                self.serialConnectButton.setEnabled(False)
        else:
            self.networkConnectButton.setText("Connect")
            self.serialConnectButton.setText("Connect")
            self.networkConnectButton.setEnabled(True)            
            self.serialConnectButton.setEnabled(True)

    def on_network_connect(self):

        if self.networkConnectButton.text() == "Connect":
            host = self.hostLineEdit.text()
            port = int(self.portLineEdit.text())
            self.client.connect_wifi(host,port)
        else:
            self.client.disconnect_wifi()
            host = None
            port = None
        self.update_button_status()
        

    def on_serial_connect(self):
        if self.serialConnectButton.text() == "Connect":
            selected_port_idx = self.portComboBox.currentIndex()
            selected_port = self.portList[selected_port_idx]

            full_port_name = selected_port.portName()
            if platform == "linux" or platform == "linux2" or platform == "darwin":
                full_port_name = "/dev/" + full_port_name
            
            self.client.connect_serial(full_port_name)        
        else:
            self.client.disconnect_serial()
        
        self.update_button_status()

    def get_lane_count(self):
        lanes = int(self.laneCountLineEdit.text())
        return lanes
