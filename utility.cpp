#include "utility.h"

void messaggioInformativo(const QString &titolo, const QString &testo, QWidget *parent)
{
    QMessageBox *messaggio = new QMessageBox(parent);
    messaggio->setWindowTitle(titolo);
    messaggio->setText(testo);
    messaggio->exec();
}

void messaggioErrore(const QString &titolo, const QString &testo, QWidget *parent)
{
    QErrorMessage *messaggio = new QErrorMessage(parent);
    messaggio->setWindowTitle(titolo);
    messaggio->showMessage(testo);
}
