#include "investimento.h"

Investimento::Investimento(const uint numero,Cont_corr * num, const QDate & fine, Ospite *int1, const QDate & d,
                           const double & intb, const double &intc, const double & somma):
    Servizio(int1,d),NumeroInvestimento(numero),conto_collegato(num),Fine_inv(fine),int_banca(intb),int_cliente(intc),somma_inv(somma){
    if(numero==0 || !num){
        string result="ALL_DATAIN";
        throw(result);
    }
    if(fine<d){
        string result="ERR_DATE";
        throw(result);
    }
}

uint Investimento::NumeroInvestimenti=0;

uint Investimento::GetNumeroInvestimento()const {
    return NumeroInvestimento;
}

QDate Investimento::GetDataFine()const{
    return Fine_inv;
}

double Investimento::GetSommaInvestita() const{
    return somma_inv;
}

double Investimento::GetIntbanca() const{
    return int_banca;
}

double Investimento::GetIntcliente() const{
    return int_cliente;
}

Cont_corr* Investimento::GetContoCollegato() const{
    return conto_collegato;
}

double Investimento::Getguadagno() const{
    int durata= GetAttivazione().daysTo(Fine_inv);
    if (durata==0|| somma_inv==0|| int_banca==0){
        return 0;
    }
    else{
        return (somma_inv*int_banca)*durata;
    }
}

double Investimento::GetCostoAttivazione() const{
    int durata=GetIntestatario()->Fedelta();
        int duratain= ((GetAttivazione()).daysTo(GetDataFine()))/365;
        int duratacc= ((GetContoCollegato()->GetAttivazione()).daysTo(QDate::currentDate()))/365;

        if (duratacc<1) //se ho appena aperto un cc e voglio fare un investimento subito
        {
            if (GetSommaInvestita()>=10000)
                return 300*GetIntbanca()-(durata*10)-(duratain*10);
            else return 500*GetIntbanca()-(durata*5)-(duratain*5);
        }
        else
        {
            if (GetSommaInvestita()>=15000)
                return 400*GetIntbanca()-(durata*5)-(duratain*10);
            else return 700*GetIntbanca()-(durata*5)-(duratain*5);

        }
}


