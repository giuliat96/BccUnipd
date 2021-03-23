#include "soggetti.h"

Soggetti::nodo::nodo(Persona* persona, nodo *p, nodo *n):info(persona), prev(p), next(n){}

Soggetti::nodo::nodo(const nodo& n):info(n.info), prev(n.prev), next(n.next){}

Soggetti::nodo::~nodo(){
    if(next) delete next;
}

Soggetti::nodo* Soggetti::clone(nodo* p,nodo*&l){
        if(p==nullptr) return l=nullptr;
        nodo* prec=new nodo(p->info,nullptr,nullptr);
        nodo* succ=prec;
        nodo* start=prec;
        while(p->next!=nullptr){
            succ=new nodo(p->next->info,prec,nullptr);
            prec->next=succ;
            p=p->next;
            prec=prec->next;
        }
        l=succ;
        return start;
    }

bool Soggetti::isLess(nodo* n1,nodo* n2){
    if(n2==nullptr) return false;
    if(n1==nullptr) return true;
    return n1->info < n2->info || (n1->info==n2->info && isLess(n1->next,n2->next));
}

Soggetti::Soggetti():last(nullptr),first(nullptr){}

Soggetti::Soggetti(Persona* p): first(new nodo(p)){
    last=first;
}

Soggetti::Soggetti(const Soggetti & s): first(clone(s.first,last)){}

Soggetti::~Soggetti(){
   delete first;
}

Soggetti& Soggetti::operator=(const Soggetti& s){
    if(this!= &s){
        delete first;
        first=clone(s.first,last);
    }
    return *this;
}

void Soggetti::addOrdineL(Persona* p){
    nodo* persona = new nodo(p);
    if (first == nullptr) {
        first= persona;
        last=persona;
    }
    else if (first->info < persona->info) {
        nodo* tmp = first;
        while (tmp->next && tmp->next->info < persona->info) {
           tmp = tmp->next;
        }
        persona->next = tmp->next;
        persona->prev=tmp;
        tmp->next = persona;
        if (persona->next == nullptr) last = persona;
    }
    else {
        persona->next = first;
        first->prev=persona;
        first = persona;
    }
}

bool Soggetti::operator<(const Soggetti& s){
    return isLess(first,s.first);
}

Operatore* Soggetti::GetOperatore(const string &text) const{
    Operatore* result =nullptr;
    Operatore* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Operatore*>(*it);
            if(tmp && (tmp)->Operatore::GetUsername() == text ){
                result= tmp;
                return result;
            }
        }
    }
    return result;
}

Ospite* Soggetti::GetOspite(const uint &number) const{
    Ospite* result =nullptr;
    Ospite* tmp=nullptr;
    if(first && number){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Ospite*>(*it);
            if(tmp && (tmp)->GetNumeroIdentificativo()==number){
                result=tmp;
                return result;
            }
        }
    }
    return result;
}

Soggetti* Soggetti::GetOperatori() const{
    Soggetti* alloperatori=new Soggetti();
    Operatore* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Operatore*>(*it);
            if(tmp) alloperatori->addOrdineL(tmp);
        }
    }
    return alloperatori;
}

Soggetti* Soggetti::GetOpSportello() const{
    Soggetti* alloperatori=new Soggetti();
    Operatore* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Operatore*>(*it);
            if(tmp && !tmp->GestioneDipendenti()) alloperatori->addOrdineL(tmp);
        }
    }
    return alloperatori;
}

Soggetti* Soggetti::GetOpPersonale() const{
    Soggetti* alloperatori=new Soggetti();
    Operatore* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Operatore*>(*it);
            if(tmp && tmp->GestioneDipendenti()) alloperatori->addOrdineL(tmp);
        }
    }
    return alloperatori;
}

Soggetti* Soggetti::GetOspiti() const{
    Soggetti* allospiti=new Soggetti();
    Ospite* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Ospite*>(*it);
            if(tmp) allospiti->addOrdineL(tmp);
        }
    }
    return allospiti;
}

Soggetti::Iteratore::Iteratore(nodo * p, bool pte=false) : punt(p), passTheEnd(pte){}

Soggetti::Iteratore::Iteratore() : punt(nullptr), passTheEnd(false) {}

bool Soggetti::Iteratore::operator ==(const Iteratore& i) const{
    return punt==i.punt;
}

bool Soggetti::Iteratore::operator !=(const Iteratore& i) const{
    return punt!=i.punt;
}

Persona* Soggetti::Iteratore::operator* () const{
    return punt->info;
}

Persona** Soggetti::Iteratore::operator-> () const{
    return &(punt->info);
}

Soggetti::Iteratore& Soggetti::Iteratore::operator =(const Iteratore& i){
    punt=i.punt;
    passTheEnd=i.passTheEnd;
    return *this;
}

Soggetti::Iteratore& Soggetti::Iteratore::operator++(){
    if(punt) {
        if(!passTheEnd){
            if(punt->next==nullptr) {
                ++punt;
                passTheEnd=true;
            }
            else punt=punt->next;
         }
    }
    return *this;
}

Soggetti::Iteratore Soggetti::Iteratore::operator++(int){
    Iteratore tmp=*this;
    if(punt) {
        if(!passTheEnd){
            if(punt->next==nullptr) {
                ++punt;
                passTheEnd=true;
            }
            else punt=punt->next;
         }
    }
    return tmp;
}

Soggetti::Iteratore Soggetti::Iteratore::operator--(){
    if(punt) {
        if(punt->prev!=nullptr){
            punt=punt->next;
         }
    }
    return *this;
}

Soggetti::Iteratore Soggetti::it_begin() const{
    return Iteratore(first);
}

Soggetti::Iteratore Soggetti::it_end() const {
    if(last==nullptr) return nullptr;
    return Iteratore(last+1,true);
}

Soggetti::constIteratore::constIteratore(nodo * p, bool pte=false) : punt(p), passTheEnd(pte){}

Soggetti::constIteratore::constIteratore() : punt(nullptr), passTheEnd(false) {}

bool Soggetti::constIteratore::operator ==(const constIteratore& i) const{
    return punt==i.punt;
}

bool Soggetti::constIteratore::operator !=(const constIteratore& i) const{
    return punt!=i.punt;
}

const Persona* Soggetti::constIteratore::operator* () const{
    return punt->info;
}

const Persona*const* Soggetti::constIteratore::operator-> () const{
    return &(punt->info);
}

Soggetti::constIteratore& Soggetti::constIteratore::operator =(const constIteratore& i)noexcept{
    punt=i.punt;
    passTheEnd=i.passTheEnd;
    return *this;
}

Soggetti::constIteratore& Soggetti::constIteratore::operator++(){
    if(punt) {
        if(!passTheEnd){
            if(punt->next==nullptr) {
                ++punt;
                passTheEnd=true;
            }
            else punt=punt->next;
         }
    }
    return *this;
}

Soggetti::constIteratore Soggetti::constIteratore::operator++(int){
    constIteratore tmp=*this;
    if(punt) {
        if(!passTheEnd){
            if(punt->next==nullptr) {
                ++punt;
                passTheEnd=true;
            }
            else punt=punt->next;
         }
    }
    return tmp;
}

Soggetti::constIteratore Soggetti::cit_begin()const{
    return constIteratore(first);
}

Soggetti::constIteratore Soggetti::cit_end() const{
    if(last==nullptr) return nullptr;
    return constIteratore(last+1,true);
}

string Soggetti::CheckOnePerson(Persona* newperson, Operatore* utente)const{
    Dipendente* nuovapersona=dynamic_cast<Dipendente*>(newperson);
    if(first){
        auto it=cit_begin();
        for( ;it!=cit_end(); ++it){
            if(nuovapersona){
                if(dynamic_cast<const Dipendente*>(*it) || dynamic_cast<const dipendente_cliente*>(*it)){
                    const Operatore* tmp=dynamic_cast<const Operatore*>(*it);
                    if(newperson->GetCF()==(*it)->GetCF()){
                        return "NO_CF";
                    }
                    if(nuovapersona->GetUsername()==(tmp)->GetUsername()){
                        return "NO_US";
                    }
                }
                else if(dynamic_cast<const Cliente*>(*it)){
                    if(nuovapersona->GetCF()==(*it)->GetCF() && nuovapersona->GetNome()==(*it)->GetNome() && nuovapersona->GetCognome()==(*it)->GetCognome() && nuovapersona->GetDataNascita()==(*it)->GetDataNascita()){
                        return "CAMBIO";
                    }
                    else if(nuovapersona->GetCF()==(*it)->GetCF() && (nuovapersona->GetNome()!=(*it)->GetNome() || nuovapersona->GetCognome()!=(*it)->GetCognome() || nuovapersona->GetDataNascita()!=(*it)->GetDataNascita())){
                        return "NO_CF";
                    }
                }
            }
            else{
                Cliente* nuovapersona=dynamic_cast<Cliente*>(newperson);
                if(nuovapersona){
                    if(dynamic_cast<const Cliente*>(*it) || dynamic_cast<const dipendente_cliente*>(*it)){
                        const Ospite* tmp=dynamic_cast<const Ospite*>(*it);
                        if(newperson->GetCF()==(*it)->GetCF()){
                            return "NO_CF";
                        }
                        if(nuovapersona->GetNumeroIdentificativo()==(tmp)->GetNumeroIdentificativo()){
                            return "NO_NUM";
                        }
                    }
                    else if(dynamic_cast<const Dipendente*>(*it)){
                        if(nuovapersona->GetCF()==(utente)->GetCF() && nuovapersona->GetNome()==(utente)->GetNome() && nuovapersona->GetCognome()==(utente)->GetCognome() && nuovapersona->GetDataNascita()==(utente)->GetDataNascita()){
                            return "NO_AUTO";
                        }
                        else if(nuovapersona->GetCF()==(*it)->GetCF() && nuovapersona->GetNome()==(*it)->GetNome() && nuovapersona->GetCognome()==(*it)->GetCognome() && nuovapersona->GetDataNascita()==(*it)->GetDataNascita()){
                            return "CAMBIO";
                        }
                        else if(nuovapersona->GetCF()==(*it)->GetCF() && (nuovapersona->GetNome()!=(*it)->GetNome() || nuovapersona->GetCognome()!=(*it)->GetCognome()|| nuovapersona->GetDataNascita()!=(*it)->GetDataNascita())){
                            return "NO_CF";
                        }
                    }
                }
            }
        }
    }
    return "SI";
}

bool Soggetti::CheckModifiche(Persona* newperson) const{
    Operatore* nuovapersona=dynamic_cast<Operatore*>(newperson);
    string result;
    if(first){
        auto it=cit_begin();
        for( ;it!=cit_end(); ++it){
            if(nuovapersona){
                const Operatore* tmp=dynamic_cast<const Operatore*>(*it);
                if(tmp && nuovapersona->GetCF()!=tmp->GetCF()){
                    if(nuovapersona->GetUsername()==(tmp)->GetUsername()){
                       result="NO_US";
                        throw(result);
                    }   
                }
            }
            else {
                Ospite* nuovapersona=dynamic_cast<Ospite*>(newperson);
                const Ospite* tmp=dynamic_cast<const Ospite*>(*it);
                if(tmp && nuovapersona->GetCF()!=tmp->GetCF()){
                    if(nuovapersona->GetNumeroIdentificativo()==(tmp)->GetNumeroIdentificativo()){
                       result="NO_NUM";
                        throw(result);
                    }
                }
            }
        }
    }
    return true;
}

const Operatore* Soggetti::CheckLogin(const string &username, const string &password)const{
     const Operatore* logged_user=nullptr;
     const Operatore* tmp=nullptr;
     if(first){
         auto it=cit_begin();
         for( ;it!=cit_end() && !logged_user; ++it){
             tmp=dynamic_cast<const Operatore*>(*it);
             if(tmp && (tmp->GetUsername()==username && tmp->GetPassword()==password))
                 logged_user=tmp;
         }
     }
     return logged_user;
}

void Soggetti::ChangeType(Persona* persona, Prodotti* prodotti){
    Dipendente* nuovapersona=dynamic_cast<Dipendente*>(persona);
    if(nuovapersona){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            if(dynamic_cast<Cliente*>(*it)){
                Cliente* tmp=dynamic_cast<Cliente*>(*it);
                if(nuovapersona->GetCF()==(*it)->GetCF() && nuovapersona->GetNome()==(*it)->GetNome() && nuovapersona->GetCognome()==(*it)->GetCognome() && nuovapersona->GetDataNascita()==(*it)->GetDataNascita()){
                   dipendente_cliente* persona_aggiornare= new dipendente_cliente(nuovapersona->GetEmail(), nuovapersona->GetCellulare(),
                                        nuovapersona->GetUsername(), nuovapersona->GetPassword(), nuovapersona->GetNome(),
                                       nuovapersona->GetCognome(),nuovapersona->GetCF(),nuovapersona->GetDataNascita(), nuovapersona->GetInquadratura(),
                                       tmp->GetEmail(),tmp->GetCellulare(),nuovapersona->GetInizioContratto(),nuovapersona->GetTipoContratto(),
                                       nuovapersona->GetFineContratto(),nuovapersona->GetPersoneACarico(),tmp->GetDataInizioRapporto(),
                                       tmp->GetNumeroIdentificativo(), tmp->GetAppOnline());
                   personaServizi(tmp,persona_aggiornare,prodotti);
                   removePerson(*it);
                   addOrdineL(persona_aggiornare);
                   return;
                }
            }
        }
    }
    else {
        Cliente* nuovapersona=dynamic_cast<Cliente*>(persona);
        Iteratore it=it_begin();
            for( ;it!=it_end(); ++it){
                if(dynamic_cast<Dipendente*>(*it)){
                    Dipendente* tmp=dynamic_cast<Dipendente*>(*it);
                    if(nuovapersona->GetCF()==(*it)->GetCF() && nuovapersona->GetNome()==(*it)->GetNome() && nuovapersona->GetCognome()==(*it)->GetCognome() && nuovapersona->GetDataNascita()==(*it)->GetDataNascita()){
                       dipendente_cliente* persona_aggiornare= new dipendente_cliente(tmp->GetEmail(), tmp->GetCellulare(),
                                            tmp->GetUsername(), tmp->GetPassword(), tmp->GetNome(),
                                           tmp->GetCognome(),tmp->GetCF(),tmp->GetDataNascita(), tmp->GetInquadratura(),
                                           nuovapersona->GetEmail(),nuovapersona->GetCellulare(),tmp->GetInizioContratto(),tmp->GetTipoContratto(),
                                           tmp->GetFineContratto(),tmp->GetPersoneACarico(),nuovapersona->GetDataInizioRapporto(),
                                           nuovapersona->GetNumeroIdentificativo(), nuovapersona->GetAppOnline());
                       removePerson(*it);
                       addOrdineL(persona_aggiornare);
                       return;
                    }
                }
            }
    }
}

bool Soggetti::AggiungiPersona(Persona* persona, Operatore* loggato, Prodotti* prodotti){
    string resultOnePerson=CheckOnePerson(persona,loggato);
    if(resultOnePerson=="NO_CF" || resultOnePerson=="NO_US" || resultOnePerson=="NO_NUM" ||resultOnePerson=="NO_AUTO") {
        delete persona;
        throw(resultOnePerson);
    }
    else{
        if(resultOnePerson=="SI"){
            addOrdineL(persona);
        }
        else if(resultOnePerson=="CAMBIO"){
            ChangeType(persona,prodotti);
        }
        if(dynamic_cast<Ospite*>(persona)) Cliente::NumeroClienti++;
        return true;
    }
}

bool Soggetti::RimuoviPersona(Persona* p_rimuovere,Operatore* loggato,Prodotti* prodotti){
    bool found=false;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end() && !found; ++it){
            if(*it==p_rimuovere){
                found=true;
                dipendente_cliente* tmp= dynamic_cast<dipendente_cliente*>(p_rimuovere);
                if(tmp) {
                    dipendente_cliente* persona_rimuovere=dynamic_cast<dipendente_cliente*>(p_rimuovere);
                    if(loggato->GestioneDipendenti()){
                        Cliente* persona=new Cliente(persona_rimuovere->GetNome(),persona_rimuovere->GetCognome(),
                                                     persona_rimuovere->GetCF(),persona_rimuovere->GetDataNascita(),
                                                     persona_rimuovere->Ospite::GetEmail(),persona_rimuovere->Ospite::GetCellulare(),
                                                     persona_rimuovere->GetDataInizioRapporto(),
                                                     persona_rimuovere->GetNumeroIdentificativo(),
                                                     persona_rimuovere->GetAppOnline());
                        personaServizi(tmp,persona,prodotti);
                        removePerson(p_rimuovere);
                        addOrdineL(persona);
                    }
                    else {
                        if(!CheckNoServizi(p_rimuovere,prodotti)) return false;
                        Dipendente* persona=new Dipendente(persona_rimuovere->GetUsername(),persona_rimuovere->GetPassword(),
                                                           persona_rimuovere->GetNome(),persona_rimuovere->GetCognome(),
                                                           persona_rimuovere->GetCF(),persona_rimuovere->GetDataNascita(),
                                                           persona_rimuovere->GetInquadratura(),persona_rimuovere->Operatore::GetEmail(),
                                                           persona_rimuovere->Operatore::GetCellulare(),persona_rimuovere->GetInizioContratto(),
                                                           persona_rimuovere->GetTipoContratto(),persona_rimuovere->GetFineContratto(),
                                                           persona_rimuovere->GetPersoneACarico());
                        removePerson(p_rimuovere);
                        addOrdineL(persona);
                    }
                }
                if(dynamic_cast<Ospite*>(p_rimuovere)){
                    if(!CheckNoServizi(p_rimuovere,prodotti)) return false;
                }
                removePerson(p_rimuovere);
            }
        }
    }
    return found;
}

void Soggetti::personaServizi(Persona* p_rimuovere,Persona* persona,Prodotti*prodotti){
    Ospite* sostituire=dynamic_cast<Ospite*>(p_rimuovere);
    Ospite* sostituto=dynamic_cast<Ospite*>(persona);
    Prodotti* servizi=prodotti->GetCont(sostituire);
    if(!servizi->isempty()){
        Prodotti::Iteratore it=servizi->it_begin();
        for (;it!=servizi->it_end();it++){
            if(sostituire==(*it)->GetIntestatario()) (*it)->Intestatario=sostituto;
            else (*it)->Intestatario2=sostituto;
        }
    }
    servizi=prodotti->GetIN(sostituire);
    if(!servizi->isempty()){
        Prodotti::Iteratore it=servizi->it_begin();
        for (;it!=servizi->it_end();it++){
            (*it)->Intestatario=sostituto;
        }
    }
}

void Soggetti::removePerson(Persona* p_rimuovere){
    Iteratore it=it_begin();
    bool found=false;
    for( ;it!=it_end() && !found; ++it){
        if(*it==p_rimuovere){
        if(it.punt==first && it.punt==last){
            first=last=nullptr;
        }
        else {
            if(it.punt==first){
                first=it.punt->next;
                first->prev=nullptr;
            }
            else if(it.punt==last){
                last=it.punt->prev;
                last->next=nullptr;
            }
            else{
                it.punt->prev->next=it.punt->next;
                it.punt->next->prev=it.punt->prev;
            }
        }
        delete *it;
        found=true;
        }
    }
}

bool Soggetti::CheckNoServizi(Persona* cliente, Prodotti* servizi){
    Ospite* tmp=dynamic_cast<Ospite*>(cliente);

    Prodotti* serviziospite=new Prodotti();
    serviziospite=servizi->GetIN(tmp);
    if(!serviziospite->isempty()) return false;
    else {
        serviziospite=servizi->GetCont(tmp);
        if(!serviziospite->isempty()) return false;
        else return true;
    }
}

Persona* Soggetti::CercaCF(Operatore* utente,const string& CF){
    if(CF==""){
        string result="ERR_CF";
        throw(result);
    }
   Persona* tmp=nullptr;
    if(first){
        if(utente->GestioneDipendenti()){
            for(Iteratore it=it_begin() ;it!=it_end(); ++it){
                if(dynamic_cast<Operatore*>(*it) && (*it)->GetCF()==CF){
                    tmp=*it;
                    return tmp;
                }
            }
        }
        else {
            for(Iteratore it=it_begin() ;it!=it_end(); ++it){
                if(dynamic_cast<Ospite*>(*it) && (*it)->GetCF()==CF){
                    tmp=*it;
                    return tmp;
                }
            }
        }
    }
    return tmp;
}

Soggetti* Soggetti::CercaNS(Operatore* utente,const string& Nome,const string& Cognome){
    if(Nome=="" || Cognome==""){
        string result="ERR_CERCANS";
        throw(result);
    }
    Soggetti* tmp=new Soggetti();
    if(first){
        if(utente->GestioneDipendenti()){
            for(Iteratore it=it_begin() ;it!=it_end(); ++it){
                if(dynamic_cast<Operatore*>(*it) && (*it)->GetNome()==Nome && (*it)->GetCognome()==Cognome){
                    tmp->addOrdineL(*it);
                }
            }
            return tmp;
        }
        else {
            for(Iteratore it=it_begin() ;it!=it_end(); ++it){
                if(dynamic_cast<Ospite*>(*it) && (*it)->GetNome()==Nome && (*it)->GetCognome()==Cognome){
                    tmp->addOrdineL(*it);
                }
            }
            return tmp;
        }
    }
    else return tmp;
}

bool Soggetti::isempty(){
    if(first==last && first==nullptr) return true;
    else return false;
}


Soggetti* Soggetti::Senior(Operatore* loggato)const{
    Soggetti* soggetti=new Soggetti();
    if(first){
        for(Iteratore it=it_begin() ;it!=it_end(); ++it){
            Operatore* tmp=dynamic_cast<Operatore*>(*it);
            if(loggato->GestioneDipendenti() && tmp && tmp->Senior()){
                soggetti->addOrdineL(*it);
            }
            else if(!loggato->GestioneDipendenti() && !tmp && (*it)->Senior()){
                soggetti->addOrdineL(*it);
            }
        }
    }
    return soggetti;
}
