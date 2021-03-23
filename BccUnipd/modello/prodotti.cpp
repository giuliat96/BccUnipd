#include "prodotti.h"

Prodotti::nodo::nodo(Servizio* servizio, nodo *p, nodo *n):info(servizio), prev(p), next(n){}

Prodotti::nodo::nodo(const nodo& n):info(n.info), prev(n.prev), next(n.next){}

Prodotti::nodo::~nodo(){
    if(next) delete next;
}

Prodotti::nodo* Prodotti::clone(nodo* p,nodo*&l){
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

Prodotti::Prodotti():last(nullptr),first(nullptr){}

Prodotti::Prodotti(Servizio* s): first(new nodo(s)){
    last=first;
}

Prodotti::Prodotti(const Prodotti& p): first(clone(p.first,last)){}

Prodotti::~Prodotti(){
   delete first;
}

Prodotti& Prodotti::operator=(const Prodotti& s){
    if(this!= &s){
        delete first;
        first=clone(s.first,last);
    }
    return *this;
}

void Prodotti::addServizio(Servizio * servizio){
    Cont_corr* serv=dynamic_cast<Cont_corr*>(servizio);
    if (serv){
        if(first){
            for (Iteratore it= it_begin(); it!=it_end(); ++it){
                Cont_corr* inv= dynamic_cast<Cont_corr*>(*it);
                if (inv && inv->GetNCC()==serv->GetNCC()){
                    string result="ERR_NCC";
                    throw(result);
                }
            }
        }
    }
    else {
        Investimento* serv=dynamic_cast<Investimento*>(servizio);
        if(first){
            for (Iteratore it= it_begin(); it!=it_end(); ++it){
                Investimento* inv= dynamic_cast<Investimento*>(*it);
                if (inv && inv->GetNumeroInvestimento()==serv->GetNumeroInvestimento()){
                    string result="ERR_NINV";
                    throw(result);
                }
            }
        }
    }
    if(!first) first=last=new nodo(servizio);
    else {
        last->next=new nodo(servizio,last);
        last=last->next;
    }
}

Prodotti* Prodotti::GetIN(const Ospite* os) const{
    Prodotti* investimenti=new Prodotti();
    Investimento* inv= nullptr;

    if(first){
        for (Iteratore it= it_begin(); it!=it_end(); ++it){
            inv= dynamic_cast<Investimento*>(*it);
            if (inv && inv->GetIntestatario()== os)
                investimenti->addServizio(*it);
        }
    }
    return investimenti;
}

Prodotti* Prodotti::GetCont(const Ospite* os) const{
    Prodotti* ccorrenti=new Prodotti();
    Cont_corr* inv= nullptr;

    if(first){
        for (Iteratore it= it_begin(); it!=it_end(); ++it){
            inv= dynamic_cast<Cont_corr*>(*it);
            if (inv && (inv->GetIntestatario()== os || inv->GetCoIntestatario()==os))
                ccorrenti->addServizio(*it);
        }
    }
    return ccorrenti;
}

Cont_corr* Prodotti::GetConto(const uint &text) const{
    Cont_corr* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Cont_corr*>(*it);
            if(tmp && (tmp)->Cont_corr::GetNCC() == text ){
                return tmp;
            }
        }
    }
    return nullptr;
}

Investimento* Prodotti::GetInvest(const uint &text) const{
    Investimento* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Investimento*>(*it);
            if(tmp && (tmp)->Investimento::GetNumeroInvestimento() == text ){
                return tmp;
            }
        }
    }
    return nullptr;
}

Prodotti* Prodotti::InvestimentiCC(const Cont_corr* conto) const{
    Prodotti* investimenti=GetInvestimenti();
    Iteratore it=investimenti->it_begin();
    Prodotti* inv_cc=new Prodotti();
    Investimento* tmp=nullptr;
    if(!investimenti->isempty()){
        for( ;it!=investimenti->it_end(); ++it){
            tmp=dynamic_cast<Investimento*>(*it);
            if(tmp && (tmp)->Investimento::GetContoCollegato() == conto ){
                inv_cc->addServizio(tmp);
            }
        }
    }
    return inv_cc;
}

void Prodotti::removeServizio(Servizio* servizio){
    Iteratore it=it_begin();
    bool found=false;
    for( ;it!=it_end() && !found; ++it){
        if(*it==servizio){
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

bool Prodotti::RimuoviServizio(Servizio* servizio){
    if(!isempty()){
        Cont_corr* tmp=dynamic_cast<Cont_corr*>(servizio);
        if(tmp){
            Prodotti* investimenti=InvestimentiCC(tmp);
            if(!investimenti->isempty())return false;
            else{
                removeServizio(servizio);
                return true;
            }
        }
        else {
            Investimento* tmp2=dynamic_cast<Investimento*>(servizio);
            QDate oggi=QDate::currentDate();
            if(tmp2->GetDataFine()>oggi) return false;
            else {
                removeServizio(servizio);
                return true;
            }
        }
    }
    else return false;
}

Prodotti::Iteratore::Iteratore(nodo * p, bool pte=false) : punt(p), passTheEnd(pte){}

Prodotti::Iteratore::Iteratore() : punt(nullptr), passTheEnd(false) {}

bool Prodotti::Iteratore::operator ==(const Iteratore& i) const{
    return punt==i.punt;
}

bool Prodotti::Iteratore::operator !=(const Iteratore& i) const{
    return punt!=i.punt;
}

Servizio* Prodotti::Iteratore::operator *() const{
    return punt->info;
}

Servizio** Prodotti::Iteratore::operator ->() const{
    return &(punt->info);
}

Prodotti::Iteratore& Prodotti::Iteratore::operator =(const Iteratore& i){
    punt=i.punt;
    passTheEnd=i.passTheEnd;
    return *this;
}

Prodotti::Iteratore& Prodotti::Iteratore::operator++(){
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
Prodotti::Iteratore Prodotti::Iteratore::operator++(int){
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

Prodotti::Iteratore Prodotti::it_begin()const {
    return Iteratore(first);
}

Prodotti::Iteratore Prodotti::it_end() const{
    if(last==nullptr) return nullptr;
    return Iteratore(last+1,true);
}

Prodotti::constIteratore::constIteratore(nodo * p, bool pte=false) : punt(p), passTheEnd(pte){}

Prodotti::constIteratore::constIteratore() : punt(nullptr), passTheEnd(false) {}

bool Prodotti::constIteratore::operator ==(const constIteratore& i) const{
    return punt==i.punt;
}

bool Prodotti::constIteratore::operator !=(const constIteratore& i) const{
    return punt!=i.punt;
}

const Servizio* Prodotti::constIteratore::operator *() const{
    return punt->info;
}

const Servizio*const* Prodotti::constIteratore::operator ->() const{
    return &(punt->info);
}

Prodotti::constIteratore& Prodotti::constIteratore::operator =(const constIteratore& i)noexcept{
    punt=i.punt;
    passTheEnd=i.passTheEnd;
    return *this;
}

Prodotti::constIteratore& Prodotti::constIteratore::operator++(){
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

Prodotti::constIteratore Prodotti::constIteratore::operator++(int){
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

Prodotti::constIteratore Prodotti::cit_begin()const{
    return constIteratore(first);
}

Prodotti::constIteratore Prodotti::cit_end() const{
    if(last==nullptr) return nullptr;
    return constIteratore(last+1,true);
}

Prodotti* Prodotti::GetCCorrenti() const{
    Prodotti* allcc=new Prodotti();
    Cont_corr* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Cont_corr*>(*it);
            if(tmp) allcc->addServizio(tmp);
        }
    }
    return allcc;
}

Prodotti* Prodotti::GetInvestimenti() const{
    Prodotti* allinvestimenti=new Prodotti();
    Investimento* tmp=nullptr;
    if(first){
        Iteratore it=it_begin();
        for( ;it!=it_end(); ++it){
            tmp=dynamic_cast<Investimento*>(*it);
            if(tmp) allinvestimenti->addServizio(tmp);
        }
    }
    return allinvestimenti;
}

bool Prodotti::isempty(){
    if(first==last && first==nullptr) return true;
    else return false;
}
