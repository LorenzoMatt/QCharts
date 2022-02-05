#include "fettatorta.h"

const string &FettaTorta::getVoce() const
{
    return voce;
}

double FettaTorta::getValore() const
{
    return valore;
}

FettaTorta::FettaTorta()
{

}

FettaTorta::FettaTorta(const string &voce, double valore) : voce(voce),
    valore(valore)
{}
