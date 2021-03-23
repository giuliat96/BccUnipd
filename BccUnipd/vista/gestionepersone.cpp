#include "gestionepersone.h"

gestionePersone::gestionePersone(Persona* persona,Operatore* utente,Soggetti* persone,Prodotti* prodotti):
    personagestita(persona),loggato(utente),personetotali(persone),prestazioni(prodotti)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
}

//..................PERSONE......................

void gestionePersone::infoPersona(){
    setWindowTitle("Informazioni Utente");
    labelName= new QLabel("Nome:");
    labelSurname=  new QLabel("Cognome:");
    labelCF= new QLabel("Codice Fiscale:");
    labelData_Nascita= new QLabel("Data di nascita:");
    labelEmail= new QLabel("Email:");
    labelTelefono= new QLabel("Telefono:");


    textName=new QLineEdit();
    textName->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z]{1,20}$")));
    textSurname=new QLineEdit();
    textSurname->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z]{1,20}$")));
    textTelefono=new QLineEdit();
    textTelefono->setValidator(new QRegExpValidator(QRegExp("^[0-9]{9}|[0-9]{10}$")));
    textCF=new QLineEdit();
    textCF->setValidator(new QRegExpValidator(QRegExp("^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$")));
    textData_Nascita=new QDateEdit();
    textEmail=new QLineEdit();
    textEmail->setValidator(new QRegExpValidator(QRegExp("\\b[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}\\b")));


}

void gestionePersone::infoOperatore(){
    labelUsername= new QLabel("Username:");
    labelPassword=new QLabel("Password:");
    labelRuolo= new QLabel("Ruolo:");
    labelTipoContratto= new QLabel("Tipo contratto:");
    labelInizioContratto= new QLabel("Data inizio contratto:");
    labelFineContratto= new QLabel("Data fine contratto:");
    labelFamiliariACarico= new QLabel("Numero familiari a carico:");

    textUsername=new QLineEdit();
    textUsername->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]{1,15}$")));
    textPassword=new QLineEdit();
    textPassword->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]{1,15}$")));
    textRuolo=new QLineEdit();
    textTipoContratto=new QLineEdit();
    textInizioContratto=new QDateEdit();
    textFineContratto=new QDateEdit();
    textFamiliariACarico=new QLineEdit();
    textFamiliariACarico->setValidator(new QRegExpValidator(QRegExp("^[0-9]*$")));

}

void gestionePersone::infoOspite(){

    labelNumeroIdentificativo= new QLabel("Numero Identificativo:");
    labelDataInizioRapporto= new QLabel("Data Inizio Rapporto:");
    checkAppOnline= new QCheckBox("Utilizza l'App");

    textNumeroIdentificativo=new QLineEdit();
    textDataInizioRapporto=new QDateEdit();

}

void gestionePersone::setForm(){

    formModificaProfilo=new QFormLayout();
    layoutModificaProfilo=new QHBoxLayout();
    layoutModificaProfilo->addLayout(formModificaProfilo);
    setLayout(layoutModificaProfilo);

    if(loggato->GestioneDipendenti() || personagestita==loggato){
        formModificaProfilo->addRow(labelUsername,textUsername);
        formModificaProfilo->addRow(labelPassword,textPassword);
        formModificaProfilo->addRow(labelName,textName);
        formModificaProfilo->addRow(labelSurname,textSurname);
        formModificaProfilo->addRow(labelCF,textCF);
        formModificaProfilo->addRow(labelData_Nascita,textData_Nascita);
        formModificaProfilo->addRow(labelEmail,textEmail);
        formModificaProfilo->addRow(labelTelefono,textTelefono);
        formModificaProfilo->addRow(labelRuolo,textRuolo);
        formModificaProfilo->addRow(labelTipoContratto,textTipoContratto);
        formModificaProfilo->addRow(labelInizioContratto,textInizioContratto);
        formModificaProfilo->addRow(labelFineContratto,textFineContratto);
        formModificaProfilo->addRow(labelFamiliariACarico,textFamiliariACarico);
    }
    else {
        formModificaProfilo->addRow(labelNumeroIdentificativo,textNumeroIdentificativo);
        formModificaProfilo->addRow(labelName,textName);
        formModificaProfilo->addRow(labelSurname,textSurname);
        formModificaProfilo->addRow(labelCF,textCF);
        formModificaProfilo->addRow(labelData_Nascita,textData_Nascita);
        formModificaProfilo->addRow(labelEmail,textEmail);
        formModificaProfilo->addRow(labelTelefono,textTelefono);
        formModificaProfilo->addRow(labelDataInizioRapporto,textDataInizioRapporto);
        formModificaProfilo->addRow(0,checkAppOnline);
    }
}

void gestionePersone::ModifyProfile(){

    infoPersona();
    infoOperatore();

    textName->setText(QString::fromStdString(personagestita->GetNome()));
    textSurname->setText(QString::fromStdString(personagestita->GetCognome()));
    textTelefono->setText(QString::fromStdString(loggato->GetCellulare()));
    textCF->setText(QString::fromStdString(personagestita->GetCF()));
    textData_Nascita->setDate(personagestita->GetDataNascita());
    textEmail->setText(QString::fromStdString(loggato->GetEmail()));
    textUsername->setText(QString::fromStdString(loggato->GetUsername()));
    textPassword->setText(QString::fromStdString(loggato->GetPassword()));
    textRuolo->setText(QString::fromStdString(loggato->GetInquadratura()));
    textTipoContratto->setText(QString::fromStdString(loggato->GetTipoContratto()));
    textInizioContratto->setDate(loggato->GetInizioContratto());
    textFineContratto->setDate(loggato->GetFineContratto());
    textFamiliariACarico->setText(QString::number(loggato->GetPersoneACarico()));

    textName->setReadOnly(true);
    textSurname->setReadOnly(true);
    textCF->setReadOnly(true);
    textData_Nascita->setReadOnly(true);
    textRuolo->setReadOnly(true);
    textTipoContratto->setReadOnly(true);
    textInizioContratto->setReadOnly(true);
    textFineContratto->setReadOnly(true);
    textFamiliariACarico->setReadOnly(true);


    pushSalva=new QPushButton("Salva Modifiche");

    setForm();
    formModificaProfilo->addRow(pushSalva);
    connect(pushSalva,SIGNAL(clicked()),this,SLOT(inviaModifiche()));

}

void gestionePersone::ModifyDipendente(){

    infoPersona();
    infoOperatore();

    Operatore* tmp= dynamic_cast<Operatore*>(personagestita);
    textName->setText(QString::fromStdString(personagestita->GetNome()));
    textSurname->setText(QString::fromStdString(personagestita->GetCognome()));
    textTelefono->setText(QString::fromStdString(tmp->Operatore::GetCellulare()));
    textCF->setText(QString::fromStdString(personagestita->GetCF()));
    textData_Nascita->setDate(personagestita->GetDataNascita());
    textEmail->setText(QString::fromStdString(tmp->Operatore::GetEmail()));
    textUsername->setText(QString::fromStdString(tmp->GetUsername()));
    textPassword->setText(QString::fromStdString(tmp->GetPassword()));
    textRuolo->setText(QString::fromStdString(tmp->GetInquadratura()));
    textTipoContratto->setText(QString::fromStdString(tmp->GetTipoContratto()));
    textInizioContratto->setDate(tmp->GetInizioContratto());
    textFineContratto->setDate(tmp->GetFineContratto());
    textFamiliariACarico->setText(QString::number(tmp->GetPersoneACarico()));

    textUsername->setReadOnly(true);
    textPassword->setReadOnly(true);
    textName->setReadOnly(true);
    textSurname->setReadOnly(true);
    textCF->setReadOnly(true);
    textData_Nascita->setReadOnly(true);
    textInizioContratto->setCalendarPopup(true);
    textFineContratto->setCalendarPopup(true);

    pushSalva=new QPushButton("Salva Modifiche");
    pushElimina=new QPushButton("Elimina Utente");

    setForm();
    formModificaProfilo->addRow(pushSalva,pushElimina);

    connect(pushSalva,SIGNAL(clicked()),this,SLOT(inviaModifiche()));
    connect(pushElimina,SIGNAL(clicked()),this,SLOT(Eliminazione()));
}

void gestionePersone::ModifyCliente(){

    setFixedWidth(900);
    infoPersona();
    infoOspite();

    Ospite* tmp= dynamic_cast<Ospite*>(personagestita);
    textName->setText(QString::fromStdString(personagestita->GetNome()));
    textSurname->setText(QString::fromStdString(personagestita->GetCognome()));
    textTelefono->setText(QString::fromStdString(tmp->Ospite::GetCellulare()));
    textCF->setText(QString::fromStdString(personagestita->GetCF()));
    textData_Nascita->setDate(personagestita->GetDataNascita());
    textEmail->setText(QString::fromStdString(tmp->Ospite::GetEmail()));
    textNumeroIdentificativo->setText(QString::number(tmp->GetNumeroIdentificativo()));
    textDataInizioRapporto->setDate(tmp->GetDataInizioRapporto());
    checkAppOnline->setChecked(tmp->GetAppOnline());

    textNumeroIdentificativo->setReadOnly(true);
    textName->setReadOnly(true);
    textSurname->setReadOnly(true);
    textCF->setReadOnly(true);
    textData_Nascita->setReadOnly(true);
    textDataInizioRapporto->setReadOnly(true);

    pushSalva=new QPushButton("Salva Modifiche");
    pushElimina=new QPushButton("Elimina Utente");

    setForm();
    formModificaProfilo->addRow(pushSalva,pushElimina);

    pushAddCC=new QPushButton("Aggiungi Conto Corrente");
    pushAddInv=new QPushButton("Aggiungi Investimento");
    formModificaProfilo->addRow(pushAddCC);
    formModificaProfilo->addRow(pushAddInv);

    tablecc= new table_lists(personetotali,prestazioni,this);
    tablecc->viewCCPersona(tmp);

    tableinv= new table_lists(personetotali,prestazioni,this);
    tableinv->setMaximumHeight(400);
    tableinv->setMaximumWidth(950);

    tableinv->viewInvPersona(tmp);

    gridTable = new QGridLayout();
    gridTable->addWidget(tablecc);
    gridTable->addWidget(tableinv);

    layoutModificaProfilo->addLayout(gridTable);

    connect(pushSalva,SIGNAL(clicked()),this,SLOT(inviaModifiche()));
    connect(pushElimina,SIGNAL(clicked()),this,SLOT(Eliminazione()));
    connect(pushAddCC,SIGNAL(clicked()),this,SLOT(AddCC()));
    connect(pushAddInv,SIGNAL(clicked()),this,SLOT(AddInv()));
    connect(tablecc,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(clickTablecc(int,int)));
    connect(tableinv,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(clickTableinv(int,int)));

}

void gestionePersone::FormOperazione(){
    setWindowTitle("Risultato della richiesta");
    setMinimumWidth(250);
    risultato=new QLineEdit();
    layoutFinal= new QFormLayout();
    layoutFinal->addRow(risultato);
    setLayout(layoutFinal);
    risultato->setReadOnly(true);
}

void gestionePersone::setResult(double text){
    risultato->setText(QString::number(text));
}

void gestionePersone::Eliminazione(){
    emit EliminaPersona(personagestita);
}

void gestionePersone::inviaModifiche(){
    if(personagestita->GetCF()==loggato->GetCF()){
    emit modificaUtente(loggato,textUsername->text().toStdString(),
                        textPassword->text().toStdString(),textEmail->text().toStdString(),textTelefono->text().toStdString());
    }
    else if(loggato->GestioneDipendenti()){
        emit modificaDipendente(personagestita,textEmail->text().toStdString(),textTelefono->text().toStdString(),
        textRuolo->text().toStdString(), textTipoContratto->text().toStdString(), textInizioContratto->date(),
        textFineContratto->date(),textFamiliariACarico->text().toUInt());
    }
    else{
        emit modificaCliente(personagestita,textEmail->text().toStdString(),textTelefono->text().toStdString(),checkAppOnline->isChecked());
    }

    this->close();

}

void gestionePersone::AggiungiDipendente(){

    setFixedWidth(450);
    infoPersona();
    infoOperatore();
    textUsername->setToolTip("L'username deve avere almeno 6 caratteri");
    textPassword->setToolTip("La password deve avere almeno 6 caratteri");
    textData_Nascita->setCalendarPopup(true);
    textInizioContratto->setCalendarPopup(true);
    textInizioContratto->setDate(QDate::currentDate());
    textFineContratto->setCalendarPopup(true);
    textFineContratto->setDate(QDate::currentDate());
    textRuolo->setToolTip("Ruoli: Sportello, Ufficio Personale");
    textRuolo->setPlaceholderText("Sportello o Ufficio Personale");

    pushSalva=new QPushButton("Salva Persona");
    pushElimina=new QPushButton("Annulla");

    setForm();
    formModificaProfilo->addRow(pushSalva,pushElimina);
    connect(pushSalva,SIGNAL(clicked()),this,SLOT(NuovaPersona()));
    connect(pushElimina,SIGNAL(clicked()),this,SLOT(close()));
}

void gestionePersone::AggiungiCliente(){

    infoPersona();
    infoOspite();
    uint NumeroCliente=Cliente::NumeroClienti+1;
    textNumeroIdentificativo->setText(QString::number(NumeroCliente));
    textNumeroIdentificativo->setReadOnly(true);
    textData_Nascita->setCalendarPopup(true);
    textDataInizioRapporto->setCalendarPopup(true);
    textDataInizioRapporto->setDate(QDate::currentDate());

    pushSalva=new QPushButton("Salva Persona");
    pushElimina=new QPushButton("Annulla");

    setForm();
    formModificaProfilo->addRow(pushSalva,pushElimina);
    connect(pushSalva,SIGNAL(clicked()),this,SLOT(NuovaPersona()));
    connect(pushElimina,SIGNAL(clicked()),this,SLOT(close()));
}

void gestionePersone::NuovaPersona(){
    if(loggato->GestioneDipendenti()){
        emit nuovo_operatore(textUsername->text().toStdString(),textPassword->text().toStdString(),
                      textName->text().toStdString(),textSurname->text().toStdString(),
                      textCF->text().toStdString(),textData_Nascita->date(),textRuolo->text().toStdString(),
                      textEmail->text().toStdString(), textTelefono->text().toStdString(),
                      textInizioContratto->date(), textTipoContratto->text().toStdString(),
                      textFineContratto->date(),textFamiliariACarico->text().toUInt());
    }
    else {
        emit nuovo_ospite(textNumeroIdentificativo->text().toUInt(),
                          textName->text().toStdString(),textSurname->text().toStdString(),
                          textCF->text().toStdString(),textData_Nascita->date(),
                          textEmail->text().toStdString(), textTelefono->text().toStdString(),
                          textDataInizioRapporto->date(), checkAppOnline->isChecked());
    }
}

void gestionePersone::SearchForOperation(const string & pulsante){
    setWindowTitle("Ricerca Persona");
    labelCF= new QLabel("Codice Fiscale:");
    textCF=new QLineEdit();
    textCF->setValidator(new QRegExpValidator(QRegExp("^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$")));
    formCF=new QFormLayout();
    pushCercaCF= new QPushButton("Cerca");
    formCF->addRow(labelCF,textCF);
    formCF->addRow(pushCercaCF);

    setLayout(formCF);

    botton=pulsante;
    connect(pushCercaCF,SIGNAL(clicked(bool)),this,SLOT(CercaCF()));
}

void gestionePersone::CercaCF(){
    emit CF(textCF->text().toStdString(),botton);
}
void gestionePersone::SearchPersona(){
    setWindowTitle("Ricerca Persona");
    cercaCF= new QGroupBox(tr("Ricerca per Codice fiscale"));
    labelCF= new QLabel("Codice Fiscale:");
    textCF=new QLineEdit();
    textCF->setValidator(new QRegExpValidator(QRegExp("^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$")));
    formCF=new QFormLayout();
    pushCercaCF= new QPushButton("Cerca");
    formCF->addRow(labelCF,textCF);
    formCF->addRow(pushCercaCF);

    cercaNS= new QGroupBox(tr("Ricerca per Nome e Cognome"));
    labelName= new QLabel("Nome:");
    labelSurname=  new QLabel("Cognome:");
    textName=new QLineEdit();
    textSurname=new QLineEdit();
    pushCercaNS= new QPushButton("Cerca");
    formNS=new QFormLayout();
    formNS->addRow(labelName,textName);
    formNS->addRow(labelSurname,textSurname);
    formNS->addRow(pushCercaNS);

    connect(pushCercaCF,SIGNAL(clicked(bool)),this,SLOT(cercaPersona()));
    connect(pushCercaNS,SIGNAL(clicked(bool)),this,SLOT(cercaPersona()));

    layoutSearch=new QVBoxLayout();
    layoutSearch->addWidget(cercaCF);
    layoutSearch->addWidget(cercaNS);
    this->setLayout(layoutSearch);

    cercaCF->setLayout(formCF);
    cercaNS->setLayout(formNS);
}

void gestionePersone::cercaPersona(){
    emit CercaPersona(textCF->text().toStdString(),textName->text().toStdString(),textSurname->text().toStdString());
}

//......................SERVIZI.....................
void gestionePersone::infoCC(){
    formServizio= new QFormLayout();
    labelIntestatario1= new QLabel("Intestatario:");
    labelIntestatario2= new QLabel("Co-Intestatario:");
    labelDataApertura= new QLabel("Data apertura:");
    labelNumeroCC= new QLabel("Numero Conto:");
    labelInteressi= new QLabel("Interessi Annui:");

    textIntestatario1=new QLineEdit();
    textIntestatario2=new QLineEdit();
    textDataApertura=new QDateEdit();
    textNumeroCC=new QLineEdit();
    textInteressi=new QLineEdit();
    textInteressi->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[.]?[0-9]+$")));

    formServizio->addRow(labelIntestatario1,textIntestatario1);
    formServizio->addRow(labelIntestatario2,textIntestatario2);
    formServizio->addRow(labelDataApertura,textDataApertura);
    formServizio->addRow(labelNumeroCC,textNumeroCC);
    formServizio->addRow(labelInteressi,textInteressi);
}

void gestionePersone::infoInv(){
    formServizio= new QFormLayout();
    labelNumeroInvestimento= new QLabel("Numero Investimento:");
    labelIntestatario1= new QLabel("Intestatario:");
    labelDataApertura= new QLabel("Data apertura:");
    labelDataFine= new QLabel("Data Fine:");
    labelNumeroCC= new QLabel("Conto collegato:");
    labelInteressibanca= new QLabel("Interessi Banca:");
    labelInteressicliente= new QLabel("Interessi Cliente:");
    labelSommainv=new QLabel("Somma investita");

    textNumeroInvestimento=new QLineEdit();
    textIntestatario1=new QLineEdit();
    textDataApertura=new QDateEdit();
    textDataFine=new QDateEdit();
    textNumeroCC=new QLineEdit();
    textInteressibanca=new QLineEdit();
    textInteressibanca->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[.]?[0-9]+$")));
    textInteressicliente=new QLineEdit();
    textInteressicliente->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[.]?[0-9]+$")));
    textSommainv=new QLineEdit();
    textSommainv->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[.]?[0-9]+$")));

    formServizio->addRow(labelNumeroInvestimento,textNumeroInvestimento);
    formServizio->addRow(labelIntestatario1,textIntestatario1);
    formServizio->addRow(labelDataApertura,textDataApertura);
    formServizio->addRow(labelDataFine,textDataFine);
    formServizio->addRow(labelNumeroCC,textNumeroCC);
    formServizio->addRow(labelInteressibanca,textInteressibanca);
    formServizio->addRow(labelInteressicliente,textInteressicliente);
    formServizio->addRow(labelSommainv,textSommainv);

}

void gestionePersone::AddCC(){
    gestionePersone* formAddServizio=new gestionePersone(personagestita,loggato,personetotali,prestazioni);
    formAddServizio->setWindowTitle("Nuovo Conto Corrente");
    Ospite* cliente= dynamic_cast<Ospite*>(personagestita);

    infoCC();

    textIntestatario1->setText(QString::number(cliente->GetNumeroIdentificativo()));
    textIntestatario1->setReadOnly(true);
    textDataApertura->setDate(QDate::currentDate());
    textDataApertura->setCalendarPopup(true);
    numerocc=(Cont_corr::NumeroCC)+1;
    textNumeroCC->setText(QString::number(numerocc));
    textNumeroCC->setReadOnly(true);
    textInteressi->setText(QString::number(0.50));

    pushSalva=new QPushButton("Salva");
    pushElimina=new QPushButton("Annulla");

    formServizio->addRow(pushSalva,pushElimina);

    tableoscc= new table_lists(personetotali,prestazioni,this);
    tableoscc->setMaximumHeight(400);
    tableoscc->setMaximumWidth(950);

    tableoscc->viewOspiti();
    tableoscc->viewAllOspiti();

    gridTable = new QGridLayout();
    gridTable->addWidget(tableoscc);

    layoutAddServizio=new QHBoxLayout();
    layoutAddServizio->addLayout(formServizio);
    layoutAddServizio->addLayout(gridTable);

    formAddServizio->setLayout(layoutAddServizio);
    formAddServizio->show();
    connect(pushSalva,SIGNAL(clicked(bool)),this,SLOT(NuovoCC()));
    connect(pushSalva,SIGNAL(clicked(bool)),formAddServizio,SLOT(close()));
    connect(pushElimina,SIGNAL(clicked(bool)),formAddServizio,SLOT(close()));
    connect(tableoscc,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setIntestatario2(int,int)));
}

void gestionePersone::AddInv(){
    gestionePersone* formAddServizio= new gestionePersone(personagestita,loggato,personetotali,prestazioni);
    formAddServizio->setWindowTitle("Nuovo Investimento");
    Ospite* cliente= dynamic_cast<Ospite*>(personagestita);

    infoInv();

    int numeroinv=(Investimento::NumeroInvestimenti)+1;
    textNumeroInvestimento->setText(QString::number(numeroinv));
    textNumeroInvestimento->setReadOnly(true);
    textIntestatario1->setText(QString::number(cliente->GetNumeroIdentificativo()));
    textIntestatario1->setReadOnly(true);
    textDataFine->setDate(QDate::currentDate());
    textDataFine->setCalendarPopup(true);
    textDataApertura->setDate(QDate::currentDate());
    textDataApertura->setCalendarPopup(true);
    textInteressibanca->setText(QString::number(0.50));
    textInteressicliente->setText(QString::number(0.10));
    textSommainv->setText(QString::number(500));

    pushSalva=new QPushButton("Salva");
    pushElimina=new QPushButton("Annulla");

    formServizio->addRow(pushSalva,pushElimina);

    tableccinv= new table_lists(personetotali,prestazioni,this);
    tableccinv->viewCCPersona(cliente);

    gridTable = new QGridLayout();
    gridTable->addWidget(tableccinv);

    layoutAddServizio=new QHBoxLayout();
    layoutAddServizio->addLayout(formServizio);
    layoutAddServizio->addLayout(gridTable);

    formAddServizio->setLayout(layoutAddServizio);
    formAddServizio->show();
    connect(pushSalva,SIGNAL(clicked(bool)),this,SLOT(NuovoInv()));
    connect(pushSalva,SIGNAL(clicked(bool)),formAddServizio,SLOT(close()));
    connect(pushElimina,SIGNAL(clicked(bool)),formAddServizio,SLOT(close()));
    connect(tableccinv,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setNumeroCC(int,int)));
}

void gestionePersone::NuovoCC(){
    emit AddConto(textIntestatario1->text().toUInt(),textDataApertura->date(),
                  textNumeroCC->text().toUInt(),textInteressi->text().toDouble(),textIntestatario2->text().toUInt());
}

void gestionePersone::NuovoInv(){
    emit AddInvest(textNumeroInvestimento->text().toUInt(),textIntestatario1->text().toUInt(),
                   textDataApertura->date(), textDataFine->date(),textNumeroCC->text().toUInt(),
                   textInteressibanca->text().toDouble(),textInteressicliente->text().toDouble(),
                    textSommainv->text().toDouble());
}

void gestionePersone::setNumeroCC(int row, int column){
    column=0;
    textNumeroCC->setText(QString::number(tableccinv->item(row,column)->text().toUInt()));
}

void gestionePersone::setIntestatario2(int row,int column){
    column=0;
    textIntestatario2->setText(QString::number(tableoscc->item(row,column)->text().toUInt()));
}

void gestionePersone::AggiornaCC(){
    Ospite* cliente=dynamic_cast<Ospite*>(personagestita);
    tablecc->viewCCPersona(cliente);
}

void gestionePersone::AggiornaInv(){
    Ospite* cliente=dynamic_cast<Ospite*>(personagestita);
    tableinv->viewInvPersona(cliente);
}

void gestionePersone::clickTablecc(int row,int column){
    column=0;
   emit tableclient(prestazioni->GetConto(tablecc->item(row,column)->text().toUInt()));
}

void gestionePersone::clickTableinv(int row,int column){
    column=0;
    emit tableclient(prestazioni->GetInvest(tableinv->item(row,column)->text().toUInt()));
}

void gestionePersone::ModifyCC(Cont_corr* servizio){
    setWindowTitle("Informazioni Conto Corrente");
    infoCC();

    textIntestatario1->setText(QString::number(servizio->GetIntestatario()->GetNumeroIdentificativo()));
    textIntestatario1->setReadOnly(true);
    if(servizio->GetCoIntestatario()!=nullptr) textIntestatario2->setText(QString::number(servizio->GetCoIntestatario()->GetNumeroIdentificativo()));
    textIntestatario2->setReadOnly(true);
    textDataApertura->setDate(servizio->GetAttivazione());
    textDataApertura->setReadOnly(true);
    textNumeroCC->setText(QString::number(servizio->GetNCC()));
    textNumeroCC->setReadOnly(true);
    textInteressi->setText(QString::number(servizio->GetInteressi()));
    textInteressi->setReadOnly(true);

    pushElimina=new QPushButton("Elimina");

    formServizio->addRow(pushElimina);

    connect(pushElimina,SIGNAL(clicked(bool)),this,SLOT(EliminazioneCC()));
    setLayout(formServizio);
}

void gestionePersone::ModifyInvest(Investimento* servizio){
    setWindowTitle("Informazioni Investimento");
    infoInv();

    textNumeroInvestimento->setText(QString::number(servizio->GetNumeroInvestimento()));
    textNumeroInvestimento->setReadOnly(true);
    textIntestatario1->setText(QString::number(servizio->GetIntestatario()->GetNumeroIdentificativo()));
    textIntestatario1->setReadOnly(true);
    textDataApertura->setDate(servizio->GetAttivazione());
    textDataApertura->setReadOnly(true);
    textDataFine->setDate(servizio->GetDataFine());
    textDataFine->setReadOnly(true);
    textNumeroCC->setText(QString::number(servizio->GetContoCollegato()->GetNCC()));
    textInteressibanca->setText(QString::number(servizio->GetIntbanca()));
    textInteressibanca->setReadOnly(true);
    textInteressicliente->setText(QString::number(servizio->GetIntcliente()));
    textInteressicliente->setReadOnly(true);
    textSommainv->setText(QString::number(servizio->GetSommaInvestita()));
    textSommainv->setReadOnly(true);

    pushElimina=new QPushButton("Elimina");

    formServizio->addRow(pushElimina);

    connect(pushElimina,SIGNAL(clicked(bool)),this,SLOT(EliminazioneInv()));
    setLayout(formServizio);
}

void gestionePersone::EliminazioneCC(){
    emit EliminaServizio(prestazioni->GetConto(textNumeroCC->text().toUInt()));
    this->close();
}

void gestionePersone::EliminazioneInv(){
    emit EliminaServizio(prestazioni->GetInvest(textNumeroInvestimento->text().toUInt()));
    this->close();
}

void gestionePersone::ServiceForOperation(){
    setWindowTitle("Ricerca Servizio");
    cercaCC= new QGroupBox(tr("Ricerca Conto Corrente"));
    labelNumeroCC= new QLabel("Numero:");
    textNumeroCC=new QLineEdit();
    textNumeroCC->setValidator(new QRegExpValidator(QRegExp("^[0-9]*$")));
    formCC=new QFormLayout();
    pushCercaCC= new QPushButton("Cerca");
    formCC->addRow(labelNumeroCC,textNumeroCC);
    formCC->addRow(pushCercaCC);

    cercaInv= new QGroupBox(tr("Ricerca Investimento"));
    labelNumeroInvestimento= new QLabel("Numero:");
    textNumeroInvestimento=new QLineEdit();
    textNumeroInvestimento->setValidator(new QRegExpValidator(QRegExp("^[0-9]*$")));
    pushCercaInv= new QPushButton("Cerca");
    formInv=new QFormLayout();
    formInv->addRow(labelNumeroInvestimento,textNumeroInvestimento);
    formInv->addRow(pushCercaInv);

    connect(pushCercaCC,SIGNAL(clicked(bool)),this,SLOT(trovaCC()));
    connect(pushCercaInv,SIGNAL(clicked(bool)),this,SLOT(trovaInv()));

    layoutSearch=new QVBoxLayout();
    layoutSearch->addWidget(cercaCC);
    layoutSearch->addWidget(cercaInv);
    this->setLayout(layoutSearch);

    cercaCC->setLayout(formCC);
    cercaInv->setLayout(formInv);
}

void gestionePersone::trovaCC(){
    botton="cc";
    emit CercaCC(textNumeroCC->text().toUInt(),botton);
}

void gestionePersone::trovaInv(){
    botton="inv";
    emit CercaInv(textNumeroInvestimento->text().toUInt(),botton);
}

void gestionePersone::closeEvent(QCloseEvent* event){
   event->accept();
   emit closeWindow();
}
