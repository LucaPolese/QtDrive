#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Informazioni su QtDrive");
    this->setFixedSize(QSize(300,250));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setAlignment(Qt::AlignCenter);


    QLabel* testo = new QLabel("Applicazione creata da\nLuca Polese matricola 1225425\n Alessandro Poloni matricola 1224444\n per il corso di Programmazione ad Oggetti\nAnno accademico 2020-2021");
    testo->setAlignment(Qt::AlignCenter);

    layout->addWidget(testo);
    setCentralWidget(testo);
}



InfoWidget::~InfoWidget(){
}

