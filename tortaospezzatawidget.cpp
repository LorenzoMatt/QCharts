#include "tortaospezzatawidget.h"
#include "utility.h"

TortaOSpezzataWidget::TortaOSpezzataWidget(QWidget *parent, bool graficoTorta, GraficoBase *grafico) : QWidget(parent), graficoTorta(graficoTorta), grafico(grafico)
{
    QString title = grafico ? "Modifica " : "Crea ";
    title = title + "grafico" + (graficoTorta ? " a torta" : " a linee");
    setWindowTitle(title);
    layoutDati = new QVBoxLayout();
    layout = new QVBoxLayout();
    signalMapper=new QSignalMapper;
    QPushButton *aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton *salva = new QPushButton("Salva");
    QPushButton *cancella = new QPushButton("Cancella");

    connect(salva, SIGNAL(clicked()), this, SLOT(finestraDiConferma()));
    connect(aggiungiRiga, SIGNAL(clicked()), this, SLOT(aggiungiRiga()));
    connect(cancella, SIGNAL(clicked()), this, SLOT(cancellaCreazioneGrafico()));
    connect(signalMapper,SIGNAL(mapped(QWidget*)),SLOT(rimuoviRiga(QWidget*)));


    if(grafico){
        aggiungiDatiGrafico();
    }

    layoutBottoni = new QHBoxLayout();
    layoutBottoni->addWidget(aggiungiRiga);
    layoutBottoni->addWidget(cancella);
    layoutBottoni->addWidget(salva);

    layout->addLayout(layoutDati);
    layout->addLayout(layoutBottoni);
    setLayout(layout);
    setMinimumSize(200, 200);
}

void TortaOSpezzataWidget::aggiungiDatiGrafico()
{
    GraficoSpezzata* gs = dynamic_cast<GraficoSpezzata*>(grafico);
    if(gs){
        costruisciDatiSpezzata(gs);
    }
    GraficoTorta* gt = dynamic_cast<GraficoTorta*>(grafico);
    if(gt){
        costruisciDatiTorta(gt);
    }
}

void TortaOSpezzataWidget::costruisciDatiSpezzata(GraficoSpezzata* gs)
{
    for(auto it= gs->getValori().begin(); it != gs->getValori().end(); ++it){
        costruisciRigaConDati((*it)->getNome(), (*it)->getValore());
    }
}

void TortaOSpezzataWidget::costruisciDatiTorta(GraficoTorta* gt)
{
    for(auto it= gt->getFette().begin(); it != gt->getFette().end(); ++it){
        costruisciRigaConDati(it->first, it->second);
    }
}

void TortaOSpezzataWidget::costruisciRigaConDati(string n, double v)
{
    QLineEdit *nome = new QLineEdit();
    nome->setText(QString::fromStdString(n));
    QLineEdit *valore = new QLineEdit();
    valore->setText(QString::number(v, 'f', 2));
    valore->setValidator(new QDoubleValidator);
    QPushButton* rimuovi = new QPushButton("Rimuovi");
    connect(rimuovi,SIGNAL(clicked()),signalMapper,SLOT(map()));
    QLineEditPair* editPair = new QLineEditPair(nome, valore);
    dati.push_back(editPair);
    QLineEditPairAndRemove* lineEditPairAndRemove = new QLineEditPairAndRemove(editPair, rimuovi, this);
    signalMapper->setMapping(rimuovi, lineEditPairAndRemove);
    layoutDati->addWidget(lineEditPairAndRemove);
}


void TortaOSpezzataWidget::finestraDiConferma()
{
    if (!dati.empty() && !(*(dati.begin()))->nome->text().isEmpty() && !(*(dati.begin()))->valore->text().isEmpty())
    {
        QMessageBox *dialogo = new QMessageBox(this);
        dialogo->setInformativeText("Confermi la creazione del grafico con i dati inseriti?");
        QPushButton *ok = new QPushButton("Conferma");
        QPushButton *annulla = new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok, QMessageBox::AcceptRole);
        dialogo->addButton(annulla, QMessageBox::RejectRole);

        connect(ok, SIGNAL(clicked()), this, SLOT(confermaCreazione()));
        connect(annulla, SIGNAL(clicked()), dialogo, SLOT(close()));
        dialogo->exec();
    }
    else
    {
        messaggioErrore("Valori non ammessi", "Inserire dei valori", this);
    }
}

void TortaOSpezzataWidget::confermaCreazione()
{
    bool chiaviDuplicate = false;

    if (graficoTorta)
    {
        map<string, double> v;
        for (auto it = dati.begin(); it != dati.end() && !chiaviDuplicate; ++it)
        {
            string chiave = (*it)->nome->text().toStdString();
            if (v.count(chiave) == 0)
            {
                v[chiave] = (*it)->valore->text().toDouble();
            }
            else
            {
                chiaviDuplicate = true;
            }
        }
        if (!chiaviDuplicate)
        {
            emit Torta(v);
            close();
        }
        else
        {
            messaggioErrore("Valori duplicati", "Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
        }
    }
    else
    {
        list<CoordinataSpezzata *> v;
        for (auto it = dati.begin(); it != dati.end() && !chiaviDuplicate; ++it)
        {
            string chiave = (*it)->nome->text().toStdString();
            double valore = (*it)->valore->text().toDouble();
            for (auto it2 = v.begin(); it2 != v.end() && !chiaviDuplicate; ++it2)
            {
                if ((*it2)->getNome() == chiave)
                    chiaviDuplicate = true;
            }
            if (!chiaviDuplicate && !chiave.empty())
            {
                v.push_back(new CoordinataSpezzata(chiave, valore));
            }
        }
        if (!chiaviDuplicate)
        {
            emit Spezzata(v);
            close();
        }
        else
        {
            messaggioErrore("Valori duplicati", "Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
        }
    }
}

void TortaOSpezzataWidget::aggiungiRiga()
{
    QLineEdit *nome = new QLineEdit();
    nome->setPlaceholderText("inserisci il nome");
    QLineEdit *valore = new QLineEdit();
    valore->setPlaceholderText("inserisci il valore");
    valore->setValidator(new QDoubleValidator);
    QPushButton* rimuovi = new QPushButton("Rimuovi");
    connect(rimuovi,SIGNAL(clicked()),signalMapper,SLOT(map()));
    QLineEditPair* editPair = new QLineEditPair(nome, valore);
    dati.push_back(editPair);
    QLineEditPairAndRemove* lineEditPairAndRemove = new QLineEditPairAndRemove(editPair, rimuovi, this);
    signalMapper->setMapping(rimuovi, lineEditPairAndRemove);
    layoutDati->addWidget(lineEditPairAndRemove);
}

void TortaOSpezzataWidget::cancellaCreazioneGrafico()
{
    emit cancella();
}

void TortaOSpezzataWidget::rimuoviRiga(QWidget * l)
{
    QLineEditPairAndRemove* lineEdit = dynamic_cast<QLineEditPairAndRemove*>(l);
    if(lineEdit){
        dati.removeOne(lineEdit->editPair);
        layoutDati->removeWidget(lineEdit);
        lineEdit->hide();
    }
}

TortaOSpezzataWidget::QLineEditPairAndRemove::QLineEditPairAndRemove(QLineEditPair * editPair, QPushButton * rimuovi, QWidget *parent) :QWidget(parent), editPair(editPair), rimuovi(rimuovi)
{
    QHBoxLayout* layoutRiga = new QHBoxLayout();
    layoutRiga->addWidget(editPair->nome);
    layoutRiga->addWidget(editPair->valore);
    layoutRiga->addWidget(rimuovi);
    setLayout(layoutRiga);
}

TortaOSpezzataWidget::QLineEditPair::QLineEditPair(QLineEdit *nome, QLineEdit *valore): QObject(nullptr), nome(nome), valore(valore)
{

}
