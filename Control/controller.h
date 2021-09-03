#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/container.h"
#include "../Model/deepptr.h"
#include "../Model/file.h"
#include "../Model/account.h"
#include "../Model/xmlify.h"
#include <QDebug>

class Controller {
private:
    Container<Deepptr<Account>> listaAccount;
    Xmlify xml;
    bool modificato;
public:
    Controller();
    void aggiungiAccount(QString, QString, Account::servizio, unsigned int);
    void aggiungiFile(int, File*);
    void eliminaFile(int indiceAccount, int indiceFile);
    int getNumeroAccount() const;
    void salvaModificaAccount(int, QString, QString);
    void eliminaAccount(int);
    bool checkAccount(QString, Account::servizio) const;
    Container<Deepptr<Account>> getListaAccount() const;
    Account* getAccount(int) const;
    void aggiornaAccount();
    Xmlify getXml() const;
    bool salvataggioAccount() const;
    void aggiornaPercorso(QString nuovoPercorso);
    bool getModificato() const;
    void setModificato(bool);
};

#endif // CONTROLLER_H
