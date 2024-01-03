#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_USE_NAMESPACE

class myChartView : public QChartView
{
public:
    myChartView(QChart *chart, QWidget *parent = 0);
protected:
    bool viewportEvent(QEvent *event);
};

#endif // MYCHARTVIEW_H
