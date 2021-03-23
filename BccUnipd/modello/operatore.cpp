#include "operatore.h"

Operatore::Operatore(const string& Usrname,const string& Pword, const string& Name,
       const string& Surname,const string& CFiscale, const QDate& Data_Nascita,
       const string& Ruolo,const string& email,const string& Telefono,
       const QDate& InizioContratto, const string& TipoContratto,
       const QDate& FineContratto,unsigned int FamiliariACarico):
       Persona(Name,Surname,CFiscale,Data_Nascita),
       EmailOperatore(email),CellulareOperatore(Telefono),
       Username(Usrname), Password(Pword), Inquadratura(Ruolo),
       DataInizioContratto(InizioContratto),
       Contratto(TipoContratto), DataFineContratto(FineContratto),
       PersoneACarico(FamiliariACarico){
    if(Usrname=="" || Pword==""){
        string result="ALL_DATAUT";
        throw(result);
    }
    if (Ruolo==""){
        string result="RUOLO";
        throw(result);
    }
    if(Pword.length()<6) {
        string result="PW_LENGHT";
        throw(result);
    }
    if(Ruolo!="Sportello" && Ruolo!="Ufficio Personale"){
        string result="ERR_RUOLO";
        throw(result);
    }
    if(Telefono.length()!=9 && Telefono.length()!=10 && Telefono.length()!=0){
                string result="ERR_TELL";
                throw(result);
            }
    if(email!="" && email.find('@')==string::npos) {
        string result="ERR_EMAIL";
        throw(result);
    }
    if(FineContratto<InizioContratto){
        string result="ERR_CONTR";
        throw(result);
    }
    if(InizioContratto>QDate::currentDate()){
        string result="ERR_DATA";
        throw(result);
    }
}


string Operatore::GetEmail() const{
    return EmailOperatore;
}

string Operatore::GetCellulare() const{
    return CellulareOperatore;
}

string Operatore::GetUsername() const {
    return Username;
}

string Operatore::GetPassword() const {
    return Password;
}

string Operatore::GetInquadratura() const{
    return Inquadratura;
}

QDate Operatore::GetInizioContratto() const{
    return DataInizioContratto;
}

string Operatore::GetTipoContratto() const{
    return Contratto;
}

QDate Operatore::GetFineContratto() const{
    return DataFineContratto;
}

unsigned int Operatore::GetPersoneACarico() const{
    return PersoneACarico;
}

bool Operatore::GestioneDipendenti() const{
    if(Inquadratura=="Ufficio Personale") return true;
    else return false;
}

void Operatore::ModificaAccount(const string& username,const string& password,const string& email,const string& telefono){
    if(telefono.length()!=9 && telefono.length()!=10 && telefono.length()!=0){
                string result="ERR_TELL";
                throw(result);
            }
    if(email!="" && email.find('@')==string::npos) {
        string result="ERR_EMAIL";
        throw(result);
    }
    if(Username!=username) Username=username;
    if(Password!=password) Password=password;
    if(this->GetEmail()!=email) EmailOperatore=email;
    if(this->GetCellulare()!=telefono) CellulareOperatore=telefono;

}

void Operatore::modificaOperatore(const string& email, const string& Telefono,const string& Ruolo,
                                 const string& TipoContratto,const QDate&InizioContratto,
                                 const QDate&FineContratto,const unsigned int FamiliariACarico){

    if(email!="" && email.find('@')==string::npos) {
        string result="ERR_EMAIL";
        throw(result);
    }
    if(Telefono.length()!=9 && Telefono.length()!=10 && Telefono.length()!=0){
        string result="ERR_TELL";
        throw(result);
    }
    if(Ruolo!="Sportello" && Ruolo!="Ufficio Personale"){
        string result="ERR_RUOLO";
        throw(result);
    }
    if(FineContratto<InizioContratto){
        string result="ERR_CONTR";
        throw(result);
    }
    if(GetEmail()!=email)EmailOperatore=email;
    if(GetCellulare()!=Telefono)CellulareOperatore=Telefono;
    if(GetInquadratura()!=Ruolo) Inquadratura=Ruolo;
    if(GetInizioContratto()!=InizioContratto)DataInizioContratto=InizioContratto;
    if(GetTipoContratto()!=TipoContratto) Contratto=TipoContratto;
    if(GetFineContratto()!=FineContratto)DataFineContratto=FineContratto;
    if(GetPersoneACarico()!=FamiliariACarico)PersoneACarico=FamiliariACarico;
}



