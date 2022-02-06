#include "mainwindow.h"
#include "graficicontroller.h"
#include "creatortaospezzatawidget.h"


//rimuovere il bool, serve solo a fine di test
QChartView* MainWindow::createGraficoTorta()
{
    GraficoTorta* grafico = dynamic_cast<GraficoTorta*>(controller->getGrafico());

    double tot = 0;
    // calcolo il totale
    for(auto it = grafico->getFette().begin();it!= grafico->getFette().end(); ++it){
        tot += it->second;
    }
    QPieSeries *series = new QPieSeries();
    for (auto it= grafico->getFette().begin();it != grafico->getFette().end();++it) {
        QPieSlice *slice = new QPieSlice(QString::fromStdString(it->first), calcoloPercentuale(it->second, tot));
        series->append(slice);
        slice->setLabelVisible();
    }    
    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(grafico->getTitolo()));
    chart->legend()->hide();

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graficoTorta = chartView;
    setCentralWidget(graficoTorta);
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
    return graficoTorta;
}

void MainWindow::setChartView(QChartView *newChartView)
{
    graficoTorta = newChartView;
}

void MainWindow::apriEsploraRisorse()
{
    QString a=QFileDialog::getOpenFileName(
                const_cast<MainWindow*>(this),
                "Seleziona file",
                QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                );
    emit carica(a);
}

void MainWindow::creaGraficoTorta()
{
    CreaTortaOSpezzataWidget* creaTortaWidget = new CreaTortaOSpezzataWidget();
    creaTortaWidget->show();
    connect(creaTortaWidget,SIGNAL(creaTorta(map<std::string, double>)),controller,SLOT(creaNuovaTorta(map<std::string, double>)));
}

void MainWindow::creaGraficoBarre()
{
    graficoBarre = createGraficoBarre();
    setCentralWidget(graficoBarre);
}



void MainWindow::creaGraficoSpezzata()
{
//    graficoSpezzata = createGraficoSpezzata();
//    setCentralWidget(graficoSpezzata);
    CreaTortaOSpezzataWidget* creaSpezzataWidget = new CreaTortaOSpezzataWidget(nullptr, false);
    creaSpezzataWidget->show();
    connect(creaSpezzataWidget,SIGNAL(creaSpezzata(const list<CoordinataSpezzata*>&)),controller,SLOT(creaNuovaSpezzata(const list<CoordinataSpezzata*>&)));
}


QChartView* MainWindow::createGraficoBarre()
{
    controller->getGraficoBarre();
    GraficoBarre* graficoBarre =dynamic_cast<GraficoBarre*>(controller->getGrafico());

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

QChartView * MainWindow::createGraficoSpezzata()
{
    GraficoSpezzata* graficoLinee =dynamic_cast<GraficoSpezzata*>(controller->getGrafico());
//    GraficoSpezzata* graficoLinee = controller->getGraficoLinee();
    QLineSeries *series = new QLineSeries();
    QCategoryAxis *axisX = new QCategoryAxis();

    unsigned int contatore = 1;
    for (auto it = graficoLinee->getValori().begin();it != graficoLinee->getValori().end();++it) {
        series->append(contatore, (*it)->getValore());
        axisX->append(QString::fromStdString((*it)->getNome()), contatore);
        contatore++;
    }
    // Create chart, add data, hide legend, and add axis
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Customize the title font
    QFont font;
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(QString::fromStdString(graficoLinee->getTitolo()));

    // Change the line color and weight
    QPen pen(QRgb(0x000000));
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    // Change the x axis categories

    chart->setAxisX(axisX, series);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graficoSpezzata = chartView;
    setCentralWidget(graficoSpezzata);
    return chartView;
}

MainWindow::~MainWindow()
{
}


double MainWindow::calcoloPercentuale(double valore, double totale) const
{
    return valore*100/totale;
}

QMenuBar* MainWindow::creaMenu()
{
    QMenuBar* barraMenu=new QMenuBar();
    QMenu* menu1=new QMenu("File");
    QMenu* menu2=new QMenu("Guida");

    //voci File menu
    QMenu* menu11=new QMenu("Crea Grafico");
    QAction* barre=new QAction("Barre");
    QAction* spezzata=new QAction("Spezzata");
    QAction* torta=new QAction("Torta");
    menu11->addAction(barre);
    menu11->addAction(spezzata);
    menu11->addAction(torta);

    QAction* carica=new QAction("Carica Grafico");


    menu1->addMenu(menu11);
    menu1->addAction(carica);
    connect(carica,SIGNAL(triggered()),this,SLOT(apriEsploraRisorse()));
    connect(torta,SIGNAL(triggered()),this,SLOT(creaGraficoTorta()));
    connect(spezzata,SIGNAL(triggered()),this,SLOT(creaGraficoSpezzata()));
    connect(barre,SIGNAL(triggered()),this,SLOT(creaGraficoBarre()));



    barraMenu->addMenu(menu1);
    barraMenu->addMenu(menu2);
    return barraMenu;
}

MainWindow::MainWindow(GraficiController *controller, QWidget *parent) : QMainWindow(parent),
    controller(controller)
{
    QMenuBar* barraMenu =creaMenu();
    setMenuBar(barraMenu);
    graficoBarre= createGraficoBarre();
    setCentralWidget(graficoBarre);
    resize(420, 300);
    show();

}
