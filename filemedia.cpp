#include "filemedia.h"

FileMedia::FileMedia(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, FileMedia::compressione compressione_):
File(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_), tipoCompressione(compressione_){
}

FileMedia::compressione FileMedia::getTipoCompressione() const {
    return tipoCompressione;
}
