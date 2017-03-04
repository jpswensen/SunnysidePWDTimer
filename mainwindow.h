#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>
#include <array>
#include <QtSerialPort/QtSerialPort>
#include "participantinfo.h"

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


private slots:
    void on_resetButton_clicked();
    void on_startButton_clicked();
    void on_acceptButton_clicked();

    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError serialPortError);

};

#endif // MAINWINDOW_H
