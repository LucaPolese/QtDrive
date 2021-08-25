#include "account.h"

std::vector<File*> tipiDiFile;

Account::Account(QString email_, QString password_, servizio host_, unsigned int spazioFornito_, Container<Deepptr<File>> listaFile_):
    email(email_), password(password_), host(host_), spazioFornito(spazioFornito_), listaFile(){}

Account* Account::clone() const{
    return new Account(*this);
}

const QString &Account::getEmail() const {
    return email;
}

void Account::setEmail(QString nuovaEmail) {
    email = nuovaEmail;
}

const QString &Account::getPassword() const {
    return password;
}

void Account::setPassword(QString nuovaPassword) {
    password = nuovaPassword;
}

Account::servizio Account::getHost() const {
    return host;
}

unsigned int Account::getSpazioFornito() const {
    return spazioFornito;
}

const Container<Deepptr<File> > &Account::getListaFile() const {
    return listaFile;
}

void Account::serializza(QXmlStreamWriter &scrittore) const{
    QString errore;
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
        }catch(QString e){
            errore = e;
        }
        scrittore.writeEndElement();
    scrittore.writeEndElement();
if (scrittore.hasError()) throw errore;
}

Account* Account::deserializza(QXmlStreamReader & lettore){
    //Informazioni per costruire un oggetto di classe Account
    QString _email;
    QString _password;
    servizio _host;
    unsigned int _spazioFornito;
    Container<Deepptr<File>> _listaFile;
    riempiTipiDiFile();

    if(lettore.name() != "account") throw QString("Non è presente alcun Account all'interno del file!");
    else{
        //Lettura Email Account
        if(lettore.readNextStartElement() && lettore.name() == "email") _email = lettore.readElementText();
        //Lettura Password Account
        if(lettore.readNextStartElement() && lettore.name() == "password") _password = lettore.readElementText();
        //Lettura Host Account
        if(lettore.readNextStartElement() && lettore.name() == "host") _host = servizio(lettore.readElementText().toInt());
        //Lettura Spazio Fornito
        if(lettore.readNextStartElement() && lettore.name() == "spazioFornito") _spazioFornito = lettore.readElementText().toUInt();

        //Lettura Files
        if(lettore.readNextStartElement() && lettore.name() == "listaFile"){
            while(lettore.readNextStartElement() && lettore.name() == "file"){
                bool trovato= false;
                QString tipo = lettore.attributes().value("type").toString();
                if(tipo != ""){
                    for(auto it = tipiDiFile.begin(); it != tipiDiFile.end() && !trovato ; it++){
                        if((*it)->getInformazioniFile() == tipo){
                            try{
                                _listaFile.push_back((*it)->deserializza(lettore));
                                trovato = true;
                            }catch(QString s){
                                throw s;
                            }
                        }
                    }
                }else throw QString("Il documento che è stato aperto non è ben formato: un file letto non è di alcun tipo!");
            }
        }

    }
    lettore.skipCurrentElement();
    return new Account(_email, _password, _host, _spazioFornito, _listaFile);
}

void Account::riempiTipiDiFile(){
    //Aggiunta alla creazione dell'account
    tipiDiFile.push_back(new FileArchivio());
    tipiDiFile.push_back(new FileAudio());
    tipiDiFile.push_back(new FileImmagine());
    tipiDiFile.push_back(new FileTesto());
    tipiDiFile.push_back(new FileVideo());
}

