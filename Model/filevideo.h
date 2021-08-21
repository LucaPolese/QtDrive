#ifndef FILEVIDEO_H
#define FILEVIDEO_H

#include "filemedia.h"
#include "fileaudio.h"

class FileVideo: public FileMedia {
    private:
        QString codec;
        unsigned int durata;
        unsigned int larghezza;
        unsigned int altezza;
        unsigned int fps;

    public:
        FileVideo(QString, QString, unsigned int, QDate, QDate, QString, FileMedia::compressione, QString, unsigned int, unsigned int, unsigned int, unsigned int);
        ~FileVideo();

        const QString &getCodec() const;
        unsigned int getDurata() const;
        unsigned int getLarghezza() const;
        unsigned int getAltezza() const;
        unsigned int getFps() const;

        QString getInformazioniFile() const override;
        FileVideo* clone() const override;
        void serializza(QXmlStreamWriter &scrittore) const override;
};
#endif // FILEVIDEO_H
