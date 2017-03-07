#ifndef RACERESULTSDIALOG_H
#define RACERESULTSDIALOG_H

#include <QDialog>
#include <QStandardItem>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QDialogButtonBox>

#include "participantinfo.h"

namespace Ui {
class RaceResultsDialog;
}

class RaceResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RaceResultsDialog(QList<ParticipantInfo>& participants, QWidget *parent = 0);
    ~RaceResultsDialog();

    void setTableFont (QFont& font);
    void updateResultsTable ();

private:
    Ui::RaceResultsDialog *ui;

    QList<ParticipantInfo>& m_participants;

private slots:
    void on_printButton_clicked();
    void on_closeButton_clicked();

    void sortByColumn(int column);
};

#endif // RACERESULTSDIALOG_H
