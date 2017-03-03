#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(true);
    ui->startButton->setEnabled(true);
    ui->acceptButton->setEnabled(false);

    // TODO: Stop UDP listening threads and send the UDP "RESET" message to the microcontroller

}

void MainWindow::on_startButton_clicked()
{
    ui->acceptButton->setEnabled(false);

    // TODO: Kick off a thread to start listening for the UDP message for the race results
}

void MainWindow::on_acceptButton_clicked()
{
    ui->resetButton->setEnabled(true);
    ui->acceptButton->setEnabled(false);

    // TODO: Move the results from this race up into the final results



    // TESTING: Print a whole window
    // FIXME: This is printing too large, even when I tell the print dialog to "scale to fit page".
    // I think I probably need to use a QPainter to paint to the full size and then just scale that
    // QPainter output and then render to the printer.
    QPrinter printer;
    QPrintDialog(&printer).exec();

    // FIXME: Create QPainter and render the window to the QPainter instead
    this->render(&printer);

    // FIXME: Scale the QPainter and then render the QPainter to the QPrinter
}





// NOTES: Here are a few notes about things I have been thinking about how the code should work
//  1) We want to make it easy to be able to "re-run" a particular heat in the case that a car jumps the track, etc.
//     So, the plan is to have the columns in the "Heat Overview Panel" be selectable. If selected, then it will populate the
//     "Single Heat Panel" with the racer names. Then if the race is reset, run, and accepted, it will replace the results
//     in the "Heat Overview Panel".
//  2) When running a race, the time will increment equally for all the racers in the "Single Heat Panel" and then stop
//     incrementing once that car has crossed the finish line. This way we don't need a separate timer for the overall
//     elapsed time. The text should be big enough on a projector for everyone to easily see.
//  3) Printing would be nice so that kids can take home a memory of how they did. It might even be nice to have a separate printout for each boy
//     These could easily be rendered off-screen and just printed out with their time from all 4 races.
