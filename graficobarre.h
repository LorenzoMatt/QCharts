#ifndef GRAFICOBARRE_H
#define GRAFICOBARRE_H

#include "datigraficobarre.h"
#include "graficobase.h"
#include "utility.h"
#include <QFile>
#include <list>

using std::list;

class DatiGraficoBarre;

class GraficoBarre: public GraficoBase
{
private:
    list<string> categorie;
    list<DatiGraficoBarre*> dati;
    list<DatiGraficoBarre*> copiaDati(const list<DatiGraficoBarre*>&);

public:
    GraficoBarre();
    ~GraficoBarre();
    GraficoBarre(const list<string> &categorie, const list<DatiGraficoBarre *> &dati, string = "Grafico a Barre");
    GraficoBarre(const GraficoBarre&);

    void salvaDati( QXmlStreamWriter *) const;
    string getNomeClasse() const;
    const list<string> &getCategorie() const;
    void removeCategoriaAndValoreAt(int index);
    void setCategorie(const list<string> &newCategorie);
    const list<DatiGraficoBarre *> &getDati() const;
    void setDati(const list<DatiGraficoBarre *> &newDati);
};

#endif // GRAFICOBARRE_H
