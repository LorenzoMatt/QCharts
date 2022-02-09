#ifndef GRAFICOTORTAWIDGET_H
#define GRAFICOTORTAWIDGET_H

#include "graficobasewidget.h"
#include "graficotorta.h"
#include <QPieSeries>

using QtCharts::QPieSeries;
using QtCharts::QPieSlice;

class GraficoTortaWidget : public GraficoBaseWidget
{
public:
    GraficoTortaWidget();
    GraficoTortaWidget(GraficoBase*);
    void visualizzaGrafico() override;
private:
    double calcoloPercentuale(double valore, double totale) const;
};

#endif // GRAFICOTORTAWIDGET_H
