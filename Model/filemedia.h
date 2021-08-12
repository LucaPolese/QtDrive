#ifndef FILEMEDIA_H
#define FILEMEDIA_H

#include "file.h"

class FileMedia: public File {
    public:
        enum compressione { // ENUM PUBBLICO?
            nessuna, lossless, lossy
        };

        FileMedia(QString, QString, unsigned int, QDate, QDate, QString, compressione);

        compressione getTipoCompressione() const;

    private:
        compressione tipoCompressione;

};

#endif // FILEMEDIA_H
