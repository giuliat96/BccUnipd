#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H
#include "servizio.h"
#include "cont_corr.h"


class Investimento : public Servizio
{
private:

    const uint NumeroInvestimento;
    Cont_corr* conto_collegato;
    QDate Fine_inv;
    double int_banca;
    double int_cliente;
    double somma_inv;

public:
    Investimento(const uint,Cont_corr* ,const QDate&, Ospite* , const QDate& =QDate::currentDate(),
                 const double& =0.50, const double& =0.10, const double & =500);
    double Getguadagno() const;
    uint GetNumeroInvestimento()const;
    QDate GetDataFine()const;
    double GetIntbanca() const;
    double GetIntcliente() const;
    double GetSommaInvestita() const;
    Cont_corr* GetContoCollegato() const;
    double GetCostoAttivazione() const;

    static uint NumeroInvestimenti;
};

#endif // INVESTIMENTO_H
