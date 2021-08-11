#include "filetesto.h"

FileTesto::FileTesto(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, unsigned int numeroCaratteri_, unsigned int numeroParole_):
File(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_), numeroCaratteri(numeroCaratteri_), numeroParole(numeroParole_){
}

FileTesto::~FileTesto() = default;

unsigned int FileTesto::getNumeroCaratteri() const {
    return numeroCaratteri;
}

unsigned int FileTesto::getNumeroParole() const {
    return numeroParole;
}

QString FileTesto::getInformazioniFile() const {
    return "Prova";
}

FileTesto* FileTesto::clone() const {
    return new FileTesto(*this);
}
