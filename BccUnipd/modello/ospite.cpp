#include "ospite.h"

Ospite::Ospite(const string& Name, const string& Surname,
               const string& CFiscale, const QDate& Data_Nascita,
               const string& email,const string& Telefono,
               const QDate& InizioRapporto,
               const unsigned int Number,const bool& App):
    Persona(Name,Surname,CFiscale,Data_Nascita), EmailCliente(email), CellulareCliente(Telefono),
    DataInizioRapporto(InizioRapporto),NumeroIdentificativo(Number), AppOnline(App){
    if(Number==0){
        string result="ALL_DATAOS";
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
    if(InizioRapporto>QDate::currentDate()){
        string result="ERR_DATA";
        throw(result);
    }
}

unsigned int Ospite::NumeroClienti=0;

QDate Ospite::GetDataInizioRapporto()const {
    return DataInizioRapporto;
}

string Ospite::GetEmail() const{
    return EmailCliente;
}

string Ospite::GetCellulare() const{
    return CellulareCliente;
}

unsigned int Ospite::GetNumeroIdentificativo() const{
    return NumeroIdentificativo;
}

bool Ospite::GetAppOnline() const{
    return AppOnline;
}

void Ospite::modificaOspite(const string& email, const string& Telefono,const bool& appOnline){
    if(email!="" && email.find('@')==string::npos) {
        string result="ERR_EMAIL";
        throw(result);
    }
    if(Telefono.length()!=9 && Telefono.length()!=10 && Telefono.length()!=0) {
        string result="ERR_TELL";
        throw(result);
    }
    if(GetEmail()!=email)EmailCliente=email;
    if(GetCellulare()!=Telefono)CellulareCliente=Telefono;
    if(GetAppOnline()!=appOnline) AppOnline=appOnline;
}
