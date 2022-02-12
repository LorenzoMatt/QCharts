#include "graficobasewidget.h"

GraficoBase *GraficoBaseWidget::getGrafico() const
{
    return grafico;
}

void GraficoBaseWidget::setGrafico(GraficoBase *newGrafico)
{
    grafico = newGrafico;
}

void GraficoBaseWidget::buildBackground()
{
        // Customize chart title
        QFont font;
        font.setPixelSize(18);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::white));

        // Customize chart background
        QLinearGradient backgroundGradient;
        backgroundGradient.setStart(QPointF(0, 0));
        backgroundGradient.setFinalStop(QPointF(0, 1));
        backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
        backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        chart->setBackgroundBrush(backgroundGradient);

        // Customize plot area background
        QLinearGradient plotAreaGradient;
        plotAreaGradient.setStart(QPointF(0, 1));
        plotAreaGradient.setFinalStop(QPointF(1, 0));
        plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
        plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
        plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        chart->setPlotAreaBackgroundBrush(plotAreaGradient);
        chart->setPlotAreaBackgroundVisible(true);
}

GraficoBaseWidget::GraficoBaseWidget(): grafico(nullptr)
{
    chart = new QChart();
    chart->setTheme(QChart::ChartThemeQt);
    buildBackground();
    setRenderHint(QPainter::Antialiasing);

}

GraficoBaseWidget::~GraficoBaseWidget()
{

}

GraficoBaseWidget::GraficoBaseWidget(GraficoBase *grafico)
    : QChartView(), grafico(grafico)
{
    chart = new QChart();
    chart->setTheme(QChart::ChartThemeQt);
    buildBackground();
    setRenderHint(QPainter::Antialiasing);
}
