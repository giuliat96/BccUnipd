#include "table_lists.h"

table_lists::table_lists(Soggetti *persone,Prodotti* prodotti,QWidget *parent):
    QTableWidget(parent),listapersone(persone),listaprodotti(prodotti){}

//........................PERSONE................................

void table_lists::viewOperatori(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,250);
    setColumnWidth(1,250);
    setColumnWidth(2,250);
    setColumnWidth(3,220);
    setMaximumWidth(1200);
    tableHeader<<"Username"<<"Nome"<<"Cognome"<<"Codice Fiscale";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void table_lists::viewOspiti(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,250);
    setColumnWidth(1,250);
    setColumnWidth(2,250);
    setColumnWidth(3,220);
    setMaximumWidth(1200);
    tableHeader<<"Numero Cliente"<<"Nome"<<"Cognome"<<"Codice Fiscale";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void table_lists::viewAllOperatori(){
    int row=0;
        Soggetti* ListOperatori= listapersone->GetOperatori();
        Soggetti::Iteratore it=ListOperatori->it_begin();
        for(; it!=ListOperatori->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableOperatore(row,*it);
                row++;
            }
        }
}

void table_lists::viewAllSportello(){
    int row=0;
        Soggetti* ListOperatori= listapersone->GetOpSportello();
        Soggetti::Iteratore it=ListOperatori->it_begin();
        for(; it!=ListOperatori->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableOperatore(row,*it);
                row++;
            }
        }
}

void table_lists::viewAllPersonale(){
    int row=0;
        Soggetti* ListOperatori= listapersone->GetOpPersonale();
        Soggetti::Iteratore it=ListOperatori->it_begin();
        for(; it!=ListOperatori->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableOperatore(row,*it);
                row++;
            }
        }
}

void table_lists::viewAllOspiti(){
    int row=0;
        Soggetti* ListOspiti= listapersone->GetOspiti();
        Soggetti::Iteratore it=ListOspiti->it_begin();
        for(; it!=ListOspiti->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableOspite(row,*it);
                row++;
            }
        }
}

void table_lists::viewAllInvestitori(){
    int row=0;
        Prodotti* ListInv= listaprodotti->GetInvestimenti();
        if(!ListInv->isempty()){
        Prodotti::Iteratore it=ListInv->it_begin();
            Soggetti* Investitori=new Soggetti();
            for(; it!=ListInv->it_end() ;it++){
                Investitori->addOrdineL((*it)->GetIntestatario());
            }
            Soggetti::Iteratore in=Investitori->it_begin();
            Soggetti::Iteratore in2=Investitori->it_begin();
            for(; in!=Investitori->it_end() ;in=in2){
                in2++;

                bool ok=true;
                while(ok){
                    if((*in)!=(*in2)) ok=false;
                    else in2++;
                }
                setRowCount(row+1);
                addtableOspite(row,(*in));
                row++;
            }
        }
}

void table_lists::viewSoggetti(Soggetti* senior,Operatore* loggato){
    int row=0;
    if(!senior->isempty()){
        Soggetti::Iteratore it=senior->it_begin();
        if(loggato->GestioneDipendenti()){
            for(; it!=senior->it_end() ;it++){
                if(*it){
                    setRowCount(row+1);
                    addtableOperatore(row,*it);
                    row++;
                }
            }
        }
        else{
            for(; it!=senior->it_end() ;it++){
                if(*it){
                    setRowCount(row+1);
                    addtableOspite(row,*it);
                    row++;
                }
            }
        }
    }
}

void table_lists::addtableOperatore(int row, Persona* operatore){
    Operatore* tmp=dynamic_cast<Operatore*>(operatore);
    setItem(row,0,new QTableWidgetItem(QString::fromStdString(tmp->GetUsername())));
    setItem(row,1,new QTableWidgetItem(QString::fromStdString(operatore->GetNome())));
    setItem(row,2,new QTableWidgetItem(QString::fromStdString(operatore->GetCognome())));
    setItem(row,3,new QTableWidgetItem(QString::fromStdString(operatore->GetCF())));
}

void table_lists::addtableOspite(int row, Persona* ospite){
    Ospite* tmp=dynamic_cast<Ospite*>(ospite);
    QTableWidgetItem* item= new QTableWidgetItem;
    item->setData(Qt::EditRole,tmp->GetNumeroIdentificativo());
    setItem(row,0,item);
    setItem(row,1,new QTableWidgetItem(QString::fromStdString(ospite->GetNome())));
    setItem(row,2,new QTableWidgetItem(QString::fromStdString(ospite->GetCognome())));
    setItem(row,3,new QTableWidgetItem(QString::fromStdString(ospite->GetCF())));

}

void table_lists::tableSearch(Operatore* loggato,Soggetti* soggetti){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,255);
    setColumnWidth(1,210);
    setColumnWidth(2,200);
    setColumnWidth(3,265);
    setMaximumWidth(933);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    if(soggetti){
        Soggetti::Iteratore it=soggetti->it_begin();
        if(loggato->GestioneDipendenti()){
                tableHeader<<"Username"<<"Nome"<<"Cognome"<<"Codice Fiscale";
                setHorizontalHeaderLabels(tableHeader);
                for(; it!=soggetti->it_end() ;it++){
                    if(dynamic_cast<Operatore*>(*it)){
                            setRowCount(row+1);
                            addtableOperatore(row,*it);
                            row++;
                    }
                }
            }
        else{
            tableHeader<<"Numero Cliente"<<"Nome"<<"Cognome"<<"Codice Fiscale";
            setHorizontalHeaderLabels(tableHeader);
            for(; it!=soggetti->it_end() ;it++){
                if(dynamic_cast<Ospite*>(*it)){
                        setRowCount(row+1);
                        addtableOspite(row,*it);
                        row++;
                    }
                }
            }
        }
}

//...........................SERVIZI.............................

void table_lists::viewCCPersona(Ospite* cliente){
    setRowCount(0);
    QStringList tableHeader;
    setColumnCount(3);
    setColumnWidth(0,150);
    setColumnWidth(1,150);
    setColumnWidth(2,150);
    tableHeader<<"Numero Conto"<<"Data Apertura"<<"Co-Intestatario";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
        Prodotti* ListProdotti= listaprodotti->GetCont(cliente);
        if(!ListProdotti->isempty()){
            Prodotti::Iteratore it=ListProdotti->it_begin();
            for(; it!=ListProdotti->it_end() ;it++){
                setRowCount(row+1);
                QTableWidgetItem* item_0= new QTableWidgetItem();
                Cont_corr* tmp=dynamic_cast<Cont_corr*>(*it);
                item_0->setData(Qt::EditRole,tmp->GetNCC());
                setItem(row,0,item_0);
                QTableWidgetItem* item_1= new QTableWidgetItem();
                item_1->setData(Qt::EditRole,(tmp)->GetAttivazione());
                setItem(row,1,item_1);
                if(tmp->GetIntestatario()==cliente){
                    if(tmp->GetCoIntestatario()!=nullptr){
                    setItem(row,2,new QTableWidgetItem(QString::fromStdString((tmp)->GetCoIntestatario()->GetCF())));
                    }
                }
                else {
                    setItem(row,2,new QTableWidgetItem(QString::fromStdString((tmp)->GetIntestatario()->GetCF())));
                }

                row++;
            }
        }
}

void table_lists::viewInvPersona(Ospite* cliente){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,150);
    setColumnWidth(1,150);
    setColumnWidth(2,150);
    setColumnWidth(3,150);
    tableHeader<<"Numero Investimento"<<"CC Collegato"<<"Durata"<<"Somma Investita";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
        Prodotti* ListProdotti= listaprodotti->GetIN(cliente);
        if(!ListProdotti->isempty()){
            Prodotti::Iteratore it=ListProdotti->it_begin();
            for(; it!=ListProdotti->it_end() ;it++){
                setRowCount(row+1);
                QTableWidgetItem* item= new QTableWidgetItem();
                Investimento* tmp=dynamic_cast<Investimento*>(*it);
                item->setData(Qt::EditRole,tmp->GetNumeroInvestimento());
                setItem(row,0,item);
                QTableWidgetItem* item1= new QTableWidgetItem();
                item1->setData(Qt::EditRole,tmp->GetContoCollegato()->GetNCC());
                setItem(row,1,item1);
                QTableWidgetItem* item2= new QTableWidgetItem();
                item2->setData(Qt::EditRole,tmp->GetDataFine());
                setItem(row,2,item2);
                QTableWidgetItem* item3= new QTableWidgetItem();
                item3->setData(Qt::EditRole,tmp->GetSommaInvestita());
                setItem(row,3,item3);
                row++;
            }
        }
}

void table_lists::viewInvestimenti(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(5);
    setColumnWidth(0,200);
    setColumnWidth(1,200);
    setColumnWidth(2,200);
    setColumnWidth(3,200);
    setColumnWidth(4,200);
    setMaximumWidth(1200);
    tableHeader<<"Numero Investimento"<<"CC Collegato"<<"CF Cliente"<<"Durata"<<"Somma Investita";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void table_lists::viewContiCorrenti(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(5);
    setColumnWidth(0,200);
    setColumnWidth(1,200);
    setColumnWidth(2,200);
    setColumnWidth(3,200);
    setColumnWidth(4,200);
    setMaximumWidth(1200);
    tableHeader<<"Numero Conto"<<"Numero Cliente"<<"CF Cliente"<<"Nome"<<"Cognome";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void table_lists::viewAllCC(){
    int row=0;
        Prodotti* ListProdotti= listaprodotti->GetCCorrenti();
        Prodotti::Iteratore it=ListProdotti->it_begin();
        for(; it!=ListProdotti->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableCC(row,*it);
                row++;
            }
        }
}

void table_lists::viewAllInvestimenti(){
    int row=0;
        Prodotti* ListProdotti= listaprodotti->GetInvestimenti();
        Prodotti::Iteratore it=ListProdotti->it_begin();
        for(; it!=ListProdotti->it_end() ;it++){
            if(*it){
                setRowCount(row+1);
                addtableInv(row,*it);
                row++;
            }
        }
}

void table_lists::addtableCC(int row, Servizio* conto){
    Cont_corr* tmp=dynamic_cast<Cont_corr*>(conto);
    QTableWidgetItem* item= new QTableWidgetItem();
    item->setData(Qt::EditRole,tmp->GetNCC());
    setItem(row,0,item);
    QTableWidgetItem* item2= new QTableWidgetItem();
    item2->setData(Qt::EditRole,tmp->GetIntestatario()->GetNumeroIdentificativo());
    setItem(row,1,item2);
    setItem(row,2,new QTableWidgetItem(QString::fromStdString(tmp->GetIntestatario()->GetCF())));
    setItem(row,3,new QTableWidgetItem(QString::fromStdString(tmp->GetIntestatario()->GetNome())));
    setItem(row,4,new QTableWidgetItem(QString::fromStdString(tmp->GetIntestatario()->GetCognome())));
}

void table_lists::addtableInv(int row, Servizio* investimento){
    Investimento* tmp=dynamic_cast<Investimento*>(investimento);
    QTableWidgetItem* item= new QTableWidgetItem();
    item->setData(Qt::EditRole,tmp->GetNumeroInvestimento());
    setItem(row,0,item);
    QTableWidgetItem* item2= new QTableWidgetItem();
    item2->setData(Qt::EditRole,tmp->GetContoCollegato()->GetNCC());
    setItem(row,1,item2);
    setItem(row,2,new QTableWidgetItem(QString::fromStdString(tmp->GetIntestatario()->GetCF())));
    QTableWidgetItem* item3= new QTableWidgetItem();
    item3->setData(Qt::EditRole,tmp->GetDataFine());
    setItem(row,3,item3);
    QTableWidgetItem* item4= new QTableWidgetItem();
    item4->setData(Qt::EditRole,tmp->GetSommaInvestita());
    setItem(row,4,item4);
}

