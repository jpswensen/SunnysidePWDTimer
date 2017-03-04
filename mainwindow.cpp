#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serialPort(NULL),
    m_standardOutput(stdout)
{
    ui->setupUi(this);

    // Set up a std::array for each type of field for easy access by indexing later.
    racerNames = {{ui->racerName1, ui->racerName2, ui->racerName3, ui->racerName4}};
    racerLanes = {{ui->racerLane1, ui->racerLane2, ui->racerLane3, ui->racerLane4}};
    racerTimes = {{ui->racerTime1, ui->racerTime2, ui->racerTime3, ui->racerTime4}};
    racerFinish = {{ui->racerFinish1, ui->racerFinish2, ui->racerFinish3, ui->racerFinish4}};

    // Start the thread to be listening for the UDP messages
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

    //m_serialPort = QSerialPort(&serialPortInfos[0]);
}

MainWindow::~MainWindow()
{
    if (m_serialPort)
        m_serialPort->close();

    delete ui;
}

void MainWindow::handleReadyRead()
{

    /*
    QByteArray data = m_serialPort->read(1);
    while (data[0] != '$')
    {
        data = m_serialPort->read(1);
    }
    m_readData.append(data);

    while (data[0] != '*')
    {
        data = m_serialPort->read(1);
        m_readData.append(data);
    }

    QString message = QString::fromUtf8(m_readData.data());
*/
    QString message = "";
    if (m_serialPort->bytesAvailable() > 64)
        message = m_serialPort->readLine();
    else
        return;

    //m_standardOutput << message << endl;

    QRegExp rx("[$, *\r\n]");// match a comma or a space
    QStringList list = message.split(rx, QString::SkipEmptyParts);
    if (list.length() < 7)
    {
        m_readData.clear();
        return;
    }
    //qDebug() << list;

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
