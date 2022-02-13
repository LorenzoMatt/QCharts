#include "graficobarre.h"

#include <QXmlStreamWriter>
#include "graficononsalvato.h"
const list<string> &GraficoBarre::getCategorie() const
{
    return categorie;
}

void GraficoBarre::removeCategoriaAndValoreAt(int index)
{
    auto it = categorie.begin();
    for(int i = 0; i < index; ++i){
        ++it;
    }
    categorie.erase(it);
    for(auto it2=dati.begin(); it2!= dati.end();++it2){
        auto itValore = (*it2)->getValori().begin();
        for(int i =0 ; i < index; ++i){
            ++itValore;
        }
        (*it2)->getValori().erase(itValore);
    }
}

void GraficoBarre::setCategorie(const list<string> &newCategorie)
{
    categorie = newCategorie;
}

string GraficoBarre::getNomeClasse() const
{
    return "Barre";
}

void GraficoBarre::salvaDati(QXmlStreamWriter * inp) const
{
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
}

const list<DatiGraficoBarre *> &GraficoBarre::getDati() const
{
    return dati;
}

void GraficoBarre::setDati(const list<DatiGraficoBarre *> &newDati)
{
    dati = newDati;
}

list<DatiGraficoBarre *> GraficoBarre::copiaDati(const list<DatiGraficoBarre *> & d)
{
    list<DatiGraficoBarre *> copia;
    for(auto it = d.begin(); it!= d.end(); ++it){
        copia.push_back(new DatiGraficoBarre(**it));
    }
    return copia;
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

GraficoBarre::GraficoBarre(const GraficoBarre & g): GraficoBase(g), categorie(g.categorie), dati(copiaDati(g.dati))
{
}

