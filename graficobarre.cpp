#include "graficobarre.h"

const map<string, list<double> > &GraficoBarre::getDati() const
{
    return dati;
}

void GraficoBarre::setDati(const map<string, list<double> > &newDati)
{
    dati = newDati;
}

void GraficoBarre::salva(string path) const
{

}

string GraficoBarre::getNomeClasse() const
{
    return "Barre";

}

const list<string> &GraficoBarre::getCategorie() const
{
    return categorie;
}

void GraficoBarre::setCategorie(const list<string> &newCategorie)
{
    categorie = newCategorie;
}

GraficoBarre::GraficoBarre()
{

}

GraficoBarre::GraficoBarre(const map<string, list<double> > &dati) : dati(dati)
{}
