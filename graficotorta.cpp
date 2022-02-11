#include "graficotorta.h"

#include <QFile>
#include <QXmlStreamWriter>
#include "utility.h"
#include "graficononsalvato.h"

const map<string, double> &GraficoTorta::getFette() const
{
    return fette;
}

void GraficoTorta::setFette(const map<std::string, double> &newFette)
{
    fette = newFette;
}

void GraficoTorta::salva(string path) const
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
        inp->writeStartElement("valori"); // inizio dei valori
        for (auto it = fette.begin(); it != fette.end(); ++it)
        {
            inp->writeStartElement("dato"); // inizio singolo dato
            inp->writeTextElement("nome", QString::fromStdString(it->first));
            inp->writeTextElement("valore", QString::fromStdString(std::to_string(it->second)));
            inp->writeEndElement(); // fine di un dato
        }
        inp->writeEndElement(); // fine della lista dei valori
        inp->writeEndElement(); // fine dati del grafico

        inp->writeEndDocument();
        file->close();
    }
}

string GraficoTorta::getNomeClasse() const
{
    return "Torta";
}

GraficoTorta::GraficoTorta()
{
}

GraficoTorta::GraficoTorta(const map<string, double> &fette, string titolo) : GraficoBase(titolo), fette(fette)
{
}
