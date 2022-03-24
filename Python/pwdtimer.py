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

class PWDTimer(QtWidgets.QMainWindow):
    connected = False
    num_lanes = 4
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
        toolButton.clicked.connect(self.on_open_comms_button_press)
        self.mainToolBar.addWidget(toolButton)


        # Set up the action handlers
        # self.commsButton.clicked.connect(self.on_open_comms_button_press)
        # self.competitorsButton.clicked.connect(self.on_open_competitors_button_press)
       
        self.create_race_table_view()

        groupsModel = QStandardItemModel()
        groupsModel.setHorizontalHeaderItem(0, QStandardItem("Group"))
        groupsModel.dataChanged.connect(self.on_groups_changed)
        
        self.groupsTreeView.setModel(groupsModel)
        self.groupsTreeView.setSelectionModel(QItemSelectionModel())
        self.groupsTreeView.selectionModel().selectionChanged.connect(self.on_group_selection_changed)

        self.heatsGroupTreeView.setModel(groupsModel)
        self.heatsGroupTreeView.setSelectionModel(QItemSelectionModel())
        self.heatsGroupTreeView.selectionModel().selectionChanged.connect(self.on_heat_group_selection_changed)

        racersModel = QStandardItemModel(0,3,self)
        racersModel.setHorizontalHeaderItem(0, QStandardItem("Name"))
        racersModel.setHorizontalHeaderItem(1, QStandardItem("Car Name"))
        racersModel.setHorizontalHeaderItem(2, QStandardItem("Number"))
        racersModel.dataChanged.connect(self.on_racers_changed)
        self.racersTableView.setModel(racersModel)

        self.create_heats_table()

        self.client = PWDTimerClient()

        # Initialize a timer for the communications with the timer electronics
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.monitorTimerThread)
        self.timer.start(25)      

        

    def on_load_races(self):
        
        filename = QFileDialog.getOpenFileName(self,"Open race data", ".", "JSON (*.json)")

        self.participants = []
        self.filename = filename[0]
        if self.filename != '':
            self.racedata = RaceData(self.filename)
            self.update_groups_and_racers()
    
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


    def on_groups_changed(self, tleft, bright, roles):
        row = tleft.row()
        col = tleft.column()

        model = self.groupsTreeView.model()
        name = model.data(model.index(row,0))
        self.racedata.groups[row].name = name

    def on_racers_changed(self, tleft, bright):
        racer_row = tleft.row()
        racer_col = tleft.column()

        groups_index = self.groupsTreeView.currentIndex()
        groups_row = groups_index.row()

        if groups_row == -1:
            print('ERROR: group not selected')
            return
        
        model = self.racersTableView.model()
        name = model.data(model.index(racer_row,0))
        car_name = model.data(model.index(racer_row,1))
        car_number = model.data(model.index(racer_row,2))

        self.racedata.groups[groups_row].racers[racer_row].name = name
        self.racedata.groups[groups_row].racers[racer_row].car_name = car_name
        self.racedata.groups[groups_row].racers[racer_row].car_number = car_number        
    
    
    
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
        font = QApplication.font()
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

        # Need to add a new racer
        self.racedata.groups[index.row()].add_racer( Racer('<racer name>', '<car name>', '<car number>', []))

        # Populate the row with placeholder data
        racersModel.setData(racersModel.index(rowPosition,0), '<racer name>')
        racersModel.setData(racersModel.index(rowPosition,1), '<car name>')
        racersModel.setData(racersModel.index(rowPosition,2), '<car number>')
       

    def remove_racer(self):
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
        # index = racersModel.index(0,0)
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
            
    def update_groups_and_racers(self):
        
        groupsModel = self.groupsTreeView.model()
        groupsModel.removeRows(0, groupsModel.rowCount())

        for group in self.racedata.groups:
            item = QStandardItem(group.name)
            groupsModel.appendRow(item)

        # Select the first item in the treeview (should trigger and update signal for loading the racers)
        index = groupsModel.index(0,0)
        self.groupsTreeView.setCurrentIndex(index)
        self.heatsGroupTreeView.setCurrentIndex(index)


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
            newModel.dataChanged.connect(self.on_racers_changed)
            self.racersTableView.setModel(newModel)     

    def on_heat_group_selection_changed(self, selected, deselected):
        if selected.indexes():
            heatsModel = self.heatsTableView.model()
            heatsModel.removeRows(0, heatsModel.rowCount())

            row = selected.indexes()[ 0 ].row()
            newModel = QStandardItemModel(self.num_lanes,len(self.racedata.groups[row].racers),self)
            for I in range(self.num_lanes):
                newModel.setVerticalHeaderItem(I, QStandardItem(f"Lane {I+1}"))

            racers = self.racedata.groups[row].racers
            for I,racer in enumerate(racers):                
                for J in range(self.num_lanes):
                    col = (I+J)%len(racers)
                    newModel.setData(newModel.index(J,col), racer.name)

                    if len(racer.times) > 0 and racer.times[J] != 0:
                        row, col = self.participantLaneToRowCol(I, J)
                        # model.setData(model.index(row,col), QVariant(QColor(Qt.red)), Qt.DecorationRole)
                        newModel.setData(newModel.index(row,col), QVariant(self.style().standardIcon(QStyle.SP_DialogApplyButton)), Qt.DecorationRole)
                        
            self.heatsTableView.setModel(newModel)

    def on_groups_tab(self):
        self.tabWidget.setCurrentIndex(0)

    def on_heat_tab(self):
        self.tabWidget.setCurrentIndex(1)

    def on_race_tab(self): 
        self.tabWidget.setCurrentIndex(2)

    def create_heats_table(self):
        model = QStandardItemModel(self.num_lanes, len(self.participants) )
        for I in range(self.num_lanes):
            model.setVerticalHeaderItem(I, QStandardItem(f"Lane {I+1}"))

        # for I, part in enumerate(self.participants):
        #     for J in range(self.num_lanes):
        #         col = (I+J)%len(self.participants)
        #         model.setData(model.index(J,col), part.participantName)

        #         if part.raceTimes[J] != 0:
        #             row, col = self.participantLaneToRowCol(I, J)
        #             # model.setData(model.index(row,col), QVariant(QColor(Qt.red)), Qt.DecorationRole)
        #             model.setData(model.index(row,col), QVariant(self.style().standardIcon(QStyle.SP_DialogApplyButton)), Qt.DecorationRole)
                    
        self.heatsTableView.setModel(model)

        self.heatsTableView.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        font = QApplication.font() # self.competitorsButton.font()
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

        racers = self.racedata.groups[row].racers

        idx1 = participant + lane*(len(racers)+1)
        idx2 = participant + lane*(len(racers))

        col = idx1 % len(racers)
        row = int(idx2 / len(racers))

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
    app.setStyle(QStyleFactory.create("Fusion"))

    window = PWDTimer()
    window.show()

    sys.exit(app.exec_())