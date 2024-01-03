#include "mychart.h"
#include <QChart>

myChart::myChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{

}

myChart::~myChart()
{

}

