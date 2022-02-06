#ifndef GRAFICICONTROLLER_H
#define GRAFICICONTROLLER_H
#include <QObject>
#include<mainwindow.h>
#include "graficotorta.h"
#include "graficospezzata.h"
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
    GraficoSpezzata* getGraficoLinee();
    GraficoBase *getGrafico() const;
    void setGrafico(GraficoBase *newGrafico);

signals:
public slots:
    void creaNuovaTorta(map<std::string, double> valori);
    void creaNuovaSpezzata(const list<CoordinataSpezzata *> &valori);


};

#endif // GRAFICICONTROLLER_H
