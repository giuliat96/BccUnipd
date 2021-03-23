#include "servizio.h"

Servizio::Servizio(Ospite*const int1,const QDate& Data):Intestatario(int1),Intestatario2(nullptr),DataAttivazione(Data){
    if(!int1){
        string result="ERR_INT";
        throw(result);
    }
    if(Data>QDate::currentDate()){
        string result="ERR_DATA";
        throw(result);
    }
}

Servizio::Servizio(Ospite*const int1,Ospite*const int2, const QDate& Data):Intestatario(int1),Intestatario2(int2),DataAttivazione(Data){
    if(!int1){
        string result="ERR_INT";
        throw(result);
    }
    if(int1==int2){
        string result="ERR_COINT";
        throw(result);
    }
    if(Data>QDate::currentDate()){
        string result="ERR_DATA";
        throw(result);
    }
}

Servizio::~Servizio() {}

QDate Servizio::GetAttivazione() const{
    return DataAttivazione;
}

Ospite* Servizio::GetIntestatario() const{
    return Intestatario;
}

Ospite* Servizio::GetCoIntestatario() const{
    return Intestatario2;
}
