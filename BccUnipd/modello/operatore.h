#ifndef OPERATORE_H
#define OPERATORE_H

#include "persona.h"

using std::string;

class Operatore: virtual public Persona
    {
    private:
        string EmailOperatore;
        string CellulareOperatore;
        string Username;
        string Password;
        string Inquadratura;
        QDate DataInizioContratto;
        string Contratto;
        QDate DataFineContratto;
        unsigned int PersoneACarico;

    public:
        Operatore(const string& ,const string& , const string& ,
               const string&,const string&, const QDate&,
               const string& ="Sportello",
               const string& ="", const string& ="",
                const QDate& =QDate::currentDate(), const string& ="Indeterminato",
               const QDate& =QDate(),const unsigned int =0);

       virtual double GetStipendio() const = 0;
       string GetEmail() const;
       string GetCellulare() const;
       string GetUsername() const;
       string GetPassword() const;
       string GetInquadratura() const;
       QDate GetInizioContratto() const;
       string GetTipoContratto() const;
       QDate GetFineContratto() const;
       unsigned int GetPersoneACarico() const;
       bool GestioneDipendenti() const;
       void ModificaAccount(const string&,const string&,const string&,const string&);
       void modificaOperatore(const string&,const string&,const string&,const string&,const QDate&,
                       const QDate&,const unsigned int);

    };


#endif // OPERATORE_H
