#ifndef GRAFICICONTROLLER_H
#define GRAFICICONTROLLER_H
#include <QObject>
#include<mainwindow.h>
#include "graficotorta.h"
#include "graficolinee.h"
#include "graficobarre.h"

class MainWindow;

class GraficiController : public QObject
{
    Q_OBJECT
private:
    MainWindow* vista;
    GraficoBase* grafico;
public:
    explicit GraficiController(QObject *parent = nullptr);
    GraficiController(MainWindow *vista, GraficoBase *grafico, QObject *parent = nullptr);
    ~GraficiController();
    MainWindow *getVista() const;
    void setVista(MainWindow *newVista);

    GraficoBarre* getGraficoBarre();
    GraficoTorta* getGraficoTorta();
    GraficoLinee* getGraficoLinee();
    GraficoBase *getGrafico() const;
    void setGrafico(GraficoBase *newGrafico);

signals:
public slots:
    void creaNuovaTorta(map<std::string, double> valori);

};

#endif // GRAFICICONTROLLER_H
