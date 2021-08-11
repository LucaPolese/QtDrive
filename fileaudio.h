#ifndef FILEAUDIO_H
#define FILEAUDIO_H

#include <filemedia.h>

class FileAudio: public FileMedia {
    private:
        unsigned int bitrate;
        unsigned int durata;
        QString genere;
        QString autore;
        QString album;

    public:
        FileAudio(QString, QString, unsigned int, QDate, QDate, QString, FileMedia::compressione, unsigned int, unsigned int, QString, QString, QString);
        ~FileAudio();

        unsigned int getBitrate() const;
        unsigned int getDurata() const;
        const QString &getGenere() const;
        const QString &getAutore() const;
        const QString &getAlbum() const;

        QString getInformazioniFile() const override;
        FileAudio* clone() const override;
};

#endif // FILEAUDIO_H
