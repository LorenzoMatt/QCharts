#ifndef CREASPEZZATAWIDGET_H
#define CREASPEZZATAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include<QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>

#include "string"
#include "map"
using std::map;
using std::string;
class CreaSpezzataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreaSpezzataWidget(QWidget *parent = nullptr);
private:
    QVBoxLayout* layout;
    QFormLayout* formLayout;
    QMap<QLineEdit*, QLineEdit*> dati;
    QHBoxLayout* layoutBottoni;

signals:
    void creaTorta(map<std::string, double>);

private slots:
    void finestraDiConferma();
    void confermaCreazioneSpezzata();
    void aggiungiRiga();
signals:

};

#endif // CREASPEZZATAWIDGET_H
