#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H


#include <string>
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QRegExpValidator>
#include <QPixmap>
#include <QCheckBox>

using std::string;

class LoginWindow: public QDialog{
private:
    Q_OBJECT
    QLabel * windowIcon;

    QLabel * labelLogin;
    QLabel * labelUsernameLogin;
    QLabel * labelPasswordLogin;
    QLineEdit * textUsernameLogin;
    QLineEdit * textPasswordLogin;
    QPushButton * pushLogin;
    QGridLayout * gridLogin;

    QLabel * labelRegister;
    QLabel * labelUsernameRegister;
    QLabel * labelPasswordRegister;
    QLabel * labelName;
    QLabel * labelSurname;
    QLabel * labelCodiceFiscale;
    QLabel * labelDataNascita;
    QLineEdit * textUsernameRegister;
    QLineEdit * textPasswordRegister;
    QLineEdit * textName;
    QLineEdit * textSurname;
    QLineEdit * textCodiceFiscale;
    QDateEdit * textDataNascita;
    QComboBox * selectRole;
    QPushButton * pushRegister;
    QGridLayout * gridRegister;

    QVBoxLayout * finalLayout;
    QHBoxLayout * layoutLogin;

public:
    LoginWindow();
    void empty();

public slots:
    void login();
    void register_user();

signals:
    void doLogin(const string&, const string&);
    void doRegister(const string&, const string&, const string&, const string&,const string&, const QDate&,const string&);
};

#endif // LOGINWINDOW_H
