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
        QDomElement root = documento.documentElement();//salvo la radice del file
        QDomNodeList nodes = root.elementsByTagName("grafico");
        if(nodes.size() == 1)
        {
            QDomElement el = nodes.at(0).toElement();
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
                        el = nodo.toElement();
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

                    }
                }else{
                    nodo=nodo.nextSibling();
                }
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
