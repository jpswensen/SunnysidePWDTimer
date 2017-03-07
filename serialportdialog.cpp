#include "serialportdialog.h"
#include "ui_serialportdialog.h"



SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);

    m_portList = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : m_portList) {
        ui->portComboBox->addItem(serialPortInfo.portName());
    }

}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

QSerialPortInfo SerialPortDialog::getSelectedPort()
{
    int portListIndex = ui->portComboBox->currentIndex();
    return m_portList[portListIndex];
}
