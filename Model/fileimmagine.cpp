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

void FileImmagine::serializza(QXmlStreamWriter &scrittore) const{
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

        //Informazioni specifiche di FileImmagine:
        //Tipo di Immagine
        scrittore.writeStartElement("tipoImmagine");
        scrittore.writeCharacters(QString::number(tipoImmagine));
        scrittore.writeEndElement();

        //Larghezza
        scrittore.writeStartElement("larghezza");
        scrittore.writeCharacters(QString::number(larghezza));
        scrittore.writeEndElement();

        //Altezza
        scrittore.writeStartElement("altezza");
        scrittore.writeCharacters(QString::number(altezza));
        scrittore.writeEndElement();
    scrittore.writeEndElement();
    if (scrittore.hasError()){
        throw QString("Errore in scrittura di un FileImmagine");
    }
}

