#include "accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) : QWidget(parent){
    setWindowTitle("Aggiungi account");
    setFixedSize(QSize(300,180));
    controller = new Controller;
    layout = new QVBoxLayout;
    formLayout = new QFormLayout;

    email = new QLineEdit;
    formLayout->addRow(tr("&Email:"), email);

    password = new QLineEdit;
    formLayout->addRow(tr("&Password:"), password);

    servizio = new QComboBox;
    servizio->addItem("AmazonDrive"); servizio->setItemIcon(0, QIcon(":res/icons/AmazonDrive.ico"));
    servizio->addItem("Box"); servizio->setItemIcon(1, QIcon(":res/icons/Box.ico"));
    servizio->addItem("Dropbox"); servizio->setItemIcon(2, QIcon(":res/icons/Dropbox.ico"));
    servizio->addItem("GDrive"); servizio->setItemIcon(3, QIcon(":res/icons/GDrive.ico"));
    servizio->addItem("iCloud"); servizio->setItemIcon(4, QIcon(":res/icons/iCloud.ico"));
    servizio->addItem("Mediafire"); servizio->setItemIcon(5, QIcon(":res/icons/Mediafire.ico"));
    servizio->addItem("Mega"); servizio->setItemIcon(6, QIcon(":res/icons/Mega.ico"));
    servizio->addItem("Next"); servizio->setItemIcon(7, QIcon(":res/icons/Next.ico"));
    servizio->addItem("OneDrive"); servizio->setItemIcon(8, QIcon(":res/icons/OneDrive.ico"));
    servizio->addItem("Qihoo360"); servizio->setItemIcon(9, QIcon(":res/icons/Qihoo360.ico"));
    formLayout->addRow(tr("Servizio:"), servizio);

    spazioFornito = new QSpinBox;
    spazioFornito->setAlignment(Qt::AlignRight);
    formLayout->addRow(tr("Spazio fornito (GB):"), spazioFornito);

    buttonLayout = new QHBoxLayout;
    aggiungiAccount  = new QPushButton("Aggiungi");
    annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(aggiungiAccount);
    buttonLayout->addWidget(annulla);

    layout->addLayout(formLayout);
    layout->addLayout(buttonLayout);
    setLayout(layout);

    // Connessione "Aggiungi"
    connect(aggiungiAccount, &QPushButton::clicked, [=]() {
            qDebug() << email->text();
            controller->aggiungiAccount();
       });

    // Connessione "Annulla"
    connect(annulla, &QPushButton::clicked, [=]() {
        emit this->close();
    });
}
