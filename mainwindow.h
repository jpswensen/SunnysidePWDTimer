#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>
#include <array>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::array<QLabel *,4> racerNames;
    std::array<QLabel *,4> racerLanes;
    std::array<QLabel *,4> racerTimes;
    std::array<QLabel *,4> racerFinish;


private slots:
    void on_resetButton_clicked();
    void on_startButton_clicked();
    void on_acceptButton_clicked();

};

#endif // MAINWINDOW_H
