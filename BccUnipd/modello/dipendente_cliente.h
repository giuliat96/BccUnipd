#ifndef DIPENDENTE_CLIENTE_H
#define DIPENDENTE_CLIENTE_H
#include "operatore.h"
#include "ospite.h"

class dipendente_cliente : public Operatore, public Ospite
{
    static unsigned int BonusStipendio;
public:
    dipendente_cliente(const string&,const string&,
                       const string&,const string&, const string&,
                       const string&,const string&, const QDate&,
                       const string& ="Sportello",
                       const string& ="", const string& ="",
                       const QDate& =QDate::currentDate(), const string& ="Indeterminato",
                       const QDate& =QDate(),const unsigned int =0,
                       const QDate& =QDate(),
                       const unsigned int =0, const bool& =0);

    double GetStipendio() const;
    unsigned int BonusAnnuo() const;
    dipendente_cliente* Senior();
    unsigned int Fedelta() const;
};

#endif // DIPENDENTE_CLIENTE_H
