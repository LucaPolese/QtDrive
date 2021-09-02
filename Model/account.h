#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>
#include "container.h"
#include "deepptr.h"
#include "file.h"
#include "filearchivio.h"
#include "fileaudio.h"
#include "fileimmagine.h"
#include "filetesto.h"
#include "filevideo.h"
#include <QXmlStreamWriter>
#include <iostream>
class Account {
public:
    enum servizio {AmazonDrive, Box, Dropbox, GDrive, iCloud, Mediafire, Mega, Next, OneDrive, Qihoo360};
    Account(QString, QString, servizio, unsigned int, Container<Deepptr<File>> = Container<Deepptr<File>>());
    Account* clone() const;
    void serializza(QXmlStreamWriter& w) const;
    static Account* deserializza(QXmlStreamReader & reader);
    const QString &getPassword() const;
    void setPassword(QString);
    servizio getHost() const;
    unsigned int getSpazioFornito() const;
    const Container<Deepptr<File>> &getListaFile() const;
    const QString &getEmail() const;
    void setEmail(QString);
    void aggiungiFile(File*);
    void eliminaFile(int);
    float getSpazioOccupato() const;
    template <class T>
    int contaFile() const{
        unsigned int contatore = 0;
        for(auto it = listaFile.begin(); it != listaFile.end(); it++){
            if(dynamic_cast<T*>((*it).getPuntatore())) contatore++;
        }
        return contatore;
    }
    bool checkFile(QString, QString) const;
private:
    QString email;
    QString password;
    servizio host;
    unsigned int spazioFornito;
    Container<Deepptr<File>> listaFile;
    //Funzioni
    static void riempiTipiDiFile();
};
#endif // ACCOUNT_H
