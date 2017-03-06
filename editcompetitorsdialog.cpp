#include "editcompetitorsdialog.h"
#include "ui_editcompetitorsdialog.h"

EditCompetitorsDialog::EditCompetitorsDialog(QList<ParticipantInfo>& participants, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCompetitorsDialog),
    m_participants(participants)
{
    ui->setupUi(this);

    updateCompetitorsTable();
}

EditCompetitorsDialog::~EditCompetitorsDialog()
{
    delete ui;
}

void EditCompetitorsDialog::updateCompetitorsTable ()
{
    // Set up the model of the QTableView
    QStandardItemModel *model = new QStandardItemModel(m_participants.length()+1,3,this); //2 Rows and 3 Columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Car Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Delete")));

    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        model->setData(model->index(i, 0), part.participantName());
        model->setData(model->index(i, 1), part.carName());
    }
    ui->participantsTable->setModel(model);

    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        QPushButton* delButton = new QPushButton();
        delButton->setText("Delete");

        ui->participantsTable->setIndexWidget(model->index(i , 2), delButton);

        connect(delButton, &QPushButton::released, [=]{
            handleDeleteButton(i);
        });
    }

    connect(ui->participantsTable->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));

}

void EditCompetitorsDialog::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    int row = topLeft.row();
    int col = topLeft.column();
    if (row == ui->participantsTable->model()->rowCount()-1)
    {
        ui->participantsTable->model()->insertRow(row+1);

        QPushButton* delButton = new QPushButton();
        delButton->setText("Delete");

        ui->participantsTable->setIndexWidget(ui->participantsTable->model()->index(row , 2), delButton);

        connect(delButton, &QPushButton::released, [=]{
            handleDeleteButton(row);
        });
    }
}

void EditCompetitorsDialog::handleDeleteButton(int row)
{
    ui->participantsTable->model()->removeRow(row);
}

QDialogButtonBox* EditCompetitorsDialog::buttonBox()
{
    return ui->buttonBox;
}

QList<ParticipantInfo> EditCompetitorsDialog::participants()
{
    QList<ParticipantInfo> retval;
    for (int i = 0 ; i < ui->participantsTable->model()->rowCount()-1 ; i++)
    {
        QString name = ui->participantsTable->model()->data(ui->participantsTable->model()->index(i,0)).toString();
        QString carName = ui->participantsTable->model()->data(ui->participantsTable->model()->index(i,1)).toString();

        retval.append( ParticipantInfo(name, carName, i+1));
    }

    return retval;
}
