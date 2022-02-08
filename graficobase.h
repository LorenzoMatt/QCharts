#ifndef GRAFICOBASE_H
#define GRAFICOBASE_H

#include <string>
using std::string;

class GraficoBase
{
private:
    string titolo;

public:
    GraficoBase();
    GraficoBase(const string &titolo);
    virtual ~GraficoBase();
    virtual void salva(string) const = 0;
    virtual string getNomeClasse() const = 0;
    const string &getTitolo() const;
    void setTitolo(const string &newTitolo);
};

#endif // GRAFICOBASE_H
