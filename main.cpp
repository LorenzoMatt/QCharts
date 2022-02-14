#include "graficicontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("../style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    a.setStyleSheet(styleSheet);
    GraficiController c;
    return a.exec();
}
