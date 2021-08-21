#ifndef FILEAUDIO_H
#define FILEAUDIO_H

#include "filemedia.h"

class FileAudio: public FileMedia {
private:
    unsigned int bitrate;
    unsigned int durata;

public:
    FileAudio(QString, QString, unsigned int, QDate, QDate, QString, FileMedia::compressione, unsigned int, unsigned int);
    ~FileAudio();

    unsigned int getBitrate() const;
    unsigned int getDurata() const;

    QString getInformazioniFile() const override;
    FileAudio* clone() const override;
    void serializza(QXmlStreamWriter &scrittore) const override;
};

#endif // FILEAUDIO_H
