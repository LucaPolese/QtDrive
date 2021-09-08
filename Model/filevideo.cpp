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
    QString informazioni;
    if(tipoCompressione == nessuna) informazioni = "File video non compresso\n";
    else if(tipoCompressione == lossy) informazioni = "File video lossy\n";
    else if(tipoCompressione == lossless) informazioni = "File video lossless\n";
    return informazioni + "Durata: " + QDateTime::fromTime_t(durata*60).toUTC().toString("hh:mm:ss") + "\nCodec: " + codec + "\nFPS: " + QString::number(fps) + "\nRisoluzione: " + QString::number(larghezza) + "x" + QString::number(altezza) + " pixels\n";
}

QString FileVideo::getTipoFile() const {
    return "FileVideo";
}

FileVideo* FileVideo::clone() const {
    return new FileVideo(*this);
}

void FileVideo::serializza(QXmlStreamWriter &scrittore) const{
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

FileVideo *FileVideo::deserializza(QXmlStreamReader &lettore){
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
    QString _codec;
    unsigned int _durata;
    unsigned int _larghezza;
    unsigned int _altezza;
    unsigned int _fps;

    //Lettura Nome File
    if(lettore.readNextStartElement() && lettore.name() == "nome") _nome = lettore.readElementText();
    //Lettura Estensione File
    if(lettore.readNextStartElement() && lettore.name() == "estensione") _estensione = lettore.readElementText();
    //Lettura Dimensione File
    if(lettore.readNextStartElement() && lettore.name() == "dimensione") _dimensione = lettore.readElementText().toInt();
    //Lettura Data Creazione File
    if(lettore.readNextStartElement() && lettore.name() == "dataCreazione") _dataCreazione = QDate::fromString(lettore.readElementText());
    //Lettura Data Caricamento File
    if(lettore.readNextStartElement() && lettore.name() == "dataCaricamento") _dataCaricamento = QDate::fromString(lettore.readElementText());
    //Lettura Descrizione File
    if(lettore.readNextStartElement() && lettore.name() == "descrizione") _descrizione = lettore.readElementText();

    //Lettura Tipo Compressione Media
    if(lettore.readNextStartElement() && lettore.name() == "tipoCompressione") _tipoCompressione = compressione(lettore.readElementText().toInt());

    //Lettura Codec Video
    if(lettore.readNextStartElement() && lettore.name() == "codec") _codec = lettore.readElementText();
    //Lettura Durata Video
    if(lettore.readNextStartElement() && lettore.name() == "durata") _durata = lettore.readElementText().toInt();
    //Lettura Larghezza Video
    if(lettore.readNextStartElement() && lettore.name() == "larghezza") _larghezza = lettore.readElementText().toInt();
    //Lettura Altezza Video
    if(lettore.readNextStartElement() && lettore.name() == "altezza") _altezza = lettore.readElementText().toInt();
    //Lettura FPS Video
    if(lettore.readNextStartElement() && lettore.name() == "fps") _fps = lettore.readElementText().toInt();

    //Fine della lettura del singolo file
    lettore.skipCurrentElement();
    return new FileVideo(_nome, _estensione, _dimensione, _dataCreazione, _dataCaricamento,
                 _descrizione, _tipoCompressione, _codec, _durata, _larghezza, _altezza, _fps);

}

bool FileVideo::ricercaAvanzata(QString input, Qt::CaseSensitivity cs) const {
    if(getInformazioniFile().contains(input, cs))
        return true;
    return false;
}
