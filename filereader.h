#ifndef FILEREADER_H
#define FILEREADER_H

#include "graficobase.h"
#include "string"

#include <QDomDocument>

using std::string;

class FileReader
{
private:
    string path;
public:
    FileReader();
    FileReader(const string &path);
    const string &getPath() const;
    void setPath(const string &newPath);

    GraficoBase* getGraficoFromFile(const std::string &path) const;
};

#endif // FILEREADER_H
