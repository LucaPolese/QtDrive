#include "guidawidget.h"

GuidaWidget::GuidaWidget(QWidget *parent): QWidget(parent){
    setWindowTitle("Guida");
    setMinimumSize(QSize(800, 600));
    setMaximumSize(QSize(1024, 720));

    QTextBrowser* testo = new QTextBrowser();
    testo->setText(tr(
    "<h1>QtDrive</h1>"
    "<b>Funzionalità del menù</b><br><br>"
    "<img src=\":res/icons/menubar/apri.png\"/> <b>Apri</b><br>Consente di aprire un file...<br><br>"
    "<img src=\":res/icons/menubar/salva.png\"/> <b>Salva</b><br>Consente di salvare un file...<br><br>"
    "<img src=\":res/icons/menubar/esci.png\"/> <b>Esci</b><br>Chiude l'applicazione.<br><br>"

    ));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(testo);
    setLayout(layout);

    // Shortcut Ctrl+H per chiudere il widget
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_H), this);
    connect(shortcut, &QShortcut::activated, [=]{
        emit this->close();
    });
}
