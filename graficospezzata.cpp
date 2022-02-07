#include "graficospezzata.h"

#include "utility.h"

void GraficoSpezzata::salva(string path) const
{
    QFile *file = new QFile(QString::fromStdString(path)); // costruttore con il nome del file
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        messaggioErrore("file non aperto", "file non aperto correttamente");
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
        inp->writeStartElement("valori"); // inizio dei valori
        for (auto it = valori.begin(); it != valori.end(); ++it)
        {
            inp->writeStartElement("dato"); // inizio singolo dato
            inp->writeTextElement("nome", QString::fromStdString((*it)->getNome()));
            inp->writeTextElement("valore", QString::fromStdString(std::to_string((*it)->getValore())));
            inp->writeEndElement(); // fine di un dato
        }
        inp->writeEndElement(); // fine della lista dei valori
        inp->writeEndElement(); // fine dati del grafico

        inp->writeEndDocument();
        file->close();
    }
}

string GraficoSpezzata::getNomeClasse() const
{
    return "Linee";
}

const list<CoordinataSpezzata *> &GraficoSpezzata::getValori() const
{
    return valori;
}

void GraficoSpezzata::setValori(const list<CoordinataSpezzata *> &newValori)
{
    valori = newValori;
}

GraficoSpezzata::GraficoSpezzata()
{
}

GraficoSpezzata::~GraficoSpezzata()
{
    for (auto it = valori.begin(); it != valori.end(); ++it)
    {
        if (*it)
            delete *it;
    }
}

GraficoSpezzata::GraficoSpezzata(const list<CoordinataSpezzata *> &valori, string titolo) : GraficoBase(titolo), valori(valori)
{
}
