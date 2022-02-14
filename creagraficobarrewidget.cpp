#include "creagraficobarrewidget.h"
#include "utility.h"
#include "gridlayuotutil.h"


void CreaGraficoBarreWidget::creaSchermataInserimentoDati()
{
    row = 0;
    QString title = "Inserisci valori";
    setWindowTitle(title);
    gridLayoutDatiEditabili = new QGridLayout();

    QPushButton *aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton *salva = new QPushButton("Salva");
    QPushButton *cancella = new QPushButton("Cancella");
    signalMapperDatiEditabili = new QSignalMapper();

    connect(salva, SIGNAL(clicked()), this, SLOT(finestraDiConfermaDatiEditabili()));
    connect(aggiungiRiga, SIGNAL(clicked()), this, SLOT(aggiungiRigaDatiEditabili()));
    connect(cancella, SIGNAL(clicked()), this, SLOT(cancellaCreazioneGrafico()));
    connect(signalMapperDatiEditabili,SIGNAL(mapped(QObject*)),SLOT(rimuoviRigaDatiEditabili(QObject*)));

    layoutBottoniDatiEditabiliWidget = new QHBoxLayout();
    layoutBottoniDatiEditabiliWidget->addWidget(aggiungiRiga);
    layoutBottoniDatiEditabiliWidget->addWidget(cancella);
    layoutBottoniDatiEditabiliWidget->addWidget(salva);

    clearWidgets(layoutPrincipale);

    creaLayoutDatiEditabili();

    layoutPrincipale->addLayout(gridLayoutDatiEditabili);

    layoutPrincipale->addLayout(layoutBottoniDatiEditabiliWidget);

    setMinimumSize(200, 200);
}

void CreaGraficoBarreWidget::clearWidgets(QLayout *layout)
{
    if (!layout)
        return;
    while (auto item = layout->takeAt(0))
    {
        delete item->widget();
        clearWidgets(item->layout());
    }
}

void CreaGraficoBarreWidget::creaLayoutDatiEditabili()
{
    gridLayoutDatiEditabili->addWidget(new QLabel("Nome"), row, 0, Qt::AlignTop);
    int col = 1;
    for (auto it = categorie.begin(); it != categorie.end(); ++it, ++col)
    {
        QLabel *label = new QLabel(QString::fromStdString(*it));
        label->setAlignment(Qt::AlignCenter);
        gridLayoutDatiEditabili->addWidget(label, row, col, Qt::AlignTop);
    }
    row++;

    if(grafico){
        for(auto it1 = grafico->getDati().begin(); it1!= grafico->getDati().end(); ++it1){
            QList<QLineEdit *> val;
            QLineEdit *nomeEditabile = new QLineEdit();

            nomeEditabile->setText(QString::fromStdString((*it1)->getNome()));
            gridLayoutDatiEditabili->addWidget(nomeEditabile, row, 0, Qt::AlignTop);

            int colonna = 1;
            list<double> valori = (*it1)->getValori();
            auto iteratorValori = valori.begin();
            for (auto it = categorie.begin(); it != categorie.end(); ++it, ++colonna)
            {
                QLineEdit *categoriaEditabile = new QLineEdit();
                if(iteratorValori!= valori.end()){
                    categoriaEditabile->setText(QString::number(*iteratorValori, 'f', 2));
                    iteratorValori++;
                }
                else
                    categoriaEditabile->setPlaceholderText("inserisci il valore");
                categoriaEditabile->setValidator(new QDoubleValidator);
                gridLayoutDatiEditabili->addWidget(categoriaEditabile, row, colonna, Qt::AlignTop);
                val.push_back(categoriaEditabile);
            }
            QLineEditPair* dato = new QLineEditPair(nomeEditabile, val, row);
            datiEditabili.push_back(dato);
            QPushButton* rimuovi = new QPushButton("Rimuovi");
            gridLayoutDatiEditabili->addWidget(rimuovi, row, colonna + 1, Qt::AlignTop);
            connect(rimuovi,SIGNAL(clicked()),signalMapperDatiEditabili,SLOT(map()));
            signalMapperDatiEditabili->setMapping(rimuovi, dato);
            row++;
        }
    }
}

void CreaGraficoBarreWidget::aggiungiRigaDatiEditabili()
{
    QList<QLineEdit *> val;
    QLineEdit *nomeEditabile = new QLineEdit();

    nomeEditabile->setPlaceholderText("inserisci nome");
    gridLayoutDatiEditabili->addWidget(nomeEditabile, row, 0, Qt::AlignTop);

    int colonna = 1;
    for (auto it = categorie.begin(); it != categorie.end(); ++it, ++colonna)
    {
        QLineEdit *categoriaEditabile = new QLineEdit();
        categoriaEditabile->setPlaceholderText("inserisci il valore");
        categoriaEditabile->setValidator(new QDoubleValidator);
        gridLayoutDatiEditabili->addWidget(categoriaEditabile, row, colonna, Qt::AlignTop);
        val.push_back(categoriaEditabile);
    }
    QLineEditPair* dato = new QLineEditPair(nomeEditabile, val, row);
    datiEditabili.push_back(dato);
    QPushButton* rimuovi = new QPushButton("Rimuovi");
    gridLayoutDatiEditabili->addWidget(rimuovi, row, colonna + 1, Qt::AlignTop);
    connect(rimuovi,SIGNAL(clicked()),signalMapperDatiEditabili,SLOT(map()));
    signalMapperDatiEditabili->setMapping(rimuovi, dato);
    row++;
}

CreaGraficoBarreWidget::CreaGraficoBarreWidget(GraficoBarre *grafico, QWidget *parent)
    : QWidget(parent), grafico(grafico)
{
    QString title = "Inserisci categorie";
    signalMapperCategorie = new QSignalMapper();
    setWindowTitle(title);
    layoutPrincipale = new QVBoxLayout();
    QPushButton *aggiungiRiga = new QPushButton("Aggiungi valori");
    QPushButton *salva = new QPushButton("Salva");
    QPushButton *cancella = new QPushButton("Cancella");
    layoutCategorieWidget = new QVBoxLayout();
    layoutBottoniCategorieWidget = new QHBoxLayout();

    if(grafico)
        aggiungiDatiCategorie();

    connect(salva, SIGNAL(clicked()), this, SLOT(finestraDiConfermaCategorie()));
    connect(aggiungiRiga, SIGNAL(clicked()), this, SLOT(aggiungiRigaNuovaCategoria()));
    connect(cancella, SIGNAL(clicked()), this, SLOT(cancellaCreazioneGrafico()));
    connect(signalMapperCategorie,SIGNAL(mapped(QWidget*)),SLOT(rimuoviRigaCategoria(QWidget*)));


    layoutBottoniCategorieWidget->addWidget(aggiungiRiga);
    layoutBottoniCategorieWidget->addWidget(cancella);
    layoutBottoniCategorieWidget->addWidget(salva);


    layoutPrincipale->addLayout(layoutCategorieWidget);

    layoutPrincipale->addLayout(layoutBottoniCategorieWidget);
    setLayout(layoutPrincipale);

    setMinimumSize(200, 200);
}

void CreaGraficoBarreWidget::rimuoviRigaCategoria(QWidget * w)
{
    QLineEditAndRemoveButton* lineEdit = dynamic_cast<QLineEditAndRemoveButton*>(w);
    if(lineEdit){
        int index = categorieEditabili.indexOf(lineEdit->categoria);
        categorieEditabili.removeOne(lineEdit->categoria);
        layoutCategorieWidget->removeWidget(lineEdit);
        lineEdit->hide();
        if(grafico)
            grafico->removeCategoriaAndValoreAt(index);
    }
}

void CreaGraficoBarreWidget::rimuoviRigaDatiEditabili(QObject * o)
{
    QLineEditPair* l = dynamic_cast<QLineEditPair*>(o);
    if(l){
        int riga = l->riga;
        datiEditabili.removeOne(l);
        GridLayoutUtil::rimuoviRiga(gridLayoutDatiEditabili, riga);
    }
}

CreaGraficoBarreWidget::QLineEditPair::QLineEditPair(QLineEdit *nome, QList<QLineEdit *> valori, int riga) : nome(nome), valori(valori), riga(riga)
{
}

void CreaGraficoBarreWidget::finestraDiConfermaCategorie()
{
    if (!categorieEditabili.empty() && !(*categorieEditabili.begin())->text().isEmpty())
    {
        QMessageBox *dialogo = new QMessageBox(this);
        dialogo->setInformativeText("Confermi le categorie inserite?");
        QPushButton *ok = new QPushButton("Conferma");
        QPushButton *annulla = new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok, QMessageBox::AcceptRole);
        dialogo->addButton(annulla, QMessageBox::RejectRole);

        connect(ok, SIGNAL(clicked()), this, SLOT(confermaCreazioneCategorie()));
        connect(annulla, SIGNAL(clicked()), dialogo, SLOT(close()));
        dialogo->exec();
    }
    else
    {
        messaggioErrore("Valori non ammessi", "Inserire dei valori", this);
    }
}

void CreaGraficoBarreWidget::aggiungiRigaNuovaCategoria()
{
    QLineEdit *nomeCategoria = new QLineEdit();
    nomeCategoria->setPlaceholderText("inserisci il nome della categoria");
    categorieEditabili.push_back(nomeCategoria);
    QPushButton* rimuovi = new QPushButton("Rimuovi");
    connect(rimuovi,SIGNAL(clicked()),signalMapperCategorie,SLOT(map()));
    QLineEditAndRemoveButton * lineEditAndRemove = new QLineEditAndRemoveButton(nomeCategoria, rimuovi, this);
    signalMapperCategorie->setMapping(rimuovi, lineEditAndRemove);
    layoutCategorieWidget->addWidget(lineEditAndRemove);}

void CreaGraficoBarreWidget::aggiungiDatiCategorie()
{
    for(auto it = grafico->getCategorie().begin(); it!= grafico->getCategorie().end(); ++it){
        QLineEdit *nomeCategoria = new QLineEdit();
        nomeCategoria->setText(QString::fromStdString(*it));
        categorieEditabili.push_back(nomeCategoria);
        QPushButton* rimuovi = new QPushButton("Rimuovi");
        connect(rimuovi,SIGNAL(clicked()),signalMapperCategorie,SLOT(map()));
        QLineEditAndRemoveButton * lineEditAndRemove = new QLineEditAndRemoveButton(nomeCategoria, rimuovi, this);
        signalMapperCategorie->setMapping(rimuovi, lineEditAndRemove);
        layoutCategorieWidget->addWidget(lineEditAndRemove);
    }

}

void CreaGraficoBarreWidget::finestraDiConfermaDatiEditabili()
{
    if (!datiEditabili.empty() && !(*datiEditabili.begin())->nome->text().isEmpty())
    {
        QMessageBox *dialogo = new QMessageBox(this);
        dialogo->setInformativeText("Confermi i dati inseriti?");
        QPushButton *ok = new QPushButton("Conferma");
        QPushButton *annulla = new QPushButton("Annulla");
        ok->setObjectName("Ok");
        dialogo->setIcon(QMessageBox::Question);
        dialogo->addButton(ok, QMessageBox::AcceptRole);
        dialogo->addButton(annulla, QMessageBox::RejectRole);

        connect(ok, SIGNAL(clicked()), this, SLOT(confermaCreazioneGraficoBarre()));
        connect(annulla, SIGNAL(clicked()), dialogo, SLOT(close()));
        dialogo->exec();
    }
    else
    {
        messaggioErrore("Valori non ammessi", "Inserire dei valori", this);
    }
}

void CreaGraficoBarreWidget::cancellaCreazioneGrafico()
{
    emit cancella();
}

void CreaGraficoBarreWidget::confermaCreazioneCategorie()
{
    bool chiaviDuplicate = false;
    for (auto it = categorieEditabili.begin(); it != categorieEditabili.end() && !chiaviDuplicate; ++it)
    {
        string categoria = (*it)->text().toStdString();
        for (auto it2 = categorie.begin(); it2 != categorie.end() && !chiaviDuplicate; ++it2)
        {
            if ((*it2) == categoria)
                chiaviDuplicate = true;
        }
        if (!chiaviDuplicate && !categoria.empty())
        {
            categorie.push_back(categoria);
        }
    }
    if (!chiaviDuplicate)
    {
        creaSchermataInserimentoDati();
    }
    else
    {
        messaggioErrore("Valori duplicati", "Ci sono valori duplicati, è necessario cambiare il testo delle categorie", this);
        categorie.clear();
    }
}

void CreaGraficoBarreWidget::confermaCreazioneGraficoBarre()
{
    list<DatiGraficoBarre *> dati;
    for (auto it = datiEditabili.begin(); it != datiEditabili.end(); ++it)
    {
        string nome = ((*it)->nome->text()).toStdString();
        list<double> valoriInseriti;
        QList<QLineEdit *> valoriList = (*it)->valori;
        if (!nome.empty())
        {
            for (auto it2 = valoriList.begin(); it2 != valoriList.end(); ++it2)
            {
                valoriInseriti.push_back((*it2)->text().toDouble());
            }
        }
        dati.push_back(new DatiGraficoBarre(nome, valoriInseriti));
    }
    emit creaGraficoBarre(categorie, dati);
    close();
}

CreaGraficoBarreWidget::QLineEditAndRemoveButton::QLineEditAndRemoveButton(QLineEdit * categoria, QPushButton * rimuovi, QWidget * parent): QWidget(parent), categoria(categoria), rimuovi(rimuovi)
{
    QHBoxLayout* layoutRiga = new QHBoxLayout();
    layoutRiga->addWidget(categoria);
    layoutRiga->addWidget(rimuovi);
    setLayout(layoutRiga);
}
