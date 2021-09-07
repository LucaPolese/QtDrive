#ifndef FILEIMMAGINE_H
#define FILEIMMAGINE_H

#include "filemedia.h"
#include <QIcon>

class FileImmagine: public FileMedia {
    public:
        enum tipo{raster, vettoriale};
        FileImmagine(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate = QDate(1970,1,1), QString = "", compressione = compressione(), tipo = tipo(), unsigned int = 0, unsigned int = 0);
        ~FileImmagine();

        //Funzioni Getter
        unsigned int getLarghezza() const;
        unsigned int getAltezza() const;

        //Funzioni Polimorfe
        QString getInformazioniFile() const override;
        FileImmagine* clone() const override;
        void serializza(QXmlStreamWriter &scrittore) const override;
        FileImmagine* deserializza(QXmlStreamReader& lettore) override;
        QString getTipoFile() const override;

        //Funzione di Ricerca
        bool ricercaAvanzata(QString, Qt::CaseSensitivity) const override;
    private:
        tipo tipoImmagine;
        unsigned int larghezza;
        unsigned int altezza;
};

#endif // FILEIMMAGINE_H
