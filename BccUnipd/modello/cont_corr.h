#ifndef CONT_CORR_H
#define CONT_CORR_H
#include "servizio.h"

class Cont_corr : public Servizio
{
private:
    const unsigned int NCC;
    double int_annui;

public:
    Cont_corr(Ospite *const , const uint&, const QDate & =QDate::currentDate(),const double & =0.05);
    Cont_corr(Ospite *,const uint&,Ospite*const =nullptr, const QDate & =QDate::currentDate(),const double& =0.05);

    double GetInteressi () const;
    uint GetNCC() const;
    double GetCostoAttivazione() const;
    static uint NumeroCC;
};

#endif // CONT_CORR_H
