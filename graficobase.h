#ifndef GRAFICOBASE_H
#define GRAFICOBASE_H

#include <QFile>
#include <QXmlStreamWriter>

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
    void salva(string) const;
    virtual void salvaDati(QXmlStreamWriter *) const = 0;
    virtual string getNomeClasse() const = 0;
    const string &getTitolo() const;
    void setTitolo(const string &newTitolo);
};

#endif // GRAFICOBASE_H
