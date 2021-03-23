#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <QDate>

using std::string;

class Persona
{

private:
    const string CF;
    const string Nome;
    const string Cognome;
    const QDate DataNascita;


public:
    Persona( const string&,const string& ,
            const string&, const QDate&);

    virtual ~Persona() =0;
    string GetNome() const;
    string GetCognome() const;
    string GetCF() const;
    QDate GetDataNascita() const;
    virtual Persona* Senior()=0;
    virtual unsigned int Fedelta() const =0;

};

#endif // PERSONA_H
