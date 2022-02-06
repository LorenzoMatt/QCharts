#include "utility.h"

QString  imposta_stile()
{
    QFile file("../style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    return styleSheet;
}
void messaggio_informativo(const QString& titolo,const QString& testo, QWidget* parent)
{
     QMessageBox* messaggio=new QMessageBox(parent);
     messaggio->setWindowTitle(titolo);
     messaggio->setText(testo);
     messaggio->exec();
 }

 void messaggio_errore(const QString& titolo,const QString& testo, QWidget* parent)
 {
     QErrorMessage* messaggio=new QErrorMessage(parent);
     messaggio->setWindowTitle(titolo);
     messaggio->showMessage(testo);
 }
