#ifndef EDITCOMPETITORSDIALOG_H
#define EDITCOMPETITORSDIALOG_H

#include <QDialog>
#include <QStandardItem>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include <QDialogButtonBox>

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

    QDialogButtonBox* buttonBox();

    QList<ParticipantInfo> participants();

private:
    Ui::EditCompetitorsDialog *ui;

    QList<ParticipantInfo>& m_participants;

private slots:
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    void handleDeleteButton(int row);
};

#endif // EDITCOMPETITORSDIALOG_H
