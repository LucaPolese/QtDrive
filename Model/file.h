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

        //Funzioni Getter
        const QString &getNome() const;
        const QString &getEstensione() const;
        unsigned int getDimensione() const;
        QDate getDataCreazione() const;
        QDate getDataCaricamento() const;
        const QString &getDescrizione() const;

        //Funzioni Setter
        void setNome(QString);
        void setDescrizione(QString);

        //Funzioni Polimorfe
        virtual QString getInformazioniFile() const =0;
        virtual File* clone() const =0;
        virtual void serializza(QXmlStreamWriter& scrittore) const = 0;
        virtual File* deserializza(QXmlStreamReader& lettore) = 0;
        virtual QString getTipoFile() const =0;

        //Funzioni di Ricerca
        bool ricercaNome(QString, Qt::CaseSensitivity) const;
        bool ricercaDescrizione(QString, Qt::CaseSensitivity) const;
        virtual bool ricercaAvanzata(QString, Qt::CaseSensitivity) const = 0;
};

#endif // FILE_H
