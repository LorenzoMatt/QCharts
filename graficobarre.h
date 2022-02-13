#ifndef GRAFICOBARRE_H
#define GRAFICOBARRE_H

#include "datigraficobarre.h"
#include "graficobase.h"
#include "utility.h"
#include <QFile>
#include <list>

using std::list;

class GraficoBarre: public GraficoBase
{
private:
    list<string> categorie;
    list<DatiGraficoBarre*> dati;

public:
    GraficoBarre();
    ~GraficoBarre();
    GraficoBarre(const list<string> &categorie, const list<DatiGraficoBarre *> &dati, string = "Grafico a Barre");

    void salvaDati( QXmlStreamWriter *) const;
    string getNomeClasse() const;
    const list<string> &getCategorie() const;
    void setCategorie(const list<string> &newCategorie);
    const list<DatiGraficoBarre *> &getDati() const;
    void setDati(const list<DatiGraficoBarre *> &newDati);
};

#endif // GRAFICOBARRE_H
