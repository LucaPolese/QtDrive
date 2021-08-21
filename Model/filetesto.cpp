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

void FileTesto::serializza(QXmlStreamWriter &scrittore) const{
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

        //Informazioni specifiche di FileTesto:
        //Numero di Caratteri
        scrittore.writeStartElement("numeroCaratteri");
        scrittore.writeCharacters(QString::number(numeroCaratteri));
        scrittore.writeEndElement();

        //Numero di Parole
        scrittore.writeStartElement("numeroParole");
        scrittore.writeCharacters(QString::number(numeroParole));
        scrittore.writeEndElement();
    scrittore.writeEndElement();
    if (scrittore.hasError()){
        throw QString("Errore in scrittura di un FileTesto");
    }
}
