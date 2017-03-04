#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QStandardItem>
#include <QDesktopWidget>

#include "editcompetitorsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serialPort(NULL),
    m_standardOutput(stdout)
{
    ui->setupUi(this);

    // Set up a std::array for each type of field for easy access by indexing later.
    racerNames  = {{ui->racerName1, ui->racerName2, ui->racerName3, ui->racerName4}};
    racerLanes  = {{ui->racerLane1, ui->racerLane2, ui->racerLane3, ui->racerLane4}};
    racerTimes  = {{ui->racerTime1, ui->racerTime2, ui->racerTime3, ui->racerTime4}};
    racerFinish = {{ui->racerFinish1, ui->racerFinish2, ui->racerFinish3, ui->racerFinish4}};

    // Fake some racer names so that we can fill in the race brackets
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


    // Initialize the table with the current participants
    updateHeatsTable();

    // Configure the serial port
    setupSerial();


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
        racerNames[i]->setText(m_participants[parts[i]].participantName());
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


            m_place = 1;
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
    EditCompetitorsDialog* ecd = new EditCompetitorsDialog(m_participants, this);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(ecd);
    ecd->resize(availableGeometry.width() / 3, availableGeometry.height() * 2 / 3);
    ecd->move((availableGeometry.width() - ecd->width()) / 2,
                        (availableGeometry.height() - ecd->height()) / 2);

    ecd->show();

}

void MainWindow::on_resultsButton_clicked()
{

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


    m_place = 1;
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



    /*
    // TESTING: Print a whole window
    // FIXME: This is printing too large, even when I tell the print dialog to "scale to fit page".
    // I think I probably need to use a QPainter to paint to the full size and then just scale that
    // QPainter output and then render to the printer.
    QPrinter printer;
    QPrintDialog(&printer).exec();

    // FIXME: Create QPainter and render the window to the QPainter instead
    this->render(&printer);

    // FIXME: Scale the QPainter and then render the QPainter to the QPrinter
    */
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
