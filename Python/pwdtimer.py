from http.client import RESET_CONTENT
from json import tool
import sys
from PyQt5 import QtWidgets, uic, QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import time
import configparser
from pathlib import Path
import os

from resources import *
from commdialog import *
from editcompetitorsdialog import *
from pwdtimer_communications import *

from racefiles import *

class CircleLabel(QLabel):

    def __init__(self, parent=None):
        QLabel.__init__(self,parent)
        self.pixmap = DrawCircle()
        self.setPixmap(self.pixmap)

    def setColor(self, color):
        self.pixmap.setColor(color)
        self.setPixmap(self.pixmap)

class DrawCircle(QPixmap):
    size = 20
    color = Qt.red

    def __init__(self, parent=None):
        QPixmap.__init__(self, self.size, self.size)
        self.fill(Qt.transparent)
        self.painter = QPainter(self)
        self.painter.begin(self)
        self.redraw()

    def __del__(self):
        self.painter.end()

    def redraw(self):
        radx = (self.size-2)/2
        rady = (self.size-2)/2
        center = QPoint(self.size/2,self.size/2)
                
        self.painter.setRenderHint(QPainter.Antialiasing)
        self.painter.setPen(self.color)
        self.painter.setBrush(self.color)
        self.painter.drawEllipse(center, radx, rady)

    def setColor(self, color):
        self.color = color

        self.redraw()

class VLine(QFrame):
    # a simple VLine, like the one you get from designer
    def __init__(self):
        super(VLine, self).__init__()
        self.setFrameShape(self.VLine|self.Sunken)

class PWDTimer(QtWidgets.QMainWindow):
    connected = False
    
    participants = []
    filename = None
    racedata = None

    def __init__(self):
        super().__init__()

        uic.loadUi(resource_path('mainwindow.ui'),self)

        
        self.raceGroupsWidget = self.tabWidget.widget(0) 
        self.raceHeatsWidget = self.tabWidget.widget(1)
        self.currentRaceWidget = self.tabWidget.widget(2)
        # TODO third widget

        self.racedata = RaceData()
        self.update_panel_racedata()

        self.raceHeatsWidget.set_heat_selection_callback(self.heat_selection_changed)

        toolButton = QToolButton()
        toolButton.setText("Apple")
        toolButton.setCheckable(True)
        toolButton.setAutoExclusive(True)
        toolButton.setIcon(QIcon(resource_path("icon1.png")))
        toolButton.clicked.connect(self.on_open_comms_button_press)
        self.mainToolBar.addWidget(toolButton)


        self.statusBar = QStatusBar()
        self.commTypeLabel = QLabel("No comm selected")        
        self.commStatusLabel = CircleLabel()
        
        self.statusBar.addPermanentWidget(VLine())
        self.statusBar.addPermanentWidget(self.commTypeLabel)
        self.statusBar.addPermanentWidget(VLine())
        self.statusBar.addPermanentWidget(self.commStatusLabel)
        self.statusBar.addPermanentWidget(VLine())
        self.setStatusBar(self.statusBar)

        # self.commStatusLabel.setColor(Qt.green)
        self.client = PWDTimerClient()
        # self.client.connect_serial('/dev/cu.usbserial-0001')

        # Initialize a timer for the communications with the timer electronics
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.monitorTimerThread)
        self.timer.start(25)      

    def heat_selection_changed(self,groupnum, heatnum):
        self.currentRaceWidget.update_heat_data(groupnum,heatnum)

    def update_panel_racedata(self):
        self.raceGroupsWidget.set_racedata(self.racedata)
        self.raceHeatsWidget.set_racedata(self.racedata)
        self.currentRaceWidget.set_racedata(self.racedata)

    def on_load_races(self):
        
        filename = QFileDialog.getOpenFileName(self,"Open race data", ".", "JSON (*.json)")

        self.participants = []
        self.filename = filename[0]
        if self.filename != '':
            self.racedata = RaceData(self.filename)

            self.update_panel_racedata()
    
    def on_import_from_csv(self):
        filename = QFileDialog.getOpenFileName(self,"Open race data", ".", "CSV (*.csv)")
        csv_filename = filename[0]
        if csv_filename != '':
            self.racedata = RaceData()
            self.racedata.import_from_csv(csv_filename)
            self.update_groups_and_racers()

    def on_save_races(self):

        if self.filename == None :
            self.on_save_races_as()
        else:
            json_dict = self.racedata.dict()
            
            with open(self.filename, 'w') as outfile:              
                json.dump(json_dict, outfile, indent=4, sort_keys=True)

    def on_save_races_as(self):
        filename = QFileDialog.getSaveFileName(self, "Save race data as...", ".", "JSON (*.json)")
        if filename != "":
            self.filename = filename[0]
            self.on_save_races()

   

    def on_open_comms_button_press(self):
        dialog = CommDialog(self.racedata.num_lanes, self.client)
        result = dialog.exec_()
        if result == QDialog.Accepted:
            lanes = dialog.get_lane_count()
            self.racedata.num_lanes = lanes
            self.update_panel_racedata()

    def on_groups_tab(self):
        self.tabWidget.setCurrentIndex(0)

    def on_heat_tab(self):
        self.tabWidget.setCurrentIndex(1)

    def on_race_tab(self): 
        self.tabWidget.setCurrentIndex(2)

    def participantLaneToRowCol(self, participant, lane):

        racers = self.racedata.groups[row].racers

        idx1 = participant + lane*(len(racers)+1)
        idx2 = participant + lane*(len(racers))

        col = idx1 % len(racers)
        row = int(idx2 / len(racers))

        return col,row

    def heat_to_participants(self,heat):
        #, int (&part)[4], int (&lane)[4])
        lane = []
        part = []
        for I in range(self.racedata.num_lanes):
            p = (heat + len(self.participants) - I) % len(self.participants)
            l = I
            lane.append(I)
            part.append(p)
        return lane, part

    @QtCore.pyqtSlot()
    def monitorTimerThread(self):

        if self.client.is_connected():
            self.commStatusLabel.setColor(Qt.green)
        else:
            self.commStatusLabel.setColor(Qt.red)

        mstr = self.client.recv_message()
        if mstr == None or len(mstr) < 3:            
            return
        timestamp = time.time()
        msg = PWDTimerMessage(mstr)

        if msg.get_state() == PWDTimerState.RESET:
            print(f"Waiting for race to start: {timestamp}")
        elif msg.get_state() == PWDTimerState.SET:
            print(f"Gate armed and waiting for race to start: {timestamp}")
        elif msg.get_state() == PWDTimerState.IN_RACE:
            print(f'Timer time: {msg.get_lane_times()}    Timestamp: : {timestamp}')
        elif msg.get_state() == PWDTimerState.FINISHED:
            print(f'Race done: {timestamp}')

        self.currentRaceWidget.set_current_race_state(msg)

# Launch the application
if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    app.setApplicationName("PWDTimer")
    app.setStyle(QStyleFactory.create("Fusion"))

    window = PWDTimer()
    window.show()

    sys.exit(app.exec_())