#include "controller.h"

Controller::Controller() : listaAccount(), modificato(false), xml(""){}

Controller::~Controller() = default;

void Controller::aggiungiAccount(QString email, QString password, Account::servizio host, unsigned int spazioFornito) {
    listaAccount.push_back(new Account(email, password, host, spazioFornito));
}

void Controller::aggiungiFile(int indice, File *nuovoFile) {
    listaAccount[indice]->aggiungiFile(nuovoFile);
    delete nuovoFile;
}

void Controller::eliminaFile(int indiceAccount, int indiceFile) {
    listaAccount[indiceAccount]->eliminaFile(indiceFile);
}

int Controller::getNumeroAccount() const {
    return listaAccount.size();
}

void Controller::salvaModificaAccount(int indice, QString nuovaEmail, QString nuovaPassword) {
    if(checkAccount(nuovaEmail,listaAccount[indice]->getHost())){
        listaAccount[indice]->setEmail(nuovaEmail);
        listaAccount[indice]->setPassword(nuovaPassword);
    }else{
        QMessageBox* vuoto = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: le credenziali che hai modificato appartengono ad un servizio che è già presente nel tuo profilo!"
                                             "<br>Il tuo account non può essere salvato.",
                                             QMessageBox::Ok);
        vuoto->exec();
    }
}

void Controller::eliminaAccount(int indice) {
    listaAccount.erase(indice);
}

bool Controller::checkAccount(QString email, Account::servizio host) const {
    for(auto it = listaAccount.begin(); it != listaAccount.end(); ++it) {
        if(email == it->getPuntatore()->getEmail() && host == it->getPuntatore()->getHost())
            return false;
    }
    return true;
}

Container<Deepptr<Account>> Controller::getListaAccount() const{
    return listaAccount;
}

Account* Controller::getAccount(int posizione) const {
    return listaAccount[posizione].getPuntatore();
}

void Controller::aggiornaAccount(){
    listaAccount = xml.acquisisciAccount();
}

Xmlify Controller::getXml() const{
    return xml;
}

bool Controller::salvataggioAccount() const{
    return xml.salvaAccount(listaAccount);
}

void Controller::aggiornaPercorso(QString nuovoPercorso){
    xml.setPercorso(nuovoPercorso);
}

bool Controller::getModificato() const{
    return modificato;
}

void Controller::setModificato(bool mod){
    modificato = mod;
}

void Controller::azzeraContenutoAccount(){
    listaAccount.clear();
}
