#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>
#include <array>
#include <QtSerialPort/QtSerialPort>
#include "participantinfo.h"
#include "editcompetitorsdialog.h"
#include "raceresultsdialog.h"
#include "serialportdialog.h"

namespace Ui {

/*! Enumeration for specifying lane by name */
typedef enum LaneEnum {
    LANEA = 0,
    LANEB,
    LANEC,
    LANED
} Lane_t;

/*! Enumeration for the possibles states of the microcontroller timer hardware */
typedef enum TimerStateEnum {
    UNDEFINED = 0,
    RESET,
    SET,
    IN_RACE,
    FINISHED
} TimerState_t;

class MainWindow;
}


/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupSerial ();
    void updateHeatsTable ();

    void heatToParticipants (int heat, int (&part)[4], int (&lane)[4]);
    void participantLaneToRowColumn (int participant, Ui::Lane_t lane, int& row, int& col);

private:
    Ui::MainWindow *ui;

    // Various arrays to give indexed access to UI elements.
    std::array<QLabel *,4> racerNames;
    std::array<QLabel *,4> racerLanes;
    std::array<QLabel *,4> racerTimes;
    std::array<QLabel *,4> racerFinish;

    // Variables for use with serial port hardware
    QSerialPortInfo m_serialPortInfo;
    QSerialPort *m_serialPort;
    QByteArray  m_readData;
    QTimer      m_timer;

    QTextStream m_standardOutput;

    // The full list of participants and their current race times
    QList<ParticipantInfo> m_participants;

    // Variables indicating the current race, the current participants
    int m_currentHeat;
    QList<ParticipantInfo> m_currentHeatParticipants;

    // Stores the current race filename
    QString m_filename;


    // Secondary dialogue window used for modifying racers.
    EditCompetitorsDialog* m_ecd;
    RaceResultsDialog*     m_rrd;
    SerialPortDialog*      m_spd;

private slots:


    void loadRaces();
    void saveRaces();
    void saveRacesAs();

    void acceptParticipantsDialog();
    void rejectParticipantsDialog();

    void acceptSerialPortDialog();

    void on_resetButton_clicked();
    void on_acceptButton_clicked();

    void on_competitorsButton_clicked();
    void on_resultsButton_clicked();
    void on_serialButton_clicked();

    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError serialPortError);

    void onColumnChanged(const QModelIndex &index);

};

#endif // MAINWINDOW_H
