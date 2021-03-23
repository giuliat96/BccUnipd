#ifndef CLIENTE_H
#define CLIENTE_H
#include "ospite.h"

class Cliente : public Ospite
{
public:
    Cliente(const string&, const string&,
            const string&,const QDate&,
            const string& ="", const string& ="",
            const QDate& =QDate::currentDate(),
            const unsigned int =0, const bool& =0);

    unsigned int BonusAnnuo() const;
    Cliente* Senior();
    unsigned int Fedelta() const;
};

#endif // CLIENTE_H
