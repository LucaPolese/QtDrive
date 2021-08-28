#include "xmlifycopia.h"
XmlifyCopia::XmlifyCopia(const QString& percorsoFile) : account(percorsoFile){}
bool XmlifyCopia::salvaFile(const File* fileDaSalvare1, const File* fileDaSalvare2) const {
    QFile file("C:/Users/xpant/Desktop/prova.xml");
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }
    QXmlStreamWriter scrittore(&file);
    scrittore.setAutoFormatting(true);
    //Inizializzazione del file che conterrà gli account
    scrittore.writeStartDocument();
    scrittore.writeStartElement("files");
    //Scrittura del contenuto del Container di Account
    try{
        fileDaSalvare1->serializza(scrittore);
        fileDaSalvare2->serializza(scrittore);
    }catch(QString s){
        QMessageBox* alert = new QMessageBox(QMessageBox::Warning, "Errore",
                                             QString("Attenzione: errore in scrittura"
                                                     "<br><b>Descrizione:<b> %1").arg(s),
                                             QMessageBox::Ok);
        alert->exec();
        return false;
    }
    //Fine della Scrittura
    scrittore.writeEndElement();
    //Chiusura del File
    scrittore.writeEndDocument();
    return true;
}
