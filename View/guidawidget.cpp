#include "guidawidget.h"

GuidaWidget::GuidaWidget() {
    setWindowTitle("Guida");
    setFixedSize(QSize(400, 200));

    QTextBrowser* testo = new QTextBrowser();
    testo->setText(tr(
    "<h1>QtDrive</h1>"
    "<b>Funzionalità del menù</b><br><br>"
    "<img src=\":res/icons/menubar/apri.png\"/> <b>Apri</b><br>Consente di aprire un file...<br><br>"
    "<img src=\":res/icons/menubar/salva.png\"/> <b>Salva</b><br>Consente di salvare un file...<br><br>"
    "<img src=\":res/icons/menubar/esci.png\"/> <b>Esci</b><br>Chiude l'applicazione.<br><br>"

    ));

    setCentralWidget(testo);
}
