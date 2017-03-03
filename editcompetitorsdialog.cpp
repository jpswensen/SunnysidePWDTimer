#include "editcompetitorsdialog.h"
#include "ui_editcompetitorsdialog.h"

EditCompetitorsDialog::EditCompetitorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCompetitorsDialog)
{
    ui->setupUi(this);
}

EditCompetitorsDialog::~EditCompetitorsDialog()
{
    delete ui;
}
