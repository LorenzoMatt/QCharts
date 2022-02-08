#include "graficicontroller.h"
#include "utility.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(impostaStile());
    GraficiController c;
    return a.exec();
}
