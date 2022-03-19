import sys
from PyQt5 import QtWidgets, uic, QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import time
import configparser
from pathlib import Path
import os

from pwdtimer_communications import *

class PWDTimer(QtWidgets.QMainWindow):

    connected = False

    def __init__(self):
        super().__init__()
        uic.loadUi("mainwindow.ui",self)

        # Set up the action handlers
        self.actionLoad.triggered.connect(self.on_load_races)
        self.actionSave.triggered.connect(self.on_save_races)
        self.actionSaveAs.triggered.connect(self.on_save_races_as)
        self.actionHeats.triggered.connect(self.on_heat_tab)
        self.actionRace.triggered.connect(self.on_race_tab)
        

        # Connect the buttons back to the PyQT5 .ui file
        # self.loadConfigFileButton.clicked.connect(self.loadConfigFileButtonPress)
        # self.loadDataFileButton.clicked.connect(self.loadDataFileButtonPress)
        # self.processDataFileButton.clicked.connect(self.processDataFileButtonPress)
        # self.analyzePushButton.clicked.connect(self.analyzePushButtonPress)

        # self.reboundStopTimeLineEdit.editingFinished.connect(self.reboundStopTimeEditingFinished)

        # self.shotGatesTextEdits = [self.shotGate1TextEdit, self.shotGate2TextEdit, self.shotGate3TextEdit, self.shotGate4TextEdit]
        # self.reboundGatesTextEdits = [self.reboundGate1TextEdit, self.reboundGate2TextEdit, self.reboundGate3TextEdit, self.reboundGate4TextEdit]

        # self.useShotGatesCheckBox = [self.useShotGate1CheckBox,self.useShotGate2CheckBox,self.useShotGate3CheckBox,self.useShotGate4CheckBox]
        # self.useReboundGatesCheckBox = [self.useReboundGate1CheckBox,self.useReboundGate2CheckBox,self.useReboundGate3CheckBox,self.useReboundGate4CheckBox]
       
        self.client = PWDTimerClient()
        self.client.connect('pwdtimer.local',8080) # this works because of the MDNS software running on the device
        self.client.recv_flush()
        self.client.reset_race()

        # Initialize a timer for the communications with the timer electronics
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.monitorTimerThread)
        self.timer.start(25)            
    
    def on_load_races(self):
        pass
    
    def on_save_races(self):
        pass

    def on_save_races_as(self):
        pass

    def on_heat_tab(self):
        self.tabWidget.setCurrentIndex(0)

    def on_race_tab(self): 
        self.tabWidget.setCurrentIndex(1)

    @QtCore.pyqtSlot()
    def monitorTimerThread(self):
        print("Thread")
        mstr = self.client.recv_message()
        if len(mstr) < 3:
            return
        timestamp = time.time()
        msg = PWDTimerMessage(mstr)

        if msg.get_state() == PWDTimerState.RESET:
            print(f"Waiting for race to start: {timestamp}")
            self.stateLabel.setText("ON YOUR MARK (please arm the start gate)")
        elif msg.get_state() == PWDTimerState.SET:
            print(f"Gate armed and waiting for race to start: {timestamp}")
            self.stateLabel.setText("GET SET (place cars on the track)")
        elif msg.get_state() == PWDTimerState.IN_RACE:
            print(f'Timer time: {msg.get_lane_times()}    Timestamp: : {timestamp}')
            self.stateLabel.setText("GO!!!!")
        elif msg.get_state() == PWDTimerState.FINISHED:
            print(f'Race done, resetting in 5 seconds: {timestamp}')
            self.stateLabel.setText("RACE FINISHED")
            # time.sleep(2)
            # self.client.recv_flush()
            # self.client.reset_race()

# Launch the application
if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    app.setApplicationName("PWDTimer")

    window = PWDTimer()
    window.show()

    sys.exit(app.exec_())