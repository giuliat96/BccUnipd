#include "cont_corr.h"


Cont_corr::Cont_corr(Ospite *const in1, const uint & num , const QDate & d, const double & annui):
    Servizio(in1,d), NCC(num), int_annui(annui){
    if(num==0){
        string result="ALL_DATACC";
        throw(result);
    }
}

Cont_corr::Cont_corr(Ospite  *const in1, const uint & num,Ospite *const in2, const QDate & d, const double & annui):
    Servizio(in1,in2,d), NCC (num), int_annui(annui){
    if(num==0){
        string result="ALL_DATAOS";
        throw(result);
    }
}

uint Cont_corr::NumeroCC=0;

double Cont_corr::GetInteressi() const{
    return int_annui;
}

uint Cont_corr::GetNCC() const{
    return NCC;
}

double Cont_corr::GetCostoAttivazione() const{

       int durata=GetIntestatario()->Fedelta();
       int durata2=0;
       if(GetCoIntestatario()) durata2=GetCoIntestatario()->Fedelta();

       if (durata<10)
       {   if (durata2>=1)
               return 20-(durata*10);
           else return 20-(durata*10)+20;
        }
       else
       {
          if (durata2>=1) return 20;
          else return 10;
       }
}







