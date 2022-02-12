#include <QAreaSeries>
#include <QPen>

#include "sysinfo.h"
#include "memorywidget.h"

constexpr int CHART_X_RANGE_COUNT = 50;
constexpr int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
constexpr int COLOR_DARK_BLUE = 0x209fdf;
constexpr int COLOR_LIGHT_BLUE = 0xbfdfef;
constexpr int PEN_WIDTH = 3;


MemoryWidget::MemoryWidget(QWidget *parent) :
    SysInfoWidget(parent),
    mSeries(new QLineSeries(this)),
    mPointPositionX(0)
{
    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0,0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);


    QAreaSeries* areaSeries = new QAreaSeries(mSeries);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);

    QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory used");

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setVisible(false);
    chart->axes(Qt::Horizontal).back()->setRange(0, CHART_X_RANGE_MAX);
    chart->axes(Qt::Vertical).back()->setRange(0,100);
}

void MemoryWidget::updateSeries(){
    double memoryUsed = SysInfo::instance().memoryUsed();
    mSeries->append(mPointPositionX++, memoryUsed);

    if(mSeries->count() > CHART_X_RANGE_COUNT){
        QChart* chart = chartView().chart();
        chart->scroll(chart->plotArea().width()/CHART_X_RANGE_MAX, 0);
        mSeries->remove(0);
    }
}
