#include "graficolinee.h"

const map<string, double> &GraficoLinee::getValori() const
{
    return valori;
}

void GraficoLinee::setValori(const map<string, double> &newValori)
{
    valori = newValori;
}

void GraficoLinee::salva(string path) const
{

}

string GraficoLinee::getNomeClasse() const
{
    return "Linee";

}

GraficoLinee::GraficoLinee()
{

}

GraficoLinee::GraficoLinee(const map<string, double> &valori) : valori(valori)
{}
