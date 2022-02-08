
#include "filereader.h"
#include "utility.h"

const string &FileReader::getPath() const
{
    return path;
}

void FileReader::setPath(const string &newPath)
{
    path = newPath;
}

GraficoBase *FileReader::ottieniGraficoDaFile(const string& path) const
{
    GraficoBase* grafico = nullptr;
    QFile* file=new QFile(QString::fromStdString(path));
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        messaggioErrore("dati non presenti","non è presente il file da cui leggere i dati");
    }
    else
    {
        QDomDocument documento;
        if(!documento.setContent(file)){
            return nullptr;
        }
        QDomElement el = documento.documentElement();//salvo la radice del file
        QDomNode nodo = el.firstChild();
        QString tipo, titolo;
        while (!nodo.isNull()) {
            QDomElement elemento = nodo.toElement();
            QString tagName = elemento.tagName();
            if(tagName == "titolo"){
                titolo = elemento.text();
            }
            if(tagName == "tipo"){
                tipo = elemento.text();
                if(tipo == "Torta"){
                    nodo=nodo.nextSibling();
                    elemento = nodo.toElement();
                    tagName = elemento.tagName();
                    map<string, double> fette;
                    if(tagName == "valori"){
                        QDomElement valoriNodi =el.toElement();
                        QDomNodeList listaValoriNodi =valoriNodi.elementsByTagName("dato");
                        for(int i = 0; i<listaValoriNodi.count(); ++i){
                            QDomElement datoNodo= listaValoriNodi.at(i).toElement();
                            QString nome;
                            double valore;
                            QDomNode elementiDelDato = datoNodo.firstChild();
                            while (!elementiDelDato.isNull()){
                                QDomElement elementoDato=elementiDelDato.toElement(); //che è comento
                                QString tagElementoDato = elementoDato.tagName();
                                if(tagElementoDato == "nome"){
                                    nome = elementoDato.text();
                                }
                                if(tagElementoDato == "valore"){
                                    valore = std::stod(elementoDato.text().toStdString());
                                }
                                elementiDelDato = elementiDelDato.nextSibling();
                            }
                            fette[nome.toStdString()]= valore;
                        }
                    }
                    grafico = new GraficoTorta(fette, titolo.toStdString());
                }else{
                    if(tipo == "Linee"){
                        nodo=nodo.nextSibling();
                        elemento = nodo.toElement();
                        tagName = elemento.tagName();
                        list<CoordinataSpezzata*> valori;
                        if(tagName == "dati"){
                            QDomElement valoriNodi =el.toElement();
                            QDomNodeList listaValoriNodi =valoriNodi.elementsByTagName("dato");
                            for(int i = 0; i<listaValoriNodi.count(); ++i){
                                QDomElement datoNodo= listaValoriNodi.at(i).toElement();
                                QString nome;
                                double valore;
                                QDomNode elementiDelDato = datoNodo.firstChild();
                                while (!elementiDelDato.isNull()){
                                    QDomElement elementoDato=elementiDelDato.toElement(); //che è comento
                                    QString tagElementoDato = elementoDato.tagName();
                                    if(tagElementoDato == "nome"){
                                        nome = elementoDato.text();
                                    }
                                    if(tagElementoDato == "valore"){
                                        valore = std::stod(elementoDato.text().toStdString());
                                    }
                                    elementiDelDato = elementiDelDato.nextSibling();
                                }
                                valori.push_back(new CoordinataSpezzata(nome.toStdString(), valore));
                            }
                        }
                        grafico = new GraficoSpezzata(valori);
                    }
                    else{
                        if(tipo == "Barre"){
                            nodo=nodo.nextSibling();
                            elemento = nodo.toElement();
                            tagName = elemento.tagName();
                            list<string> categorie;
                            list<DatiGraficoBarre*> dati;
                            if(tagName == "categorie"){
                                QDomElement categorieNodi =el.toElement();
                                QDomNodeList listaValoriNodi =categorieNodi.elementsByTagName("categoria");
                                for(int i = 0; i<listaValoriNodi.count(); ++i){
                                    categorie.push_back(listaValoriNodi.at(i).toElement().text().toStdString());
                                }
                            }
                            nodo=nodo.nextSibling();
                            elemento = nodo.toElement();
                            tagName = elemento.tagName();
                            if(tagName == "dati"){
                                QDomElement valoriNodi =el.toElement();
                                QDomNodeList listaValoriNodi =valoriNodi.elementsByTagName("dato");
                                for(int i = 0; i<listaValoriNodi.count(); ++i){
                                    QDomElement datoNodo= listaValoriNodi.at(i).toElement();
                                    QString nome;
                                    list<double> valori;
                                    QDomNode elementiDelDato = datoNodo.firstChild();
                                    while (!elementiDelDato.isNull()){
                                        QDomElement elementoDato=elementiDelDato.toElement(); //che è comento
                                        QString tagElementoDato = elementoDato.tagName();
                                        if(tagElementoDato == "nome"){
                                            nome = elementoDato.text();
                                        }
                                        if(tagElementoDato == "valori"){
                                            QDomElement valoreElemento=datoNodo.toElement();
                                            QDomNodeList listaValoriElemento =valoreElemento.elementsByTagName("valore");
                                            for(int x=0; x<listaValoriElemento.count(); ++x)
                                            {
                                                valori.push_back(listaValoriElemento.at(x).toElement().text().toDouble());
                                            }
                                        }
                                        elementiDelDato = elementiDelDato.nextSibling();
                                    }
                                    dati.push_back(new DatiGraficoBarre(nome.toStdString(), valori));
                                }
                            }
                            grafico = new GraficoBarre(categorie,dati);
                        }
                    }
                }
            }else{
                nodo=nodo.nextSibling();
            }
        }
        file->close();
    }
    return grafico;

}



FileReader::FileReader()
{

}

FileReader::FileReader(const string &path) : path(path)
{}
