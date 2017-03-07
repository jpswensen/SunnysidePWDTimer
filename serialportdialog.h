#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

#include <QSerialPortInfo>

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(QWidget *parent = 0);
    ~SerialPortDialog();

    QSerialPortInfo getSelectedPort();

private:
    Ui::SerialPortDialog *ui;

    QList<QSerialPortInfo> m_portList;
};

#endif // SERIALPORTDIALOG_H
