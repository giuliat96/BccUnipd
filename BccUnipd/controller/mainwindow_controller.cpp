#include "mainwindow_controller.h"

MainWindowController::MainWindowController(QObject* parent) : QObject(parent){
    login=new LoginWindow();
    connect(login,SIGNAL(doLogin(string,string)),this,SLOT(doLoginController(string,string)));
    connect(login,SIGNAL(doRegister(string,string,string,string,string,QDate,string)),this,
            SLOT(doRegisterController(string,string,string,string,string,QDate,string)));
    login->show();
    mainWindow=nullptr;
    persone= new Soggetti();
    prodotti= new Prodotti();
}

MainWindowController::~MainWindowController(){
    delete persone;
    delete prodotti;
}


void MainWindowController::doLoginController(const string &username, const string &password){
    logged_user=const_cast<Operatore*>(persone->CheckLogin(username,password));
    if(!logged_user){
        QMessageBox::warning(0,"Errore login", "Credenziali errate, ritenta.");
        login->empty();
    }
    else{
        mainWindow = new MainWindow(logged_user,persone,prodotti);
        connect(mainWindow,SIGNAL(Logout()),this,SLOT(NuovaLogin()));
        login->close();
        login=nullptr;
        mainWindow->show();
        connect(mainWindow,SIGNAL(ModificaProfilo(Operatore*)),this,SLOT(ModificaProfilo(Operatore*)));
        connect(mainWindow,SIGNAL(addPersona()),this,SLOT(addPersona()));
        connect(mainWindow,SIGNAL(searchPersona()),this,SLOT(searchPersona()));
        connect(mainWindow,SIGNAL(gestionePersona(Persona*)),this,SLOT(gestionePersona(Persona*)));
        connect(mainWindow,SIGNAL(RimuoviPersona(Persona*)),this,SLOT(EliminaPersona(Persona*)));
        connect(mainWindow,SIGNAL(gestioneServizio(Servizio*)),this,SLOT(gestioneServizio(Servizio*)));
        connect(mainWindow,SIGNAL(ClickBonus()),this,SLOT(CalcolaBonus()));
        connect(mainWindow,SIGNAL(ClickStipendio()),this,SLOT(CalcolaStipendio()));
        connect(mainWindow,SIGNAL(ClickAttivazione()),this,SLOT(CalcolaAttivazione()));
        connect(mainWindow,SIGNAL(ClickFedelta()),this,SLOT(CalcolaSenior()));
    }
}

void MainWindowController::doRegisterController(const string &username, const string &password,const string &name,const string &surname,
                                                const string &cf, const QDate& date, const string& role){
    try{
        Operatore* newperson=new Dipendente(username,password,name,surname,cf,date,role);
        if(persone->AggiungiPersona(newperson,nullptr,prodotti)){
            QMessageBox::information(0,"Inserimento persona", "Inserimento avvenuto con successo!");
            login->empty();
        }
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::NuovaLogin(){
    if(!login)
        login=new LoginWindow();

    connect(login,SIGNAL(doLogin(string,string)),this,SLOT(doLoginController(string,string)));
    connect(login,SIGNAL(doRegister(string,string,string,string,string,QDate,string)),this,SLOT(doRegisterController(string,string,string,string,string,QDate,string)));

    login->empty();
    login->show();
}

void MainWindowController::aggiornaUtente(Operatore* utente,const string& Username,const string& Password,const string& Email,const string&Telefono){
   try{
        if(persone->CheckModifiche(utente)){
              utente->ModificaAccount(Username,Password,Email,Telefono);
              QMessageBox::information(0,"Operazione effettuata","Modifiche salvate correttamente");
              mainWindow->aggiornaPersone();
              viewModificaProfilo->close();
              viewModificaProfilo=nullptr;
        }
    }
    catch(string result){
    mainWindow->gestisciErrore(result);
    ModificaProfilo(utente);
    }
}

void MainWindowController::ModificaProfilo(Operatore* utente){
    viewModificaProfilo= new gestionePersone(utente,utente,persone,prodotti);
    viewModificaProfilo->ModifyProfile();
    connect(viewModificaProfilo,SIGNAL(modificaUtente(Operatore*,string,string,string,string)),this,SLOT(aggiornaUtente(Operatore*,string,string,string,string)));
    viewModificaProfilo->show();
}

void MainWindowController::modifica_dipendente(Persona* gestionepersona,const string& Email,
                                          const string& Telefono,const string& Ruolo,const string& TipoContratto,const QDate&InizioContratto,
                                          const QDate&FineContratto,unsigned int FamiliariACarico){
    try{
            Operatore* operatore=dynamic_cast<Operatore*>(gestionepersona);
            if(persone->CheckModifiche(operatore)){
            operatore->modificaOperatore(Email,Telefono,Ruolo,TipoContratto,InizioContratto,FineContratto,FamiliariACarico);
            QMessageBox::information(0,"Operazione effettuata","Modifiche salvate correttamente");
            mainWindow->aggiornaPersone();
            viewModifica->close();
            }
    }
    catch(string result){
    mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::modifica_cliente(Persona* gestionepersona,const string& Email,const string& Telefono,const bool& AppOnline){

    try{
            Ospite* ospite=dynamic_cast<Ospite*>(gestionepersona);
            if(persone->CheckModifiche(ospite)){
                ospite->modificaOspite(Email,Telefono,AppOnline);
                QMessageBox::information(0,"Operazione effettuata","Modifiche salvate correttamente");
                mainWindow->aggiornaPersone();
                viewModifica->close();
            }
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::Aggiungi_Operatore(const string& Username,const string& Password,const string& Name,const string& Surname,
                                            const string& CFiscale,const QDate& Data_Nascita,const string& Ruolo,
                                            const string& Email, const string& Telefono,
                                            const QDate& InizioContratto, const string& TipoContratto,const QDate& FineContratto,
                                            uint FamiliariACarico){
    try{
        Operatore* nuovooperatore= new Dipendente(Username,Password,Name,Surname,CFiscale,
                                                                 Data_Nascita,Ruolo,Email,Telefono,InizioContratto,TipoContratto,FineContratto,FamiliariACarico);
        if (persone->AggiungiPersona(nuovooperatore,logged_user,prodotti)) {
              QMessageBox::information(0,"Inserimento persona", "Inserimento avvenuto con successo!");
              mainWindow->aggiornaPersone();
              viewAddPersona->close();
              viewAddPersona=nullptr;
        }
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::Aggiungi_Ospite(const uint& Numeroidentificativo,const string& Name,const string& Surname,
                                            const string& CFiscale,const QDate& Data_Nascita,
                                            const string& Email, const string& Telefono,
                                            const QDate& InizioRapporto,const bool& Apponline){
    try{
        Ospite* nuovoospite= new Cliente(Name,Surname,CFiscale,Data_Nascita,Email,Telefono,InizioRapporto,Numeroidentificativo,Apponline);
        if (persone->AggiungiPersona(nuovoospite,logged_user,prodotti)) {
            QMessageBox::information(0,"Inserimento persona", "Inserimento avvenuto con successo!");
            mainWindow->aggiornaPersone();
            viewAddPersona->close();
            viewAddPersona=nullptr;
        }
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}


void MainWindowController::EliminaPersona(Persona* persona_rimuovere){
    if(persone->RimuoviPersona(persona_rimuovere,logged_user,prodotti)) {
        QMessageBox::information(0,"Eliminazione Avvenuta","Operazione avvenuta con successo");
        mainWindow->aggiornaPersone();
    }
    else QMessageBox::warning(0,"Attenzione","Impossibile rimuovere la persona perchè presenta servizi attivi");
}

void MainWindowController::addPersona(){
    viewAddPersona= new gestionePersone(nullptr,logged_user,persone,prodotti);
    if(logged_user->GestioneDipendenti()) {
        viewAddPersona->AggiungiDipendente();
        connect(viewAddPersona,SIGNAL(nuovo_operatore(const string&,const string&,const string&,const string&,
                             const string&,const QDate&,const string&,const string&,const string&,
                             const QDate&,const string&,const QDate&,unsigned int)),
                this,SLOT(Aggiungi_Operatore(const string&,const string&,const string&,const string&,
                                            const string&,const QDate&,const string&,const string&,const string&,
                                          const QDate&,const string&,const QDate&,unsigned int)));

    }
    else {
        viewAddPersona->AggiungiCliente();
        connect(viewAddPersona,SIGNAL(nuovo_ospite(uint,string,string,string,QDate,string,string,QDate,bool)),
                this,SLOT(Aggiungi_Ospite(uint,string,string,string,QDate,string,string,QDate,bool)));
    }
    viewAddPersona->show();
}


void MainWindowController::gestionePersona(Persona* modifyUser){
    viewModifica= new gestionePersone(modifyUser,logged_user,persone,prodotti);
    if(logged_user->GestioneDipendenti()){
        viewModifica->ModifyDipendente();
        connect(viewModifica,SIGNAL(modificaDipendente(Persona*,string,string,string,string,QDate,QDate,unsigned int)),
                this,SLOT(modifica_dipendente(Persona*,string,string,string,string,QDate,QDate,unsigned int)));
    }
    else {
        viewModifica->ModifyCliente();
        connect(viewModifica,SIGNAL(modificaCliente(Persona*,string,string,bool)),
            this,SLOT(modifica_cliente(Persona*,string,string,bool)));
        connect(viewModifica,SIGNAL(AddConto(uint,QDate,uint,double,uint)),this,SLOT(AddCC(uint,QDate,uint,double,uint)));
        connect(viewModifica,SIGNAL(AddInvest(uint,uint,QDate,QDate,uint,double,double,double)),
                this,SLOT(AddInv(uint,uint,QDate,QDate,uint,double,double,double)));
    }
    connect(viewModifica,SIGNAL(EliminaPersona(Persona*)),mainWindow,SLOT(removePersona(Persona*)));
    connect(viewModifica,SIGNAL(EliminaPersona(Persona*)),viewModifica,SLOT(close()));
    connect(viewModifica,SIGNAL(tableclient(Servizio*)),this,SLOT(gestioneServizio(Servizio*)));
    connect(viewModifica,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    viewModifica->show();
}

void MainWindowController::searchPersona(){
    viewModifica= new gestionePersone(nullptr,logged_user,persone,prodotti);
    viewModifica->SearchPersona();
    connect(viewModifica,SIGNAL(CercaPersona(string,string,string)),this,SLOT(CercaPersona(string,string,string)));
    connect(viewModifica,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    viewModifica->show();
}

void MainWindowController::CercaPersona(const string& CF,const string& Nome,const string& Cognome){

    try{
        if(CF=="" && Nome=="" && Cognome=="") QMessageBox::warning(0,"Attenzione", "Inserire CF oppure Nome e Cognome");
        else{
            if(CF=="") {
                Soggetti* soggetti=persone->CercaNS(logged_user,Nome,Cognome);
                if(soggetti){
                    viewModifica->close();
                    mainWindow->ShowTableSearch(logged_user,soggetti);
                }
                else QMessageBox::warning(0,"Attenzione","Nessuna persona trovata");
            }
            else{
                Persona* persona=nullptr;
                persona=persone->CercaCF(logged_user,CF);

                if(!persona) QMessageBox::warning(0,"Attenzione","Nessuna persona trovata");
                else {
                    viewModifica->close();
                    if(logged_user==persona) ModificaProfilo(logged_user);
                    else gestionePersona(persona);
                }
            }
        }
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::CalcolaBonus(){
    string bottone="bonus";
    CalcolaOperazione(bottone);
}

void MainWindowController::CalcolaStipendio(){
    string bottone="stipendio";
    CalcolaOperazione(bottone);
}

void MainWindowController::CalcolaOperazione(const string& pulsante){
    viewModifica= new gestionePersone(nullptr,logged_user,persone,prodotti);
    viewModifica->SearchForOperation(pulsante);
    connect(viewModifica,SIGNAL(CF(const string&,const string&)),this,SLOT(SetformOperazione(const string &,const string &)));
    connect(viewModifica,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    viewModifica->show();
}

void MainWindowController::SetformOperazione(const string& CF, const string & bottonepremuto){
    if(CF=="") QMessageBox::warning(0,"Attenzione","Inserire CF");
    else{
        Persona* persona=nullptr;
        persona=persone->CercaCF(logged_user,CF);

        if(!persona) QMessageBox::warning(0,"Attenzione","Nessuna persona trovata");
        else {
            viewModifica->close();
          if(logged_user==persona) ModificaProfilo(logged_user);
            else gestionePersona(persona);
          viewOperazione=new gestionePersone(nullptr,logged_user,persone,prodotti);
          viewOperazione->FormOperazione();
          if(bottonepremuto=="stipendio"){
              Operatore* tmp=dynamic_cast<Operatore*>(persona);
              viewOperazione->setResult(tmp->GetStipendio());
          }
          else if(bottonepremuto=="bonus"){
              Ospite* tmp=dynamic_cast<Ospite*>(persona);
              viewOperazione->setResult(tmp->BonusAnnuo());
          }
          viewOperazione->show();
        }
    }
}

void MainWindowController::CalcolaSenior(){
    Soggetti* senior=persone->Senior(logged_user);
    mainWindow->AggiornaSenior(senior);
}

//.......................SERVIZI..............................

void MainWindowController::AddCC(const uint& int1,const QDate& dataapertura,const uint& numerocc,const double& interessi,const uint& int2){
    try{
            Cont_corr* newcc=new Cont_corr(persone->GetOspite(int1),numerocc,persone->GetOspite(int2),dataapertura,interessi);
            prodotti->addServizio(newcc);
            QMessageBox::information(0,"Operazione Effettuata","Inserimento avvenuto con successo");
            Cont_corr::NumeroCC++;
            viewModifica->AggiornaCC();
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::AddInv(const uint& numeroinv,const uint& int1,const QDate& dataapertura,const QDate& datafine,
               const uint& ccollegato,const double& intbanca,const double& intcliente,const double& sommainv){

    try{
        Investimento* newinv=new Investimento(numeroinv,prodotti->GetConto(ccollegato),datafine,persone->GetOspite(int1),dataapertura,intbanca,intcliente,sommainv);
        prodotti->addServizio(newinv);
        QMessageBox::information(0,"Operazione Effettuata","Inserimento avvenuto con successo");
        Investimento::NumeroInvestimenti++;
        viewModifica->AggiornaInv();
    }
    catch(string result){
        mainWindow->gestisciErrore(result);
    }
}

void MainWindowController::gestioneServizio(Servizio* modifyServizio){
    viewModificaServizio= new gestionePersone(modifyServizio->GetIntestatario(),logged_user,persone,prodotti);
    Cont_corr* tmp=dynamic_cast<Cont_corr*>(modifyServizio);
    if(tmp){
        viewModificaServizio->ModifyCC(tmp);
    }
    else{
        Investimento* tmp2=dynamic_cast<Investimento*>(modifyServizio);
        viewModificaServizio->ModifyInvest(tmp2);
    }
    connect(viewModificaServizio,SIGNAL(EliminaServizio(Servizio*)),this,SLOT(EliminaServizio(Servizio*)));
    viewModificaServizio->show();
}

void MainWindowController::EliminaServizio(Servizio* servizio){
   if(dynamic_cast<Cont_corr*>(servizio)){
       if(prodotti->RimuoviServizio(servizio)){
           QMessageBox::information(0,"Operazione avvenuta","Conto eliminato correttamente");
           mainWindow->CC();
           if(viewModifica) viewModifica->AggiornaCC();
       }
       else QMessageBox::warning(0,"Attenzione","Impossibile eliminare il conto perchè collegato ad investimenti ancora attivi");
      }
   else{
       if(prodotti->RimuoviServizio(servizio)){
           QMessageBox::information(0,"Operazione avvenuta","Investimento eliminato correttamente");
           mainWindow->Invest();
           if(viewModifica) viewModifica->AggiornaInv();
       }
       else QMessageBox::warning(0,"Attenzione","Impossibile eliminare l'investimento perchè non è ancora stata raggiunta la data di fine");
      }
}

void MainWindowController::CalcolaAttivazione(){
    viewModifica= new gestionePersone(nullptr,logged_user,persone,prodotti);
    viewModifica->ServiceForOperation();
    connect(viewModifica,SIGNAL(CercaCC(const uint&,const string&)),this,SLOT(SetformServizio(const uint&,const string&)));
    connect(viewModifica,SIGNAL(CercaInv(const uint&,const string&)),this,SLOT(SetformServizio(const uint&,const string&)));
    connect(viewModifica,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
    viewModifica->show();
}

void MainWindowController::SetformServizio(const uint& numeroservizio, const string & bottonepremuto){
    if(numeroservizio==0) QMessageBox::warning(0,"Attenzione","Inserire il numero del conto o dell'investimento cercato");
    else{
        Servizio* servizio=nullptr;

        if(bottonepremuto=="cc"){
            servizio=prodotti->GetConto(numeroservizio);
        }
        else{
            servizio=prodotti->GetInvest(numeroservizio);
        }

        if(!servizio) QMessageBox::warning(0,"Attenzione","Nessuna servizio trovato");
        else {
          viewModifica->close();
          viewModificaServizio=new gestionePersone(nullptr,logged_user,persone,prodotti);
          viewOperazione=new gestionePersone(nullptr,logged_user,persone,prodotti);
          viewOperazione->FormOperazione();
          if(bottonepremuto=="cc"){
              Cont_corr* tmp=dynamic_cast<Cont_corr*>(servizio);
              viewModificaServizio->ModifyCC(tmp);
          }
          else {
              Investimento* tmp=dynamic_cast<Investimento*>(servizio);
              viewModificaServizio->ModifyInvest(tmp);
          }
          connect(viewModificaServizio,SIGNAL(EliminaServizio(Servizio*)),this,SLOT(EliminaServizio(Servizio*)));
          viewModificaServizio->show();
          viewOperazione->setResult(servizio->GetCostoAttivazione());
          viewOperazione->show();
        }
    }
}

void MainWindowController::closeWindow(){
    viewModifica=nullptr;
}

