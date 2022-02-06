#ifndef GRAFICOLINEE_H
#define GRAFICOLINEE_H

#include "graficobase.h"
#include<map>
using std::map;

class GraficoLinee : public GraficoBase
{
private:
    map<string, double> valori;
public:
    GraficoLinee();
    GraficoLinee(const map<string, double> &valori);
    const map<string, double> &getValori() const;
    void setValori(const map<string, double> &newValori);

    void salva(string) const;
    string getNomeClasse() const;
};

#endif // GRAFICOLINEE_H
