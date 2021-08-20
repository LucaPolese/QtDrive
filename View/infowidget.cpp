#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent): QWidget(parent){
    setWindowTitle("Informazioni su QtDrive");
    setFixedSize(QSize(300,250));

    QTextBrowser* testo = new QTextBrowser();
    testo->setText(tr(
    "<img src=\":res/icons/icon.png\" width=\"64\" height=\"64\"><br>"
    "<b>QtDrive</b><br><br>"
    "Applicazione creata da<br><b>Luca Polese</b> <i>matricola 1225425</i><br><b>Alessandro Poloni</b> <i>matricola 1224444</i><br><br><br>Corso di <b>Programmazione ad Oggetti</b><br><br>Università di Padova<br>Anno accademico 2020-2021"
    ));
    testo->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(testo);
    setLayout(layout);

    // Shortcut Ctrl+I per chiudere il widget
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_I), this);
    connect(shortcut, &QShortcut::activated, [=]{
        emit this->close();
    });
}

InfoWidget::~InfoWidget(){
}

