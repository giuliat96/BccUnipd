#ifndef SERVIZIO_H
#define SERVIZIO_H

#include "cliente.h"

class Servizio{

    friend class Soggetti;

private:
    Ospite* Intestatario;
    Ospite* Intestatario2;
    QDate DataAttivazione;

public:
    Servizio(Ospite* const,const QDate& =QDate::currentDate());
    Servizio(Ospite*const,Ospite*const int2= nullptr, const QDate& =QDate::currentDate());
    virtual ~Servizio() =0;
    virtual double GetCostoAttivazione() const=0;
    QDate GetAttivazione() const;
    Ospite* GetIntestatario() const;
    Ospite* GetCoIntestatario() const;
};

#endif // SERVIZIO_H
