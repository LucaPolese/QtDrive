#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Informazioni su QtDrive");
    setFixedSize(QSize(300,250));

    QPixmap logo = QPixmap(":/res/icons/icon.png");
    QLabel* logoLabel = new QLabel();
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(logo);



    QLabel* testo = new QLabel(tr("Applicazione creata da<br><br><b>Luca Polese</b> <i>matricola 1225425</i><br><br><b>Alessandro Poloni</b> <i>matricola 1224444</i><br><br><br>Corso di <b>Programmazione ad Oggetti</b><br><br>Università di Padova<br>Anno accademico 2020-2021"));
    testo->setAlignment(Qt::AlignCenter);

    setCentralWidget(testo);
}

InfoWidget::~InfoWidget(){
}

