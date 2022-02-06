#include "mainwindow.h"
#include "graficicontroller.h"

QChartView* MainWindow::creaTorta()
{
    GraficoTorta* t = controller->getGraficoTorta();

    QPieSeries *series = new QPieSeries();
    for (auto it= t->getFette().begin();it != t->getFette().end();++it) {
        QPieSlice *slice = new QPieSlice(QString::fromStdString(it->first),it->second);
        series->append(slice);
        slice->setLabelVisible();
    }

    // Add label, explode and define brush for 2nd slice
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setExploded();
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::darkGreen, 2));
    slice1->setBrush(Qt::green);

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(t->getTitolo()));
    chart->legend()->hide();

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

GraficiController *MainWindow::getController() const
{
    return controller;
}

void MainWindow::setController(GraficiController *newController)
{
    controller = newController;
}

QChartView *MainWindow::getChartView() const
{
    return chartView;
}

void MainWindow::setChartView(QChartView *newChartView)
{
    chartView = newChartView;
}

QChartView* MainWindow::createGraficoBarre()
{
    GraficoBarre* graficoBarre =controller->getGraficoBarre();

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    for (auto it = graficoBarre->getDati().begin(); it!=graficoBarre->getDati().end();++it ) {
        QBarSet* bar = new QBarSet(QString::fromStdString(it->first));
        list<double> l = it->second;
        for(auto it2 = l.begin(); it2!= l.end(); ++it2){
            bar->append(*it2);
        }
        series->append(bar);
    }

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle(QString::fromStdString(graficoBarre->getTitolo()));

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles


    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;
    for(auto it = graficoBarre->getCategorie().begin(); it!= graficoBarre->getCategorie().end(); ++it){
        categories.append(QString::fromStdString(*it));
    }
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // 2. Stacked Bar chart
    // chart->setAxisY(axis, series);

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

 QChartView * MainWindow::createGraficoLinee()
{
    GraficoLinee* graficoLinee = controller->getGraficoLinee();
    QLineSeries *series = new QLineSeries();
    QCategoryAxis *axisX = new QCategoryAxis();

    unsigned int contatore = 0;
    for (auto it = graficoLinee->getValori().begin();it != graficoLinee->getValori().end();++it) {
        series->append(contatore, it->second);
        axisX->append(QString::fromStdString(it->first), contatore);
        contatore++;
    }
    // Create chart, add data, hide legend, and add axis
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(QString::fromStdString(graficoLinee->getTitolo()));

    // Change the line color and weight
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    // Change the x axis categories

    chart->setAxisX(axisX, series);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

MainWindow::~MainWindow()
{
}


MainWindow::MainWindow(GraficiController *controller, QChartView *chartView, QWidget *parent) : QMainWindow(parent),
    controller(controller),
    chartView(chartView)
{

    // 3. Line chart example
    // Other options here https://doc.qt.io/qt-5.11/qtcharts-customchart-example.html

//     chartView= createGraficoLinee();


//    chartView = creaTorta();
    chartView= createGraficoBarre();
//    GraficoBarre *g = new GraficoBarre();
//    controller->setGrafico(g);
    setCentralWidget(chartView);
    resize(420, 300);
    show();

}
