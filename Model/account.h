#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "container.h"
#include "deepptr.h"
#include "file.h"

class Account {
    private:
        enum servizio {AmazonDrive, Box, Dropbox, GDrive, iCloud, Mediafire, Mega, Next, OneDrive, Qihoo360};
        QString email;
        QString password;
        servizio host;
        unsigned int spazioFornito;
        Container<Deepptr<File>> listaFile;

    public:
        Account(QString, QString, servizio, unsigned int);
};

#endif // ACCOUNT_H
