#ifndef FILEARCHIVIO_H
#define FILEARCHIVIO_H

#include "file.h"
#include <QIcon>

class FileArchivio: public File {
private:
    unsigned int dimensioneOriginale;
    unsigned int numeroDiFile;
    bool protetto; // True sse archivio protetto da password
public:
    FileArchivio(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate  = QDate(1970,1,1), QString ="", unsigned int = 0, unsigned int = 0, bool = false);
    ~FileArchivio();

    unsigned int getDimensioneOriginale() const;
    unsigned int getNumeroDiFile() const;
    bool getProtetto() const;

    QString getInformazioniFile() const override;
    FileArchivio* clone() const override;
    void serializza(QXmlStreamWriter &scrittore) const override;
    FileArchivio* deserializza(QXmlStreamReader& lettore) override;

    QString getTipoFile() const override;
    QIcon getIcona() const override;

    bool ricercaAvanzata(QString) const override;
};

#endif // FILEARCHIVIO_H
