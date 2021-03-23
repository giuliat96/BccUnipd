#ifndef DIPENDENTE_H
#define DIPENDENTE_H
#include "operatore.h"

class Dipendente : public Operatore
{
public:
    Dipendente(const string&,const string&, const string&,
           const string&, const string&,
           const QDate&,const string& ="Sportello",
           const string& ="", const string& ="",
           const QDate& =QDate::currentDate(),
           const string& ="",
           const QDate& =QDate::currentDate(),const unsigned int =0);

   double GetStipendio() const;
   Dipendente* Senior();
    unsigned int Fedelta() const;
};

#endif // DIPENDENTE_H
