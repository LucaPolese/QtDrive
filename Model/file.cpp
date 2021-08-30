#include "file.h"

File::File(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_):
nome(nome_), estensione(estensione_), dimensione(dimensione_), dataCreazione(dataCreazione_), dataCaricamento(dataCaricamento_), descrizione(descrizione_){
}

File::~File(){}

const QString &File::getNome() const {
    return nome;
}

void File::setNome(QString nuovo) {
    nome = nuovo;
}

const QString &File::getEstensione() const {
    return estensione;
}

const QString &File::getDescrizione() const {
    return descrizione;
}

void File::setDescrizione(QString nuova) {
    descrizione = nuova;
}

unsigned int File::getDimensione() const {
    return dimensione;
}

QDate File::getDataCreazione() const {
    return dataCreazione;
}

QDate File::getDataCaricamento() const {
    return dataCaricamento;
}
