#include "fileaudio.h"

FileAudio::FileAudio(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, FileMedia::compressione compressione_, unsigned int bitrate_, unsigned int durata_):
    FileMedia(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_, compressione_), bitrate(bitrate_), durata(durata_) {
}

FileAudio::~FileAudio() = default;

unsigned int FileAudio::getBitrate() const {
    return bitrate;
}

unsigned int FileAudio::getDurata() const {
    return durata;
}

QString FileAudio::getInformazioniFile() const {
    return "File audio";
}

FileAudio* FileAudio::clone() const {
    return new FileAudio(*this);
}
