#include "filearchivio.h"

FileArchivio::FileArchivio(QString nome_, QString estensione_, unsigned int dimensione_, QDate dataCreazione_, QDate dataCaricamento_, QString descrizione_, unsigned int dimensioneOriginale_, unsigned int numeroDiFile_, bool protetto_):
File(nome_, estensione_, dimensione_, dataCreazione_, dataCaricamento_, descrizione_), dimensioneOriginale(dimensioneOriginale_), numeroDiFile(numeroDiFile_), protetto(protetto_){
}

FileArchivio::~FileArchivio() = default;

unsigned int FileArchivio::getDimensioneOriginale() const {
    return dimensioneOriginale;
}

unsigned int FileArchivio::getNumeroDiFile() const {
    return numeroDiFile;
}

bool FileArchivio::getProtetto() const {
    return protetto;
}

QString FileArchivio::getInformazioniFile() const {
    return "Archivio";
}

FileArchivio* FileArchivio::clone() const {
    return new FileArchivio(*this);
}

void FileArchivio::serializza(QXmlStreamWriter &scrittore) const{
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

        //Informazioni specifiche di FileArchivio:
        //Dimensione Originale
        scrittore.writeStartElement("dimensioneOriginale");
        scrittore.writeCharacters(QString::number(dimensioneOriginale));
        scrittore.writeEndElement();

        //Numero di File
        scrittore.writeStartElement("numeroDiFile");
        scrittore.writeCharacters(QString::number(numeroDiFile));
        scrittore.writeEndElement();

        //Protetto
        scrittore.writeStartElement("protetto");
        scrittore.writeCharacters(protetto? "si" : "no");
        scrittore.writeEndElement();
    scrittore.writeEndElement();
    if (scrittore.hasError()){
        throw QString("Errore in scrittura di un FileArchivio");
    }
}
