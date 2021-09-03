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
    QString informazioni;
    if(protetto) informazioni = "File archivio protetto da password\n";
    else if(!protetto) informazioni = "File archivio non protetto da password\n";
    return informazioni + "Dimensione del file non compresso: "+QString::number(dimensioneOriginale)+" MB"+"\nNumero di file presenti nell'archivio: "+QString::number(numeroDiFile)+"\n";
}

QString FileArchivio::getTipoFile() const {
    return "FileArchivio";
}

FileArchivio* FileArchivio::clone() const {
    return new FileArchivio(*this);
}

void FileArchivio::serializza(QXmlStreamWriter &scrittore) const{
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

FileArchivio* FileArchivio::deserializza(QXmlStreamReader & lettore){
    //Informazioni per costruire il sottoggetto di tipo File
    QString _nome;
    QString _estensione;
    unsigned int _dimensione;
    QDate _dataCreazione;
    QDate _dataCaricamento;
    QString _descrizione;
    //Informazioni per costruire un oggetto di classe FileArchivio
    unsigned int _dimensioneOriginale;
    unsigned int _numeroDiFile;
    bool _protetto = false;

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

    //Lettura Dimensione File
    if(lettore.readNextStartElement() && lettore.name() == "dimensioneOriginale") _dimensioneOriginale = lettore.readElementText().toUInt();
    //Lettura Dimensione File
    if(lettore.readNextStartElement() && lettore.name() == "numeroDiFile") _numeroDiFile = lettore.readElementText().toUInt();
    //Lettura Dimensione File
    if(lettore.readNextStartElement() && lettore.name() == "protetto") _protetto = lettore.readElementText() == "si" ? 1 : 0;

    //Fine della lettura del singolo file
    lettore.skipCurrentElement();
    return new FileArchivio(_nome, _estensione, _dimensione, _dataCreazione, _dataCaricamento,
                 _descrizione, _dimensioneOriginale, _numeroDiFile, _protetto);

}

QIcon FileArchivio::getIcona() const {
    return QIcon(":res/icons/file/archivio.png");
}

bool FileArchivio::ricercaAvanzata(QString input, Qt::CaseSensitivity cs) const {
    if(getInformazioniFile().contains(input, cs))
        return true;
    return false;
}
