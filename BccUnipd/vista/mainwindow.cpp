#include "mainwindow.h"

MainWindow::MainWindow(Operatore* log,Soggetti* persone,Prodotti* prodotti ,QWidget *parent) :
    QMainWindow(parent),utente(log),soggetti(persone),prestazioni(prodotti){
    this->setAttribute(Qt::WA_DeleteOnClose);
        setWindowTitle("Bcc Unipd");

        setFixedHeight(700);
        setFixedWidth(1000);

        OpzioniMenu();
        layoutOperatoreWindow();

}

void MainWindow::Info(){
    QMessageBox info;
    info.setWindowFlags(Qt::WindowTitleHint);
    info.setWindowTitle("Informazioni sul programma");
    info.setText("Il programma permette di gestire informazioni riguardo dipendenti e clienti della banca");
    info.exec();
}

void MainWindow::OpzioniMenu(){
    opzioni= new QMenu("Profilo",this);
    modifyProfile= new QAction("Modifica Profilo",this);
    menuLogout= new QAction("Log Out",this);
    opzioni->addAction(modifyProfile);
    opzioni->addAction(menuLogout);

    connect(modifyProfile,SIGNAL(triggered(bool)),this,SLOT(modificaProfilo()));
    connect(menuLogout,SIGNAL(triggered(bool)),this,SLOT(closeMainWindow()));

    menuBar()->addMenu(opzioni);

    menu=new QMenu();
    addmenu=new QAction("Aggiungi nuovo");
    modifymenu=new QAction("Cerca");

    menu->addAction(addmenu);
    menu->addAction(modifymenu);

    menuBar()->addMenu(menu);

    if(utente->GestioneDipendenti()){
        menu->setTitle("Dipendenti");
        connect(addmenu,SIGNAL(triggered(bool)),this,SIGNAL(addPersona()));
    }
    else {
        menu->setTitle("Clienti");
        connect(addmenu,SIGNAL(triggered(bool)),this,SIGNAL(addPersona()));
    }

    connect(modifymenu,SIGNAL(triggered(bool)),this,SIGNAL(searchPersona()));
}

void MainWindow::layoutOperatoreWindow(){

    finestraOperatore = new QWidget(this);
    setStyleSheet("QGroupBox{ border: 1px solid gray;  margin-top: 5px;}"
                          "QGroupBox::title{ subcontrol-origin: margin; subcontrol-position:top center;}");
    table=nullptr;

    labelUsernameInfo=new QLabel("Username:");
    labelPasswordInfo=new QLabel("Password:");
    labelNameInfo=new QLabel("Name:");
    labelSurnameInfo=new QLabel("Surname:");
    textUsernameInfo=new QLineEdit();
    textUsernameInfo->setText(QString::fromStdString(utente->GetUsername()));
    textUsernameInfo->setReadOnly(true);
    textPasswordInfo=new QLineEdit();
    textPasswordInfo->setText(QString::fromStdString(utente->GetPassword()));
    textPasswordInfo->setReadOnly(true);
    textNameInfo=new QLineEdit();
    textNameInfo->setText(QString::fromStdString(utente->GetNome()));
    textNameInfo->setReadOnly(true);
    textSurnameInfo=new QLineEdit();
    textSurnameInfo->setText(QString::fromStdString(utente->GetCognome()));
    textSurnameInfo->setReadOnly(true);
    pushLogout=new QPushButton("Logout");

    formInfo=new QFormLayout();
    formInfo->addRow(labelUsernameInfo,textUsernameInfo);

    formInfo->addRow(labelPasswordInfo,textPasswordInfo);
    formInfo->addRow(labelNameInfo,textNameInfo);
    formInfo->addRow(labelSurnameInfo,textSurnameInfo);
    formInfo->addRow(pushLogout);

    info= new QGroupBox(tr("Informazioni Utente"));
    info->setFixedWidth(250);
    info->setFixedHeight(250);

    Upmainwindow=new QHBoxLayout();
    Upmainwindow->addWidget(info);
    info->setLayout(formInfo);
    connect(pushLogout,SIGNAL(clicked()),this,SLOT(closeMainWindow()));

    table= new table_lists(soggetti,prestazioni,this);
    table->setMaximumHeight(400);
    table->setMaximumWidth(950);
    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(clicktabella(int,int)));

    gridTable = new QGridLayout();
    gridTable->addWidget(table);

    if(utente->GestioneDipendenti()){
        table->viewOperatori();
        table->viewAllOperatori();
    }
    else{
        table->viewOspiti();
        table->viewAllOspiti();
    }
    table->show();

    if(utente->GestioneDipendenti()){
        Upmainwindow->addWidget(MetodiDipendenti());
    }
    else Upmainwindow->addWidget(MetodiClienti());

    Downmainwindow = new QVBoxLayout();
    Downmainwindow->addLayout(gridTable);
    Downmainwindow->setAlignment(Qt::AlignHCenter);

    totalLayout= new QVBoxLayout();
    totalLayout->addLayout(Upmainwindow);
    totalLayout->addLayout(Downmainwindow);
    finestraOperatore->setLayout(totalLayout);

    this->setCentralWidget(finestraOperatore);
}

QGroupBox* MainWindow::MetodiDipendenti(){
    MetodiGroupBox = new QGroupBox(tr("Operazioni Disponibili"));
    MetodiGroupBox->setFixedHeight(250);
    QGridLayout *metodi = new QGridLayout;
    pushStipendio= new QPushButton("Calcola Stipendio");
    pushOperatori=new QPushButton("Tutti Dipendenti");
    pushSportello=new QPushButton("Dipendenti Sportello");
    pushPersonale=new QPushButton("Dipendenti U.Personale");
    pushFidelizzazione=new QPushButton("Dipendenti Senior");

    metodi->addWidget(pushOperatori,0,0);
    metodi->addWidget(pushSportello,0,1);
    metodi->addWidget(pushPersonale,0,2);
    metodi->addWidget(pushStipendio,1,0);
    metodi->addWidget(pushFidelizzazione,1,1);
    MetodiGroupBox->setLayout(metodi);

    connect(pushStipendio,SIGNAL(clicked(bool)),this,SIGNAL(ClickStipendio()));
    connect(pushOperatori,SIGNAL(clicked(bool)),this,SLOT(Persone()));
    connect(pushSportello,SIGNAL(clicked(bool)),this,SLOT(Sportello()));
    connect(pushPersonale,SIGNAL(clicked(bool)),this,SLOT(Personale()));
    connect(pushFidelizzazione,SIGNAL(clicked(bool)),this,SIGNAL(ClickFedelta()));

    return MetodiGroupBox;
}

QGroupBox* MainWindow::MetodiClienti(){
    MetodiGroupBox = new QGroupBox(tr("Operazioni Disponibili"));
    MetodiGroupBox->setFixedHeight(250);
    QGridLayout* metodi= new QGridLayout;
    pushBonus= new QPushButton("Calcola Bonus Annuo");
    pushCC=new QPushButton("Conti Correnti");
    pushInv=new QPushButton("Investimenti");
    pushInvPersone=new QPushButton("Visualizza Investitori");
    pushOspiti=new QPushButton("Visualizza Clienti");
    pushAttivazione=new QPushButton("Calcola Costo Attivazione");
    pushFidelizzazione=new QPushButton("Clienti Senior");

    metodi->addWidget(pushCC,0,0);
    metodi->addWidget(pushInv,0,1);
    metodi->addWidget(pushInvPersone,0,2);
    metodi->addWidget(pushOspiti,1,0);
    metodi->addWidget(pushBonus,1,1);
    metodi->addWidget(pushAttivazione,1,2);
    metodi->addWidget(pushFidelizzazione,2,0);
    MetodiGroupBox->setLayout(metodi);

    connect(pushBonus,SIGNAL(clicked(bool)),this,SIGNAL(ClickBonus()));
    connect(pushCC,SIGNAL(clicked(bool)),this,SLOT(CC()));
    connect(pushInv,SIGNAL(clicked(bool)),this,SLOT(Invest()));
    connect(pushInvPersone,SIGNAL(clicked(bool)),this,SLOT(Investitori()));
    connect(pushOspiti,SIGNAL(clicked(bool)),this,SLOT(Persone()));
    connect(pushAttivazione,SIGNAL(clicked(bool)),this,SIGNAL(ClickAttivazione()));
    connect(pushFidelizzazione,SIGNAL(clicked(bool)),this,SIGNAL(ClickFedelta()));

     return MetodiGroupBox;
}

void MainWindow::modificaProfilo(){
    emit ModificaProfilo(utente);
}

void MainWindow::Persone(){
    aggiornaPersone();
}

void MainWindow::Sportello(){
    table->viewOperatori();
    table->viewAllSportello();
}

void MainWindow::Personale(){
    table->viewOperatori();
    table->viewAllPersonale();
}

void MainWindow::CC(){
    table->viewContiCorrenti();
    table->viewAllCC();
}

void MainWindow::Invest(){
    table->viewInvestimenti();
    table->viewAllInvestimenti();
}

void MainWindow::Investitori(){
    table->viewOspiti();
    table->viewAllInvestitori();
}

void MainWindow::AggiornaSenior(Soggetti* senior){
    if(utente->GestioneDipendenti()){
        table->viewOperatori();
    }
    else{
        table->viewOspiti();
    }
    table->viewSoggetti(senior,utente);
}

void MainWindow::aggiornaPersone(){
    textUsernameInfo->setText(QString::fromStdString(utente->GetUsername()));
    textPasswordInfo->setText(QString::fromStdString(utente->GetPassword()));

    if(utente->GestioneDipendenti()){
        table->viewOperatori();
        table->viewAllOperatori();
    }
    else{
        table->viewOspiti();
        table->viewAllOspiti();
    }

    table->show();
}

void MainWindow::ShowTableSearch(Operatore* utente,Soggetti* trovati){
    table->tableSearch(utente,trovati);
    table->show();
}

void MainWindow::clicktabella(int row, int column){
    column=0;
    if(table->horizontalHeaderItem(0)->text()=="Username"){
        Operatore* modifyUser=soggetti->GetOperatore((table->item(row,column))->text().toStdString());
        if(modifyUser==utente) modificaProfilo();
        else {
            emit gestionePersona(modifyUser);
        }
    }
    else if(table->horizontalHeaderItem(0)->text()=="Numero Cliente"){
        Ospite* modifyUser=soggetti->GetOspite((table->item(row,column))->text().toUInt());
        dipendente_cliente* tmp=dynamic_cast<dipendente_cliente*>(utente);
        if(tmp && modifyUser==tmp) modificaProfilo();
        else{
            emit gestionePersona(modifyUser);
        }
    }
    else if(table->horizontalHeaderItem(0)->text()=="Numero Conto"){
        Cont_corr* modifyServizio=prestazioni->GetConto((table->item(row,column))->text().toUInt());
        emit gestioneServizio(modifyServizio);
    }
    else {
        Investimento* modifyServizio=prestazioni->GetInvest((table->item(row,column))->text().toUInt());
        emit gestioneServizio(modifyServizio);
    }
}

void MainWindow::closeMainWindow(){
    emit Logout();
    this->close();
}

void MainWindow::removePersona(Persona* persona_rimuovere){
    QMessageBox::StandardButton replay;
    replay= QMessageBox::question(this,"Eliminazione Persona", "Vuoi procedere con l'eliminazione della persona?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (replay==QMessageBox::Yes) emit RimuoviPersona(persona_rimuovere);
}

void MainWindow::gestisciErrore(string errore) const{
    if(errore=="NO_CF") QMessageBox::warning(0,"Attenzione", "Codice Fiscale già presente associato ad altra persona");
    else if(errore=="NO_US") QMessageBox::warning(0,"Attenzione", "Username già in uso");
    else if(errore=="NO_AUTO") QMessageBox::warning(0,"Attenzione", "Non è possibile inserirsi come cliente");
    else if(errore=="NO_NUM") QMessageBox::warning(0,"Attenzione", "Numero identificativo già in uso");
    else if(errore=="ERR_CF") QMessageBox::warning(0,"Attenzione", "Codice fiscale errato");
    else if(errore=="ERR_CERCANS") QMessageBox::warning(0,"Attenzione", "Inserire Nome e Cognome");
    else if(errore=="PW_LENGHT") QMessageBox::warning(0,"Attenzione", "La password deve avere almeno 6 caratteri");
    else if(errore=="ALL_DATAP") QMessageBox::warning(0,"Attenzione", "Completare i campi Nome, Cognome, Codice Fiscale, Data Nascita");
    else if(errore=="ALL_DATAUT") QMessageBox::warning(0,"Attenzione", "Completare i campi Username, Password");
    else if(errore=="RUOLO") QMessageBox::warning(0,"Attenzione", "Inserire il ruolo");
    else if(errore=="ERR_TELL") QMessageBox::warning(0,"Attenzione", "Numero di telefono errato");
    else if(errore=="ERR_CONTR") QMessageBox::warning(0,"Attenzione", "Data di fine contratto precedente alla data di inizio");
    else if(errore=="ERR_EMAIL") QMessageBox::warning(0,"Attenzione","Email non corretta");
    else if(errore=="ERR_RUOLO") QMessageBox::warning(0,"Attenzione","Ruolo non valido");
    else if(errore=="ERR_COINT") QMessageBox::warning(0,"Attenzione","Co-intestatario inserito uguale all'Intestatario");
    else if(errore=="ERR_DATE") QMessageBox::warning(0,"Attenzione","La data di fine investimento precede la data di apertura");
    else if(errore=="ALL_DATAIN") QMessageBox::warning(0,"Attenzione","E' necessario inserire un conto corrente collegato");
    else if(errore=="ERR_DATA")  QMessageBox::warning(0,"Attenzione","La data di inizio non può essere successiva alla data odierna");
}
