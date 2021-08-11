#ifndef FILETESTO_H
#define FILETESTO_H

#include <file.h>

class FileTesto: public File {
    private:
        unsigned int numeroCaratteri;
        unsigned int numeroParole;

    public:
         FileTesto(QString, QString, unsigned int, QDate, QDate, QString, unsigned int, unsigned int);
         ~FileTesto();

         unsigned int getNumeroCaratteri() const;
         unsigned int getNumeroParole() const;

         QString getInformazioniFile() const override;
         FileTesto* clone() const override;
};

#endif // FILETESTO_H
