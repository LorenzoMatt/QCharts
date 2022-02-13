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
#include <QSignalMapper>

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

    void updateRowDatiEditabili();

    int row;
    class QLineEditAndRemoveButton : public QWidget{
    public:
        QLineEditAndRemoveButton(QLineEdit*, QPushButton*, QWidget* = nullptr);
        QLineEdit* categoria;
        QPushButton* rimuovi;
    };

    class QLineEditPair: public QObject
    {
    public:
        QLineEditPair(QLineEdit *, QList<QLineEdit *>, int riga);
        QLineEdit *nome;
        QList<QLineEdit *> valori;
        int riga;
    };
    QSignalMapper* signalMapperCategorie;
    QSignalMapper* signalMapperDatiEditabili;


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
    void rimuoviRigaCategoria(QWidget *);
    void rimuoviRigaDatiEditabili(QObject *);
signals:
    void creaGraficoBarre(const std::list<string> &, const std::list<DatiGraficoBarre *> &);
    void cancella();
};

#endif // CREAGRAFICOBARREWIDGET_H
