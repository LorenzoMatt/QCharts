#include "graficotorta.h"

#include <QFile>
#include <QXmlStreamWriter>
#include "utility.h"
#include "graficononsalvato.h"

const map<string, double> &GraficoTorta::getFette() const
{
    return fette;
}

void GraficoTorta::setFette(const map<std::string, double> &newFette)
{
    fette = newFette;
}

void GraficoTorta::salvaDati(QXmlStreamWriter * inp) const
{
    inp->writeStartElement("valori"); // inizio dei valori
    for (auto it = fette.begin(); it != fette.end(); ++it)
    {
        inp->writeStartElement("dato"); // inizio singolo dato
        inp->writeTextElement("nome", QString::fromStdString(it->first));
        inp->writeTextElement("valore", QString::fromStdString(std::to_string(it->second)));
        inp->writeEndElement(); // fine di un dato
    }
    inp->writeEndElement(); // fine della lista dei valori
}

string GraficoTorta::getNomeClasse() const
{
    return "Torta";
}

GraficoTorta::GraficoTorta()
{
}

GraficoTorta::GraficoTorta(const map<string, double> &fette, string titolo) : GraficoBase(titolo), fette(fette)
{
}
