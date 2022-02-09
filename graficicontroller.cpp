#include "graficicontroller.h"

MainWindow *GraficiController::getVista() const
{
    return vista;
}

void GraficiController::setVista(MainWindow *newVista)
{
    vista = newVista;
}
GraficiController::~GraficiController()
{
    if (vista)
        delete vista;
    if (grafico)
        delete grafico;
}

GraficoBase *GraficiController::getGrafico() const
{
    return grafico;
}

void GraficiController::setGrafico(GraficoBase *newGrafico)
{
    grafico = newGrafico;
}

void GraficiController::creaNuovaTorta(map<std::string, double> valori)
{
    if (grafico)
        delete grafico;
    grafico = new GraficoTorta(valori);
}

void GraficiController::creaNuovaSpezzata(const list<CoordinataSpezzata *> &valori)
{
    if (grafico)
        delete grafico;
    grafico = new GraficoSpezzata(valori);
}

void GraficiController::creaNuovaBarra(const list<string> &categorie, const list<DatiGraficoBarre *> &dati)
{
    if (grafico)
        delete grafico;
    grafico = new GraficoBarre(categorie, dati);
}

void GraficiController::salva(string path)
{
    if (grafico)
        grafico->salva(path);
}

void GraficiController::visualizzaGrafico()
{
    if (grafico)
    {
        if (dynamic_cast<GraficoTorta *>(grafico))
            vista->createGraficoTorta();
        if (dynamic_cast<GraficoBarre *>(grafico))
            vista->createGraficoBarre();
        if (dynamic_cast<GraficoSpezzata *>(grafico))
            vista->createGraficoSpezzata();
    }
    else
    {
        vista->setCentralWidget(new QChartView());
    }
}

void GraficiController::setTitoloSpezzata(const QString & titolo)
{
    grafico->setTitolo(titolo.toStdString());
    vista->createGraficoSpezzata();
}

void GraficiController::setTitoloBarre(const QString & titolo)
{
    grafico->setTitolo(titolo.toStdString());
    vista->createGraficoBarre();
}

void GraficiController::setTitoloTorta(const QString & titolo)
{
    grafico->setTitolo(titolo.toStdString());
    vista->createGraficoTorta();
}

void GraficiController::ottieniGraficoDaFile(const QString &path)
{
    if (!path.isEmpty())
    {
        grafico = fileReader->ottieniGraficoDaFile(path.toStdString());
        visualizzaGrafico();
    }
}

GraficiController::GraficiController(QObject *parent) : QObject(parent), vista(nullptr), grafico(nullptr)
{
    fileReader = new FileReader();
    vista = new MainWindow(this);
    vista->show();
    connect(vista, SIGNAL(carica(const QString &)), this, SLOT(ottieniGraficoDaFile(const QString &)));
    connect(vista, SIGNAL(indietro()), this, SLOT(visualizzaGrafico()));
}
