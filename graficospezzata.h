#ifndef GRAFICOSPEZZATA_H
#define GRAFICOSPEZZATA_H

#include <QFile>
#include <QXmlStreamWriter>

#include "graficobase.h"
#include "coordinataspezzata.h"
#include <map>
#include <list>
using std::list;

class GraficoSpezzata : public GraficoBase
{
private:
    list<CoordinataSpezzata *> valori;

public:
    GraficoSpezzata();
    ~GraficoSpezzata();
    GraficoSpezzata(const list<CoordinataSpezzata *> &valori, string = "Grafico a Linee");
    virtual void salvaDati(QXmlStreamWriter *) const;
    string getNomeClasse() const;
    const list<CoordinataSpezzata *> &getValori() const;
    void setValori(const list<CoordinataSpezzata *> &newValori);
};

#endif // GRAFICOSPEZZATA_H
