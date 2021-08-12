#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account {
    private:
        enum servizio {AmazonDrive, Box, Dropbox, GDrive, iCloud, Mediafire, Mega, Next, OneDrive, Qihoo360};
        QString email;
        QString password;
        servizio host;
        unsigned int spazioFornito;
        //CONTAINER FILE

    public:
        Account();
};

#endif // ACCOUNT_H
