#ifndef EDITCOMPETITORSDIALOG_H
#define EDITCOMPETITORSDIALOG_H

#include <QDialog>

namespace Ui {
class EditCompetitorsDialog;
}

class EditCompetitorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditCompetitorsDialog(QWidget *parent = 0);
    ~EditCompetitorsDialog();

private:
    Ui::EditCompetitorsDialog *ui;
};

#endif // EDITCOMPETITORSDIALOG_H
