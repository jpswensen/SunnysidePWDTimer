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

class RaceGroupsWidget(QWidget):
    racedata = None

    def __init__(self,parent=None):
        QWidget.__init__(self,parent)
        uic.loadUi(resource_path('race_groups_widget.ui'),self)

        groupsModel = QStandardItemModel()
        groupsModel.setHorizontalHeaderItem(0, QStandardItem("Group"))
        groupsModel.dataChanged.connect(self.on_groups_changed)
        
        self.groupsTreeView.setModel(groupsModel)
        self.groupsTreeView.setSelectionModel(QItemSelectionModel())
        self.groupsTreeView.selectionModel().selectionChanged.connect(self.on_group_selection_changed)

        racersModel = QStandardItemModel(0,3,self)
        racersModel.setHorizontalHeaderItem(0, QStandardItem("Name"))
        racersModel.setHorizontalHeaderItem(1, QStandardItem("Car Name"))
        racersModel.setHorizontalHeaderItem(2, QStandardItem("Number"))
        racersModel.dataChanged.connect(self.on_racers_changed)
        self.racersTableView.setModel(racersModel)

    def set_racedata(self, racedata):
        self.racedata = racedata
        self.update_groups_and_racers()

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

    def update_groups_and_racers(self):        
        groupsModel = self.groupsTreeView.model()
        groupsModel.removeRows(0, groupsModel.rowCount())

        for group in self.racedata.groups:
            item = QStandardItem(group.name)
            groupsModel.appendRow(item)

        # Select the first item in the treeview (should trigger and update signal for loading the racers)
        index = groupsModel.index(0,0)
        self.groupsTreeView.setCurrentIndex(index)
        #self.heatsGroupTreeView.setCurrentIndex(index)