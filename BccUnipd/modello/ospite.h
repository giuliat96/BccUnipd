#ifndef OSPITE_H
#define OSPITE_H

#include "persona.h"

class Ospite: virtual public Persona
{
private:
    string EmailCliente;
    string CellulareCliente;
    QDate DataInizioRapporto;
    unsigned int NumeroIdentificativo;
    bool AppOnline;


public:
    Ospite(const string&, const string&,
           const string&,const QDate&,
           const string& ="", const string& ="",
           const QDate& =QDate::currentDate(),
           const unsigned int =0, const bool& =false);

    virtual unsigned int BonusAnnuo() const = 0;
    string GetEmail() const;
    string GetCellulare() const;
    QDate GetDataInizioRapporto() const;
    unsigned int GetNumeroIdentificativo () const;
    bool GetAppOnline() const;
    void modificaOspite(const string&,const string&,const bool&);
    uint GetNumeroClienti() const;

    static unsigned int NumeroClienti;
};

#endif // OSPITE_H
