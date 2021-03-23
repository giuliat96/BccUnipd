#include "dipendente.h"

Dipendente::Dipendente(const string& Usrname,const string& Pword, const string& Name,
       const string& Surname,const string& CFiscale, const QDate& Data_Nascita,
       const string& Ruolo,const string& email,const string& Telefono,
       const QDate& InizioContratto,
        const string& TipoContratto,
       const QDate& FineContratto,const unsigned int FamiliariACarico):
       Persona(Name,Surname,CFiscale,Data_Nascita),
       Operatore(Usrname,Pword,Name,Surname,CFiscale,Data_Nascita,Ruolo,email,Telefono,InizioContratto,
                 TipoContratto,FineContratto,FamiliariACarico){}

double Dipendente::GetStipendio() const {
    int Stipendio=1000+(130*GetPersoneACarico());
            return Stipendio;
}

Dipendente* Dipendente::Senior(){
    if(Fedelta()>=10) return this;
    else return nullptr;
}

unsigned int Dipendente::Fedelta() const{
    int durata=GetInizioContratto().daysTo(QDate::currentDate());
    if (durata>=730)
    {
        if(GetInquadratura()=="Sportello") return (durata/365)+2;
        else return (durata/365)+1;
    }
    else return 1;
}
