#ifndef GRAFICOBARREWIDGET_H
#define GRAFICOBARREWIDGET_H

#include "graficobasewidget.h"
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>


using QtCharts::QBarSeries;
using QtCharts::QBarSet;
using QtCharts::QBarCategoryAxis;

class GraficoBarreWidget : public GraficoBaseWidget
{
public:
    GraficoBarreWidget();
    GraficoBarreWidget(GraficoBase * grafico);
    void visualizzaGrafico() override;
};

#endif // GRAFICOBARREWIDGET_H
