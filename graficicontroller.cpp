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
    list<double> dati1;
    dati1.push_back(283);
    dati1.push_back(341);
    dati1.push_back(313);
    dati1.push_back(338);
    dati1.push_back(346);
    dati1.push_back(335);

    map<string, list<double>> dati;

    dati["Altuve"] = dati1;
    dati["Martinez"] = dati1;


    GraficoBarre* graficoBarre = new GraficoBarre(dati);
    list<string> categorie;
    categorie.push_back("2013");
    categorie.push_back("2014");
    categorie.push_back("2015");
    categorie.push_back("2016");
    categorie.push_back("2017");
    categorie.push_back("2018");
    graficoBarre->setCategorie(categorie);
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

GraficoLinee *GraficiController::getGraficoLinee()
{
    map<string, double> valori;
    valori["1986"]=16;
    valori["1987"]=25;
    valori["1988"]=24;
    valori["1989"]=19;
    valori["1990"]=33;
    valori["1991"]=25;
    valori["1990"]=19;
    GraficoLinee* graficoLinee = new GraficoLinee(valori);
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

GraficiController::GraficiController(QObject *parent) : QObject(parent), vista(nullptr), grafico(nullptr)
{
    vista = new MainWindow(this);
    vista->show();
}

GraficiController::GraficiController(MainWindow *vista, GraficoBase* grafico, QObject *parent) : QObject(parent),
    vista(vista),
    grafico(grafico)
{
    vista->show();
}
