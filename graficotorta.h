#ifndef GRAFICOTORTA_H
#define GRAFICOTORTA_H
#include <graficobase.h>
#include <map>
using std::map;

class GraficoTorta : public GraficoBase
{
private:
    map<string, double> fette;

public:
    GraficoTorta();
    GraficoTorta(const map<string, double> &fette, string = "Grafico a Torta");
    const map<string, double> &getFette() const;
    void setFette(const map<string, double> &newFette);

    void salvaDati(QXmlStreamWriter *) const;
    string getNomeClasse() const;
};

#endif // GRAFICOTORTA_H
