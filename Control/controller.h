#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/container.h"
#include "../Model/deepptr.h"
#include "../Model/file.h"
#include "../Model/account.h"
#include "../Model/xmlify.h"

class Controller {
private:
    Container<Deepptr<Account>> listaAccount;
    Xmlify xml;
    bool modificato;
public:
    Controller();
    ~Controller();

    //Funzioni Getter
    Container<Deepptr<Account>> getListaAccount() const;
    Xmlify getXml() const;
    bool getModificato() const;
    Account* getAccount(int) const;

    //Funzioni Setter
    void aggiornaPercorso(QString nuovoPercorso);
    void setModificato(bool);
    void aggiornaAccount();

    //Funzioni Account
    void aggiungiAccount(QString, QString, Account::servizio, unsigned int);
    int getNumeroAccount() const;
    void salvaModificaAccount(int, QString, QString);
    void eliminaAccount(int);
    bool checkAccount(QString, Account::servizio) const;
    bool salvataggioAccount() const;
    void azzeraContenutoAccount();

    //Funzioni File
    void aggiungiFile(int, File*);
    void eliminaFile(int indiceAccount, int indiceFile);
};

#endif // CONTROLLER_H
