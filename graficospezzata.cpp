#include "graficospezzata.h"
#include "graficononsalvato.h"
#include "utility.h"

void GraficoSpezzata::salvaDati(QXmlStreamWriter* inp) const
{
    inp->writeStartElement("valori"); // inizio dei valori
    for (auto it = valori.begin(); it != valori.end(); ++it)
    {
        inp->writeStartElement("dato"); // inizio singolo dato
        inp->writeTextElement("nome", QString::fromStdString((*it)->getNome()));
        inp->writeTextElement("valore", QString::fromStdString(std::to_string((*it)->getValore())));
        inp->writeEndElement(); // fine di un dato
    }
    inp->writeEndElement(); // fine della lista dei valori
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
    for (auto it = valori.begin(); it != valori.end(); ++it)
    {
        if (*it)
            delete *it;
    }
}

GraficoSpezzata::GraficoSpezzata(const list<CoordinataSpezzata *> &valori, string titolo) : GraficoBase(titolo), valori(valori)
{
}
