#ifndef SOGGETTI_H
#define SOGGETTI_H

#include "operatore.h"
#include "ospite.h"
#include "persona.h"
#include "dipendente_cliente.h"
#include "cliente.h"
#include "dipendente.h"
#include "prodotti.h"

class Soggetti{

   friend class Iteratore;
   friend class constIteratore;

private:
    class nodo{
        friend class Soggetti;
    private:
        Persona* info;
        nodo *prev, *next;
        nodo(Persona*,nodo* p=nullptr, nodo* n=nullptr);
        nodo(const nodo&);
        ~nodo();
    };
    nodo* last, *first;

    static nodo* clone(nodo*, nodo*&);
    static bool isLess(nodo* n1,nodo* n2);
    void ChangeType(Persona*,Prodotti*);
    void personaServizi(Persona*,Persona*,Prodotti*);

public:

    Soggetti();
    Soggetti(Persona*);
    Soggetti(const Soggetti&);
    ~Soggetti();
    Soggetti& operator=(const Soggetti&);
    void addOrdineL(Persona* p);
    bool operator <(const Soggetti& );
    Soggetti* Senior(Operatore*)const;
    Operatore* GetOperatore(const string&)const;
    Ospite* GetOspite(const uint&) const;
    Soggetti* GetOperatori()const;
    Soggetti* GetOspiti()const;
    string CheckOnePerson(Persona*,Operatore*)const;
    bool CheckModifiche(Persona*)const;
    const Operatore *CheckLogin(const string&, const string&)const;
    bool AggiungiPersona(Persona*,Operatore*,Prodotti*);
    bool RimuoviPersona(Persona*,Operatore*,Prodotti*);
    void removePerson(Persona*);
    bool CheckNoServizi(Persona*,Prodotti*);
    Persona* CercaCF(Operatore*,const string&);
    Soggetti* CercaNS(Operatore*,const string&,const string&);
    Soggetti* GetOpSportello() const;
    Soggetti* GetOpPersonale() const;
    bool isempty();

    class Iteratore{
        friend class Soggetti;
    private:
        Soggetti::nodo* punt;
        bool passTheEnd;
        Iteratore(nodo*,bool);
    public:
        Iteratore();
        bool operator==(const Iteratore&) const;
        bool operator !=(const Iteratore&) const;
        Persona* operator* () const;
        Persona **operator-> () const;
        Iteratore& operator =(const Iteratore&);
        Iteratore& operator++();
        Iteratore operator++(int);
        Iteratore operator--();
    };

    class constIteratore{
        friend class Soggetti;
    private:
        const Soggetti::nodo* punt;
        bool passTheEnd;
        constIteratore(nodo*,bool);
    public:
        constIteratore();
        bool operator==(const constIteratore&) const;
        bool operator !=(const constIteratore&) const;
        const Persona* operator* () const;
        const Persona *const*operator-> () const;
        constIteratore& operator=(const constIteratore&) noexcept;
        constIteratore& operator++();
        constIteratore operator++(int);
    };

    Iteratore it_begin()const;
    Iteratore it_end()const;
    constIteratore cit_begin()const;
    constIteratore cit_end() const;
};


#endif // SOGGETTI_H
