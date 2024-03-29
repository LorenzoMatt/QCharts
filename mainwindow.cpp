#include "mainwindow.h"
#include "graficicontroller.h"
#include "tortaospezzatawidget.h"
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
                    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                    tr("XML files (*.xml)"));
    emit carica(path);
}

void MainWindow::apriEsploraRisorseSalvaFile()
{
    if (controller->getGrafico())
    {
        QString path;
        if(controller->getPath().isEmpty()){
            path = QFileDialog::getSaveFileName(
                        const_cast<MainWindow *>(this),
                        "Salva file",
                        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                        tr("XML files (*.xml)"));
        }else{
            path = controller->getPath();
        }

        controller->salva(path);
    }
    else
    {
        messaggioInformativo("Grafico non salvato", "Caricare o creare un grafico", this);
    }
}

void MainWindow::creaGraficoTorta()
{
    TortaOSpezzataWidget *creaTortaWidget = new TortaOSpezzataWidget();
    setCentralWidget(creaTortaWidget);
    connect(creaTortaWidget, SIGNAL(Torta(map<std::string, double>)), controller, SLOT(creaNuovaTorta(map<std::string, double>)));
    connect(creaTortaWidget, SIGNAL(Torta(map<std::string, double>)), controller, SLOT(svuotaPath()));
    connect(creaTortaWidget, SIGNAL(Torta(map<std::string, double>)), this, SLOT(inserisciTitoloTorta()));
    connect(creaTortaWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
}

void MainWindow::creaGraficoBarre()
{
    CreaGraficoBarreWidget *creaGraficoBarreWidget = new CreaGraficoBarreWidget();
    setCentralWidget(creaGraficoBarreWidget);
    connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), controller, SLOT(creaNuovaBarra(const std::list<string> &, const std::list<DatiGraficoBarre *> &)));
    connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), controller, SLOT(svuotaPath()));
    connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), this, SLOT(inserisciTitoloBarre()));
    connect(creaGraficoBarreWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
}

void MainWindow::creaGraficoSpezzata()
{
    TortaOSpezzataWidget *creaSpezzataWidget = new TortaOSpezzataWidget(nullptr, false);
    setCentralWidget(creaSpezzataWidget);
    connect(creaSpezzataWidget, SIGNAL(Spezzata(const list<CoordinataSpezzata *> &)), controller, SLOT(creaNuovaSpezzata(const list<CoordinataSpezzata *> &)));
    connect(creaSpezzataWidget, SIGNAL(Spezzata(const list<CoordinataSpezzata *> &)),  controller, SLOT(svuotaPath()));
    connect(creaSpezzataWidget, SIGNAL(Spezzata(const list<CoordinataSpezzata *> &)), this, SLOT(inserisciTitoloSpezzata()));
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

void MainWindow::modificaTitoloSpezzata()
{
    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget(QString::fromStdString(controller->getGrafico()->getTitolo()));
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloSpezzata(const QString&)));
}

void MainWindow::modificaTitoloBarre()
{
    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget(QString::fromStdString(controller->getGrafico()->getTitolo()));
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloBarre(const QString&)));
}

void MainWindow::modificaTitoloTorta()
{
    InserisciTitoloWidget* titoloWidget = new InserisciTitoloWidget(QString::fromStdString(controller->getGrafico()->getTitolo()));
    setCentralWidget(titoloWidget);
    connect(titoloWidget, SIGNAL(titoloSignal(const QString&)), controller, SLOT(setTitoloTorta(const QString&)));
}

void MainWindow::modificaGrafico()
{
    GraficoBase* g = controller->getGrafico();
    if (g)
    {
        if (dynamic_cast<GraficoTorta *>(g) || dynamic_cast<GraficoSpezzata*>(g))
        {
            TortaOSpezzataWidget* modificaTortaOSpezzata = new TortaOSpezzataWidget(nullptr, dynamic_cast<GraficoTorta *>(g), g);
            setCentralWidget(modificaTortaOSpezzata);
            connect(modificaTortaOSpezzata, SIGNAL(Torta(map<std::string, double>)), this, SLOT(modificaTitoloTorta()));
            connect(modificaTortaOSpezzata, SIGNAL(Torta(map<std::string, double>)), controller, SLOT(creaNuovaTorta(map<std::string, double>)));
            connect(modificaTortaOSpezzata, SIGNAL(Spezzata(const list<CoordinataSpezzata *> &)), this, SLOT(modificaTitoloSpezzata()));
            connect(modificaTortaOSpezzata, SIGNAL(Spezzata(const list<CoordinataSpezzata *> &)), controller, SLOT(creaNuovaSpezzata(const list<CoordinataSpezzata *> &)));
            connect(modificaTortaOSpezzata, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
        }
        GraficoBarre* barre = dynamic_cast<GraficoBarre*>(g);
        if(barre){
            CreaGraficoBarreWidget* creaGraficoBarreWidget = new CreaGraficoBarreWidget(new GraficoBarre(*barre));
            setCentralWidget(creaGraficoBarreWidget);
            connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), this, SLOT(modificaTitoloBarre()));
            connect(creaGraficoBarreWidget, SIGNAL(creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &)), controller, SLOT(creaNuovaBarra(const std::list<string> &, const std::list<DatiGraficoBarre *> &)));
            connect(creaGraficoBarreWidget, SIGNAL(cancella()), this, SLOT(tornaIndietro()));
        }
    }else {
        messaggioErrore("Modifica non disponibile", "Creare o caricare prima un grafico", this);
    }
}


void MainWindow::createGraficoTorta()
{
    graficoTorta= new GraficoTortaWidget();
    graficoTorta->setGrafico(controller->getGrafico());
    graficoTorta->visualizzaGrafico();
    setCentralWidget(graficoTorta);
}

void MainWindow::createGraficoBarre()
{
    graficoBarre = new GraficoBarreWidget();
    graficoBarre->setGrafico(controller->getGrafico());
    graficoBarre->visualizzaGrafico();
    setCentralWidget(graficoBarre);
}

void MainWindow::createGraficoSpezzata()
{
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
    QMenu *menuFile = new QMenu("File");
    QMenu *menuCreazioneModifica = new QMenu("Grafico");
    QMenu *menuGrafico = new QMenu("Crea Grafico");
    QAction *modifica = new QAction("Modifica Grafico");
    QAction *barre = new QAction("Barre");
    QAction *spezzata = new QAction("Spezzata");
    QAction *torta = new QAction("Torta");
    menuGrafico->addAction(barre);
    menuGrafico->addAction(spezzata);
    menuGrafico->addAction(torta);

    QAction *carica = new QAction("Carica Grafico");
    QAction *salva = new QAction("Salva Grafico");

    menuFile->addAction(carica);
    menuFile->addAction(salva);
    menuCreazioneModifica->addMenu(menuGrafico);
    menuCreazioneModifica->addAction(modifica);
    connect(carica, SIGNAL(triggered()), this, SLOT(apriEsploraRisorseCaricaFile()));
    connect(torta, SIGNAL(triggered()), this, SLOT(creaGraficoTorta()));
    connect(spezzata, SIGNAL(triggered()), this, SLOT(creaGraficoSpezzata()));
    connect(barre, SIGNAL(triggered()), this, SLOT(creaGraficoBarre()));
    connect(salva, SIGNAL(triggered()), this, SLOT(apriEsploraRisorseSalvaFile()));
    connect(modifica, SIGNAL(triggered()), this, SLOT(modificaGrafico()));

    barraMenu->addMenu(menuFile);
    barraMenu->addMenu(menuCreazioneModifica);
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
