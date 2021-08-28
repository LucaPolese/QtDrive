#include "controller.h"

Controller::Controller()
{

}

void Controller::aggiungiAccount(QString email, QString password, Account::servizio host, unsigned int spazioFornito) {
    listaAccount.push_back(new Account(email, password, host, spazioFornito));
}

void Controller::aggiungiFile(int indice, File *nuovoFile) {
    qDebug() << "Tentativo di inserire il file " << nuovoFile->getNome();
    listaAccount[indice]->aggiungiFile(nuovoFile);
    qDebug() << "Aggiunto file" << nuovoFile->getNome() << "all'account " << indice;
    delete nuovoFile;
}

void Controller::eliminaFile(int indiceAccount, int indiceFile) {
    listaAccount[indiceAccount]->eliminaFile(indiceFile);
}

int Controller::getNumeroAccount() const {
    return listaAccount.size();
}

void Controller::salvaModificaAccount(int indice, QString nuovaEmail, QString nuovaPassword) {
    listaAccount[indice]->setEmail(nuovaEmail);
    listaAccount[indice]->setPassword(nuovaPassword);
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

Account* Controller::getAccount(int posizione) const {
   // return listaAccount.at(posizione);
    return listaAccount[posizione].getPuntatore();
}
