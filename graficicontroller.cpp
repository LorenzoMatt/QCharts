#include "graficicontroller.h"

MainWindow *GraficiController::getVista() const
{
    return vista;
}

void GraficiController::setVista(MainWindow *newVista)
{
    vista = newVista;
}

GraficoBarre *GraficiController::getGraficoBarre()
{
    list<double> valori;
    list<DatiGraficoBarre*> d;
    valori.push_back(283);
    valori.push_back(341);
    valori.push_back(313);
    valori.push_back(338);
    valori.push_back(346);
    valori.push_back(335);

    d.push_back(new DatiGraficoBarre("Altuve", valori));
    d.push_back(new DatiGraficoBarre("Martinez", valori));


    list<string> categorie;
    categorie.push_back("2013");
    categorie.push_back("2014");
    categorie.push_back("2015");
    categorie.push_back("2016");
    categorie.push_back("2017");
    categorie.push_back("2018");
    GraficoBarre* graficoBarre = new GraficoBarre(categorie, d);
    graficoBarre->setTitolo("Grafico a barre");
    grafico = graficoBarre;
    return graficoBarre;
}

GraficoTorta *GraficiController::getGraficoTorta()
{
    map<string, double> fette;
    fette["Vegetables"]=.40;
    fette["Beans"]=.20;
    fette["Fruits"]=.15;
    fette["Seeds/Nuts"]=.10;
    fette["Whole Grains"]=.15;
    GraficoTorta* graficoTorta = new GraficoTorta(fette);
    graficoTorta->setTitolo("What Derek Ate this Week");
    grafico = graficoTorta;
    return graficoTorta;
}

GraficoSpezzata *GraficiController::getGraficoLinee()
{
    list<CoordinataSpezzata*> valori;
    valori.push_back(new CoordinataSpezzata("1986", 16));
    valori.push_back(new CoordinataSpezzata("1987", 25));
    valori.push_back(new CoordinataSpezzata("1988", 24));
    valori.push_back(new CoordinataSpezzata("1989", 19));
    valori.push_back(new CoordinataSpezzata("1990", 33));
    valori.push_back(new CoordinataSpezzata("1991", 25));
    valori.push_back(new CoordinataSpezzata("1992", 19));
    GraficoSpezzata* graficoLinee = new GraficoSpezzata(valori);
    graficoLinee->setTitolo("grafico linee");
    grafico = graficoLinee;

    return graficoLinee;
}

GraficiController::~GraficiController()
{
    if(vista)
        delete vista;
    if(grafico)
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
    if(grafico)
        delete grafico;
    grafico = new GraficoTorta(valori);
    vista->createGraficoTorta();
}

void GraficiController::creaNuovaSpezzata(const list<CoordinataSpezzata*>& valori)
{
    if(grafico)
        delete grafico;
    grafico = new GraficoSpezzata(valori);
    vista->createGraficoSpezzata();
}

void GraficiController::creaNuovaBarra(const list<string> & categorie, const list<DatiGraficoBarre *> & dati)
{
    if(grafico)
        delete grafico;
    grafico = new GraficoBarre(categorie, dati);
    vista->createGraficoBarre();
}

void GraficiController::salva(string path)
{
    if(grafico)
        grafico->salva(path);
}

void GraficiController::ottieniGraficoDaFile(const QString &path)
{
    grafico = fileReader->ottieniGraficoDaFile(path.toStdString());
    vista->createGraficoTorta();

}

GraficiController::GraficiController(QObject *parent) : QObject(parent), vista(nullptr), grafico(nullptr)
{
    fileReader = new FileReader();
    vista = new MainWindow(this);
    vista->show();
    connect(vista,SIGNAL(carica(const QString&)),this,SLOT(ottieniGraficoDaFile(const QString &)));
}

GraficiController::GraficiController(MainWindow *vista, GraficoBase* grafico, QObject *parent) : QObject(parent),
    vista(vista),
    grafico(grafico)
{
    fileReader = new FileReader();
    vista->show();
    connect(vista,SIGNAL(carica(const QString&)),this,SLOT(ottieniGraficoDaFile(const QString &)));
}
