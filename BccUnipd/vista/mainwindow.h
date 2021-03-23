#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include "table_lists.h"
#include "gestionepersone.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Operatore* utente;
    Soggetti* soggetti;
    Prodotti* prestazioni;

    QMenu* opzioni;
    QMenu* menu; 
    QAction* modifyProfile;
    QAction* menuLogout;
    QAction* addmenu;
    QAction* modifymenu;


    QWidget* finestraOperatore;
    QLabel * labelUsernameInfo;
    QLabel * labelPasswordInfo;
    QLabel * labelNameInfo;
    QLabel * labelSurnameInfo;
    QLineEdit * textUsernameInfo;
    QLineEdit * textPasswordInfo;
    QLineEdit * textNameInfo;
    QLineEdit * textSurnameInfo;
    QPushButton * pushLogout;
    QFormLayout * formInfo;

    QHBoxLayout * Upmainwindow;
    QVBoxLayout * totalLayout;
    QGroupBox * info;
    QGroupBox* MetodiGroupBox;
    QGridLayout *metodi;
    QPushButton * pushStipendio;
    QPushButton * pushBonus;
    QPushButton * pushCC;
    QPushButton * pushInv;
    QPushButton * pushCCPersone;
    QPushButton * pushInvPersone;
    QPushButton * pushOperatori;
    QPushButton * pushOspiti;
    QPushButton * pushSportello;
    QPushButton * pushPersonale;
    QPushButton * pushAttivazione;
    QPushButton * pushFidelizzazione;

    table_lists * table;
    QGridLayout * gridTable;
    QVBoxLayout* Downmainwindow;



private slots:
    void Info();

public slots:
    void closeMainWindow();
    void modificaProfilo();
    void clicktabella(int,int);
    void Persone();
    void Sportello();
    void Personale();
    void CC();
    void Invest();
    void Investitori();
    void removePersona(Persona*);

public:
    MainWindow(Operatore* ,Soggetti*,Prodotti*,QWidget *parent = 0);
    void OpzioniMenu();
    void layoutOperatoreWindow();
    void aggiornaPersone();
   void ShowTableSearch(Operatore*,Soggetti*);
   QGroupBox* MetodiDipendenti();
   QGroupBox* MetodiClienti();
   void AggiornaSenior(Soggetti*);
   void gestisciErrore(string)const;

signals:
    void Logout();
    void ModificaProfilo(Operatore*);
    void nuovo_operatore(const string&,const string&,const string&,const string&,
                             const string&,const QDate&,const string&,const string&,const string&,
                             const QDate&,const string&,const QDate&,unsigned int,const bool&);
    void modifica_dipendente(Persona*,string,string,string,string,QDate,QDate,unsigned int);
    void RimuoviPersona(Persona*);
    void addPersona();
    void searchPersona();
    void gestionePersona(Persona*);
    void gestioneServizio(Servizio*);
    void RimuoviServizio(Servizio*);
    void ClickStipendio();
    void ClickBonus();
    void ClickAttivazione();
    void ClickFedelta();

};

#endif // MAINWINDOW_H
