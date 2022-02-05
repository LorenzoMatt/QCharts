#ifndef FETTATORTA_H
#define FETTATORTA_H

#include<string>


using std::string;

class FettaTorta
{
private:
    string voce;
    double valore;
public:
    FettaTorta();
    FettaTorta(const string &voce, double valore);
    const string &getVoce() const;
    double getValore() const;
};

#endif // FETTATORTA_H
