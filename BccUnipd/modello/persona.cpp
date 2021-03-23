#include "persona.h"

Persona::Persona( const string& Name,const string& Surname,
        const string& CFiscale, const QDate& Data_Nascita):
    CF(CFiscale), Nome(Name), Cognome(Surname),
    DataNascita(Data_Nascita){
    if(Name=="" || Surname=="" || CFiscale=="" || Data_Nascita==QDate()){
        string result="ALL_DATAP";
        throw(result);
    }
    if(CFiscale.length()!=16){
        string result="ERR_CF";
        throw(result);
    }
}

Persona::~Persona() {}

string Persona::GetNome() const{
    return Nome;
}

string Persona::GetCognome() const{
    return Cognome;
}

string Persona::GetCF() const{
    return CF;
}

QDate Persona::GetDataNascita() const{
    return DataNascita;
}

