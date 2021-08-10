#include "filearchivio.h"

FileArchivio::FileArchivio(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, unsigned int dimensioneOriginale_, unsigned int numeroDiFile_, bool protetto_):
File(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_), dimensioneOriginale(dimensioneOriginale_), numeroDiFile(numeroDiFile_), protetto(protetto_){
}

unsigned int FileArchivio::getDimensioneOriginale() const {
    return dimensioneOriginale;
}

unsigned int FileArchivio::getNumeroDiFile() const {
    return numeroDiFile;
}

bool FileArchivio::getProtetto() const {
    return protetto;
}
