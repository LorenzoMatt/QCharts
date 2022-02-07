#ifndef CREAGRAFICOBARREWIDGET_H
#define CREAGRAFICOBARREWIDGET_H

#include "datigraficobarre.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QDoubleValidator>
#include <QLabel>

#include <list>
#include <string>

using std::list;
using std::string;

class CreaGraficoBarreWidget : public QWidget
{
    Q_OBJECT
private:

    list<string> categorie;
    QList<QLineEdit*> categorieEditabili;
    QVBoxLayout* layoutPrincipale;
    QVBoxLayout* layoutCategorieWidget;

    QHBoxLayout* layoutBottoniCategorieWidget;

    QGridLayout* gridLayoutDatiEditabili;

    void creaSchermataInserimentoDati();

    void creaTabellaDatiEditabili();

    void clearWidgets(QLayout*);

    int row;


    class QLineEditPair{
    public:
        QLineEditPair(QLineEdit*,QList<QLineEdit*>);
        QLineEdit* nome;
        QList<QLineEdit*> valori;
    };
    QList<QLineEditPair*> datiEditabili;

    QHBoxLayout* layoutBottoniDatiEditabiliWidget;

public:
    explicit CreaGraficoBarreWidget(QWidget *parent = nullptr);


private slots:
    void finestraDiConfermaCategorie();
    void confermaCreazioneCategorie();
    void confermaCreazioneGraficoBarre();
    void aggiungiRigaNuovaCategoria();
    void finestraDiConfermaDatiEditabili();
    void aggiungiRigaDatiEditabili();
signals:
    void creaGraficoBarre(const std::list<string> &,const std::list<DatiGraficoBarre*>&);

};

#endif // CREAGRAFICOBARREWIDGET_H
