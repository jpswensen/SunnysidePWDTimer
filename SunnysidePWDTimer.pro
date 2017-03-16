#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T23:37:47
#
#-------------------------------------------------

QT       += core gui printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SunnysidePWDTimer
TEMPLATE = app

macx:ICON = $${PWD}/icons/alignLeft.icns

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

RESOURCES += \
    pwdtimer.qrc

isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT})
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT})
}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

# Use += instead of = if you use multiple QMAKE_POST_LINKs
QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
