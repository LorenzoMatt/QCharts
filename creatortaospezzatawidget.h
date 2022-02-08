#ifndef CREATORTAOSPEZZATAWIDGET_H
#define CREATORTAOSPEZZATAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include<QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>

#include "coordinataspezzata.h"
#include "string"
#include "map"
#include "list"
using std::map;
using std::string;
using std::list;

class CreaTortaOSpezzataWidget : public QWidget
{
    Q_OBJECT
private:
    class QLineEditPair{
    public:
        QLineEditPair(QLineEdit*,QLineEdit*);
        QLineEdit* nome;
        QLineEdit* valore;
    };

    QVBoxLayout* layout;
    QFormLayout* formLayout;
    QList<QLineEditPair> dati;
    QHBoxLayout* layoutBottoni;
    bool graficoTorta;


public:
    explicit CreaTortaOSpezzataWidget(QWidget *parent = nullptr, bool = true);
signals:
    void creaTorta(map<std::string, double>);
    void creaSpezzata(const list<CoordinataSpezzata*>&);
    void cancella();

private slots:
    void finestraDiConferma();
    void confermaCreazione();
    void aggiungiRiga();
    void cancellaCreazioneGrafico();

};

#endif // CREATORTAOSPEZZATAWIDGET_H
