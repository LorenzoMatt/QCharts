#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
// The main window to which you add toolbars,
// menubars, widgets and status bar
#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>

// Used to draw bars representing data provided
// grouped into categories
#include <QtCharts/QBarSeries>

// Represents 1 set of bars in a bar chart
#include <QtCharts/QBarSet>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Adds categories to the charts axes
#include <QtCharts/QBarCategoryAxis>

// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
using namespace QtCharts;

class GraficiController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    GraficiController* controller;


    //funzioni
    QChartView *createGraficoBarre();
    QChartView *creaTorta();
    QChartView *createGraficoLinee();
    QChartView * chartView;
    
public:
    MainWindow(GraficiController *controller = nullptr, QChartView *chartView = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    GraficiController *getController() const;
    void setController(GraficiController *newController);
    QChartView *getChartView() const;
    void setChartView(QChartView *newChartView);
};
#endif // MAINWINDOW_H
