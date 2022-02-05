#ifndef TORTA_H
#define TORTA_H
#include<fettatorta.h>
#include<graficobase.h>
#include<map>
using std::map;

class Torta: public GraficoBase
{
private:
    map<string, FettaTorta*> fette;
public:
    Torta();
    ~Torta();
    Torta(const map<string, FettaTorta *> &fette);
    const map<string, FettaTorta *> &getFette() const;
    void setFette(const map<string, FettaTorta *> &newFette);
    void salva() const;
    string getNomeClasse() const;
};

#endif // TORTA_H
