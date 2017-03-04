#ifndef EDITCOMPETITORSDIALOG_H
#define EDITCOMPETITORSDIALOG_H

#include <QDialog>
#include <QStandardItem>
#include <QList>
#include <QPushButton>

#include "participantinfo.h"


namespace Ui {
class EditCompetitorsDialog;
}

class EditCompetitorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditCompetitorsDialog(QList<ParticipantInfo>& participants, QWidget *parent = 0);
    ~EditCompetitorsDialog();

    void updateCompetitorsTable ();

private:
    Ui::EditCompetitorsDialog *ui;

    QList<ParticipantInfo>& m_participants;
};

#endif // EDITCOMPETITORSDIALOG_H
