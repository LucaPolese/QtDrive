#ifndef INFOFILEWIDGET_H
#define INFOFILEWIDGET_H

#include <QWidget>
#include "../Control/controller.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class InfoFileWidget: public QWidget {
    Q_OBJECT

private:
    Controller* controller;
    QLineEdit* nome;
    QLabel* estensione;
    QLabel* dimensione;
    QLabel* dataCreazione;
    QLabel* dataInserimento;
    QLineEdit* descrizione;
    QPushButton* conferma;
    QPushButton* annulla;
    QString nomeOriginale;
    QString descrizioneOriginale;
    QLabel* informazioniAggiuntive;
    File* fileAperto;
    int indiceAccount;

public:
    InfoFileWidget(Controller *controller_, QWidget *parent = nullptr);
    ~InfoFileWidget();
    void closeEvent(QCloseEvent *event) override;

signals:
    void fileModificato() const;

public slots:
    void visualizzaFile(int, int);
    void controlloModifiche();
};

#endif // INFOFILEWIDGET_H
