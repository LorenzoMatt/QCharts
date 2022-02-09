#ifndef INSERISCITITOLOWIDGET_H
#define INSERISCITITOLOWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>


class InserisciTitoloWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* titolo;
public:
    explicit InserisciTitoloWidget(QString titoloStringa = "", QWidget *parent = nullptr);

signals:
    void titoloSignal(const QString&);
    void cancella();

private slots:
    void finestraDiConfermaCreazioneTitolo();
    void cancellaCreazioneGrafico();

};

#endif // INSERISCITITOLOWIDGET_H
