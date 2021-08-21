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
        File(QString, QString, unsigned int, QDate, QDate, QString);
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
};

#endif // FILE_H
