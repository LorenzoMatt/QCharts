#ifndef FILEREADER_H
#define FILEREADER_H

#include "graficotorta.h"
#include "coordinataspezzata.h"
#include "graficospezzata.h"
#include "datigraficobarre.h"
#include "graficobarre.h"

#include "string"
#include <map>
#include <QDomDocument>
#include <QFile>
#include <list>

using std::list;
using std::map;
using std::string;

class FileReader
{
private:
    string path;
    GraficoTorta *estraiDatiTorta(QDomNode nodo, QString titolo, const QDomElement &el) const;

    GraficoSpezzata *estraiGraficoSpezzate(QDomNode nodo, QString titolo, const QDomElement &el) const;

    GraficoBarre *estraiGraficoBarre(QDomNode nodo, QString titolo, const QDomElement &el) const;

public:
    FileReader();
    FileReader(const string &path);
    const string &getPath() const;
    void setPath(const string &newPath);
    GraficoBase *ottieniGraficoDaFile(const std::string &path) const;
};

#endif // FILEREADER_H
