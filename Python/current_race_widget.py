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
from pwdtimer_communications import *
from racefiles import *

class CurrentRaceWidget(QWidget):
    num_lanes = 0
    racedata = None
    group = -1

    def __init__(self,parent=None):
        QWidget.__init__(self,parent)
        uic.loadUi(resource_path('current_race_widget.ui'),self)

    def reset_button_clicked(self):
        print('Should trigger callback to reset the timer and clear the times')
        

    def set_racedata(self, racedata):
        self.racedata = racedata

        self.create_race_table_view()

    def set_current_race_state(self, msg):
        if msg.get_state() == PWDTimerState.RESET:
            self.statusLabel.setText("ON YOUR MARK (please arm the start gate)")
        elif msg.get_state() == PWDTimerState.SET:
            self.statusLabel.setText("GET SET (place cars on the track)")
        elif msg.get_state() == PWDTimerState.IN_RACE:
            self.statusLabel.setText("GO!!!!")

            model = self.raceTableView.model()
            for I in range(msg.num_lanes):            
                if msg.end_times[I] == 0:
                    racetime = (msg.curr_time - msg.start_time) * 1E-6
                else:
                    racetime = (msg.end_times[I] - msg.start_time) * 1E-6

                timeStr = f'{racetime:0.4f}'

                model.setData(model.index(I,2), timeStr)

        elif msg.get_state() == PWDTimerState.FINISHED:
            self.statusLabel.setText("RACE FINISHED")


        

        # long endTime[4];
        # for (int i = 0 ; i < 4 ; i++)
        # {
        #     endTime[i] = list.at(3+i).toLong();

        #     if (endTime[i] == 0)
        #     {
        #         endTime[i] = currentTime;
        #     }

        #     float tempTime = (endTime[i]-startTime)*1E-6; // time since start in seconds

        #     this->racerTimes[i]->setText( QString::number(tempTime,'f',4) );
        # }


    def update_heat_data(self,group,heat):
        print(f'Heat changed to group {group} heat {heat}')
    
        model = self.raceTableView.model()
        for I in range(self.racedata.num_lanes):

            model.setData(model.index(I,2), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,2), "0.000")
            
            model.setData(model.index(I,3), Qt.AlignCenter, Qt.TextAlignmentRole)
            model.setData(model.index(I,3), "-")            

        #currentHeat = index.column()
        lane, part = self.heat_to_participants(group, heat)

        for I in range(self.racedata.num_lanes):
            racer = self.racedata.groups[group].racers[part[I]].name
            #racer = self.participants[part[I]].participantName
            model.setData(model.index(I,0), racer)

            if I < len(self.racedata.groups[group].racers[part[I]].times):
                racetime = self.racedata.groups[group].racers[part[I]].times[I]
                timeStr = f'{racetime:0.4f}'
                model.setData(model.index(I,2), timeStr)

    def heat_to_participants(self,group,heat):
        #, int (&part)[4], int (&lane)[4])
        lane = []
        part = []

        racers = self.racedata.groups[group].racers
        for I in range(self.racedata.num_lanes):
            p = (heat + len(racers) - I) % len(racers)
            l = I
            lane.append(I)
            part.append(p)
        return lane, part

    def create_race_table_view(self):
        # Create the header row
        model = QStandardItemModel(self.racedata.num_lanes,4,self.raceTableView)
        model.setHorizontalHeaderItem(0, QStandardItem("Name"))
        model.setHorizontalHeaderItem(1, QStandardItem("Lane"))
        model.setHorizontalHeaderItem(2, QStandardItem("Time"))
        model.setHorizontalHeaderItem(3, QStandardItem("Place"))
        self.raceTableView.setModel(model)

        # Fill with empty values
        for I in range(self.racedata.num_lanes):
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
    