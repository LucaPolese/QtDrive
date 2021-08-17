#include "filevideo.h"

FileVideo::FileVideo(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, FileMedia::compressione compressione_, QString codec_, unsigned int durata_, unsigned int larghezza_, unsigned int altezza_, unsigned int fps_):
    FileMedia(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_, compressione_), codec(codec_), durata(durata_), larghezza(larghezza_), altezza(altezza_), fps(fps_){
}

FileVideo::~FileVideo() = default;

const QString &FileVideo::getCodec() const {
    return codec;
}

unsigned int FileVideo::getDurata() const {
    return durata;
}

unsigned int FileVideo::getLarghezza() const {
    return larghezza;
}

unsigned int FileVideo::getAltezza() const {
    return altezza;
}

unsigned int FileVideo::getFps() const {
    return fps;
}

QString FileVideo::getInformazioniFile() const {
    return "File video";
}

FileVideo* FileVideo::clone() const {
    return new FileVideo(*this);
}
