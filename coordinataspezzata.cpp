#include "coordinataspezzata.h"

const string &CoordinataSpezzata::getNome() const
{
    return nome;
}

void CoordinataSpezzata::setNome(const string &newNome)
{
    nome = newNome;
}

double CoordinataSpezzata::getValore() const
{
    return valore;
}

void CoordinataSpezzata::setValore(double newValore)
{
    valore = newValore;
}

CoordinataSpezzata::CoordinataSpezzata()
{
}

CoordinataSpezzata::CoordinataSpezzata(const string &nome, double valore) : nome(nome),
                                                                            valore(valore)
{
}
