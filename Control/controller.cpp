#include "controller.h"

Controller::Controller()
{

}

void Controller::aggiungiAccount(QString email, QString password, Account::servizio host, unsigned int spazioFornito) {
    listaAccount.push_back(new Account(email, password, host, spazioFornito));
}

int Controller::getNumeroAccount() const {
    return listaAccount.size();
}

void Controller::salvaModificaAccount(int indice, QString nuovaEmail, QString nuovaPassword) {
    listaAccount.at(indice)->setEmail(nuovaEmail);
    listaAccount.at(indice)->setPassword(nuovaPassword);
}

void Controller::eliminaAccount(int indice) {
    listaAccount.erase(listaAccount.begin() + indice);
}

Account* Controller::getAccount(int posizione) const {
    return listaAccount.at(posizione);
}
