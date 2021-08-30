#ifndef FILEMEDIA_H
#define FILEMEDIA_H

#include "file.h"
#include <QIcon>

class FileMedia: public File {
    public:
        enum compressione { // ENUM PUBBLICO?
            nessuna, lossless, lossy
        };

        FileMedia(QString, QString, unsigned int, QDate, QDate, QString, compressione);

        compressione getTipoCompressione() const;

    protected:
        compressione tipoCompressione;

};

#endif // FILEMEDIA_H
