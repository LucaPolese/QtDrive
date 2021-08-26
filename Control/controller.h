#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/container.h"
#include "../Model/deepptr.h"
#include "../Model/file.h"
#include "../Model/account.h"
#include <QDebug>

class Controller {
private:
    std::vector<Account*> listaAccount;

public:
    Controller();
    void aggiungiAccount(QString, QString, Account::servizio, unsigned int);
    void aggiungiFile(int, File*);
    int getNumeroAccount() const;
    void salvaModificaAccount(int, QString, QString);
    void eliminaAccount(int);
    Account* getAccount(int) const;
};

#endif // CONTROLLER_H
