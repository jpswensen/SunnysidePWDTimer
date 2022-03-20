from PyQt5 import QtWidgets, uic, QtCore, QtSerialPort
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from sys import platform

from resources import *
from pwdtimer_communications import *

class ParticipantInfo:
    participantName = ''
    carName = ''
    carNumber = ''
    raceTimes = []

    def __init__(self, participant_name='', car_name='', car_number=-1, race_times=[]) -> None:
        self.participantName = participant_name
        self.carName = car_name
        self.carNumber = car_number
        self.raceTimes = race_times
        

class EditCompetitorsDialog(QDialog):
    def __init__(self, competitor_list=[], parent=None):
        QDialog.__init__(self, parent)
        uic.loadUi(resource_path('editcompetitorsdialog.ui'),self)

        self.competitors = competitor_list
        self.updateCompetitorsTable()

    def updateCompetitorsTable(self):
        # Create the header row
        model = QStandardItemModel(len(self.competitors)+1,3,self)
        model.setHorizontalHeaderItem(0, QStandardItem("Name"))
        model.setHorizontalHeaderItem(1, QStandardItem("Car Name"))
        model.setHorizontalHeaderItem(2, QStandardItem("Delete"))

        # Fill in the existing data
        for K,competitor in enumerate(self.competitors):
            model.setData(model.index(K,0), competitor.participantName)
            model.setData(model.index(K,1), competitor.carName)        
        self.participantsTable.setModel(model)

        # Add the buttons for deleting a row
        for K,competitor in enumerate(self.competitors):
            part = self.competitors[K]

            delButton = QPushButton()
            delButton.setText("Delete")

            self.participantsTable.setIndexWidget(model.index(K,2), delButton)

            delButton.clicked.connect(lambda state, x=K: self.on_delete_button_pushed(x))

        self.participantsTable.model().dataChanged.connect(self.on_data_changed)
        # connect(ui->participantsTable->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));

    def on_delete_button_pushed(self,idx):
        self.participantsTable.model().removeRow(idx)

    def on_data_changed(self, tleft, bright):
        row = tleft.row()
        col = tleft.column()

        model = self.participantsTable.model()
        if row == model.rowCount()-1:
            model.insertRow(row+1)

            delButton = QPushButton()
            delButton.setText("Delete")
            
            self.participantsTable.setIndexWidget(model.index(row,2), delButton)
            delButton.clicked.connect(lambda state, x=row: self.on_delete_button_pushed(x))

    def participants(self):
        participants = []
        model = self.participantsTable.model()
        for I in range(model.rowCount()-1):
            name = model.data(model.index(I,0))
            car_name = model.data(model.index(I,1))
            participants.append( ParticipantInfo(name,car_name, I+1))
        return participants

