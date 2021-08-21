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

void FileAudio::serializza(QXmlStreamWriter &scrittore) const{
    //Introduzione di ogni account
    scrittore.writeStartElement("file");
    scrittore.writeAttribute("type",getInformazioniFile());
        //Aggiunta degli attributi:
        //Nome File
        scrittore.writeStartElement("nome");
        scrittore.writeCharacters(getNome());
        scrittore.writeEndElement();

        //Estensione File
        scrittore.writeStartElement("estensione");
        scrittore.writeCharacters(getEstensione());
        scrittore.writeEndElement();

        //Dimensione File
        scrittore.writeStartElement("dimensione");
        scrittore.writeCharacters(QString::number(getDimensione()));
        scrittore.writeEndElement();

        //Data di Creazione File
        scrittore.writeStartElement("dataCreazione");
        scrittore.writeCharacters(getDataCreazione().toString());
        scrittore.writeEndElement();

        //Data di Caricamento File
        scrittore.writeStartElement("dataCaricamento");
        scrittore.writeCharacters(getDataCaricamento().toString());
        scrittore.writeEndElement();

        //Descrizione File
        scrittore.writeStartElement("descrizione");
        scrittore.writeCharacters(getDescrizione());
        scrittore.writeEndElement();

        //Informazioni specifiche di FileAudio:
        //Dimensione Originale
        scrittore.writeStartElement("bitrate");
        scrittore.writeCharacters(QString::number(bitrate));
        scrittore.writeEndElement();

        //Numero di File
        scrittore.writeStartElement("durata");
        scrittore.writeCharacters(QString::number(durata));
        scrittore.writeEndElement();
    scrittore.writeEndElement();
    if (scrittore.hasError()){
        throw QString("Errore in scrittura di un FileAudio");
    }
}
