#include "mainwindow.h"
#include "graficicontroller.h"
#include "creatortaospezzatawidget.h"
#include "creagraficobarrewidget.h"
#include "inseriscititolowidget.h"

void MainWindow::createGraficoTorta()
{
    GraficoTorta *grafico = dynamic_cast<GraficoTorta *>(controller->getGrafico());

    double tot = 0;
    for (auto it = grafico->getFette().begin(); it != grafico->getFette().end(); ++it)
    {
        tot += it->second;
    }
    QPieSeries *series = new QPieSeries();
    for (auto it = grafico->getFette().begin(); it != grafico->getFette().end(); ++it)
    {
        QPieSlice *slice = new QPieSlice(QString::fromStdString(it->first), calcoloPercentuale(it->second, tot));
        series->append(slice);
        slice->setLabelVisible();
    }
    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(grafico->getTitolo()));
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graficoTorta = chartView;
    setCentralWidget(graficoTorta);
}

GraficiController *MainWindow::getController() const
{
    return controller;
}

void MainWindow::setController(GraficiController *newController)
{
    controller = newController;
}

void MainWindow::setChartView(QChartView *newChartView)
{
    graficoTorta = newChartView;
}

void MainWindow::apriEsploraRisorseCaricaFile()
{
    QString path = QFileDialog::getOpenFileName(
        const_cast<MainWindow *>(this),
        "Seleziona file",
        QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
        tr("XML files (*.xml)"));
    emit carica(path);
}

void MainWindow::apriEsploraRisorseSalvaFile()
{
    if (controller->getGrafico())
    {
        QString path = QFileDialog::getSaveFileName(
            const_cast<MainWindow *>(this),
            "Salva file",
            QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
            tr("XML files (*.xml)"));
        controller->salva(path.toStdString());
    }
    else
    {
        messaggioInformativo("Grafico non salvato", "Caricare o creare un grafico", this);
    }
}

void MainWindow::creaGraficoTorta()
{
    CreaTortaOSpezzataWidget *creaTortaWidget = new CreaTortaOSpezzataWidget();
    setCentralWidget(creaTortaWidget);
    connect(creaTortaWidget, SIGNAL(creaTorta(map<std::string, double>)), controller, SLOT(creaNuovaTorta(map<std::string, double>)));
    connect(creaTortaWidget, SIGNAL(creaTorta(map<std::string, double>)), this, SLOT(inserisciTitoloTorta()));
    connect(creaTortaWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
}

void MainWindow::creaGraficoBarre()
{
    CreaGraficoBarreWidget *creaGraficoBarreWidget = new CreaGraficoBarreWidget();
    setCentralWidget(creaGraficoBarreWidget);
    connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), controller, SLOT(creaNuovaBarra(const std::list<string> &, const std::list<DatiGraficoBarre *> &)));
    connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), this, SLOT(inserisciTitoloBarre()));
    connect(creaGraficoBarreWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
}

void MainWindow::creaGraficoSpezzata()
{
    CreaTortaOSpezzataWidget *creaSpezzataWidget = new CreaTortaOSpezzataWidget(nullptr, false);
    setCentralWidget(creaSpezzataWidget);
    connect(creaSpezzataWidget, SIGNAL(creaSpezzata(const list<CoordinataSpezzata *> &)), controller, SLOT(creaNuovaSpezzata(const list<CoordinataSpezzata *> &)));
    connect(creaSpezzataWidget, SIGNAL(creaSpezzata(const list<CoordinataSpezzata *> &)), this, SLOT(inserisciTitoloSpezzata()));
    connect(creaSpezzataWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
}

void MainWindow::tornaIndietro()
{
    emit indietro();
}

void MainWindow::inserisciTitoloSpezzata()
{
    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget();
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloSpezzata(const QString&)));

}

void MainWindow::inserisciTitoloBarre()
{

    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget();
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloBarre(const QString&)));
}

void MainWindow::inserisciTitoloTorta()
{

    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget();
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloTorta(const QString&)));
}

void MainWindow::createGraficoBarre()
{
    GraficoBarre *grafico = dynamic_cast<GraficoBarre *>(controller->getGrafico());

    QBarSeries *series = new QBarSeries();

    for (auto it = grafico->getDati().begin(); it != grafico->getDati().end(); ++it)
    {
        QBarSet *bar = new QBarSet(QString::fromStdString((*it)->getNome()));
        list<double> l = (*it)->getValori();
        for (auto it2 = l.begin(); it2 != l.end(); ++it2)
        {
            bar->append(*it2);
        }
        series->append(bar);
    }

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(grafico->getTitolo()));

    chart->setAnimationOptions(QChart::AllAnimations);
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;
    for (auto it = grafico->getCategorie().begin(); it != grafico->getCategorie().end(); ++it)
    {
        categories.append(QString::fromStdString(*it));
    }
    axis->append(categories);
    chart->createDefaultAxes();

    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graficoBarre = chartView;
    setCentralWidget(graficoBarre);
}

void MainWindow::createGraficoSpezzata()
{
    GraficoSpezzata *graficoLinee = dynamic_cast<GraficoSpezzata *>(controller->getGrafico());
    QLineSeries *series = new QLineSeries();
    QCategoryAxis *axisX = new QCategoryAxis();

    unsigned int contatore = 1;
    for (auto it = graficoLinee->getValori().begin(); it != graficoLinee->getValori().end(); ++it)
    {
        series->append(contatore, (*it)->getValore());
        axisX->append(QString::fromStdString((*it)->getNome()), contatore);
        contatore++;
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    QFont font;
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(QString::fromStdString(graficoLinee->getTitolo()));
    QPen pen(QRgb(0x000000));
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAxisX(axisX, series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    graficoSpezzata = chartView;
    setCentralWidget(graficoSpezzata);
}

MainWindow::~MainWindow()
{
}

QChartView *MainWindow::getGraficoTorta() const
{
    return graficoTorta;
}

QChartView *MainWindow::getGraficoSpezzata() const
{
    return graficoSpezzata;
}

QChartView *MainWindow::getGraficoBarre() const
{
    return graficoBarre;
}

double MainWindow::calcoloPercentuale(double valore, double totale) const
{
    return valore * 100 / totale;
}

QMenuBar *MainWindow::creaMenu()
{
    QMenuBar *barraMenu = new QMenuBar();
    QMenu *menu1 = new QMenu("File");
    QMenu *menu11 = new QMenu("Crea Grafico");
    QAction *barre = new QAction("Barre");
    QAction *spezzata = new QAction("Spezzata");
    QAction *torta = new QAction("Torta");
    menu11->addAction(barre);
    menu11->addAction(spezzata);
    menu11->addAction(torta);

    QAction *carica = new QAction("Carica Grafico");
    QAction *salva = new QAction("Salva Grafico");

    menu1->addMenu(menu11);
    menu1->addAction(carica);
    menu1->addAction(salva);
    connect(carica, SIGNAL(triggered()), this, SLOT(apriEsploraRisorseCaricaFile()));
    connect(torta, SIGNAL(triggered()), this, SLOT(creaGraficoTorta()));
    connect(spezzata, SIGNAL(triggered()), this, SLOT(creaGraficoSpezzata()));
    connect(barre, SIGNAL(triggered()), this, SLOT(creaGraficoBarre()));
    connect(salva, SIGNAL(triggered()), this, SLOT(apriEsploraRisorseSalvaFile()));

    barraMenu->addMenu(menu1);
    return barraMenu;
}

MainWindow::MainWindow(GraficiController *controller, QWidget *parent) : QMainWindow(parent),
                                                                         controller(controller)
{
    QMenuBar *barraMenu = creaMenu();
    setMenuBar(barraMenu);
    graficoTorta = new QChartView();
    graficoSpezzata = new QChartView();
    graficoBarre = new QChartView();
    setCentralWidget(graficoBarre);
    resize(420, 300);
    show();
}
