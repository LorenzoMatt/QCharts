#include "graficobasewidget.h"


GraficoBase *GraficoBaseWidget::getGrafico() const
{
    return grafico;
}

void GraficoBaseWidget::setGrafico(GraficoBase *newGrafico)
{
    grafico = newGrafico;
}

GraficoBaseWidget::GraficoBaseWidget(): grafico(nullptr)
{
}

GraficoBaseWidget::GraficoBaseWidget(GraficoBase *grafico)
    : QChartView(), grafico(grafico)
{
}
