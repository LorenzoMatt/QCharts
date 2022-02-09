#include "graficobasewidget.h"


GraficoBase *GraficoBaseWidget::getGrafico() const
{
    return grafico;
}

void GraficoBaseWidget::setGrafico(GraficoBase *newGrafico)
{
    grafico = newGrafico;
}

GraficoBaseWidget::GraficoBaseWidget()
{
    QChart* chart = new QChart();
    setChart(chart);
}

GraficoBaseWidget::GraficoBaseWidget(GraficoBase *grafico)
    : QChartView(), grafico(grafico)
{
    QChart* chart = new QChart();
    setChart(chart);
    chart->setTitle(QString::fromStdString(grafico->getTitolo()));
}
