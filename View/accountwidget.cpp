#include "accountwidget.h"

AccountWidget::AccountWidget(Controller *controller_, QWidget *parent): QWidget(parent), controller(controller_) {
    setWindowTitle("Aggiungi account");
    setFixedSize(QSize(300,180));
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
    connect(aggiungiAccount, &QPushButton::clicked, this, &AccountWidget::aggiungi);


    // Connessione "Annulla"
    connect(annulla, &QPushButton::clicked, [=]() {
        // pulisco il form
        email->clear();
        password->clear();
        servizio->setCurrentIndex(0);
        spazioFornito->setValue(0);
        emit this->hide();
    });
}

void AccountWidget::aggiungi() {
    QString nEmail = email->text(); email->clear();
    QString nPassword = password->text(); password->clear();
    Account::servizio nServizio;
    switch(servizio->currentIndex()){
        case 0: nServizio = Account::servizio::AmazonDrive; break;
        case 1: nServizio = Account::servizio::Box; break;
        case 2: nServizio = Account::servizio::Dropbox; break;
        case 3: nServizio = Account::servizio::GDrive; break;
        case 4: nServizio = Account::servizio::iCloud; break;
        case 5: nServizio = Account::servizio::Mediafire; break;
        case 6: nServizio = Account::servizio::Mega; break;
        case 7: nServizio = Account::servizio::Next; break;
        case 8: nServizio = Account::servizio::OneDrive; break;
        case 9: nServizio = Account::servizio::Qihoo360; break;
    }
    servizio->setCurrentIndex(0);
    int nSpazioFornito = spazioFornito->value(); spazioFornito->setValue(0);
    controller->aggiungiAccount(nEmail, nPassword, nServizio, nSpazioFornito);
    emit this->hide();
    emit accountAggiunto();
}

void AccountWidget::closeEvent(QCloseEvent *event) {
    // Se l'utente chiude il form premendo la X della finestra, il form viene resettato
    email->clear();
    password->clear();
    servizio->setCurrentIndex(0);
    spazioFornito->setValue(0);
}

AccountWidget::~AccountWidget() = default;
