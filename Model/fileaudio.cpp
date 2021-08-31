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
    QString informazioni;
    if(tipoCompressione == nessuna) informazioni = "File audio non compresso\n";
    else if(tipoCompressione == lossy) informazioni = "File audio lossy\n";
    else if(tipoCompressione == lossless) informazioni = "File audio lossless\n";
    return informazioni + "Bitrate: " + QString::number(bitrate) + " kbit/s" + "\nDurata: " + QDateTime::fromTime_t(durata).toUTC().toString("hh:mm:ss") + "\n";
}

QString FileAudio::getTipoFile() const {
    return "FileAudio";
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

        //Informazioni specifiche di FileMedia:
        //Compressione
        scrittore.writeStartElement("tipoCompressione");
        scrittore.writeCharacters(QString::number(getTipoCompressione()));
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

FileAudio* FileAudio::deserializza(QXmlStreamReader & lettore){
    //Informazioni per costruire il sottoggetto di tipo File
    QString _nome;
    QString _estensione;
    unsigned int _dimensione;
    QDate _dataCreazione;
    QDate _dataCaricamento;
    QString _descrizione;
    //Informazioni per costruire un oggetto di classe FileMedia
    compressione _tipoCompressione;
    //Informazioni per costruire un oggetto di classe FileArchivio
    unsigned int _bitrate;
    unsigned int _durata;

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

    //Lettura Bitrate Audio
    if(lettore.readNextStartElement() && lettore.name() == "bitrate") _bitrate = lettore.readElementText().toUInt();
    //Lettura Durata Audio
    if(lettore.readNextStartElement() && lettore.name() == "durata") _durata = lettore.readElementText().toUInt();

    //Fine della lettura del singolo file
    lettore.skipCurrentElement();
    return new FileAudio(_nome, _estensione, _dimensione, _dataCreazione, _dataCaricamento,
                 _descrizione, _tipoCompressione, _bitrate, _durata);

}

QIcon FileAudio::getIcona() const {
    return QIcon(":res/icons/file/audio.png");
}
