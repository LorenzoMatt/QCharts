#ifndef GRAFICOSPEZZATAWIDGET_H
#define GRAFICOSPEZZATAWIDGET_H

#include "graficospezzata.h"
#include "graficobasewidget.h"


#include <QCategoryAxis>
#include <QLineSeries>

using QtCharts::QCategoryAxis;
using QtCharts::QLineSeries;

class GraficoSpezzataWidget : public GraficoBaseWidget
{

public:
    GraficoSpezzataWidget();
    GraficoSpezzataWidget(GraficoBase *grafico);
    void visualizzaGrafico() override;
};

#endif // GRAFICOSPEZZATAWIDGET_H
