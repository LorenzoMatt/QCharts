#ifndef CREAGRAFICOBARREWIDGET_H
#define CREAGRAFICOBARREWIDGET_H

#include "datigraficobarre.h"
#include "graficobarre.h"

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
    GraficoBarre *grafico;
    QList<QLineEdit *> categorieEditabili;
    QVBoxLayout *layoutPrincipale;
    QVBoxLayout *layoutCategorieWidget;

    QHBoxLayout *layoutBottoniCategorieWidget;

    QGridLayout *gridLayoutDatiEditabili;

    void aggiungiDatiCategorie();

    void creaSchermataInserimentoDati();

    void creaLayoutDatiEditabili();

    void clearWidgets(QLayout *);

    int row;

    class QLineEditPair
    {
    public:
        QLineEditPair(QLineEdit *, QList<QLineEdit *>);
        QLineEdit *nome;
        QList<QLineEdit *> valori;
    };
    QList<QLineEditPair *> datiEditabili;

    QHBoxLayout *layoutBottoniDatiEditabiliWidget;

public:
    explicit CreaGraficoBarreWidget(GraficoBarre* grafico = nullptr, QWidget *parent = nullptr);

private slots:
    void finestraDiConfermaCategorie();
    void confermaCreazioneCategorie();
    void confermaCreazioneGraficoBarre();
    void aggiungiRigaNuovaCategoria();
    void finestraDiConfermaDatiEditabili();
    void aggiungiRigaDatiEditabili();
    void cancellaCreazioneGrafico();
signals:
    void creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &);
    void cancella();
};

#endif // CREAGRAFICOBARREWIDGET_H
