#ifndef MODIFICAGRAFICOWIDGET_H
#define MODIFICAGRAFICOWIDGET_H

#include "graficobase.h"

#include <QWidget>

class ModificaGraficoWidget : public QWidget
{
    Q_OBJECT
private:
    GraficoBase* grafico;
public:
    explicit ModificaGraficoWidget(GraficoBase* grafico, QWidget *parent = nullptr);
    virtual void modifica() = 0;
signals:

};

#endif // MODIFICAGRAFICOWIDGET_H
