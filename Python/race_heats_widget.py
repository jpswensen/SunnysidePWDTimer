import sys
from PyQt5 import QtWidgets, uic, QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import time
import configparser
from pathlib import Path
import os
import typing

from resources import *
from racefiles import *

class RaceHeatsWidget(QWidget):
    num_lanes = 0
    racedata = None

    def __init__(self,parent=None):
        QWidget.__init__(self,parent)
        uic.loadUi(resource_path('race_heats_widget.ui'),self)

        groupsModel = QStandardItemModel()
        groupsModel.setHorizontalHeaderItem(0, QStandardItem("Group"))
        groupsModel.dataChanged.connect(self.on_groups_changed)
        
        self.groupsTreeView.setModel(groupsModel)
        self.groupsTreeView.setSelectionModel(QItemSelectionModel())
        self.groupsTreeView.selectionModel().selectionChanged.connect(self.on_group_selection_changed)

        model = QStandardItemModel(0, 0)
        self.heatsTableView.setModel(model)

    def set_racedata(self, racedata):
        self.racedata = racedata

        model = QStandardItemModel(self.racedata.num_lanes, 0)
        self.heatsTableView.setModel(model)

        self.update_groups_and_heats()

    def update_groups_and_heats(self):
        groupsModel = self.groupsTreeView.model()
        groupsModel.removeRows(0, groupsModel.rowCount())

        for group in self.racedata.groups:
            item = QStandardItem(group.name)
            groupsModel.appendRow(item)

        # Select the first item in the treeview (should trigger and update signal for loading the racers)
        index = groupsModel.index(0,0)
        self.groupsTreeView.setCurrentIndex(index)

        self.create_heats_table()

    def create_heats_table(self):
        index = self.groupsTreeView.currentIndex()
        groupRow = index.row()
        
        numRows = 0
        if groupRow != -1:
            numRows = len(self.racedata.groups[groupRow].racers)
        model = QStandardItemModel(self.racedata.num_lanes, numRows)
        for I in range(self.racedata.num_lanes):
            model.setVerticalHeaderItem(I, QStandardItem(f"Lane {I+1}"))

        # for I, part in enumerate(self.participants):
        #     for J in range(self.racedata.num_lanes):
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

        self.populate_heats(groupRow)

        self.heatsTableView.selectionModel().currentColumnChanged.connect(self.on_column_changed)

    def on_groups_changed(self, tleft, bright, roles):
        row = tleft.row()
        col = tleft.column()

        model = self.groupsTreeView.model()
        name = model.data(model.index(row,0))
        self.racedata.groups[row].name = name

    def populate_heats(self, row):

        numRows = 0
        if row == -1:
            return
            
        numRows = len(self.racedata.groups[row].racers)
        newModel = QStandardItemModel(self.racedata.num_lanes,numRows,self)
        for I in range(self.racedata.num_lanes):
            newModel.setVerticalHeaderItem(I, QStandardItem(f"Lane {I+1}"))

        racers = self.racedata.groups[row].racers
        for I,racer in enumerate(racers):                
            for J in range(self.racedata.num_lanes):
                col = (I+J)%len(racers)
                newModel.setData(newModel.index(J,col), racer.name)

                if len(racer.times) > 0 and racer.times[J] != 0:
                    row, col = self.participantLaneToRowCol(I, J)
                    # model.setData(model.index(row,col), QVariant(QColor(Qt.red)), Qt.DecorationRole)
                    newModel.setData(newModel.index(row,col), QVariant(self.style().standardIcon(QStyle.SP_DialogApplyButton)), Qt.DecorationRole)
                    
        self.heatsTableView.setModel(newModel)

    def on_group_selection_changed(self, selected, deselected):
        if selected.indexes():
            heatsModel = self.heatsTableView.model()
            heatsModel.removeRows(0, heatsModel.rowCount())

            row = selected.indexes()[ 0 ].row()
            self.populate_heats(row)

    def on_column_changed(self, index):

        pass

    

        # self.update_groups_and_heats()