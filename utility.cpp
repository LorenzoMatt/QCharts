#include "utility.h"

QString  impostaStile()
{
    QFile file("../style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    return styleSheet;
}
void messaggioInformativo(const QString& titolo,const QString& testo, QWidget* parent)
{
     QMessageBox* messaggio=new QMessageBox(parent);
     messaggio->setWindowTitle(titolo);
     messaggio->setText(testo);
     messaggio->exec();
 }

 void messaggioErrore(const QString& titolo,const QString& testo, QWidget* parent)
 {
     QErrorMessage* messaggio=new QErrorMessage(parent);
     messaggio->setWindowTitle(titolo);
     messaggio->showMessage(testo);
 }
