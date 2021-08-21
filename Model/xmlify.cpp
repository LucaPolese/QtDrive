#include "xmlify.h"

Xmlify::Xmlify(const QString& percorsoFile) : account(percorsoFile){}

/*void Xmlify::salvaAccount(const Container<Deepptr<Account>>& listaAccount) const {
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter w(&file);
    w.writeStartDocument();
    w.writeStartElement("partita");
    w.writeTextElement("seed", QString::number(Controller::getSeed()));
    w.writeStartElement("tavolo");
    w.writeTextElement("tipo", QString(QChar(controller_->cartaSulTavoloChar())));
    if (controller_->cartaSulTavoloColore() != -1) {
        w.writeTextElement("colore", QString::number(controller_->cartaSulTavoloColore()));
    } else {
        w.writeTextElement("colore", "N");
    }
    w.writeEndElement();
    for (int i = 0; i < controller_->getNumeroGiocatori(); ++i) {
        w.writeStartElement("giocatore");
        for (int j = 0; j < controller_->getNumeroCarte(i); ++j) {
            w.writeStartElement("carta");
            w.writeTextElement("tipo", QString(QChar(controller_->cartaInManoChar(i, j))));
            if (controller_->cartaInManoColore(i, j) != -1) {
                w.writeTextElement("colore", QString::number(controller_->cartaInManoColore(i, j)));
            } else {
                w.writeTextElement("colore", "N");
            }
            w.writeEndElement();
        }
        w.writeEndElement();
    }
    w.writeEndElement();
    w.writeEndDocument();
}


Container<Deepptr<Account>> Xmlify::acquisisciAccount() const{
    Container<Deepptr<Account>> accountLetti;
    QFile file(account);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox* alert = new QMessageBox(QMessageBox::Warning, "Errore! ","Attenzione: non è possibile leggere il file che hai tentato di aprire.",QMessageBox::Ok);
        alert->exec();
        throw ErroreAperturaFile();
        return accountLetti;
    }

    QXmlStreamReader reader(&file);

    // Inizio a leggere il file XML
    if(reader.readNextStartElement() && reader.name() == "serverList")
    {
        while(reader.readNextStartElement())
        {
            try
            {
                qontainer.pushBack(Server::dataUnserialize(reader));
            }
            catch(std::string s)
            {
                QMessageBox box(QMessageBox::Warning,
                                "Errore caricamento file",
                                QString("Non è stato possibile caricare il file a causa di un errore nella lettura. "
                                "<br><u>Motivo:</u> %1").arg(QString::fromStdString(s)),
                                QMessageBox::Ok);
                box.exec();
                throw 1;
            }
        }
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,
                        "Errore caricamento file",
                        "Non è stato possibile leggere il file dal momento che "
                        "il contenuto non è stato riconosciuto.",
                        QMessageBox::Ok);
        box.exec();
        throw 1;
    }

    file.close();
    return qontainer;
}

bool Xmlify::scriviAccount(const Container<Deepptr<Account> > &) const
{

}*/

bool Xmlify::salvaAccount(const Container<Deepptr<Account>>& listaAccount) const {

    QFile file(account);

    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QXmlStreamWriter scrittore(&file);

    scrittore.setAutoFormatting(true);

    //Inizializzazione del contenuto
    scrittore.writeStartDocument();
    scrittore.writeStartElement("accountList");

    //Scrittura del contenuto del Container di Account
    try{
        for(auto cit = listaAccount.begin(); cit != listaAccount.end(); ++cit) (*cit)->serializza(scrittore);
    }catch(std::string s){
        return false;
    }

    scrittore.writeEndElement();
    scrittore.writeEndDocument();

    //file.commit();
    return true;
}
