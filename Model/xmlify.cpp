#include "xmlify.h"

Xmlify::Xmlify(const QString& percorsoFile) : account(percorsoFile){}

bool Xmlify::salvaAccount(const Container<Deepptr<Account>>& listaAccount) const {

    QFile file(account);

    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QXmlStreamWriter scrittore(&file);

    scrittore.setAutoFormatting(true);

    //Inizializzazione del file che conterrà gli account
    scrittore.writeStartDocument();
    scrittore.writeStartElement("listaAccount");

    //Scrittura del contenuto del Container di Account
    try{
        for(auto cit = listaAccount.begin(); cit != listaAccount.end(); ++cit) (*cit)->serializza(scrittore);
    }catch(QString s){
        throw s;
    }

    //Fine della Scrittura
    scrittore.writeEndElement();
    //Chiusura del File
    scrittore.writeEndDocument();

    return true;
}

Container<Deepptr<Account>> Xmlify::acquisisciAccount() const{
    Container<Deepptr<Account>> letturaAccount;
    QFile file(account);
    if(file.size() == 0){
        QMessageBox* alert = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: il file che hai tentato di aprire è vuoto",
                                             QMessageBox::Ok);
        alert->exec();
        return letturaAccount;

    }

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox* alert = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: il file che hai tentato di aprire non può essere letto",
                                             QMessageBox::Ok);
        alert->exec();
        return letturaAccount;
    }

    QXmlStreamReader lettore(&file);

    // Inizio a leggere il file XML
    if(lettore.readNextStartElement() && lettore.name() == "listaAccount"){

        //Inizio lettura di tutti gli account
        while(lettore.readNextStartElement()){
            try{
                //Aggiunta di tutti gli account letti
                letturaAccount.push_back(Deepptr<Account>(Account::deserializza(lettore)));
            }catch(QString s){
                QMessageBox box(QMessageBox::Warning,
                                "Errore",
                                QString("Il file che hai scelto non può essere caricato per un errore in lettura. "
                                "<br><b>Descrizione:</b> %1").arg(s),
                                QMessageBox::Ok);
                box.exec();
            }
        }
        lettore.skipCurrentElement();
    }else{
        QMessageBox box(QMessageBox::Critical,
                        "Errore",
                        "Le informazioni contenute in questo file non rispecchiano la struttura originale."
                        "<br><b>Verificare:</b> "
                        "<ul><li>Che il contenuto non sia corrotto</li><li>Di aver selezionato il file corretto</li></ul>",
                        QMessageBox::Ok);
        box.exec();
    }

    file.close();
    return letturaAccount;
}
