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

namespace Ui {

typedef enum LaneEnum {
    LANE1 = 0,
    LANE2,
    LANE3,
    LANE4
} Lane_t;

typedef enum TimerStateEnum {
  UNDEFINED = 0,
  RESET,
  IN_RACE,
  FINISHED
} TimerState_t;

class MainWindow;
}

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

    std::array<QLabel *,4> racerNames;
    std::array<QLabel *,4> racerLanes;
    std::array<QLabel *,4> racerTimes;
    std::array<QLabel *,4> racerFinish;

    QSerialPort *m_serialPort;
    QByteArray  m_readData;
    QTimer      m_timer;
    int         m_place;

    QTextStream m_standardOutput;

    QList<ParticipantInfo> m_participants;
    int m_currentHeat;
    QList<ParticipantInfo> m_currentHeatParticipants;

    QString m_filename;
    EditCompetitorsDialog* m_ecd;

private slots:

    void loadRaces();
    void saveRaces();
    void saveRacesAs();

    void acceptParticipantsDialog();
    void rejectParticipantsDialog();

    void on_resetButton_clicked();
    void on_startButton_clicked();
    void on_acceptButton_clicked();

    void on_competitorsButton_clicked();
    void on_resultsButton_clicked();

    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError serialPortError);

    void onColumnChanged(const QModelIndex &index);

};

#endif // MAINWINDOW_H
