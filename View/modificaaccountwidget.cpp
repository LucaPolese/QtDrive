#include "modificaaccountwidget.h"

ModificaAccountWidget::ModificaAccountWidget(Controller *controller_, QWidget *parent): QWidget(parent), controller(controller_) {
    setWindowTitle("Modifica account");
    setFixedSize(QSize(300,100));
    setWindowIcon(QIcon(":res/icons/tabs/tab1.png"));

    QVBoxLayout* layout = new QVBoxLayout;
    QFormLayout* formLayout = new QFormLayout;

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);
    nuovaEmail = new QLineEdit;
    nuovaEmail->setValidator(new QRegularExpressionValidator(rx, this));
    formLayout->addRow("Email:", nuovaEmail);

    nuovaPassword = new QLineEdit;
    formLayout->addRow("Password:", nuovaPassword);

    QHBoxLayout* layoutPulsanti = new QHBoxLayout;
    salva = new QPushButton("Salva");
    connect(salva, &QPushButton::clicked, this, &ModificaAccountWidget::salvaModifiche);
    layoutPulsanti->addWidget(salva);
    annulla = new QPushButton("Annulla");
    connect(annulla, &QPushButton::clicked, this, &ModificaAccountWidget::annullaModifiche);
    layoutPulsanti->addWidget(annulla);

    layout->addLayout(formLayout);
    layout->addLayout(layoutPulsanti);
    setLayout(layout);
}

void ModificaAccountWidget::visualizzaInfo(int indice, QString email, QString password) {
    nuovaEmail->setText(email);
    nuovaPassword->setText(password);
    indiceAccountAperto = indice;
}

void ModificaAccountWidget::salvaModifiche(){
    Account* a = controller->getAccount(indiceAccountAperto);
    bool ok = true;
    if(!nuovaEmail->hasAcceptableInput()) {
        QMessageBox::warning(this, tr("Errore"), tr("Indirizzo email non valido."), QMessageBox::Ok);
        nuovaEmail->setText(a->getEmail());
        ok = false;
    }
    else if(nuovaPassword->text() == "") {
        QMessageBox::warning(this, tr("Errore"), tr("Password non valida."), QMessageBox::Ok);
        nuovaPassword->setText(a->getPassword());
        ok = false;
    }
    if(ok){
        if(a->getEmail() != nuovaEmail->text() || a->getPassword() != nuovaPassword->text()) {
            if(controller->checkAccount(nuovaEmail->text(), a->getHost())){
                QMessageBox messageBox(QMessageBox::Question, tr("Modifica account"), tr("Salvare le modifiche effettuate?"), QMessageBox::Yes | QMessageBox::No, this);
                messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
                messageBox.setButtonText(QMessageBox::No, tr("No"));
                int ret = messageBox.exec();
                if(ret == QMessageBox::Yes) {
                    controller->setModificato(true);
                    controller->salvaModificaAccount(indiceAccountAperto, nuovaEmail->text(), nuovaPassword->text());
                    hide();
                    emit accountModificato();
                }
            } else {
                QMessageBox::warning(this, tr("Errore"), tr("Email già associata ad un altro account."), QMessageBox::Ok);
            }
        }
        else hide();
    }
}

void ModificaAccountWidget::annullaModifiche() {
    hide();
}

ModificaAccountWidget::~ModificaAccountWidget() = default;
