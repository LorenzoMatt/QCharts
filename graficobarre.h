#ifndef GRAFICOBARRE_H
#define GRAFICOBARRE_H

#include "graficobase.h"

#include <list>
#include <map>

using std::list;
using std::map;

class GraficoBarre: public GraficoBase
{
private:
    map<string, list<double>> dati;
    list<string> categorie;
public:
    GraficoBarre();
    GraficoBarre(const map<string, list<double> > &dati);
    const map<string, list<double> > &getDati() const;
    void setDati(const map<string, list<double> > &newDati);
    void salva() const;
    string getNomeClasse() const;
    const list<string> &getCategorie() const;
    void setCategorie(const list<string> &newCategorie);
};

#endif // GRAFICOBARRE_H
