#include "guidawidget.h"
#include <QTextBrowser>

GuidaWidget::GuidaWidget(QWidget *parent): QWidget(parent){
    setWindowTitle("Guida");
    setWindowIcon(QIcon(":res/icons/menubar/guida.png"));
    setMinimumSize(QSize(800, 600));
    setMaximumSize(QSize(1024, 720));
/*
    QTextBrowser* testo = new QTextBrowser();
    testo->setText(tr(
        "<h1>QtDrive</h1><br>"
        "<b>Funzionalità del menù</b><br><br>"
        "<img src=\":res/icons/menubar/apri.png\"/> <b>Apri</b><br>Consente di caricare le informazioni degli account gestiti da QtDrive da un opportuno file in formato XML. All'avvio dell'applicazione, di default, viene creato il file account.xml.<br><br>"
        "<img src=\":res/icons/menubar/salva.png\"/> <b>Salva</b><br>Consente di salvare le modifiche al file correntemente aperto.<br><br>"
        "<img src=\":res/icons/menubar/esci.png\"/> <b>Esci</b><br>Chiude l'applicazione.<br><br>"
        "<img src=\":res/icons/menubar/guida.png\"/> <b>Guida</b><br>Apre la guida in linea.<br><br>"
        "<img src=\":res/icons/menubar/info.png\"/> <b>Informazioni su QtDrive</b><br>Visualizza informazioni sull'applicazione.<br><br><br>"

        "<b>Interfaccia principale</b><br>"
        "L'interfaccia principale è costituita da tre schede: Account, File e Ricerca.<br><br>"

        "<b>Account</b><br>"
        "Da questa scheda è possibile inserire un nuovo account da gestire tramite l'applicazione e visualizzare gli altri account già registrati."
        "Premendo il pulsante <img src=\":res/icons/pulsanti/aggiungiAccount.png\" style=\"width:16px\"><b>Aggiungi account</b>, l'utente può inserire un nuovo account, specificando indirizzo email e password, il servizio di cloud e lo spazio a disposizione.<br>"
        "Selezionando dalla lista uno specifico account, l'utente può visualizzare ulteriori informazioni, come lo spazio rimasto a disposizione e la distribuzione dei diversi tipi di file all'interno dell'account."
        "È inoltre possibile modificare email e password dell'account, per salvare le modifiche è suffciente premere il pulsante <img src=\":res/icons/pulsanti/modifica.png\" style=\"width:16px\"><b>Modifica</b>."
        "L'utente che non volesse più gestire uno specifico account con questo applicativo può infine selezionare il pulsante <img src=\":res/icons/pulsanti/elimina.png\" style=\"width:16px\"/><b>Elimina</b> per rimuoverlo dalla lista."


    ));*/

    QTextBrowser *tb = new QTextBrowser;
    tb->setOpenExternalLinks(true);
    tb->setSource(QUrl("qrc:res/guida.html"));


    QVBoxLayout* layout = new QVBoxLayout();
    //layout->addWidget(testo);
    layout->addWidget(tb);
    setLayout(layout);

    // Shortcut Ctrl+H per chiudere il widget
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_H), this);
    connect(shortcut, &QShortcut::activated, [=]{
        close();
    });
}
