#include "login_window.h"

LoginWindow::LoginWindow(){
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Bcc Unipd");

    setFixedHeight(700);
    setFixedWidth(800);

    windowIcon = new QLabel();
    windowIcon->setAlignment(Qt::AlignCenter);
    QPixmap image(":/icon.png");
    windowIcon->setPixmap(image.scaled(200,190,Qt::KeepAspectRatio));

    labelLogin=new QLabel("Login");
    labelLogin->setAlignment(Qt::AlignCenter);
    labelUsernameLogin=new QLabel("Username:");
    labelPasswordLogin=new QLabel("Password:");
    textUsernameLogin=new QLineEdit();
    textPasswordLogin=new QLineEdit();
    textUsernameLogin->setPlaceholderText("Inserisci username");
    textPasswordLogin->setPlaceholderText("Inserisci password");
    textUsernameLogin->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,15}")));
    textPasswordLogin->setEchoMode(QLineEdit::Password);
    pushLogin=new QPushButton("Login");


    gridLogin=new QGridLayout;
    gridLogin->addWidget(labelLogin);
    gridLogin->addWidget(labelUsernameLogin);
    gridLogin->addWidget(textUsernameLogin);
    gridLogin->addWidget(labelPasswordLogin);
    gridLogin->addWidget(textPasswordLogin);
    gridLogin->addWidget(pushLogin);

    labelRegister=new QLabel("Register");
    labelRegister->setAlignment(Qt::AlignCenter);
    labelUsernameRegister=new QLabel("Username:");
    labelPasswordRegister=new QLabel("Password:");
    labelName=new QLabel("Name:");
    labelSurname=new QLabel("Surname:");
    labelCodiceFiscale=new QLabel("Codice Fiscale:");
    labelDataNascita=new QLabel("Data di nascita:");
    textUsernameRegister=new QLineEdit();
    textUsernameRegister->setToolTip("L'username deve avere almeno 6 caratteri");
    textPasswordRegister=new QLineEdit();
    textPasswordRegister->setToolTip("La password deve avere almeno 6 caratteri");
    textName=new QLineEdit();
    textSurname=new QLineEdit();
    textCodiceFiscale=new QLineEdit();
    textDataNascita=new QDateEdit();
    textDataNascita->setCalendarPopup(true);
    textUsernameRegister->setPlaceholderText("Inserisci username");
    textPasswordRegister->setPlaceholderText("Inserisci password");
    textName->setPlaceholderText("Inserisci nome");
    textSurname->setPlaceholderText("Inserisci cognome");
    textCodiceFiscale->setPlaceholderText("Inserisci Codice Fiscale");
    textUsernameRegister->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{1,20}")));
    textPasswordRegister->setEchoMode(QLineEdit::Password);
    textName->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,20}")));
    textSurname->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{1,20}")));
    textCodiceFiscale->setValidator(new QRegExpValidator(QRegExp("^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$")));

    selectRole=new QComboBox();
    selectRole->addItem("Sportello");
    selectRole->addItem("Ufficio Personale");

    pushRegister=new QPushButton("Register");

    gridRegister=new QGridLayout;
    gridRegister->addWidget(labelRegister);
    gridRegister->addWidget(labelUsernameRegister);
    gridRegister->addWidget(textUsernameRegister);
    gridRegister->addWidget(labelPasswordRegister);
    gridRegister->addWidget(textPasswordRegister);
    gridRegister->addWidget(labelName);
    gridRegister->addWidget(textName);
    gridRegister->addWidget(labelSurname);
    gridRegister->addWidget(textSurname);
    gridRegister->addWidget(labelCodiceFiscale);
    gridRegister->addWidget(textCodiceFiscale);
    gridRegister->addWidget(labelDataNascita);
    gridRegister->addWidget(textDataNascita);
    gridRegister->addWidget(selectRole);
    gridRegister->addWidget(pushRegister);

    layoutLogin=new QHBoxLayout();
    layoutLogin->addLayout(gridLogin);
    layoutLogin->addLayout(gridRegister);

    finalLayout= new QVBoxLayout();
    finalLayout->addWidget(windowIcon);
    finalLayout->addLayout(layoutLogin);

    setLayout(finalLayout);
    connect(pushLogin,SIGNAL(clicked()),this,SLOT(login()));
    connect(pushRegister,SIGNAL(clicked()),this,SLOT(register_user()));
}

void LoginWindow::login(){
    emit doLogin(textUsernameLogin->text().toStdString(),textPasswordLogin->text().toStdString());
}

void LoginWindow::register_user(){
    emit doRegister(textUsernameRegister->text().toStdString(),textPasswordRegister->text().toStdString(),textName->text().toStdString(),
                    textSurname->text().toStdString(),textCodiceFiscale->text().toStdString(),
                    textDataNascita->date(),selectRole->currentText().toStdString());
}

void LoginWindow::empty(){
    textUsernameLogin->clear();
    textPasswordLogin->clear();
    textUsernameRegister->clear();
    textPasswordRegister->clear();
    textName->clear();
    textSurname->clear();
    textCodiceFiscale->clear();
    textDataNascita->setCalendarPopup(true);
    textUsernameLogin->setFocus();
}

