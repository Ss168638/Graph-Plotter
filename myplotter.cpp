#include "myplotter.h"
#include "ui_myplotter.h"

#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QDebug>


MyPlotter::MyPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyPlotter)
    , ok(nullptr)
{
    ui->setupUi(this);
    conversionTypeFlag = 16;
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenu(QPoint)));
}

MyPlotter::~MyPlotter()
{
    delete ui;
}

void MyPlotter::addRow()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    int row, column;
    row = ui->tableWidget->rowCount();
    column = ui->tableWidget->columnCount();
    QTableWidgetItem *item = new QTableWidgetItem(tr("Paste/Enter data in cell"));
    ui->tableWidget->setItem(row-1, column-1, item);
}

void MyPlotter::deleteRow()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}


void MyPlotter::on_generateButton_clicked()
{

    int rowCount = ui->tableWidget->rowCount();

    for(int i=0; i<rowCount; i++)
    {
        QString rowData = ui->tableWidget->item(i, 0)->text();
        if(rowData.endsWith("\n") || rowData.endsWith(" ")) rowData.chop(1);
        QStringList data = rowData.replace('\t', " ").replace('\n', " ").split(" ").toVector().toList();
        series.append(data);    //add row data to the series

       QTableWidgetItem *item = new QTableWidgetItem(rowData); //make new TableWidgetItem and add the parsed data to it
        ui->tableWidget->setItem(i, 0, item);   //update table row with TableWidgetItem data
    }

    if(ui->hexRadioButton->isChecked()) conversionTypeFlag = 16;
    else if(ui->DecRadioButton->isChecked()) conversionTypeFlag = 10;

    drawPlot();
}

void MyPlotter::drawPlot()
{

    myChart *mChart = new myChart();
    int totalSeries = 1;
    for(auto& item : series)
    {
        qDebug() << item;

        QLineSeries *mseries = new QLineSeries();
        unsigned int size = item.length();

        for(unsigned int i = 0; i < size; i++)
        {
            qDebug() << (qreal)item[i].toInt(ok, conversionTypeFlag);
            QPointF p((qreal) i, (qreal)item[i].toInt(ok, conversionTypeFlag));
            *mseries << p;
        }
        mseries->setName(QString("Data %1").arg(totalSeries));
        mChart->addSeries(mseries);
        totalSeries++;
    }

    mChart->setTitle("Graph");
    mChart->setAnimationOptions(QChart::AllAnimations);
    mChart->createDefaultAxes();

    myChartView *mChartView = new myChartView(mChart);
    mChartView->setRenderHint(QPainter::Antialiasing);

    ui->plotLayout->addWidget(mChartView, 0, 0);
    series.clear();
}

void MyPlotter::on_addNewRowButton_clicked()
{
    addRow();
}

void MyPlotter::ShowContextMenu(const QPoint&)
{
    QMenu *menu = new QMenu;
    auto addRow = menu->addAction("Add Row");
    QObject::connect(addRow, &QAction::triggered, this, [this, menu, addRow](){
        qDebug() << "Row Added ";
        //add New Row to the table
        this->addRow();

        addRow->deleteLater();
        menu->deleteLater();
    });
    auto delRow = menu->addAction("Delete Row");
    QObject::connect(delRow, &QAction::triggered, this, [this, menu, delRow](){
        qDebug() << "Deleted Row";

        //delete the selected row from table
        deleteRow();

        delRow->deleteLater();
        menu->deleteLater();
    });
    menu->exec(QCursor::pos());
    menu->clear();

    QObject::connect(menu, &QMenu::aboutToHide, menu, &QWidget::deleteLater);
}


void MyPlotter::on_deleteRowButton_clicked()
{
    deleteRow();
}

