#ifndef GRAFICICONTROLLER_H
#define GRAFICICONTROLLER_H
#include <QObject>
#include<mainwindow.h>
#include "graficotorta.h"
#include "graficospezzata.h"
#include "graficobarre.h"
#include "filereader.h"

class MainWindow;

class GraficiController : public QObject
{
    Q_OBJECT
private:
    MainWindow* vista;
    GraficoBase* grafico;
    FileReader* fileReader;
public:
    explicit GraficiController(QObject *parent = nullptr);
    ~GraficiController();
    MainWindow *getVista() const;
    void setVista(MainWindow *newVista);
    GraficoBase *getGrafico() const;
    void setGrafico(GraficoBase *newGrafico);


signals:

public slots:
    void creaNuovaTorta(map<std::string, double> valori);
    void creaNuovaSpezzata(const list<CoordinataSpezzata *> &valori);
    void creaNuovaBarra(const std::list<string> &,const std::list<DatiGraficoBarre*>&);
    void salva(string);
    void ottieniGraficoDaFile(const QString&);
    void visualizzaGrafico();


};

#endif // GRAFICICONTROLLER_H
