#ifndef UTILITY_H
#define UTILITY_H

#include <QFile>
#include <QMessageBox>
#include <QErrorMessage>
void messaggioInformativo(const QString &titolo, const QString &testo, QWidget *parent = nullptr);
void messaggioErrore(const QString &titolo, const QString &testo, QWidget *parent = nullptr);

#endif // UTILITY_H
