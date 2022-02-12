#include "graficobarre.h"

#include <QXmlStreamWriter>
#include "graficononsalvato.h"
const list<string> &GraficoBarre::getCategorie() const
{
    return categorie;
}

void GraficoBarre::setCategorie(const list<string> &newCategorie)
{
    categorie = newCategorie;
}

string GraficoBarre::getNomeClasse() const
{
    return "Barre";
}

void GraficoBarre::salva(std::string path) const
{
    QFile *file = new QFile(QString::fromStdString(path));
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw GraficoNonSalvato();
    }
    else
    {
        QXmlStreamWriter *inp = new QXmlStreamWriter;
        inp->setAutoFormatting(true);
        inp->setDevice(file);
        inp->writeStartDocument();         // inizio a scrivere nel file
        inp->writeStartElement("grafico"); // inizio dei campi dati del grafico
        inp->writeTextElement("titolo", QString::fromStdString(getTitolo()));
        inp->writeTextElement("tipo", QString::fromStdString(getNomeClasse()));
        inp->writeStartElement("categorie"); // inizio dei valori
        for (auto it = categorie.begin(); it != categorie.end(); ++it)
        {
            inp->writeTextElement("categoria", QString::fromStdString(*it));
        }
        inp->writeEndElement();         // fine lista categorie
        inp->writeStartElement("dati"); // inizio dei valori
        for (auto it = dati.begin(); it != dati.end(); ++it)
        {
            inp->writeStartElement("dato"); // inizio singolo dato
            inp->writeTextElement("nome", QString::fromStdString((*it)->getNome()));
            inp->writeStartElement("valori"); // inizio lista dei valori di un dato
            for (auto it2 = (*it)->getValori().begin(); it2 != (*it)->getValori().end(); ++it2)
            {
                inp->writeTextElement("valore", QString::fromStdString(std::to_string((*it2))));
            }
            inp->writeEndElement(); // fine lista dei valori di un dato
            inp->writeEndElement(); // fine di un dato
        }
        inp->writeEndElement(); // fine dei dati

        inp->writeEndElement(); // fine dati del grafico

        inp->writeEndDocument();
        file->close();
    }
}

const list<DatiGraficoBarre *> &GraficoBarre::getDati() const
{
    return dati;
}

void GraficoBarre::setDati(const list<DatiGraficoBarre *> &newDati)
{
    dati = newDati;
}

GraficoBarre::GraficoBarre()
{
}

GraficoBarre::~GraficoBarre()
{
    for(auto it = dati.begin(); it!= dati.end(); ++it){
        if (*it)
            delete *it;
    }
}

GraficoBarre::GraficoBarre(const list<string> &categorie, const list<DatiGraficoBarre *> &dati, string titolo) : GraficoBase(titolo), categorie(categorie),
                                                                                                                 dati(dati)
{
}
