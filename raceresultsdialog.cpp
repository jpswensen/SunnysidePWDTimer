#include "raceresultsdialog.h"
#include "ui_raceresultsdialog.h"

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

RaceResultsDialog::RaceResultsDialog(QList<ParticipantInfo>& participants, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaceResultsDialog),
    m_participants(participants)
{
    ui->setupUi(this);

    updateResultsTable();
}

RaceResultsDialog::~RaceResultsDialog()
{
    delete ui;
}

void RaceResultsDialog::setTableFont (QFont& font)
{
    ui->resultsTableView->setFont(font);
}

void RaceResultsDialog::updateResultsTable ()
{
    // Set up the model of the QTableView
    QStandardItemModel *model = new QStandardItemModel(m_participants.length(),7,this); //2 Rows and 3 Columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Car Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Lane A")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lane B")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Lane C")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Lane D")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Average")));

    model->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignHCenter);
    model->horizontalHeaderItem(3)->setTextAlignment(Qt::AlignHCenter);
    model->horizontalHeaderItem(4)->setTextAlignment(Qt::AlignHCenter);
    model->horizontalHeaderItem(5)->setTextAlignment(Qt::AlignHCenter);
    model->horizontalHeaderItem(6)->setTextAlignment(Qt::AlignHCenter);

    for (int i = 0 ; i < m_participants.length() ; i++)
    {
        ParticipantInfo part = m_participants.at(i);

        model->setData(model->index(i, 0), part.participantName());
        model->setData(model->index(i, 1), part.carName());

        model->setData(model->index(i, 2), QString::number(part.raceTime(0)));
        model->setData(model->index(i, 3), QString::number(part.raceTime(1)));
        model->setData(model->index(i, 4), QString::number(part.raceTime(2)));
        model->setData(model->index(i, 5), QString::number(part.raceTime(3)));

        model->setData(model->index(i, 6), QString::number(part.averageRaceTime()));


        model->setData(model->index(i, 2), Qt::AlignHCenter, Qt::TextAlignmentRole);
        model->setData(model->index(i, 3), Qt::AlignHCenter, Qt::TextAlignmentRole);
        model->setData(model->index(i, 4), Qt::AlignHCenter, Qt::TextAlignmentRole);
        model->setData(model->index(i, 5), Qt::AlignHCenter, Qt::TextAlignmentRole);
        model->setData(model->index(i, 6), Qt::AlignHCenter, Qt::TextAlignmentRole);

    }
    ui->resultsTableView->setModel(model);


    ui->resultsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->resultsTableView->resizeRowsToContents();
}

void RaceResultsDialog::on_printButton_clicked()
{
    qreal in = 72;
    QRectF canvasRect(-0.1*in, -0.1*in, 6*in, 4*in);
    qreal margins = 0.1*in;
    QRectF actualCanvasRect = canvasRect.adjusted(margins,margins,-margins,-margins);

    // TESTING: Print a whole window
    // FIXME: This is printing too large, even when I tell the print dialog to "scale to fit page".
    // I think I probably need to use a QPainter to paint to the full size and then just scale that
    // QPainter output and then render to the printer.
    QPrinter printer;
    QPrinter::Orientation orient = (actualCanvasRect.width() >
                                        actualCanvasRect.height() ?
                                        QPrinter::Landscape : QPrinter::Portrait);
    printer.setOrientation(orient);
    printer.setPaperSize(canvasRect.size(), QPrinter::Point);
    printer.setPageMargins(margins, margins, margins, margins, QPrinter::Point);

    QPrintDialog(&printer).exec();

    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = ui->resultsTableView->size();
    size.scale(rect.size(), Qt::KeepAspectRatio);
    painter.setViewport(rect.x(), rect.y(),
                                size.width(), size.height());
    painter.setWindow(ui->resultsTableView->rect());
    ui->resultsTableView->render(&painter);

    // FIXME: Create QPainter and render the window to the QPainter instead
    //ui->resultsTableView->render(&printer);
    //this->render(&printer);

    // FIXME: Scale the QPainter and then render the QPainter to the QPrinter

}


void RaceResultsDialog::on_closeButton_clicked()
{
    this->close();
}
