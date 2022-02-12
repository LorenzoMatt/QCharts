#include "graficotortawidget.h"


GraficoTortaWidget::GraficoTortaWidget()
{

}

GraficoTortaWidget::GraficoTortaWidget(GraficoBase * grafico): GraficoBaseWidget(grafico)
{

}

void GraficoTortaWidget::visualizzaGrafico()
{
        GraficoTorta *graficoTorta = dynamic_cast<GraficoTorta *>(grafico);
        double tot = 0;
        for (auto it = graficoTorta->getFette().begin(); it != graficoTorta->getFette().end(); ++it)
        {
            tot += it->second;
        }
        QPieSeries *series = new QPieSeries();
        for (auto it = graficoTorta->getFette().begin(); it != graficoTorta->getFette().end(); ++it)
        {
            QPieSlice *slice = new QPieSlice(QString::fromStdString(it->first), calcoloPercentuale(it->second, tot));
            series->append(slice);
            slice->setLabelVisible();
        }
        chart->setTitle(QString::fromStdString(grafico->getTitolo()));
        chart->addSeries(series);
        chart->legend()->hide();
        setChart(chart);
}

double GraficoTortaWidget::calcoloPercentuale(double valore, double totale) const
{
    return valore * 100 / totale;
}
