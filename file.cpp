#include "file.h"

File::File(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_):
nome(nome_), estensione(estensione_), dimensione(dimensione_), dataCreazione(dataCreazione_), dataCaricamento(dataCaricamento_), descrizione(descrizione_){
}

const QString &File::getNome() const {
    return nome;
}

const QString &File::getEstensione() const {
    return estensione;
}

const QString &File::getDescrizione() const {
    return descrizione;
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
