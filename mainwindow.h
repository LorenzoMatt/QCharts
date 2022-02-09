#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QMenuBar>
#include <QString>
#include <QFileDialog>
#include <QStandardPaths>
#include "graficobasewidget.h"
using namespace QtCharts;

class GraficiController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GraficiController *controller;

    // funzioni

    GraficoBaseWidget *graficoTorta;
    GraficoBaseWidget *graficoSpezzata;
    GraficoBaseWidget *graficoBarre;

    double calcoloPercentuale(double, double) const;

    QMenuBar *creaMenu();

public:
    MainWindow(GraficiController *controller = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    GraficiController *getController() const;
    void setController(GraficiController *newController);
    void setChartView(GraficoBaseWidget *newChartView);
    void createGraficoBarre();
    void createGraficoTorta();
    void createGraficoSpezzata();

    QChartView *getGraficoTorta() const;
    QChartView *getGraficoSpezzata() const;
    QChartView *getGraficoBarre() const;

private slots:
    void apriEsploraRisorseCaricaFile();
    void apriEsploraRisorseSalvaFile();
    void creaGraficoTorta();
    void creaGraficoBarre();
    void creaGraficoSpezzata();
    void tornaIndietro();
    void inserisciTitoloSpezzata();
    void inserisciTitoloBarre();
    void inserisciTitoloTorta();

signals:
    void carica(const QString &);
    void indietro();
};
#endif // MAINWINDOW_H
