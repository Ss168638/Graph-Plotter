#include "mychartview.h"

myChartView::myChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

bool myChartView::viewportEvent(QEvent *event)
{
    return QChartView::viewportEvent(event);
}
