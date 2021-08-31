#ifndef FILEAUDIO_H
#define FILEAUDIO_H

#include "filemedia.h"
#include <QIcon>

class FileAudio: public FileMedia {
private:

    unsigned int bitrate;
    unsigned int durata;

public:
    FileAudio(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate = QDate(1970,1,1), QString = "", compressione = compressione(), unsigned int = 0, unsigned int = 0);
    ~FileAudio();

    unsigned int getBitrate() const;
    unsigned int getDurata() const;

    QString getInformazioniFile() const override;
    FileAudio* clone() const override;
    void serializza(QXmlStreamWriter &scrittore) const override;
    FileAudio* deserializza(QXmlStreamReader& lettore) override;

    QString getTipoFile() const override;
    QIcon getIcona() const override;
};

#endif // FILEAUDIO_H
