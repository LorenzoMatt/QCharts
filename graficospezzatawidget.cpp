#include "graficospezzatawidget.h"

GraficoSpezzataWidget::GraficoSpezzataWidget()
{

}

GraficoSpezzataWidget::GraficoSpezzataWidget(GraficoBase * grafico): GraficoBaseWidget(grafico)
{

}

void GraficoSpezzataWidget::visualizzaGrafico()
{
    GraficoSpezzata *graficoLinee = dynamic_cast<GraficoSpezzata *>(grafico);
    QLineSeries *series = new QLineSeries();
    QCategoryAxis *axisX = new QCategoryAxis();

    unsigned int contatore = 1;
    for (auto it = graficoLinee->getValori().begin(); it != graficoLinee->getValori().end(); ++it)
    {
        series->append(contatore, (*it)->getValore());
        axisX->append(QString::fromStdString((*it)->getNome()), contatore);
        contatore++;
    }

    chart->setTitle(QString::fromStdString(grafico->getTitolo()));
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QFont font;
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(QString::fromStdString(graficoLinee->getTitolo()));
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAxisX(axisX, series);
    setChart(chart);
}
