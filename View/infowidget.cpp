#include "infowidget.h"

InfoWidget::InfoWidget(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Informazioni su QtDrive");
    this->setFixedSize(QSize(300,250));

    QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(0,0,0,0);
        mainLayout->setAlignment(Qt::AlignCenter);
        QLabel* creato = new QLabel("Applicazione creata da Alessandro Poloni e Luca Polese\n per il corso di Programmazione ad Oggetti.");
        mainLayout->addWidget(creato);
        setCentralWidget(creato);
}



InfoWidget::~InfoWidget(){
}

