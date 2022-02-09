#ifndef MODIFICATORTAWIDGET_H
#define MODIFICATORTAWIDGET_H

#include "graficotorta.h"
#include "modificagraficowidget.h"

#include <QVBoxLayout>

class ModificaTortaWidget : public ModificaGraficoWidget
{
    Q_OBJECT
private:
    GraficoTorta* grafico;
public:
    explicit ModificaTortaWidget(GraficoTorta* grafico);

signals:


    // ModificaGraficoWidget interface
public:
    void modifica();
};

#endif // MODIFICATORTAWIDGET_H
