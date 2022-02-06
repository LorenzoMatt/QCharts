#include "graficotorta.h"

const map<string, double> &GraficoTorta::getFette() const
{
    return fette;
}

void GraficoTorta::setFette(const map<std::string, double> &newFette)
{
    fette = newFette;
}

void GraficoTorta::salva() const
{
    //TODO
}

string GraficoTorta::getNomeClasse() const
{
    return "Torta";
}

GraficoTorta::GraficoTorta()
{

}

GraficoTorta::~GraficoTorta()
{
}

GraficoTorta::GraficoTorta(const map<string, double> &fette) : fette(fette)
{}
