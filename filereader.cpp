#include "filereader.h"
#include "utility.h"
#include <QFile>


const string &FileReader::getPath() const
{
    return path;
}

void FileReader::setPath(const string &newPath)
{
    path = newPath;
}

GraficoBase *FileReader::getGraficoFromFile(const string& path) const
{
//    QFile* file=new QFile(QString::fromStdString(path));
//        if (!file->open(QFile::ReadOnly | QFile::Text))
//        {
//            messaggioErrore("dati non presenti","non è presente il file da cui leggere i dati");
//        }
//        else
//        {
//            QDomDocument documento;
//            if(!documento.setContent(file)){
//                return nullptr;
//            }
//            QDomElement root = documento.documentElement();//salvo la radice del file
//            QDomNodeList nodes = root.elementsByTagName("grafico");
//            if(nodes.size() == 1)
//            {
//                QDomElement el = nodes.at(0).toElement();
//                QDomNode nodo = el.firstChild();
//                QString tipo;


//                QString user, psw, nome, cognome,email, punti, risposte;
//                container<string> competenze, titoli;
//                while (!nodo.isNull()) {
//                    QDomElement elemento = nodo.toElement();
//                    QString tagName = elemento.tagName();
//                    if(tagName=="tipoutente")
//                    {
//                        tipo=elemento.text();
//                    }
//                    if(tagName=="username")
//                    {
//                        user=elemento.text();
//                    }
//                    if(tagName=="password")
//                    {
//                        psw=elemento.text();
//                    }
//                    if(tagName=="nome")
//                    {
//                        nome=elemento.text();
//                    }
//                    if(tagName=="cognome")
//                    {
//                        cognome=elemento.text();
//                    }
//                    if(tagName=="email")
//                    {
//                        email=elemento.text();
//                    }
//                    if(tagName=="competenze")
//                    {

//                        QDomElement comp=elemento.toElement();
//                        QDomNodeList lista_competenze =comp.elementsByTagName("competenza");
//                        for(int x=0; x<lista_competenze.count(); ++x)
//                        {
//                            competenze.push_back(lista_competenze.at(x).toElement().text().toStdString());
//                        }
//                    }
//                    if(tagName=="titoli_di_studio")
//                    {

//                        QDomElement tit=elemento.toElement();
//                        QDomNodeList lista_titoli=tit.elementsByTagName("titolo");
//                        for(int x=0; x<lista_titoli.count(); ++x)
//                        {
//                            titoli.push_back(lista_titoli.at(x).toElement().text().toStdString());
//                        }
//                    }
//                    if(tagName=="punti")
//                    {
//                        punti=elemento.text();
//                    }
//                    if(tagName=="risposte_date")
//                    {
//                        risposte=elemento.text();
//                    }
//                    nodo=nodo.nextSibling();
//                }
//                Utente* utente;
//                unsigned short int punt=std::stoi(punti.toStdString());
//                unsigned short int risp=std::stoi(risposte.toStdString());
//                if(tipo=="Basic")
//                    utente=new Basic(user.toStdString(),psw.toStdString(),nome.toStdString(),
//                                     cognome.toStdString(),email.toStdString(),punt,risp);

//                if(tipo=="Gold")
//                    utente=new Gold(user.toStdString(),psw.toStdString(),nome.toStdString(),
//                                     cognome.toStdString(),email.toStdString(),punt,risp);
//                if(tipo=="Premium")
//                    utente=new Premium(user.toStdString(),psw.toStdString(),nome.toStdString(),
//                                     cognome.toStdString(),email.toStdString(),punt,risp);
//                utente->carica_competenze(competenze);
//                utente->carica_titoli(titoli);
//                aggiungi_utente(utente);
//            }
//            file->close();
//        }
    return nullptr;
}

FileReader::FileReader()
{

}

FileReader::FileReader(const string &path) : path(path)
{}
