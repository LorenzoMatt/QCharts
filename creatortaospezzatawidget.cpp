#include "creatortaospezzatawidget.h"
#include "utility.h"



CreaTortaOSpezzataWidget::CreaTortaOSpezzataWidget(QWidget *parent, bool graficoTorta) : QWidget(parent), graficoTorta(graficoTorta)
{
    setWindowTitle((&"Crea grafico " [ graficoTorta]) ? "a torta" : "a linee");
    formLayout = new QFormLayout();
    layout = new QVBoxLayout();
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

void CreaTortaOSpezzataWidget::finestraDiConferma()
{
    if(!dati.empty() && !dati.begin()->nome->text().isEmpty() && !dati.begin()->valore->text().isEmpty()){
        QMessageBox *dialogo=new QMessageBox(this);
        dialogo->setInformativeText ("Confermi la creazione del grafico con i dati inseriti?" );
        QPushButton* ok=new QPushButton("Conferma");
        QPushButton* annulla=new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok,QMessageBox::AcceptRole);
        dialogo->addButton(annulla,QMessageBox::RejectRole);

        connect(ok,SIGNAL(clicked()),this,SLOT(confermaCreazione()));
        connect(annulla,SIGNAL(clicked()),dialogo,SLOT(close()));
        dialogo->exec();
    }else{
        messaggio_errore("Valori non ammessi","Inserire dei valori", this);
    }

}

void CreaTortaOSpezzataWidget::confermaCreazione()
{
    bool chiaviDuplicate = false;

    if(graficoTorta){
        map<string, double> v;
        for(auto it = dati.begin();it!= dati.end() && !chiaviDuplicate; ++it){
            string chiave = it->nome->text().toStdString();
            if(v.count(chiave) == 0){
                v[chiave] = it->valore->text().toDouble();
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
    else {
        list<CoordinataSpezzata*> v;
        for(auto it = dati.begin();it!= dati.end() && !chiaviDuplicate; ++it){
            string chiave = it->nome->text().toStdString();
            double valore = it->valore->text().toDouble();
            for(auto it2 = v.begin(); it2!= v.end() && !chiaviDuplicate; ++it2){
                if((*it2)->getNome()==chiave)
                    chiaviDuplicate = true;
            }
            if(!chiaviDuplicate){
                v.push_back(new CoordinataSpezzata(chiave,valore));
            }
        }
        if(!chiaviDuplicate){
            emit creaSpezzata(v);
            close();
        }
        else{
            messaggio_errore("Valori duplicati","Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
        }

    }


}

void CreaTortaOSpezzataWidget::aggiungiRiga()
{
    QLineEdit* nome = new QLineEdit();
    nome->setPlaceholderText("inserisci il nome");
    QLineEdit* valore = new QLineEdit();
    valore->setPlaceholderText("inserisci il valore");
    valore->setValidator(new QDoubleValidator(0, 100, 2, this));
    formLayout->addRow(nome, valore);
    dati.push_back(QLineEditPair(nome, valore));
}

CreaTortaOSpezzataWidget::QLineEditPair::QLineEditPair(QLineEdit * nome, QLineEdit *valore): nome(nome), valore(valore)
{
}
