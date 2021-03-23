#ifndef GESTIONEPERSONE_H
#define GESTIONEPERSONE_H

#include <QtWidgets>
#include <QLineEdit>
#include <QGridLayout>
#include <QRegExpValidator>
#include "../modello/dipendente.h"
#include "../modello/ospite.h"
#include "../modello/soggetti.h"
#include "table_lists.h"

class gestionePersone :public QDialog
{
    Q_OBJECT
    Persona* personagestita;
    Operatore* loggato;
    Soggetti* personetotali;
    Prodotti* prestazioni;

    QLabel* labelUsername;
    QLabel* labelPassword;
    QLabel* labelName;
    QLabel* labelSurname;
    QLabel* labelCF;
    QLabel* labelData_Nascita;
    QLabel* labelEmail;
    QLabel* labelTelefono;
    QLabel* labelRuolo;
    QLabel* labelTipoContratto;
    QLabel* labelInizioContratto;
    QLabel* labelFineContratto;
    QLabel* labelFamiliariACarico;
    QLabel* labelIntestatario1;
    QLabel* labelIntestatario2;
    QLabel* labelDataApertura;
    QLabel* labelInteressi;
    QLabel* labelNumeroCC;
    QLabel* labelNumeroInvestimento;
    QLabel* labelDataFine;
    QLabel* labelInteressibanca;
    QLabel* labelInteressicliente;
    QLabel* labelSommainv;

    QLineEdit* textUsername;
    QLineEdit* textPassword;
    QLineEdit* textName;
    QLineEdit* textSurname;
    QLineEdit* textCF;
    QDateEdit* textData_Nascita;
    QLineEdit* textEmail;
    QLineEdit* textTelefono;
    QLineEdit* textRuolo;
    QLineEdit* textTipoContratto;
    QDateEdit* textInizioContratto;
    QDateEdit* textFineContratto;
    QLineEdit* textFamiliariACarico;
    QLineEdit* textIntestatario1;
    QLineEdit* textIntestatario2;
    QDateEdit* textDataApertura;
    QLineEdit* textNumeroCC;
    QLineEdit* textInteressi;
    QLineEdit* textNumeroInvestimento;
    QDateEdit* textDataFine;
    QLineEdit* textInteressibanca;
    QLineEdit* textInteressicliente;
    QLineEdit* textSommainv;
    QLineEdit* risultato;

    QLabel* labelNumeroIdentificativo;
    QLabel* labelDataInizioRapporto;
    QCheckBox* checkAppOnline;

    QLineEdit* textNumeroIdentificativo;
    QDateEdit* textDataInizioRapporto;

    QPushButton *pushSalva;
    QPushButton *pushElimina;
    QPushButton *pushAddCC;
    QPushButton *pushAddInv;
    QPushButton *pushCercaCF;
    QPushButton *pushCercaNS;
    QPushButton *pushCercaCC;
    QPushButton *pushCercaInv;

    table_lists* table;
    table_lists * tablecc;
    table_lists * tableccinv;
    table_lists * tableinv;
    table_lists * tableoscc;
    QGridLayout* gridTable;

    QFormLayout *layoutFinal;
    QHBoxLayout *layoutModificaProfilo;
    QFormLayout *formModificaProfilo;
    QHBoxLayout *totalLayout;
    QVBoxLayout *layoutSearch;
    QFormLayout *formCF;
    QFormLayout *formNS;
    QFormLayout *formCC;
    QFormLayout *formInv;
    QFormLayout *formServizio;
    QHBoxLayout * layoutAddServizio;

    QGroupBox* cercaCF;
    QGroupBox* cercaNS;
    QGroupBox* cercaCC;
    QGroupBox* cercaInv;

    int numerocc;
    string botton;

public:
    gestionePersone(Persona*,Operatore*,Soggetti*,Prodotti*);
    void infoPersona();
    void infoOperatore();
    void infoOspite();
    void setForm();
    void ModifyProfile();
    void ModifyDipendente();
    void ModifyCliente();
    void FormOperazione();
    void AggiungiDipendente();
    void AggiungiCliente();
    void SearchPersona();
    void infoCC();
    void infoInv();
    void AggiornaCC();
    void AggiornaInv();
    void ModifyCC(Cont_corr*);
    void ModifyInvest(Investimento*);
    void setResult(double);
    void SearchForOperation(const string&);
    void ServiceForOperation();

public slots:
    void inviaModifiche();
    void NuovaPersona();
    void Eliminazione();
    void cercaPersona();
    void AddCC();
    void AddInv();
    void NuovoCC();
    void NuovoInv();
    void setNumeroCC(int,int);
    void setIntestatario2(int,int);
    void EliminazioneCC();
    void EliminazioneInv();
    void clickTablecc(int,int);
    void clickTableinv(int,int);
    void CercaCF();
    void trovaCC();
    void trovaInv();
    void closeEvent(QCloseEvent*);


signals:
    void modificaUtente(Operatore*,const string&,const string&,const string&,const string&);
    void modificaDipendente(Persona*,const string&,const string&,
                            const string&,const string&,const QDate&,const QDate&,unsigned int);
    void modificaCliente(Persona*,const string&,const string&,const bool&);
    void nuovo_operatore(const string&,const string&,const string&,const string&,
                         const string&,const QDate&,const string&,const string&,const string&,
                         const QDate&,const string&,const QDate&,unsigned int);
    void nuovo_ospite(unsigned int, const string&,const string&,const string&,const QDate&,const string&,
                      const string&,const QDate&,const bool&);
    void EliminaPersona(Persona*);
    void CercaPersona(const string&,const string&,const string&);
    void AddConto(const uint&,const QDate&,const uint&,const double&,const uint&);
    void AddInvest(const uint&,const uint&,const QDate&,const QDate&,const uint&,const double&,
                   const double&,const double&);
    void EliminaServizio(Servizio*);
    void CF(const string&,const string&);
    void CercaCC(const uint&,const string&);
    void CercaInv(const uint&,const string&);
    void tableclient(Servizio*);
    void closeWindow();
};

#endif // GESTIONEPERSONE_H
