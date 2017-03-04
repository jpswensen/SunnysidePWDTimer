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
    QStandardItemModel *model = new QStandardItemModel(20,3,this); //2 Rows and 3 Columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Car Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Delete")));

    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        model->setData(model->index(i, 0), part.participantName());
        model->setData(model->index(i, 1), part.carName());

        //QPushButton* delButton = new QPushButton();
        //delButton->setText("Delete");
        //ui->participantsTable->setIndexWidget(model->index(i , 2), delButton);
        //ui->tableView->setIndexWidget(model->index(i , 3), delButton);
        //    connect(delButton , SIGNAL(clicked()) , this , SLOT(delete()));
    }
    ui->participantsTable->setModel(model);

    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        QPushButton* delButton = new QPushButton();
        delButton->setText("Delete");
        ui->participantsTable->setIndexWidget(model->index(i , 2), delButton);

        //    connect(delButton , SIGNAL(clicked()) , this , SLOT(delete()));
    }

    /*
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
            */
}
