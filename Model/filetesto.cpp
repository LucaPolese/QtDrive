#include "filetesto.h"
#include <iostream>
#include <QDebug>

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
    return "File di testo\nNumero caratteri: " + QString::number(numeroCaratteri) + "\nNumero parole: " + QString::number(numeroParole) + "\n";
}

QString FileTesto::getTipoFile() const {
    return "FileTesto";
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

FileTesto *FileTesto::deserializza(QXmlStreamReader &lettore){
    //Informazioni per costruire il sottoggetto di tipo File
    QString _nome;
    QString _estensione;
    unsigned int _dimensione;
    QDate _dataCreazione;
    QDate _dataCaricamento;
    QString _descrizione;
    //Informazioni per costruire un oggetto di classe FileArchivio
    unsigned int _numeroCaratteri;
    unsigned int _numeroParole;

    //Lettura Nome File
    if(lettore.readNextStartElement() && lettore.name() == "nome") _nome = lettore.readElementText();
    //Lettura Estensione File
    if(lettore.readNextStartElement() && lettore.name() == "estensione") _estensione = lettore.readElementText();
    //Lettura Dimensione File
    if(lettore.readNextStartElement() && lettore.name() == "dimensione") _dimensione = lettore.readElementText().toUInt();
    //Lettura Data Creazione File
    if(lettore.readNextStartElement() && lettore.name() == "dataCreazione") _dataCreazione = QDate::fromString(lettore.readElementText());
    //Lettura Data Caricamento File
    if(lettore.readNextStartElement() && lettore.name() == "dataCaricamento") _dataCaricamento = QDate::fromString(lettore.readElementText());
    //Lettura Descrizione File
    if(lettore.readNextStartElement() && lettore.name() == "descrizione") _descrizione = lettore.readElementText();

    //Lettura Numero Caratteri Testo
    if(lettore.readNextStartElement() && lettore.name() == "numeroCaratteri"){
        _numeroCaratteri = lettore.readElementText().toInt();
    }
    //Lettura Numero Parole Testo
    if(lettore.readNextStartElement() && lettore.name() == "numeroParole") _numeroParole = lettore.readElementText().toInt();

    //Fine della lettura del singolo file
    lettore.skipCurrentElement();
    return new FileTesto(_nome, _estensione, _dimensione, _dataCreazione, _dataCaricamento,
                 _descrizione, _numeroCaratteri, _numeroParole);

}

QIcon FileTesto::getIcona() const {
    return QIcon(":res/icons/file/testo.png");
}

bool FileTesto::ricercaAvanzata(QString input, Qt::CaseSensitivity cs) const {
    if(getInformazioniFile().contains(input, cs))
        return true;
    return false;
}
