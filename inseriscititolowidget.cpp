#include "inseriscititolowidget.h"
#include "utility.h"

InserisciTitoloWidget::InserisciTitoloWidget(QString titoloStringa, QWidget *parent)
    : QWidget{parent}
{
    titolo = new QLineEdit();
    QLabel* label=new QLabel("Inserisci il titolo del grafico");
    QPushButton *salva = new QPushButton("Salva");

    label->setFont(QFont("Times", 30, QFont::Bold));
    label->setBuddy(titolo);
    label->setMargin(50);
    if(titoloStringa == "")
        titolo->setPlaceholderText("Inserisci titolo");
    else
        titolo->setText(titoloStringa);
    QVBoxLayout* layout = new QVBoxLayout();

    connect(salva, SIGNAL(clicked()), this, SLOT(finestraDiConfermaCreazioneTitolo()));

    layout->addWidget(label);
    layout->addWidget(titolo);
    layout->addWidget(salva);
    setLayout(layout);

}

void InserisciTitoloWidget::finestraDiConfermaCreazioneTitolo()
{
    QString t = titolo->text();
    if(!t.isEmpty())
        emit titoloSignal(titolo->text());
    else
        messaggioErrore("Inserire un titolo","Il titolo non può essere vuoto",this);
}

void InserisciTitoloWidget::cancellaCreazioneGrafico()
{
    emit cancella();

}
