#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T23:37:47
#
#-------------------------------------------------

QT       += core gui printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SunnysidePWDTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editcompetitorsdialog.cpp \
    participantinfo.cpp \
    raceresultsdialog.cpp \
    serialportdialog.cpp

HEADERS  += mainwindow.h \
    editcompetitorsdialog.h \
    participantinfo.h \
    raceresultsdialog.h \
    serialportdialog.h

FORMS    += mainwindow.ui \
    editcompetitorsdialog.ui \
    raceresultsdialog.ui \
    serialportdialog.ui
