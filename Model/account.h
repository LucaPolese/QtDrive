#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "container.h"
#include "deepptr.h"
#include "file.h"


class Account {
public:
    enum servizio {AmazonDrive, Box, Dropbox, GDrive, iCloud, Mediafire, Mega, Next, OneDrive, Qihoo360};
    Account(QString, QString, servizio, unsigned int, Container<Deepptr<File>>);
    Account* clone() const;
private:
    QString email;
    QString password;
    servizio host;
    unsigned int spazioFornito;
    Container<Deepptr<File>> listaFile;
};

#endif // ACCOUNT_H
