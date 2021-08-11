#ifndef FILEARCHIVIO_H
#define FILEARCHIVIO_H

#include <file.h>

class FileArchivio: public File {
    private:
        unsigned int dimensioneOriginale;
        unsigned int numeroDiFile;
        bool protetto; // True sse archivio protetto da password
    public:
        FileArchivio(QString, QString, unsigned int, QDate, QDate, QString descrizione_, unsigned int dimensioneOriginale_, unsigned int numeroDiFile_, bool protetto_);
        ~FileArchivio();

        unsigned int getDimensioneOriginale() const;
        unsigned int getNumeroDiFile() const;
        bool getProtetto() const;

        QString getInformazioniFile() const override;
        FileArchivio* clone() const override;
};

#endif // FILEARCHIVIO_H
