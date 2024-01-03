#ifndef MYCHART_H
#define MYCHART_H
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class myChart : public QChart
{
    Q_OBJECT
public:
    explicit myChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~myChart();

};

#endif // MYCHART_H
