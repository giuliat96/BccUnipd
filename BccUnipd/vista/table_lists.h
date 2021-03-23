#ifndef TABLE_LISTS_H
#define TABLE_LISTS_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include "../modello/soggetti.h"
#include "../modello/prodotti.h"

class table_lists : public QTableWidget
{

private:
    Soggetti* listapersone;
    Prodotti* listaprodotti;

public:
    table_lists(Soggetti*,Prodotti*, QWidget* =0);

    void viewOperatori();
    void viewOspiti();
    void viewAllOperatori();
    void viewAllSportello();
    void viewAllPersonale();
    void viewAllOspiti();
    void viewAllInvestitori();
    void addtableOperatore(int , Persona* );
    void addtableOspite(int , Persona* );

    void viewContiCorrenti();
    void viewInvestimenti();
    void viewAllCC();
    void viewAllInvestimenti();
    void viewCCPersona(Ospite*);
    void viewInvPersona(Ospite*);
    void addtableCC(int , Servizio* );
    void addtableInv(int , Servizio* );
    void viewSoggetti(Soggetti*,Operatore*);
    void tableSearch(Operatore*,Soggetti*);
};

#endif // TABLE_LISTS_H
