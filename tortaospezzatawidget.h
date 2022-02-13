#ifndef TORTAOSPEZZATAWIDGET_H
#define TORTAOSPEZZATAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalMapper>

#include "coordinataspezzata.h"
#include "string"
#include "list"
#include "graficospezzata.h"
#include "graficotorta.h"
using std::list;
using std::string;

class TortaOSpezzataWidget : public QWidget
{
    Q_OBJECT
private:
    class QLineEditPair: public QObject
    {
    public:
        QLineEditPair(QLineEdit *, QLineEdit *);
        QLineEdit *nome;
        QLineEdit *valore;
    };
    class QLineEditPairAndRemove: public QWidget
    {
    public:
        QLineEditPairAndRemove(QLineEditPair * editPair, QPushButton * rimuovi, QWidget* parent = nullptr);
        QLineEditPair * editPair;
        QPushButton * rimuovi;
    };

    QVBoxLayout *layout;
    QVBoxLayout *layoutDati;
    QList<QLineEditPair*> dati;
    QHBoxLayout *layoutBottoni;
    QSignalMapper* signalMapper;
    bool graficoTorta;
    GraficoBase* grafico;

    void aggiungiDatiGrafico();
    void costruisciDatiSpezzata(GraficoSpezzata*);
    void costruisciDatiTorta(GraficoTorta*);

    void costruisciRigaConDati(string nome, double valore);

public:
    explicit TortaOSpezzataWidget(QWidget *parent = nullptr, bool = true, GraficoBase* grafico = nullptr);
signals:
    void Torta(map<std::string, double>);
    void Spezzata(const list<CoordinataSpezzata *> &);
    void cancella();

private slots:
    void finestraDiConferma();
    void confermaCreazione();
    void aggiungiRiga();
    void cancellaCreazioneGrafico();
    void rimuoviRiga(QWidget *);
};

#endif // TORTAOSPEZZATAWIDGET_H
