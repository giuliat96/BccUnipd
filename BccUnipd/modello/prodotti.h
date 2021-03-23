#ifndef PRODOTTI_H
#define PRODOTTI_H

#include "servizio.h"
#include "cont_corr.h"
#include "investimento.h"

class Prodotti{
    friend class Iteratore;
    friend class constIteratore;

    
private:
    class nodo{
        friend class Prodotti;
    private:
        Servizio* info;
        nodo* prev; nodo* next;
        nodo (Servizio*, nodo* p=nullptr, nodo*n = nullptr);
        nodo (const nodo&);
       ~nodo();
    };
    
    nodo* last; nodo *first;
    
    static nodo* clone(nodo*, nodo*&);
 
public:
    
    Prodotti();
    Prodotti (Servizio*);
    Prodotti (const Prodotti&);
    ~Prodotti();
    
    Prodotti& operator= (const Prodotti&);
    void addServizio (Servizio*);
    
    Prodotti* GetCont (const Ospite*) const;
    Prodotti* GetIN (const Ospite*) const;
    Prodotti* GetCCorrenti() const;
    Prodotti* GetInvestimenti() const;
    Cont_corr* GetConto(const uint&) const;
    Investimento* GetInvest(const uint &text) const;
    Prodotti* InvestimentiCC(const Cont_corr*) const;
    void removeServizio(Servizio*);
    bool RimuoviServizio(Servizio*);
    bool isempty();

    class Iteratore{
        friend class Prodotti;
    private: 
        Prodotti::nodo*punt;
        bool passTheEnd;
        Iteratore(nodo*, bool);
    public:
        Iteratore();
        bool operator== (const Iteratore&)const;
        bool operator !=(const Iteratore&) const;
        Servizio* operator*() const;
        Servizio** operator-> () const;
        Iteratore& operator= (const Iteratore&);
        Iteratore& operator ++ ();
        Iteratore operator++(int);
       
    };

    class constIteratore{
        friend class Prodotti;
    private:
        const Prodotti::nodo* punt;
        bool passTheEnd;
        constIteratore(nodo*,bool);
    public:
        constIteratore();
        bool operator==(const constIteratore&) const;
        bool operator !=(const constIteratore&) const;
        const Servizio* operator*() const;
        const Servizio *const*operator->() const;
        constIteratore& operator =(const constIteratore&) noexcept;
        constIteratore& operator++();
        constIteratore operator++(int);
    };

    Iteratore it_begin()const;
    Iteratore it_end()const;
    constIteratore cit_begin()const;
    constIteratore cit_end() const;
  
};

#endif // PRODOTTI_H
