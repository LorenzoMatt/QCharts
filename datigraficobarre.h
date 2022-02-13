#ifndef DATIGRAFICOBARRE_H
#define DATIGRAFICOBARRE_H

#include <list>
#include <string>

#include "graficobarre.h"

using std::list;
using std::string;

class GraficoBarre;

class DatiGraficoBarre
{
    friend class GraficoBarre;
private:
    string nome;
    list<double> valori;

public:
    DatiGraficoBarre();
    DatiGraficoBarre(const string &nome, const list<double> &valori);
    const string &getNome() const;
    void setNome(const string &newNome);
    const list<double> &getValori() const;
    list<double> &getValori();
    void setValori(const list<double> &newValori);
};

#endif // DATIGRAFICOBARRE_H
