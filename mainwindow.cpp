#include "mainwindow.h"
#include "graficicontroller.h"
#include "creatortaospezzatawidget.h"
#include "creagraficobarrewidget.h"


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

void MainWindow::apriEsploraRisorseCaricaFile()
{
    QString path=QFileDialog::getOpenFileName(
                const_cast<MainWindow*>(this),
                "Seleziona file",
                QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                tr("XML files (*.xml)")
                );
    emit carica(path);
}

void MainWindow::apriEsploraRisorseSalvaFile()
{
    QString path=QFileDialog::getSaveFileName(
                const_cast<MainWindow*>(this),
                "Salva file",
                QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                tr("XML files (*.xml)")
                );
    controller->salva(path.toStdString());
}

void MainWindow::creaGraficoTorta()
{
    CreaTortaOSpezzataWidget* creaTortaWidget = new CreaTortaOSpezzataWidget();
    creaTortaWidget->show();
    connect(creaTortaWidget,SIGNAL(creaTorta(map<std::string, double>)),controller,SLOT(creaNuovaTorta(map<std::string, double>)));
}

void MainWindow::creaGraficoBarre()
{
//    graficoBarre = createGraficoBarre();
//    setCentralWidget(graficoBarre);
    CreaGraficoBarreWidget* creaGraficoBarreWidget = new CreaGraficoBarreWidget();
    creaGraficoBarreWidget->show();
    connect(creaGraficoBarreWidget,SIGNAL(creaGraficoBarre(const std::list<string> &,const std::list<DatiGraficoBarre*>&)),controller,SLOT(creaNuovaBarra(const std::list<string> &,const std::list<DatiGraficoBarre*>&)));
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
    GraficoBarre* grafico =dynamic_cast<GraficoBarre*>(controller->getGrafico());
    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    for (auto it = grafico->getDati().begin(); it!=grafico->getDati().end();++it ) {
        QBarSet* bar = new QBarSet(QString::fromStdString((*it)->getNome()));
        list<double> l = (*it)->getValori();
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
    chart->setTitle(QString::fromStdString(grafico->getTitolo()));

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles


    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;
    for(auto it = grafico->getCategorie().begin(); it!= grafico->getCategorie().end(); ++it){
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
    graficoBarre = chartView;
    setCentralWidget(graficoBarre);

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
    QMenu* menu11=new QMenu("Crea Grafico");
    QAction* barre=new QAction("Barre");
    QAction* spezzata=new QAction("Spezzata");
    QAction* torta=new QAction("Torta");
    menu11->addAction(barre);
    menu11->addAction(spezzata);
    menu11->addAction(torta);

    QAction* carica=new QAction("Carica Grafico");
    QAction* salva=new QAction("Salva Grafico");


    menu1->addMenu(menu11);
    menu1->addAction(carica);
    menu1->addAction(salva);
    connect(carica,SIGNAL(triggered()),this,SLOT(apriEsploraRisorseCaricaFile()));
    connect(torta,SIGNAL(triggered()),this,SLOT(creaGraficoTorta()));
    connect(spezzata,SIGNAL(triggered()),this,SLOT(creaGraficoSpezzata()));
    connect(barre,SIGNAL(triggered()),this,SLOT(creaGraficoBarre()));
    connect(salva,SIGNAL(triggered()),this,SLOT(apriEsploraRisorseSalvaFile()));



    barraMenu->addMenu(menu1);
    return barraMenu;
}

MainWindow::MainWindow(GraficiController *controller, QWidget *parent) : QMainWindow(parent),
    controller(controller)
{
    QMenuBar* barraMenu =creaMenu();
    setMenuBar(barraMenu);
//    graficoBarre= createGraficoBarre();
    graficoTorta = new QChartView();
    graficoSpezzata = new QChartView();
    graficoBarre = new QChartView();
    setCentralWidget(graficoBarre);
    resize(420, 300);
    show();

}
