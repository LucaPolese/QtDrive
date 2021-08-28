#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/container.h"
#include "../Model/deepptr.h"
#include "../Model/file.h"
#include "../Model/account.h"
#include <QDebug>

class Controller {
private:
    Container<Deepptr<Account>> listaAccount;

public:
    Controller();
    void aggiungiAccount(QString, QString, Account::servizio, unsigned int);
    void aggiungiFile(int, File*);
    void eliminaFile(int, int);
    int getNumeroAccount() const;
    void salvaModificaAccount(int, QString, QString);
    void eliminaAccount(int);
    bool checkAccount(QString, Account::servizio) const;
    Account* getAccount(int) const;
};

#endif // CONTROLLER_H
