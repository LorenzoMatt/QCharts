#include "torta.h"

const map<string, FettaTorta *> &Torta::getFette() const
{
    return fette;
}

void Torta::setFette(const map<string, FettaTorta *> &newFette)
{
    fette = newFette;
}

void Torta::salva() const
{
    //TODO
}

string Torta::getNomeClasse() const
{
    return "Torta";
}

Torta::Torta()
{

}

Torta::~Torta()
{
    for(std::map<string,FettaTorta*>::iterator it = fette.begin(); it!= fette.end(); ++it){
        FettaTorta* f = it->second;
        if(f)
            delete f;
    }

}

Torta::Torta(const map<string, FettaTorta *> &fette) : fette(fette)
{}
