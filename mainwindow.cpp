#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QStandardItem>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QFile>

#include "editcompetitorsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serialPort(NULL),
    m_standardOutput(stdout),
    m_filename("")
{
    ui->setupUi(this);

    // Set up a std::array for each type of field for easy access by indexing later.
    racerNames  = {{ui->racerName1, ui->racerName2, ui->racerName3, ui->racerName4}};
    racerLanes  = {{ui->racerLane1, ui->racerLane2, ui->racerLane3, ui->racerLane4}};
    racerTimes  = {{ui->racerTime1, ui->racerTime2, ui->racerTime3, ui->racerTime4}};
    racerFinish = {{ui->racerFinish1, ui->racerFinish2, ui->racerFinish3, ui->racerFinish4}};

    // Fake some racer names so that we can fill in the race brackets
    /*
    m_participants.append( ParticipantInfo("Jacob Swensen","Reverse Flash"));
    m_participants.append( ParticipantInfo("Aaron Swensen","The Alchemist"));
    m_participants.append( ParticipantInfo("Adam Swensen","Kokipolo"));
    m_participants.append( ParticipantInfo("Tommy Swensen","Knock Knock"));
    m_participants.append( ParticipantInfo("John Swensen","King of the Hill"));
    m_participants.append( ParticipantInfo("Brittney Swensen","Superfast"));

    int parts[4];
    int lanes[4];
    heatToParticipants(3,parts,lanes);
    for (int i = 0 ; i < 4 ; i++)
    {
        m_standardOutput << i << " " << parts[i] << " " << lanes[i] << endl;
        m_participants[parts[i]].setRaceTime(lanes[i], 1.45);
    }
    */

    connect(ui->actionLoad_races, &QAction::triggered, this, &MainWindow::loadRaces);
    connect(ui->actionSave_races, &QAction::triggered, this, &MainWindow::saveRaces);
    connect(ui->actionSave_races_as, &QAction::triggered, this, &MainWindow::saveRacesAs);

    // Initialize the table with the current participants
    updateHeatsTable();

    // Configure the serial port
    setupSerial();


}

void MainWindow::loadRaces()
{
    m_standardOutput << "load races" << endl;

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open race data"), "",
            tr("CSV (*.csv)"));
    if (fileName != "")
    {
        m_participants.clear();
        m_filename = fileName;

        // Open the file as read-only
        QFile file(m_filename);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
            return ;
        }

        // Iterate through every line, split it up by commas, generate the participant list (with times) and reload the table
        int i = 1;
        while (!file.atEnd()) {
            QStringList wordList;
            QByteArray line = file.readLine();
            foreach( QByteArray item, line.split(',') )
                wordList << item;

            float raceTimes[4] = {wordList[2].toFloat(),wordList[3].toFloat(),wordList[4].toFloat(),wordList[5].toFloat()};

            m_participants.append( ParticipantInfo(wordList[0], wordList[1], i++, raceTimes));
        }

        file.close();

        updateHeatsTable();
    }

}

void MainWindow::saveRaces()
{
    m_standardOutput << "save races" << endl;

    // If a file hasn't been loaded yet, force the Save As dialog.
    // Otherwise, save using the same filename as was previously loaded.
    if (m_filename == "")
    {
        saveRacesAs();
    }
    else
    {
        // Open the file as read-write and overwrite the file
        QFile file(m_filename);
        file.open( QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text );
        QTextStream out(&file);

        // Iterate through the list of participants and save out the participant name, car name, and race times (or zeros if they haven't been loaded yet)
        for (int i = 0 ; i < m_participants.length() ; i++)
        {
            ParticipantInfo part = m_participants.at(i);

            out << part.participantName() << "," << part.carName() << "," << part.raceTime(0) << "," << part.raceTime(1) << "," << part.raceTime(2) << "," << part.raceTime(3) << ",\n";

        }
        out.flush();
        file.close();
    }
}

void MainWindow::saveRacesAs()
{
    m_standardOutput << "save races as" << endl;

    // For Save As, always open the file save dialog to get a filename. Then trigger the normal Save function
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save race data"), "",
            tr("CSV (*.csv)"));
    if (fileName != "")
    {
        m_filename = fileName;

        saveRaces();
    }
}

MainWindow::~MainWindow()
{
    if (m_serialPort)
        m_serialPort->close();

    delete ui;
}

void MainWindow::onColumnChanged(const QModelIndex &index)
{
    m_currentHeat = index.column();

    int parts[4];
    int lanes[4];
    heatToParticipants(m_currentHeat,parts,lanes);

    for (int i = 0 ; i < 4 ; i++)
    {
        m_standardOutput << i << " " << parts[i] << " " << m_participants[parts[i]].participantName() << endl;
        racerNames[i]->setText(m_participants[parts[i]].participantName() + " (" + QString::number(m_participants[parts[i]].carNumber()) + ")");
    }
}

void MainWindow::setupSerial ()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    m_standardOutput << QObject::tr("Total number of ports available: ") << serialPortInfos.count() << endl;

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();
        m_standardOutput << endl
            << QObject::tr("Port: ") << serialPortInfo.portName() << endl
            << QObject::tr("Location: ") << serialPortInfo.systemLocation() << endl
            << QObject::tr("Description: ") << (!description.isEmpty() ? description : blankString) << endl
            << QObject::tr("Manufacturer: ") << (!manufacturer.isEmpty() ? manufacturer : blankString) << endl
            << QObject::tr("Serial number: ") << (!serialNumber.isEmpty() ? serialNumber : blankString) << endl
            << QObject::tr("Vendor Identifier: ") << (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) << endl
            << QObject::tr("Product Identifier: ") << (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString) << endl
            << QObject::tr("Busy: ") << (serialPortInfo.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) << endl;

        if (serialPortInfo.portName().startsWith("cu.wchusbserial"))
        {
            m_standardOutput << endl << "Opening serial port" << endl;
            m_serialPort = new QSerialPort(serialPortInfo);
            m_serialPort->setBaudRate(QSerialPort::Baud115200);
            m_serialPort->setDataBits(QSerialPort::Data8);
            m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
            m_serialPort->setParity(QSerialPort::NoParity);
            m_serialPort->setStopBits(QSerialPort::OneStop);
            m_serialPort->open(QIODevice::ReadWrite);

            m_serialPort->write("RESET");
            m_serialPort->flush();
            m_readData.clear();


            for (int i = 0 ; i < 4 ; i++)
            {
                racerTimes[i]->setText("0.000");
                racerFinish[i]->setText("-");
            }
            m_serialPort->flush();
            m_readData.clear();

            connect(m_serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
            connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                        this, &MainWindow::handleError);
            connect(&m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);

            m_serialPort->flush();
            m_readData.clear();

            m_timer.start(5000);

            break;
        }
    }
}

void MainWindow::updateHeatsTable ()
{
    // Set up the model of the QTableView
    QStandardItemModel *model = new QStandardItemModel(4,m_participants.length(),this); //2 Rows and 3 Columns

    model->setVerticalHeaderItem(0, new QStandardItem(QString("Lane A")));
    model->setVerticalHeaderItem(1, new QStandardItem(QString("Lane B")));
    model->setVerticalHeaderItem(2, new QStandardItem(QString("Lane C")));
    model->setVerticalHeaderItem(3, new QStandardItem(QString("Lane D")));


    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        for (int j = 0 ; j < 4 ; j++)
        {
            int column = (i+j)%m_participants.length();


            model->setData(model->index(j, column), part.participantName());

            if (part.raceTime(j) != 0.0)
            {
                int row, col;
                participantLaneToRowColumn(i, (Ui::Lane_t)j, row, col);
                m_standardOutput << "ASDF " <<  i << " " << j << " " << row << " " << col << endl;
                model->setData(model->index(row, col), QVariant(QColor(Qt::red)), Qt::DecorationRole);

            }
        }
    }

    ui->heatsTableView->setModel(model);

    ui->heatsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFont font = ui->competitorsButton->font();
    font.setPointSize(48);
    ui->heatsTableView->horizontalHeader()->setFont( font );
    ui->heatsTableView->verticalHeader()->setFont( font );
    ui->heatsTableView->setSelectionBehavior(QAbstractItemView::SelectColumns);
    ui->heatsTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->heatsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    font.setPointSize(36);
    font.setBold(false);
    ui->heatsTableView->setFont(font);


    QPalette* palette = new QPalette();
    QColor bg(50,200,50);
    palette->setColor(QPalette::Highlight,bg);
    palette->setColor(QPalette::HighlightedText,Qt::white);
    ui->heatsTableView->setPalette(*palette);

    connect(ui->heatsTableView->selectionModel()
            , SIGNAL(currentColumnChanged(QModelIndex,QModelIndex))
            , SLOT(onColumnChanged(QModelIndex)));
}

void MainWindow::heatToParticipants (int heat, int (&part)[4], int (&lane)[4])
{
    for (int i = 0 ; i < 4 ; i++)
    {
        part[i] = (heat + m_participants.length() - i) % m_participants.length();
        lane[i] = i;
    }
}

void MainWindow::participantLaneToRowColumn (int participant, Ui::Lane_t lane, int& row, int& col)
{
    // 0,1,2,3,4,5
    // 5,0,1,2,3,4
    // 4,5,0,1,2,3
    // 3,4,5,0,1,2

    // P/L => idx
    // p=0, l=0 => 0
    // p=0, l=1 => 6  => p+(l)*(N+1)
    // p=0, l=2 => 12 => p+(l)*(N+1)
    // p=0, l=3 => 18
    // p=1, l=0 => 1
    // p=1, l=1 => 7

    int idx1 = participant + lane*(m_participants.length()+1);
    int idx2 = participant + lane*(m_participants.length());

    col = idx1 % m_participants.length();
    row = idx2 / m_participants.length();
}

void MainWindow::handleReadyRead()
{
    QString message = "";
    if (m_serialPort->bytesAvailable() > 64)
        message = m_serialPort->readLine();
    else
        return;

    QRegExp rx("[$, *\r\n]");// match a comma or a space
    QStringList list = message.split(rx, QString::SkipEmptyParts);
    if (list.length() < 7)
    {
        m_readData.clear();
        return;
    }

    Ui::TimerState_t state = (Ui::TimerState_t)list.at(0).toInt();
    long startTime = list.at(1).toLong();
    long currentTime = list.at(2).toLong();
    long endTime[4];
    for (int i = 0 ; i < 4 ; i++)
    {
        endTime[i] = list.at(3+i).toLong();

        if (endTime[i] == 0)
        {
            endTime[i] = currentTime;
        }

        float tempTime = (endTime[i]-startTime)*1E-6; // time since start in seconds

        this->racerTimes[i]->setText( QString::number(tempTime,'f',4) );
    }

    for (int i = 0 ; i < 4 ; i++)
    {
        int numGreaterThan = 0;
        for (int j = 0 ; j < 4 ; j++)
        {

            if (endTime[j] > endTime[i])
            {
                numGreaterThan++;
            }
        }
        if (numGreaterThan > 0 || state == Ui::FINISHED)
            this->racerFinish[i]->setText( QString::number(4-numGreaterThan) );
    }


    m_readData.clear();


    if (!m_timer.isActive())
        m_timer.start(5000);
}

void MainWindow::handleTimeout()
{
    if (m_readData.isEmpty()) {
        m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        m_standardOutput << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        m_standardOutput << m_readData << endl;
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }
}

void MainWindow::on_competitorsButton_clicked()
{
    m_ecd = new EditCompetitorsDialog(m_participants, this);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(m_ecd);
    m_ecd->resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
    m_ecd->move((availableGeometry.width() - m_ecd->width()) / 2,
                        (availableGeometry.height() - m_ecd->height()) / 2);

    connect(m_ecd, SIGNAL(accepted()), this, SLOT(acceptParticipantsDialog()));
    //connect(m_ecd->buttonBox(), SIGNAL(rejected()), this, SLOT(rejectParticipantsDialog()));

    m_ecd->show();

}

void MainWindow::acceptParticipantsDialog()
{
    m_participants = m_ecd->participants();


    updateHeatsTable();
}

void MainWindow::rejectParticipantsDialog()
{

}

void MainWindow::on_resultsButton_clicked()
{
    m_rrd = new RaceResultsDialog(m_participants, this);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(m_rrd);
    m_rrd->resize(availableGeometry.width(), availableGeometry.height());
    m_rrd->move((availableGeometry.width() - m_rrd->width()) / 2,
                        (availableGeometry.height() - m_rrd->height()) / 2);

    //connect(m_ecd, SIGNAL(accepted()), this, SLOT(acceptParticipantsDialog()));
    //connect(m_ecd->buttonBox(), SIGNAL(rejected()), this, SLOT(rejectParticipantsDialog()));

    QFont font = ui->competitorsButton->font();
    font.setPointSize(24);
    m_rrd->setFont(font);

    font.setPointSize(36);
    font.setBold(false);
    m_rrd->setTableFont(font);



    m_rrd->show();
}

void MainWindow::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->acceptButton->setEnabled(false);

    // TODO: (1) UDP "RESET" message to the microcontroller
    //       (2) Keep the contestants the same, but zero out the times and the finish positions
    //       (3) The start button will become "enabled" once the UDP listener thread verifies that the
    //           microcontroller is in the "RESET" state.
    m_serialPort->write("RESET");
    m_serialPort->flush();
    m_readData.clear();


    for (int i = 0 ; i < 4 ; i++)
    {
        racerTimes[i]->setText("0.000");
        racerFinish[i]->setText("-");
    }
    m_serialPort->flush();
    m_readData.clear();
}

void MainWindow::on_startButton_clicked()
{
    ui->acceptButton->setEnabled(false);

    // TODO: Tell the UDP listener thread that it should be ready for the gate to open and the times to start rolling in.
}

void MainWindow::on_acceptButton_clicked()
{
    //ui->resetButton->setEnabled(true);
    //ui->acceptButton->setEnabled(false);

    // Move the results from this race up into the final results
    int parts[4];
    int lanes[4];
    heatToParticipants(m_currentHeat,parts,lanes);

    for (int i = 0 ; i < 4 ; i++)
    {
        m_participants[parts[i]].setRaceTime(lanes[i],racerTimes[i]->text().toInt());
    }
    updateHeatsTable();

}





// NOTES: Here are a few notes about things I have been thinking about how the code should work
//  1) We want to make it easy to be able to "re-run" a particular heat in the case that a car jumps the track, etc.
//     So, the plan is to have the columns in the "Heat Overview Panel" be selectable. If selected, then it will populate the
//     "Single Heat Panel" with the racer names. Then if the race is reset, run, and accepted, it will replace the results
//     in the "Heat Overview Panel". DONE
//  2) When running a race, the time will increment equally for all the racers in the "Single Heat Panel" and then stop
//     incrementing once that car has crossed the finish line. This way we don't need a separate timer for the overall
//     elapsed time. The text should be big enough on a projector for everyone to easily see. DONE
//  3) Printing would be nice so that kids can take home a memory of how they did. It might even be nice to have a separate printout for each boy
//     These could easily be rendered off-screen and just printed out with their time from all 4 races. IN PROGRESS
//  4) I should make one more dialog to select the serial port. I don't want to have to recompile if it shows up with a different name. I also plan
//     on having binaries for Windows and MacOS, so it makes sense to have it selectable by the user because the naming is very different on different
//     platforms. The setup will simply query all the serial ports like we do now and then populate a drop-down list to choose from. We can probably
//     still assume 115200-8-N-1 because the microcontroller defines that.
//  5) I think I need a better protocal/interaction between the microcontroller and the QSerialPort interface. Sometimes it glitches on both the time
//     and the finish position when doing a clear. Also, the start button doesn't reall do anything. One possible way of doing things will be to send
//     the RESET, wait a bit, then flush the serial port. That way all the new data coming it will certainly be all zeros. I think the problem is either
//     that it takes a few hundred milliseconds for the RESET to take effect in the microcontroller, or there are some messages buffered up.
//  6) I want to add a quick visual indicator of the status of the start gate. More than anything, we want to ensure that the start gate is closed and
//     that we are looking for it to open before starting the timers. I could ensure that after a RESET has been sent that the (largely symbolic) START
//     button cannot be pressed until the microcontroller verifies that the gate is closed. Hence, we might need to add one more state to the microcontroller
//     code that is after the RESET and after the gate is close and after the START button is pressed. I propose:
//          PC --> RESET --> uC == changes uC state to RESET
//          uC detects gate is closed == changes uC state to READY
//          PC --> START --> uC == changes uC state to SET
//     The microcontroller code will only look for a gate open when in the SET mode. No messages sent for the RESET state. READY state must be sent to let the PC
//     know when it is allowed to send the START message.
