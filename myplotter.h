#ifndef MYPLOTTER_H
#define MYPLOTTER_H

#include <QMainWindow>
#include "mychart.h"
#include "mychartview.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTableWidgetItem>
#include <QMenu>


QT_BEGIN_NAMESPACE
namespace Ui { class MyPlotter; }
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class MyPlotter : public QMainWindow
{
    Q_OBJECT

public:
    MyPlotter(QWidget *parent = nullptr);
    ~MyPlotter();

    void addRow();

    void deleteRow();

private slots:
    void on_generateButton_clicked();

    void on_addNewRowButton_clicked();

    void ShowContextMenu(const QPoint&);

    void on_deleteRowButton_clicked();

private:
    Ui::MyPlotter *ui;

    bool *ok;
    QVector<QStringList> series;

    unsigned char conversionTypeFlag;

    void drawPlot();
};
#endif // MYPLOTTER_H
