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
    QString informazioni;
    if(tipoCompressione == nessuna) informazioni = "Immagine non compressa";
    else if(tipoCompressione == lossy) informazioni = "Immagine lossy";
    else if(tipoCompressione == lossless) informazioni = "Immagine lossless";
    if(tipoImmagine == raster) informazioni += " di tipo raster\n";
    else informazioni += " di tipo vettoriale\n";
    return informazioni + "Risoluzione: " + QString::number(altezza) + "x" + QString::number(larghezza) + " pixels\n";
}

QString FileImmagine::getTipoFile() const {
    return "FileImmagine";
}

FileImmagine* FileImmagine::clone() const {
    return new FileImmagine(*this);
}

void FileImmagine::serializza(QXmlStreamWriter &scrittore) const{
    //Introduzione di ogni account
    scrittore.writeStartElement("file");
    scrittore.writeAttribute("type",getTipoFile());
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

        //Informazioni specifiche di FileMedia:
        //Compressione
        scrittore.writeStartElement("tipoCompressione");
        scrittore.writeCharacters(QString::number(getTipoCompressione()));
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

FileImmagine *FileImmagine::deserializza(QXmlStreamReader &lettore){
    //Informazioni per costruire il sottoggetto di tipo File
    QString _nome;
    QString _estensione;
    unsigned int _dimensione;
    QDate _dataCreazione;
    QDate _dataCaricamento;
    QString _descrizione;
    //Informazioni per copstruire un oggetto di classe FileMedia
    compressione _tipoCompressione;
    //Informazioni per costruire un oggetto di classe FileArchivio
    tipo _tipoImmagine;
    unsigned int _larghezza;
    unsigned int _altezza;

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

    //Lettura Tipo Compressione Media
    if(lettore.readNextStartElement() && lettore.name() == "tipoCompressione") _tipoCompressione = compressione(lettore.readElementText().toInt());

    //Lettura Bitrate
    if(lettore.readNextStartElement() && lettore.name() == "tipoImmagine") _tipoImmagine = tipo(lettore.readElementText().toInt());
    //Lettura Larghezza Immagine
    if(lettore.readNextStartElement() && lettore.name() == "larghezza") _larghezza = lettore.readElementText().toUInt();
    //Lettura Dimensione Immagine
    if(lettore.readNextStartElement() && lettore.name() == "altezza") _altezza = lettore.readElementText().toUInt();

    //Fine della lettura del singolo file
    lettore.skipCurrentElement();
    return new FileImmagine(_nome, _estensione, _dimensione, _dataCreazione, _dataCaricamento,
                 _descrizione, _tipoCompressione, _tipoImmagine, _larghezza, _altezza);

}

bool FileImmagine::ricercaAvanzata(QString input, Qt::CaseSensitivity cs) const {
    if(getInformazioniFile().contains(input, cs))
        return true;
    return false;
}
