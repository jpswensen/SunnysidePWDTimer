from http.client import RESET_CONTENT
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

class PWDTimer(QtWidgets.QMainWindow):
    connected = False
    num_lanes = 8
    participants = []
    filename = None
    racedata = None

    def __init__(self):
        super().__init__()

        uic.loadUi(resource_path('mainwindow.ui'),self)

        self.racedata = RaceData()

        toolButton = QToolButton()
        toolButton.setText("Apple")
        toolButton.setCheckable(True)
        toolButton.setAutoExclusive(True)
        toolButton.setIcon(QIcon(resource_path("icon1.png")))
        self.mainToolBar.addWidget(toolButton)

        # Set up the action handlers
        self.commsButton.clicked.connect(self.on_open_comms_button_press)
        self.competitorsButton.clicked.connect(self.on_open_competitors_button_press)
       
        self.create_race_table_view()

        groupsModel = QStandardItemModel()
        groupsModel.setHorizontalHeaderItem(0, QStandardItem("Group Name"))
        groupsModel.dataChanged.connect(self.on_groups_changed)
        self.groupsTreeView.setModel(groupsModel)


        self.groupsTreeView.setSelectionModel(QItemSelectionModel())
        self.groupsTreeView.selectionModel().selectionChanged.connect(self.on_group_selection_changed)

        racersModel = QStandardItemModel(0,3,self)
        racersModel.setHorizontalHeaderItem(0, QStandardItem("Name"))
        racersModel.setHorizontalHeaderItem(1, QStandardItem("Car Name"))
        racersModel.setHorizontalHeaderItem(2, QStandardItem("Number"))
        self.racersTableView.setModel(racersModel)

        self.client = PWDTimerClient()

        # Initialize a timer for the communications with the timer electronics
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.monitorTimerThread)
        self.timer.start(25)      

        self.update_heats_table()

    def on_groups_changed(self, tleft, bright, roles):
        row = tleft.row()
        col = tleft.column()

        model = self.groupsTreeView.model()
        name = model.data(model.index(row,0))
        self.racedata.groups[row].name = name
        

    def create_race_table_view(self):
        # Create the header row
        model = QStandardItemModel(self.num_lanes,4,self.raceTableView)
        model.setHorizontalHeaderItem(0, QStandardItem("Name"))
        model.setHorizontalHeaderItem(1, QStandardItem("Lane"))
        model.setHorizontalHeaderItem(2, QStandardItem("Time"))
        model.setHorizontalHeaderItem(3, QStandardItem("Place"))
        self.raceTableView.setModel(model)

        # Fill with empty values
        for I in range(self.num_lanes):
            model.setData(model.index(I,0), "---")

            model.setData(model.index(I,1), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,1), str(I+1))

            model.setData(model.index(I,2), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,2), "0.000")

            model.setData(model.index(I,3), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,3), "-")

        # Do some font sizing magic
        font = self.competitorsButton.font()
        font.setPointSize(30)
        self.raceTableView.horizontalHeader().setFont(font)
        self.raceTableView.verticalHeader().setFont(font)
        self.raceTableView.setSelectionMode(QAbstractItemView.SelectionMode.NoSelection)
        self.raceTableView.verticalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)
        self.raceTableView.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)


        self.raceTableView.horizontalHeader().setSectionResizeMode(0, QtWidgets.QHeaderView.ResizeToContents)
        self.raceTableView.horizontalHeader().setSectionResizeMode(1, QtWidgets.QHeaderView.Stretch)
        self.raceTableView.horizontalHeader().setSectionResizeMode(2, QtWidgets.QHeaderView.Stretch)
        self.raceTableView.horizontalHeader().setSectionResizeMode(3, QtWidgets.QHeaderView.Stretch)

        self.raceTableView.horizontalHeader().setResizeContentsPrecision(1000)

        font.setPointSize(40)
        font.setBold(False)
        self.raceTableView.setFont(font)

    def add_group(self):
        groupsModel = self.groupsTreeView.model()
        item = QStandardItem("<new group>")
        groupsModel.appendRow(item)

        self.racedata.groups.append(Group('<new group>'))

    def remove_group(self):
        
        # Get the current index
        index = self.groupsTreeView.currentIndex()
        if index.row() == -1:
            return

        # Dialog to ask them if they really, really want to delete a group
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Information)
        msg.setText("Are you sure you really want to delete a whole group?")
        msg.setWindowTitle("Remove Group")
        msg.setStandardButtons(QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No)
        retval = msg.exec_()
        if retval == QMessageBox.StandardButton.Yes:
            
            # Delete from the treeview
            groupsModel = self.groupsTreeView.model()
            groupsModel.removeRow(index.row())

            # Delete from the racedata
            self.racedata.groups.pop(index.row())

            # Go back to the first group (if there is one)
            index = groupsModel.index(0,0)
            if index.row() == -1:
                # If the last group was removed, clear the racers table
                racersModel = self.racersTableView.model()
                racersModel.removeRows(0, racersModel.rowCount())
            else:
                self.groupsTreeView.setCurrentIndex(index)

    def add_racer(self):

        # If a group isn't selected, don't let them add a racer
        index = self.groupsTreeView.currentIndex()
        if index.row() == -1:
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Information)
            msg.setText("You must have a group selected to add a racer")
            msg.setWindowTitle("Add Racer Error")
            msg.setStandardButtons(QMessageBox.StandardButton.Ok)
            retval = msg.exec_()
            return

        # Find the last row number and add a new row
        racersModel = self.racersTableView.model()
        rowPosition = racersModel.rowCount()
        racersModel.insertRow(rowPosition)

        # Populate the row with placeholder data
        racersModel.setData(racersModel.index(rowPosition,0), '<racer name>')
        racersModel.setData(racersModel.index(rowPosition,1), '<car name>')
        racersModel.setData(racersModel.index(rowPosition,2), '<car number>')

        # Need to add a new racer
        self.racedata.groups[index.row()].add_racer( Racer('<racer name>', '<car name>', '<car number>', []))

    def remove_racer(self):
        pass
        
        index = self.groupsTreeView.currentIndex()
        groupRow = index.row()
        if groupRow == -1:
            msg = QMessageBox()
            msg.setIcon(QMessageBox.Information)
            msg.setText("You must have a group selected to remove a racer")
            msg.setWindowTitle("Remove Racer Error")
            msg.setStandardButtons(QMessageBox.StandardButton.Ok)
            retval = msg.exec_()
            return

        index = self.racersTableView.currentIndex()
        racerRow = index.row()
        if racerRow == -1:
            return

        # Delete from the treeview
        racersModel = self.racersTableView.model()
        racersModel.removeRow(racerRow)

        # Delete from the racedata
        self.racedata.groups[groupRow].racers.pop(racerRow)

        # # Go back to the first group (if there is one)
        # index = groupsModel.index(0,0)
        # if index.row() == -1:
        #     # If the last group was removed, clear the racers table
        #     racersModel = self.racersTableView.model()
        #     racersModel.removeRows(0, racersModel.rowCount())
        # else:
        #     self.groupsTreeView.setCurrentIndex(index)

    



    def on_open_competitors_button_press(self):
        dialog = EditCompetitorsDialog(self.participants)
        result = dialog.exec_()
        if result == QDialog.Accepted:
            self.participants = dialog.participants()

            for p in self.participants:
                if len(p.raceTimes) == 0:
                    p.raceTimes = [0]*self.num_lanes               
            self.update_heats_table()


    def on_open_comms_button_press(self):
        dialog = CommDialog(self.num_lanes, self.client)
        result = dialog.exec_()
        if result == QDialog.Accepted:
            lanes = dialog.get_lane_count()
            self.num_lanes = lanes
            self.create_race_table_view()
            self.update_heats_table()
            

    def on_load_races(self):
        # filename = QFileDialog.getOpenFileName(self,"Open race data", ".", "CSV (*.csv)")
        filename = QFileDialog.getOpenFileName(self,"Open race data", ".", "JSON (*.json)")

        self.participants = []
        self.filename = filename[0]
        if self.filename != '':
            self.racedata = RaceData(self.filename)
            self.update_groups_and_racers()

            # file = QFile(self.filename)
            # if not file.open(QIODevice.ReadOnly):
            #     print(f"Error opening file with error: {file.errorString()}")
            #     return

            # I = 1
            # while not file.atEnd():
            #     line = file.readLine()
            #     line_list = line.split(',')
            #     participant = line_list[0].data().decode('utf-8')
            #     car_name = line_list[1].data().decode('utf-8')
            #     race_times = [float(x.data().decode('utf-8')) for x in line_list[2:2+self.num_lanes]]

            #     p = ParticipantInfo(participant, car_name, I, race_times)
            #     self.participants.append(p)
            # file.close()

            # self.update_heats_table()
    
    def update_groups_and_racers(self):
        pass
        groupsModel = self.groupsTreeView.model()
        groupsModel.removeRows(0, groupsModel.rowCount())

        for group in self.racedata.groups:
            item = QStandardItem(group.name)
            groupsModel.appendRow(item)

        # Select the first item in the treeview (should trigger and update signal for loading the racers)
        index = groupsModel.index(0,0)
        self.groupsTreeView.setCurrentIndex(index)
        # for racers in self.racedata.groups[0].racers:
        #     print(racers)

    def on_group_selection_changed(self, selected, deselected):
        if selected.indexes():
            racersModel = self.racersTableView.model()
            racersModel.removeRows(0, racersModel.rowCount())
            
            row = selected.indexes()[ 0 ].row()
            newModel = QStandardItemModel(len(self.racedata.groups[row].racers),3,self)
            for K,racer in enumerate(self.racedata.groups[row].racers):                
                newModel.setData(newModel.index(K,0), racer.name)
                newModel.setData(newModel.index(K,1), racer.car_name)   
                newModel.setData(newModel.index(K,2), racer.car_number)   
            self.racersTableView.setModel(newModel)     
                # print(racers.name)


    def on_save_races(self):
        if self.filename == None :
            self.on_save_races_as()
        else:
            file = QFile(self.filename)
            file.open(QIODevice.ReadWrite | QIODevice.Truncate | QIODevice.Text)
            out = QTextStream(file)
            for p in self.participants:
                out << p.participantName << ',' << p.carName << ',' 
                for tm in p.raceTimes:
                    out << tm << ','
                out << '\n'
            out.flush()
            file.close()

    def on_save_races_as(self):
        filename = QFileDialog.getSaveFileName(self, "Save race data as...", ".", "CSV (*.csv)")
        if filename != "":
            self.filename = filename[0]
            self.on_save_races()

    def on_groups_tab(self):
        self.tabWidget.setCurrentIndex(0)

    def on_heat_tab(self):
        self.tabWidget.setCurrentIndex(1)

    def on_race_tab(self): 
        self.tabWidget.setCurrentIndex(2)

    def update_heats_table(self):
        model = QStandardItemModel(self.num_lanes, len(self.participants) )
        for I in range(self.num_lanes):
            model.setVerticalHeaderItem(I, QStandardItem(f"Lane {I+1}"))

        for I, part in enumerate(self.participants):
            for J in range(self.num_lanes):
                col = (I+J)%len(self.participants)
                model.setData(model.index(J,col), part.participantName)

                if part.raceTimes[J] != 0:
                    row, col = self.participantLaneToRowCol(I, J)
                    # model.setData(model.index(row,col), QVariant(QColor(Qt.red)), Qt.DecorationRole)
                    model.setData(model.index(row,col), QVariant(self.style().standardIcon(QStyle.SP_DialogApplyButton)), Qt.DecorationRole)
                    
        self.heatsTableView.setModel(model)

        self.heatsTableView.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        font = self.competitorsButton.font()
        font.setPointSize(24)
        self.heatsTableView.horizontalHeader().setFont(font)
        self.heatsTableView.verticalHeader().setFont(font)
        self.heatsTableView.setSelectionBehavior(QAbstractItemView.SelectionBehavior.SelectColumns)
        self.heatsTableView.verticalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)
        self.heatsTableView.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)

        font.setPointSize(16)
        font.setBold(False)
        self.heatsTableView.setFont(font)

        palette = QPalette()
        bg = QColor (50,200,50)
        palette.setColor(QPalette.Highlight,bg)
        palette.setColor(QPalette.HighlightedText, Qt.white)
        self.heatsTableView.setPalette(palette)

        self.heatsTableView.selectionModel().currentColumnChanged.connect(self.on_column_changed)

    def participantLaneToRowCol(self, participant, lane):

        idx1 = participant + lane*(len(self.participants)+1)
        idx2 = participant + lane*(len(self.participants))

        col = idx1 % len(self.participants)
        row = int(idx2 / len(self.participants))

        return col,row

    def on_column_changed(self, index):

        # TODO: Check if connected
        self.client.reset_race()
        model = self.raceTableView.model()
        for I in range(self.num_lanes):

            model.setData(model.index(I,2), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,2), "0.000")
            
            model.setData(model.index(I,3), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,3), "-")
            

        currentHeat = index.column()
        lane, part = self.heat_to_participants(currentHeat)

        for I in range(self.num_lanes):
            racer = self.participants[part[I]].participantName
            model.setData(model.index(I,0), racer)

            timeStr = f'{self.participants[part[I]].raceTimes[I]:0.4f}'
            model.setData(model.index(I,2), timeStr)

    def heat_to_participants(self,heat):
        #, int (&part)[4], int (&lane)[4])
        lane = []
        part = []
        for I in range(self.num_lanes):
            p = (heat + len(self.participants) - I) % len(self.participants)
            l = I
            lane.append(I)
            part.append(p)
        return lane, part

    @QtCore.pyqtSlot()
    def monitorTimerThread(self):
        mstr = self.client.recv_message()
        if mstr == None or len(mstr) < 3:            
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