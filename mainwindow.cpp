#include "mainwindow.h"
#include "fettatorta.h"
#include "torta.h"

QChartView* MainWindow::creaTorta()
{
    Torta* t = createTorta();

    QPieSeries *series = new QPieSeries();
    for (auto it= t->getFette().begin();it != t->getFette().end();++it) {
        QPieSlice *slice = new QPieSlice(QString::fromStdString(it->second->getVoce()),it->second->getValore());
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

Torta *MainWindow::createTorta() const
{
    FettaTorta* f1 = new FettaTorta("Vegetables",.40);
    FettaTorta* f2 = new FettaTorta("Beans",.20);
    FettaTorta* f3 = new FettaTorta("Fruits",.15);
    FettaTorta* f4 = new FettaTorta("Seeds/Nuts",.10);
    FettaTorta* f5 = new FettaTorta("Whole Grains",.15);
    map<string, FettaTorta*> fette;
    fette[f1->getVoce()]=f1;
    fette[f2->getVoce()]=f2;
    fette[f3->getVoce()]=f3;
    fette[f4->getVoce()]=f4;
    fette[f5->getVoce()]=f5;


    Torta* t = new Torta(fette);
    t->setTitolo("What Derek Ate this Week");
    return t;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{     

            // Assign names to the set of bars used
            QBarSet *set0 = new QBarSet("Altuve");
            QBarSet *set1 = new QBarSet("Martinez");
            QBarSet *set2 = new QBarSet("Segura");
            QBarSet *set3 = new QBarSet("Simmons");
            QBarSet *set4 = new QBarSet("Trout");

            // Assign values for each bar
            *set0 << 283 << 341 << 313 << 338 << 346 << 335;
            *set1 << 250 << 315 << 282 << 307 << 303 << 330;
            *set2 << 294 << 246 << 257 << 319 << 300 << 325;
            *set3 << 248 << 244 << 265 << 281 << 278 << 313;
            *set4 << 323 << 287 << 299 << 315 << 306 << 313;

            // Add all sets of data to the chart as a whole
            // 1. Bar Chart
            QBarSeries *series = new QBarSeries();

            // 2. Stacked bar chart
            // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
            series->append(set0);
            series->append(set1);
            series->append(set2);
            series->append(set3);
            series->append(set4);

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
            QStringList categories;
            categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";

            // Adds categories to the axes
            QBarCategoryAxis *axis = new QBarCategoryAxis();
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

            // Used to change the palette
//            QPalette pal = qApp->palette();

//            // Change the color around the chart widget and text
//            pal.setColor(QPalette::Window, QRgb(0xffffff));
//            pal.setColor(QPalette::WindowText, QRgb(0x404044));

//            // Apply palette changes to the application
//            qApp->setPalette(pal);



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
//            QChartView* chartView = creaTorta();

            // Create the main app window
            // Set the main window widget
            setCentralWidget(chartView);
            resize(420, 300);
            show();
}



MainWindow::~MainWindow()
{
}

