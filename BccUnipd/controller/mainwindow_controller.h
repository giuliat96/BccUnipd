#ifndef MAINWINDOW_CONTROLLER_H
#define MAINWINDOW_CONTROLLER_H

#include "../vista/login_window.h"
#include "../vista/mainwindow.h"
#include <QObject>
#include <QMessageBox>

class MainWindowController:public QObject{

     Q_OBJECT

private:

    Soggetti* persone;
    Prodotti* prodotti;
    LoginWindow* login;
    MainWindow* mainWindow;
    gestionePersone* viewModificaProfilo;
    gestionePersone* viewModifica;
    gestionePersone* viewModificaServizio;
    gestionePersone* viewAddPersona;
    gestionePersone* viewOperazione;

    Operatore* logged_user;



public:
    MainWindowController(QObject* =0);
    ~MainWindowController();
    void CalcolaOperazione(const string&);

public slots:
    void doLoginController(const string &, const string &);
    void doRegisterController(const string &,const string &,const string &, const string &,
                              const string &,const QDate&,const string&);
    void NuovaLogin();
    void aggiornaUtente(Operatore* ,const string& ,const string& ,const string& ,const string&);
    void ModificaProfilo(Operatore*);
    void modifica_dipendente(Persona*,const string&,const string&,const string&,const string&,const QDate&,const QDate&,unsigned int);
    void modifica_cliente(Persona*,const string&,const string&,const bool&);
    void Aggiungi_Operatore(const string& ,const string& ,const string&,const string&,const string&,const QDate&,const string&,
                           const string&, const string&,const QDate&, const string&,const QDate&,uint);
    void Aggiungi_Ospite(const uint&,const string& ,const string& ,const string&,const QDate&,const string& , const string&,
                            const QDate& ,const bool&);
    void EliminaPersona(Persona*);
    void addPersona();
    void searchPersona();
    void gestionePersona(Persona*);
    void gestioneServizio(Servizio*);
    void CercaPersona(const string&,const string&,const string&);
    void AddCC(const uint&,const QDate&,const uint&,const double&,const uint& = 0);
    void AddInv(const uint&,const uint&,const QDate&,const QDate&,const uint&,const double&,
                   const double&,const double&);
    void EliminaServizio(Servizio*);
    void CalcolaBonus();
    void CalcolaStipendio();
    void SetformOperazione(const string &,const string&);
    void CalcolaAttivazione();
    void SetformServizio(const uint&,const string&);
    void CalcolaSenior();
    void closeWindow();

signals:
    void Operazione();

};


#endif // MAINWINDOW_CONTROLLER_H
