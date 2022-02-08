#include "datigraficobarre.h"

const string &DatiGraficoBarre::getNome() const
{
    return nome;
}

void DatiGraficoBarre::setNome(const string &newNome)
{
    nome = newNome;
}

const list<double> &DatiGraficoBarre::getValori() const
{
    return valori;
}

void DatiGraficoBarre::setValori(const list<double> &newValori)
{
    valori = newValori;
}

DatiGraficoBarre::DatiGraficoBarre()
{
}

DatiGraficoBarre::DatiGraficoBarre(const string &nome, const list<double> &valori) : nome(nome),
                                                                                     valori(valori)
{
}
