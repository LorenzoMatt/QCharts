#ifndef FILEREADER_H
#define FILEREADER_H

#include "graficotorta.h"
#include "coordinataspezzata.h"
#include "graficospezzata.h"

#include "string"
#include <map>
#include <QDomDocument>
#include <QFile>
#include <list>


using std::string;
using std::map;
using std::list;


class FileReader
{
private:
    string path;
public:
    FileReader();
    FileReader(const string &path);
    const string &getPath() const;
    void setPath(const string &newPath);

    GraficoBase* ottieniGraficoDaFile(const std::string &path) const;
};

#endif // FILEREADER_H
