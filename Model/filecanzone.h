#ifndef FILECANZONE_H
#define FILECANZONE_H

#include "fileaudio.h"

class FileCanzone: public FileAudio {
    private:
        QString genere;
        QString autore;
        QString album;
    public:
        FileCanzone(QString, QString, unsigned int, QDate, QDate, QString, FileMedia::compressione, unsigned int, unsigned int, QString, QString, QString);
        ~FileCanzone();

        const QString &getGenere() const;
        const QString &getAutore() const;
        const QString &getAlbum() const;

        QString getInformazioniFile() const override;
        FileCanzone* clone() const override;
};

#endif // FILECANZONE_H
