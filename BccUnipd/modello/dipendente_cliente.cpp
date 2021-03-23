#include "dipendente_cliente.h"

dipendente_cliente::dipendente_cliente(const string& Emaillavoro,const string& Telefonolavoro,
                                       const string& Usrname,const string& Pword, const string& Name,
                                       const string& Surname,const string& CFiscale, const QDate& Data_Nascita,
                                       const string& Ruolo,
                                       const string& EmailCliente,const string& TelefonoCliente,
                                       const QDate& InizioContratto, const string& TipoContratto,
                                       const QDate& FineContratto,const unsigned int FamiliariACarico,
                                       const QDate& InizioRapporto,
                                       const unsigned int Number,const bool& App):
    Persona(Name,Surname,CFiscale,Data_Nascita),
    Operatore(Usrname,Pword,Name,Surname,CFiscale,Data_Nascita,Ruolo,Emaillavoro,Telefonolavoro,InizioContratto
              ,TipoContratto,FineContratto,FamiliariACarico),
    Ospite(Name,Surname,CFiscale,Data_Nascita,EmailCliente,TelefonoCliente,InizioRapporto,Number,App){}

unsigned int dipendente_cliente::BonusStipendio= 100;

double dipendente_cliente::GetStipendio() const{
    int Stipendio=1000+(130*GetPersoneACarico())+BonusStipendio+(55*Fedelta());
            return Stipendio;
}

unsigned int dipendente_cliente::BonusAnnuo() const{
    int Bonus=5;
       int durata=GetDataInizioRapporto().daysTo(QDate::currentDate());
       if(durata>365)
       {
           if(GetAppOnline()){
               Bonus= Bonus+(6*(durata/365))+2;

           }
           else {
               Bonus= Bonus+(6*(durata/365));
           }
       }

       return Bonus;
}

dipendente_cliente* dipendente_cliente::Senior(){
    if(QDate::currentDate().year()-GetInizioContratto().year()>=5 && QDate::currentDate().year()-GetDataInizioRapporto().year()>=5) return this;
    else return nullptr;
}

unsigned int dipendente_cliente::Fedelta() const{
    int durata=GetInizioContratto().daysTo(QDate::currentDate());
    if (durata>=365)
    {
        if(GetInquadratura()=="Sportello") return (durata/365)+2;
        else return (durata/365)+1;
    }
    else return 0;
}
