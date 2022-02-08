#ifndef COORDINATASPEZZATA_H
#define COORDINATASPEZZATA_H

#include "string"
using std::string;

class CoordinataSpezzata
{
private:
    string nome;
    double valore;

public:
    CoordinataSpezzata();
    CoordinataSpezzata(const string &nome, double valore);
    const string &getNome() const;
    void setNome(const string &newNome);
    double getValore() const;
    void setValore(double newValore);
};

#endif // COORDINATASPEZZATA_H
