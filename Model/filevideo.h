#ifndef FILEVIDEO_H
#define FILEVIDEO_H

#include "filemedia.h"
#include "fileaudio.h"
#include <QIcon>

class FileVideo: public FileMedia {
    private:
        QString codec;
        unsigned int durata;
        unsigned int larghezza;
        unsigned int altezza;
        unsigned int fps;

    public:
        FileVideo(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate = QDate(1970,1,1), QString = "", compressione = compressione(), QString = "", unsigned int = 0, unsigned int = 0, unsigned int = 0, unsigned int = 0);
        ~FileVideo();

        const QString &getCodec() const;
        unsigned int getDurata() const;
        unsigned int getLarghezza() const;
        unsigned int getAltezza() const;
        unsigned int getFps() const;

        QString getInformazioniFile() const override;
        FileVideo* clone() const override;
        void serializza(QXmlStreamWriter &scrittore) const override;
        FileVideo* deserializza(QXmlStreamReader &lettore) override;

        QString getTipoFile() const override;
        QIcon getIcona() const override;
};
#endif // FILEVIDEO_H
