#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QDate>
#include <QXmlStreamWriter>

class File {
    private:
        QString nome;
        QString estensione;
        unsigned int dimensione;
        QDate dataCreazione;
        QDate dataCaricamento;
        QString descrizione;

    public:
        File(QString = "", QString = "", unsigned int = 0, QDate = QDate(1970,1,1), QDate = QDate(1970,1,1), QString = "");
        virtual ~File();


        const QString &getNome() const;
        const QString &getEstensione() const;
        const QString &getDescrizione() const;
        unsigned int getDimensione() const;
        QDate getDataCreazione() const;
        QDate getDataCaricamento() const;

        virtual QString getInformazioniFile() const =0;
        virtual File* clone() const =0;
        virtual void serializza(QXmlStreamWriter& scrittore) const = 0;
        virtual File* deserializza(QXmlStreamReader& lettore) = 0;
};

#endif // FILE_H
