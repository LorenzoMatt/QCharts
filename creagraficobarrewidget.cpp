#include "creagraficobarrewidget.h"
#include "utility.h"



void CreaGraficoBarreWidget::creaSchermataInserimentoDati()
{
    row = 0;
    QString title = "Inserisci valori";
    setWindowTitle(title);
    gridLayoutDatiEditabili = new QGridLayout();

    QPushButton* aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton* salva = new QPushButton("Salva");
    QPushButton* cancella = new QPushButton("Cancella");

    connect(salva,SIGNAL(clicked()),this,SLOT(finestraDiConfermaDatiEditabili()));
    connect(aggiungiRiga,SIGNAL(clicked()),this,SLOT(aggiungiRigaDatiEditabili()));
    connect(cancella,SIGNAL(clicked()),this,SLOT(close()));

    layoutBottoniDatiEditabiliWidget = new QHBoxLayout();
    layoutBottoniDatiEditabiliWidget->addWidget(aggiungiRiga);
    layoutBottoniDatiEditabiliWidget->addWidget(cancella);
    layoutBottoniDatiEditabiliWidget->addWidget(salva);

    clearWidgets(layoutPrincipale);

    creaTabellaDatiEditabili();

    layoutPrincipale->addLayout(gridLayoutDatiEditabili);

    layoutPrincipale->addLayout(layoutBottoniDatiEditabiliWidget);

    setMinimumSize(200,200);

}

void CreaGraficoBarreWidget::clearWidgets(QLayout * layout) {
    if (! layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}

void CreaGraficoBarreWidget::creaTabellaDatiEditabili()
{
    //    tabellaDatiEditabili=new QTableWidget();
    //    tabellaDatiEditabili->setColumnCount(categorie.size() + 1);
    //    tabellaDatiEditabili->setRowCount(1);
    //    QStringList *horizontalheader=new QStringList();
    //    horizontalheader->append("Nome");
    //    for(auto it = categorie.begin(); it != categorie.end(); ++it){
    //        horizontalheader->append(QString::fromStdString(*it));
    //    }
    ////    tabellaDatiEditabili->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    tabellaDatiEditabili->setHorizontalHeaderLabels(*horizontalheader);
    //    tabellaDatiEditabili->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //    QHeaderView* header = tabellaDatiEditabili->horizontalHeader();// adatta la larghezza delle colonne
    //    header->setSectionResizeMode(QHeaderView::Stretch);// adatta la larghezza delle colonne
    //    tabellaDatiEditabili->setMaximumHeight(400);

    //    layoutDatiEditabiliWidget->addWidget(tabellaDatiEditabili);

    //    aggiungiRigaDatiEditabili(false);
    gridLayoutDatiEditabili->addWidget(new QLabel("Nome"),row, 0, Qt::AlignTop);
    int col = 1;
    for(auto it = categorie.begin(); it != categorie.end(); ++it,++col){
        QLabel* label = new QLabel(QString::fromStdString(*it));
        label->setAlignment(Qt::AlignCenter);
        gridLayoutDatiEditabili->addWidget(label,row, col, Qt::AlignTop);
    }
    row++;



}

CreaGraficoBarreWidget::CreaGraficoBarreWidget(QWidget *parent)
    : QWidget(parent)
{
    QString title = "Inserisci categorie";
    setWindowTitle(title);
    layoutPrincipale = new QVBoxLayout();
    QPushButton* aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton* salva = new QPushButton("Salva");
    QPushButton* cancella = new QPushButton("Cancella");

    connect(salva,SIGNAL(clicked()),this,SLOT(finestraDiConfermaCategorie()));
    connect(aggiungiRiga,SIGNAL(clicked()),this,SLOT(aggiungiRigaNuovaCategoria()));
    connect(cancella,SIGNAL(clicked()),this,SLOT(close()));

    layoutBottoniCategorieWidget = new QHBoxLayout();
    layoutBottoniCategorieWidget->addWidget(aggiungiRiga);
    layoutBottoniCategorieWidget->addWidget(cancella);
    layoutBottoniCategorieWidget->addWidget(salva);

    layoutCategorieWidget = new QVBoxLayout();

    layoutPrincipale->addLayout(layoutCategorieWidget);

    layoutPrincipale->addLayout(layoutBottoniCategorieWidget);
    setLayout(layoutPrincipale);

    setMinimumSize(200,200);
}

CreaGraficoBarreWidget::QLineEditPair::QLineEditPair(QLineEdit * nome, QList<QLineEdit *> valori): nome(nome), valori(valori)
{

}



void CreaGraficoBarreWidget::finestraDiConfermaCategorie()
{
    if(!categorieEditabili.empty() && !(*categorieEditabili.begin())->text().isEmpty()){
        QMessageBox *dialogo=new QMessageBox(this);
        dialogo->setInformativeText ("Confermi le categorie inserite?" );
        QPushButton* ok=new QPushButton("Conferma");
        QPushButton* annulla=new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok,QMessageBox::AcceptRole);
        dialogo->addButton(annulla,QMessageBox::RejectRole);

        connect(ok,SIGNAL(clicked()),this,SLOT(confermaCreazioneCategorie()));
        connect(annulla,SIGNAL(clicked()),dialogo,SLOT(close()));
        dialogo->exec();
    }else{
        messaggioErrore("Valori non ammessi","Inserire dei valori", this);
    }

}

void CreaGraficoBarreWidget::aggiungiRigaNuovaCategoria()
{
    QLineEdit* nomeCategoria = new QLineEdit();
    nomeCategoria->setPlaceholderText("inserisci il nome della categoria");
    categorieEditabili.push_back(nomeCategoria);
    layoutCategorieWidget->addWidget(nomeCategoria);
}

void CreaGraficoBarreWidget::finestraDiConfermaDatiEditabili()
{
    if(!datiEditabili.empty() && !(*datiEditabili.begin())->nome->text().isEmpty()){
        QMessageBox *dialogo=new QMessageBox(this);
        dialogo->setInformativeText ("Confermi le categorie inserite?" );
        QPushButton* ok=new QPushButton("Conferma");
        QPushButton* annulla=new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok,QMessageBox::AcceptRole);
        dialogo->addButton(annulla,QMessageBox::RejectRole);

        connect(ok,SIGNAL(clicked()),this,SLOT(confermaCreazioneGraficoBarre()));
        connect(annulla,SIGNAL(clicked()),dialogo,SLOT(close()));
        dialogo->exec();
    }else{
        messaggioErrore("Valori non ammessi","Inserire dei valori", this);
    }

}

void CreaGraficoBarreWidget::aggiungiRigaDatiEditabili()
{
    //    if(insert)
    //        tabellaDatiEditabili->insertRow(1);
    //    QList<QLineEdit*> val;
    //    QLineEdit* nomeEditabile = new QLineEdit();

    //    nomeEditabile->setPlaceholderText("inserisci nome");
    //    int row = tabellaDatiEditabili->rowCount() -1;
    //    tabellaDatiEditabili->setCellWidget(row , 0, nomeEditabile);
    //    int colonna = 1;
    //    for(auto it = categorie.begin(); it!= categorie.end(); ++it, ++colonna){
    //        QLineEdit* categoriaEditabile = new QLineEdit();
    //        categoriaEditabile->setPlaceholderText("inserisci il valore");
    //        categoriaEditabile->setValidator(new QDoubleValidator);
    //        tabellaDatiEditabili->setCellWidget(row, colonna, categoriaEditabile);
    //        val.push_back(categoriaEditabile);
    //    }

    //    //    datiEditabili.push_back(new QLineEditPair(nomeEditabile, val));

    QList<QLineEdit*> val;
    QLineEdit* nomeEditabile = new QLineEdit();

    nomeEditabile->setPlaceholderText("inserisci nome");
    gridLayoutDatiEditabili->addWidget(nomeEditabile, row, 0, Qt::AlignTop);

    int colonna = 1;
    for(auto it = categorie.begin(); it!= categorie.end(); ++it, ++colonna){
        QLineEdit* categoriaEditabile = new QLineEdit();
        categoriaEditabile->setPlaceholderText("inserisci il valore");
        categoriaEditabile->setValidator(new QDoubleValidator);
        gridLayoutDatiEditabili->addWidget(categoriaEditabile, row, colonna, Qt::AlignTop);
        val.push_back(categoriaEditabile);
    }
    row++;

    datiEditabili.push_back(new QLineEditPair(nomeEditabile, val));

}

void CreaGraficoBarreWidget::confermaCreazioneCategorie()
{
    bool chiaviDuplicate = false;
    for(auto it = categorieEditabili.begin();it!= categorieEditabili.end() && !chiaviDuplicate; ++it){
        string categoria = (*it)->text().toStdString();
        for(auto it2 = categorie.begin(); it2!= categorie.end() && !chiaviDuplicate; ++it2){
            if((*it2) == categoria)
                chiaviDuplicate = true;
        }
        if(!chiaviDuplicate && !categoria.empty()){
            categorie.push_back(categoria);
        }
    }
    if(!chiaviDuplicate){
        creaSchermataInserimentoDati();
    }
    else{
        messaggioErrore("Valori duplicati","Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
        categorie.clear();
    }


}

void CreaGraficoBarreWidget::confermaCreazioneGraficoBarre()
{
    list<DatiGraficoBarre*> dati;
    for(auto it = datiEditabili.begin(); it!= datiEditabili.end(); ++it){
        string nome = ((*it)->nome->text()).toStdString();
        list<double> valoriInseriti;
        QList<QLineEdit*> valoriList = (*it)->valori;
        if(!nome.empty()){
            for(auto it2 = valoriList.begin(); it2 != valoriList.end(); ++it2){
                valoriInseriti.push_back((*it2)->text().toDouble());
            }
        }
        dati.push_back(new DatiGraficoBarre(nome, valoriInseriti));
    }
    emit creaGraficoBarre(categorie, dati);
    close();

}
