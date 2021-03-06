#ifndef FILETESTO_H
#define FILETESTO_H

#include "file.h"
#include <QIcon>

class FileTesto: public File {
private:
    unsigned int numeroCaratteri;
    unsigned int numeroParole;

public:
    FileTesto(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate = QDate(1970,1,1), QString = "", unsigned int = 0, unsigned int = 0);
    ~FileTesto();

    //Funzioni Getter
    unsigned int getNumeroCaratteri() const;
    unsigned int getNumeroParole() const;

    //Funzioni Polimorfe
    QString getInformazioniFile() const override;
    FileTesto* clone() const override;
    void serializza(QXmlStreamWriter &scrittore) const override;
    FileTesto* deserializza(QXmlStreamReader& lettore) override;
    QString getTipoFile() const override;

    //Funzione di Ricerca
    bool ricercaAvanzata(QString, Qt::CaseSensitivity) const override;
};

#endif // FILETESTO_H
