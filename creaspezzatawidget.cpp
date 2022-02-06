#include "creaspezzatawidget.h"
#include "utility.h"

CreaSpezzataWidget::CreaSpezzataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Crea grafico a torta");
    formLayout = new QFormLayout();
    layout = new QVBoxLayout();
    aggiungiRiga();
    QPushButton* aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton* salva = new QPushButton("Salva");
    QPushButton* cancella = new QPushButton("Cancella");

    connect(salva,SIGNAL(clicked()),this,SLOT(finestraDiConferma()));
    connect(aggiungiRiga,SIGNAL(clicked()),this,SLOT(aggiungiRiga()));
    connect(cancella,SIGNAL(clicked()),this,SLOT(close()));

    layoutBottoni = new QHBoxLayout();
    layoutBottoni->addWidget(aggiungiRiga);
    layoutBottoni->addWidget(cancella);
    layoutBottoni->addWidget(salva);

    layout->addLayout(formLayout);
    layout->addLayout(layoutBottoni);
    setLayout(layout);
    setMinimumSize(200,200);
}

void CreaSpezzataWidget::finestraDiConferma()
{
    if(!dati.empty() && !dati.begin().key()->text().isEmpty() && !dati.begin().value()->text().isEmpty()){
        QMessageBox *dialogo=new QMessageBox(this);
        dialogo->setInformativeText ("Confermi la creazione del grafico a torta con i dati inseriti?" );
        QPushButton* ok=new QPushButton("Conferma");
        QPushButton* annulla=new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok,QMessageBox::AcceptRole);
        dialogo->addButton(annulla,QMessageBox::RejectRole);

        connect(ok,SIGNAL(clicked()),this,SLOT(confermaCreazioneSpezzata()));
        connect(annulla,SIGNAL(clicked()),dialogo,SLOT(close()));
        dialogo->exec();
    }else{
        messaggio_errore("Valori non ammessi","Inserire dei valori", this);
    }

}

void CreaSpezzataWidget::confermaCreazioneSpezzata()
{
    map<string, double> v;
    bool chiaviDuplicate = false;
    for(auto it = dati.begin();it!= dati.end(); ++it){
        string chiave = it.key()->text().toStdString();
        if(v.count(chiave) == 0){
            v[chiave] = it.value()->text().toDouble();
        }
        else
        {
            chiaviDuplicate = true;
        }
    }
    if(!chiaviDuplicate){
        emit creaTorta(v);
        close();
    }
    else
    {
        messaggio_errore("Valori duplicati","Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
    }

}

void CreaSpezzataWidget::aggiungiRiga()
{
        QLineEdit* nome = new QLineEdit();
        nome->setPlaceholderText("inserisci il nome");
        QLineEdit* valore = new QLineEdit();
        valore->setPlaceholderText("inserisci il valore");
        valore->setValidator(new QDoubleValidator(0, 100, 2, this));
        formLayout->addRow(nome, valore);
        dati.insert(nome, valore);
}
