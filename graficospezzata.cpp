#include "graficospezzata.h"


void GraficoSpezzata::salva(string path) const
{

}

string GraficoSpezzata::getNomeClasse() const
{
    return "Linee";

}

const list<CoordinataSpezzata *> &GraficoSpezzata::getValori() const
{
    return valori;
}

void GraficoSpezzata::setValori(const list<CoordinataSpezzata *> &newValori)
{
    valori = newValori;
}

GraficoSpezzata::GraficoSpezzata()
{

}

GraficoSpezzata::~GraficoSpezzata()
{
    for(auto it = valori.begin(); it!= valori.end(); ++it){
        if(*it)
            delete *it;
    }

}

GraficoSpezzata::GraficoSpezzata(const list<CoordinataSpezzata *> &valori) : valori(valori)
{}
