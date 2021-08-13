#include "filecanzone.h"

FileCanzone::FileCanzone(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, FileMedia::compressione compressione_, unsigned int bitrate_, unsigned int durata_, QString genere_, QString autore_, QString album_):
FileAudio(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_, compressione_, bitrate_, durata_), genere(genere_), autore(autore_), album(album_){

}

FileCanzone::~FileCanzone() = default;

const QString &FileCanzone::getGenere() const {
    return genere;
}

const QString &FileCanzone::getAutore() const {
    return autore;
}

const QString &FileCanzone::getAlbum() const {
    return album;
}

QString FileCanzone::getInformazioniFile() const {
    return "File canzone";
}

FileCanzone* FileCanzone::clone() const {
    return new FileCanzone(*this);
}
