#ifndef FILEIMMAGINE_H
#define FILEIMMAGINE_H

#include <filemedia.h>

class FileImmagine: public FileMedia {
    public:
        enum tipo{raster, vettoriale}; // ENUM PUBBLICO?

        FileImmagine(QString, QString, unsigned int, QDate, QDate, QString, FileMedia::compressione, tipo, unsigned int, unsigned int);
        ~FileImmagine();

        unsigned int getAltezza() const;
        unsigned int getLarghezza() const;

        QString getInformazioniFile() const override;
        FileImmagine* clone() const override;

    private:
        tipo tipoImmagine;
        unsigned int larghezza;
        unsigned int altezza;
};

#endif // FILEIMMAGINE_H
