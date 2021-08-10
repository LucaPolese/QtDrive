#ifndef FILEARCHIVIO_H
#define FILEARCHIVIO_H

#include <file.h>
#include <string>

#include <QDate>

class FileArchivio: public File {
    private:
        unsigned int dimensioneOriginale;
        unsigned int numeroDiFile;
        bool protetto; // True sse archivio protetto da password
    public:
        FileArchivio(QString, QString, unsigned int, QDate, QDate, QString descrizione_, unsigned int dimensioneOriginale_, unsigned int numeroDiFile_, bool protetto_);
        unsigned int getDimensioneOriginale() const;
        unsigned int getNumeroDiFile() const;
        bool getProtetto() const;
};

#endif // FILEARCHIVIO_H
