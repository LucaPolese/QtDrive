#include "account.h"

/*Account::Account(QString email_, QString password_, provider host_, unsigned int spazioFornito_):
email(email_), password(password_), host(host_), spazioFornito(spazioFornito_), listaFile(){}*/

Account::Account(QString email_, QString password_, servizio host_, unsigned int spazioFornito_, Container<Deepptr<File>> listaFile_):
    email(email_), password(password_), host(host_), spazioFornito(spazioFornito_), listaFile(listaFile_){}

Account* Account::clone() const{
    return new Account(*this);
}

void Account::serializza(QXmlStreamWriter &scrittore) const{
    std::string errore;
    //Introduzione di ogni account
    scrittore.writeStartElement("account");
        //Aggiunta degli attributi:
        //Email
        scrittore.writeStartElement("email");
        scrittore.writeCharacters(QString(email));
        scrittore.writeEndElement();

        //Password
        scrittore.writeStartElement("password");
        scrittore.writeCharacters(QString(password));
        scrittore.writeEndElement();

        //Host
        scrittore.writeStartElement("host");
        scrittore.writeCharacters(QString::number(host));
        scrittore.writeEndElement();

        //Spazio Fornito
        scrittore.writeStartElement("spazioFornito");
        scrittore.writeCharacters(QString::number(spazioFornito));
        scrittore.writeEndElement();

        //Scrittura del contenuto del Container di Files
        scrittore.writeStartElement("listaFile");
        try{
            for(auto cit = listaFile.begin(); cit != listaFile.end(); ++cit){
                (*cit)->serializza(scrittore);
            }
        }catch(std::string e){
            errore = e;
        }
        scrittore.writeEndElement();
    scrittore.writeEndElement();
if (scrittore.hasError()) throw errore;
}
