#include "mainwindow.h"
#include "graficicontroller.h"
#include "creatortaospezzatawidget.h"
#include "creagraficobarrewidget.h"
#include "inseriscititolowidget.h"
#include "graficobarrewidget.h"
#include "graficospezzatawidget.h"
#include "graficotortawidget.h"


GraficiController *MainWindow::getController() const
{
    return controller;
}

void MainWindow::setController(GraficiController *newController)
{
    controller = newController;
}

void MainWindow::setChartView(GraficoBaseWidget *newChartView)
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

void MainWindow::createGraficoTorta()
{
    //capire perchè se non faccio una new va in eccezione solo visualizzaGrafico e non setGrafico
    graficoTorta= new GraficoTortaWidget();
    graficoTorta->setGrafico(controller->getGrafico());
    graficoTorta->visualizzaGrafico();
    setCentralWidget(graficoTorta);
}

void MainWindow::createGraficoBarre()
{
    //capire perchè se non faccio una new va in eccezione solo visualizzaGrafico e non setGrafico
    graficoBarre = new GraficoBarreWidget();
    graficoBarre->setGrafico(controller->getGrafico());
    graficoBarre->visualizzaGrafico();
    setCentralWidget(graficoBarre);
}

void MainWindow::createGraficoSpezzata()
{
    //capire perchè se non faccio una new va in eccezione solo visualizzaGrafico e non setGrafico
    graficoSpezzata = new GraficoSpezzataWidget();
    graficoSpezzata->setGrafico(controller->getGrafico());
    graficoSpezzata->visualizzaGrafico();
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
    graficoBarre = new GraficoBarreWidget();
    graficoTorta = new GraficoTortaWidget();
    graficoSpezzata = new GraficoSpezzataWidget();
    setMenuBar(barraMenu);
    setCentralWidget(new QChartView());
    resize(420, 300);
    show();
}
