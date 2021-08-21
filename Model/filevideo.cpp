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

void FileVideo::serializza(QXmlStreamWriter &scrittore) const{
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

        //Informazioni specifiche di FileVideo:
        //Codec
        scrittore.writeStartElement("codec");
        scrittore.writeCharacters(codec);
        scrittore.writeEndElement();

        //Durata
        scrittore.writeStartElement("durata");
        scrittore.writeCharacters(QString::number(durata));
        scrittore.writeEndElement();

        //Larghezza
        scrittore.writeStartElement("larghezza");
        scrittore.writeCharacters(QString::number(larghezza));
        scrittore.writeEndElement();

        //Altezza
        scrittore.writeStartElement("altezza");
        scrittore.writeCharacters(QString::number(altezza));
        scrittore.writeEndElement();

        //FPS
        scrittore.writeStartElement("fps");
        scrittore.writeCharacters(QString::number(fps));
        scrittore.writeEndElement();
    scrittore.writeEndElement();
    if (scrittore.hasError()){
        throw QString("Errore in scrittura di un FileVideo");
    }
}
