#include "fileimmagine.h"

FileImmagine::FileImmagine(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, FileMedia::compressione compressione_, FileImmagine::tipo tipoImmagine_, unsigned int larghezza_, unsigned int altezza_):
    FileMedia(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_, compressione_), tipoImmagine(tipoImmagine_), larghezza(larghezza_), altezza(altezza_){
}

FileImmagine::~FileImmagine() = default;

unsigned int FileImmagine::getAltezza() const {
    return altezza;
}

unsigned int FileImmagine::getLarghezza() const {
    return larghezza;
}

QString FileImmagine::getInformazioniFile() const {
    return "File immagine";
}

FileImmagine* FileImmagine::clone() const {
    return new FileImmagine(*this);
}
