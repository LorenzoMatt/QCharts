#include "mainwindow.h"
#include "graficotorta.h"
#include "graficobarre.h"

QChartView* MainWindow::creaTorta()
{
    GraficoTorta* t = createTorta();

    QPieSeries *series = new QPieSeries();
    for (auto it= t->getFette().begin();it != t->getFette().end();++it) {
        QPieSlice *slice = new QPieSlice(QString::fromStdString(it->first),it->second);
        series->append(slice);
        slice->setLabelVisible();
    }

    // Add label, explode and define brush for 2nd slice
    QPieSlice *slice1 = series->slices().at(1);
    slice1->setExploded();
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::darkGreen, 2));
    slice1->setBrush(Qt::green);

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle(QString::fromStdString(t->getTitolo()));
    chart->legend()->hide();

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

GraficoTorta *MainWindow::createTorta() const
{
    map<string, double> fette;
    fette["Vegetables"]=.40;
    fette["Beans"]=.20;
    fette["Fruits"]=.15;
    fette["Seeds/Nuts"]=.10;
    fette["Whole Grains"]=.15;
    GraficoTorta* t = new GraficoTorta(fette);
    t->setTitolo("What Derek Ate this Week");
    return t;
}

QChartView* MainWindow::createGraficoBarre()
{
    list<double> dati1;
    dati1.push_back(283);
    dati1.push_back(341);
    dati1.push_back(313);
    dati1.push_back(338);
    dati1.push_back(346);
    dati1.push_back(335);

    map<string, list<double>> dati;

    dati["Altuve"] = dati1;
    dati["Martinez"] = dati1;
    GraficoBarre* graficoBarre = new GraficoBarre(dati);
    list<string> categorie;
    categorie.push_back("2013");
    categorie.push_back("2014");
    categorie.push_back("2015");
    categorie.push_back("2016");
    categorie.push_back("2017");
    categorie.push_back("2018");
    graficoBarre->setCategorie(categorie);

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    for (auto it = graficoBarre->getDati().begin(); it!=graficoBarre->getDati().end();++it ) {
        QBarSet* bar = new QBarSet(QString::fromStdString(it->first));
        list<double> l = it->second;
        for(auto it2 = l.begin(); it2!= l.end(); ++it2){
            bar->append(*it2);
        }
        series->append(bar);
    }

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("Batting Avg by Year");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles


    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;
    for(auto it = graficoBarre->getCategorie().begin(); it!= graficoBarre->getCategorie().end(); ++it){
        categories.append(QString::fromStdString(*it));
    }
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // 2. Stacked Bar chart
    // chart->setAxisY(axis, series);

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Assign names to the set of bars used

//     Used to change the palette
//                QPalette pal = qApp->palette();

//                // Change the color around the chart widget and text
//                pal.setColor(QPalette::Window, QRgb(0xffffff));
//                pal.setColor(QPalette::WindowText, QRgb(0x404044));

//                // Apply palette changes to the application
//                qApp->setPalette(pal);



    // 3. Line chart example
    // Other options here https://doc.qt.io/qt-5.11/qtcharts-customchart-example.html
    /*
            QLineSeries *series = new QLineSeries();
            series->append(0, 16);
            series->append(1, 25);
            series->append(2, 24);
            series->append(3, 19);
            series->append(4, 33);
            series->append(5, 25);
            series->append(6, 34);

            // Create chart, add data, hide legend, and add axis
            QChart *chart = new QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();

            // Customize the title font
            QFont font;
            font.setPixelSize(18);
            chart->setTitleFont(font);
            chart->setTitleBrush(QBrush(Qt::black));
            chart->setTitle("Barry Bonds HRs as Pirate");

            // Change the line color and weight
            QPen pen(QRgb(0x000000));
            pen.setWidth(5);
            series->setPen(pen);

            chart->setAnimationOptions(QChart::AllAnimations);

            // Change the x axis categories
            QCategoryAxis *axisX = new QCategoryAxis();
            axisX->append("1986",0);
            axisX->append("1987",1);
            axisX->append("1988",2);
            axisX->append("1989",3);
            axisX->append("1990",4);
            axisX->append("1991",5);
            axisX->append("1992",6);
            chart->setAxisX(axisX, series);

            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            */

    // 4. Pie Chart Example
    // Define slices and percentage of whole they take up
//                QChartView* chartView = creaTorta();

    // Create the main app window
    // Set the main window widget
    QChartView *chartView= createGraficoBarre();

    setCentralWidget(chartView);
    resize(420, 300);
    show();
}


MainWindow::~MainWindow()
{
}

