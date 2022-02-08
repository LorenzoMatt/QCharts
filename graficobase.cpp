#include "graficobase.h"

const string &GraficoBase::getTitolo() const
{
    return titolo;
}

void GraficoBase::setTitolo(const string &newTitolo)
{
    titolo = newTitolo;
}

GraficoBase::GraficoBase()
{
}

GraficoBase::~GraficoBase()
{
}

GraficoBase::GraficoBase(const string &titolo) : titolo(titolo)
{
}
