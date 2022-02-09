#ifndef GRAFICOBASEWIDGET_H
#define GRAFICOBASEWIDGET_H

#include "graficobase.h"

#include <QChartView>
#include <QChart>

using QtCharts::QChartView;
using QtCharts::QChart;

class GraficoBaseWidget : public QChartView
{
    Q_OBJECT
protected:
    QChart* chart;
    GraficoBase* grafico;
public:
    explicit GraficoBaseWidget();
    explicit GraficoBaseWidget(GraficoBase* grafico);
    virtual void visualizzaGrafico() = 0;

    GraficoBase *getGrafico() const;
    void setGrafico(GraficoBase *newGrafico);

signals:

};

#endif // GRAFICOBASEWIDGET_H
