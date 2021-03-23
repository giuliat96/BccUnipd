#include "cliente.h"

Cliente::Cliente(const string& Name, const string& Surname,
                   const string& CFiscale, const QDate& Data_Nascita,
                   const string& email,const string& Telefono,
                   const QDate& InizioRapporto,
                   const unsigned int Number,const bool& App):
        Persona(Name,Surname,CFiscale,Data_Nascita),
        Ospite(Name,Surname,CFiscale,Data_Nascita,email,Telefono,InizioRapporto,Number,App){}

unsigned int Cliente::BonusAnnuo() const{
    int Bonus=((QDate::currentDate().year()-GetDataInizioRapporto().year())/5)*2;
    return Bonus;
}

Cliente* Cliente::Senior(){
    if(Fedelta()>=20) return this;
    else return nullptr;
}

unsigned int Cliente::Fedelta() const{
     int durata=GetDataInizioRapporto().daysTo(QDate::currentDate());
     if(durata>=365) return durata/365;
     else return 0;
}
