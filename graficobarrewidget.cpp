#include "graficobarre.h"
#include "graficobarrewidget.h"



GraficoBarreWidget::GraficoBarreWidget()
{

}

GraficoBarreWidget::GraficoBarreWidget(GraficoBase * grafico): GraficoBaseWidget(grafico)
{
}

void GraficoBarreWidget::visualizzaGrafico()
{
    GraficoBarre *graficoBarre = dynamic_cast<GraficoBarre *>(grafico);

    QBarSeries *series = new QBarSeries();

    for (auto it = graficoBarre->getDati().begin(); it != graficoBarre->getDati().end(); ++it)
    {
        QBarSet *bar = new QBarSet(QString::fromStdString((*it)->getNome()));
        list<double> l = (*it)->getValori();
        for (auto it2 = l.begin(); it2 != l.end(); ++it2)
        {
            bar->append(*it2);
        }
        series->append(bar);
    }
    chart = new QChart();
    chart->addSeries(series);

    chart->setAnimationOptions(QChart::AllAnimations);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;
    for (auto it = graficoBarre->getCategorie().begin(); it != graficoBarre->getCategorie().end(); ++it)
    {
        categories.append(QString::fromStdString(*it));
    }
    axis->append(categories);
    chart->createDefaultAxes();

    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    setRenderHint(QPainter::Antialiasing);
    setChart(chart);
}
