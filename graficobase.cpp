#include "graficobase.h"
#include "graficononsalvato.h"


const string &GraficoBase::getTitolo() const
{
    return titolo;
}

void GraficoBase::setTitolo(const string &newTitolo)
{
    titolo = newTitolo;
}

GraficoBase::GraficoBase()
{
}

GraficoBase::~GraficoBase()
{
}

void GraficoBase::salva(string path) const
{
    QFile *file = new QFile(QString::fromStdString(path)); // costruttore con il nome del file
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw GraficoNonSalvato();
    }
    else
    {
        QXmlStreamWriter *inp = new QXmlStreamWriter; // per scrivere dentro a file
        inp->setAutoFormatting(true);
        inp->setDevice(file);
        inp->writeStartDocument();         // inizio a scrivere nel file
        inp->writeStartElement("grafico"); // inizio dei campi dati del grafico
        inp->writeTextElement("titolo", QString::fromStdString(getTitolo()));
        inp->writeTextElement("tipo", QString::fromStdString(getNomeClasse()));
        salvaDati(inp); // chiamata virtuale per il salvataggio dei dati
        inp->writeEndElement(); // fine dati del grafico
        inp->writeEndDocument(); // chiusura
        file->close();
    }
}

GraficoBase::GraficoBase(const string &titolo) : titolo(titolo)
{
}
