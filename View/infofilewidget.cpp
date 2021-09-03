#include "infofilewidget.h"
#include <QDebug>

InfoFileWidget::InfoFileWidget(Controller *controller_, QWidget *parent): QWidget(parent), controller(controller_) {
    setWindowTitle("Informazioni file");

    QVBoxLayout* layout = new QVBoxLayout;
    QFormLayout* layoutInfo = new QFormLayout;

    nome = new QLineEdit;
    nome->setMaxLength(50);
    layoutInfo->addRow("Nome:", nome);

    estensione = new QLabel;
    layoutInfo->addRow("Estensione:", estensione);

    dimensione = new QLabel;
    layoutInfo->addRow("Dimensione:", dimensione);

    dataCreazione = new QLabel;
    layoutInfo->addRow("Data creazione:", dataCreazione);

    dataInserimento = new QLabel;
    layoutInfo->addRow("Data inserimento:", dataInserimento);

    descrizione = new QLineEdit;
    descrizione->setMaxLength(255);
    layoutInfo->addRow("Descrizione:", descrizione);

    layoutInfo->addRow("", new QLabel); // Riga per aggiungere spazio

    QHBoxLayout* layoutPulsanti = new QHBoxLayout;
    conferma = new QPushButton("Conferma"); conferma->setFixedSize(conferma->sizeHint());
    layoutPulsanti->addWidget(conferma);
    annulla = new QPushButton("Annulla"); annulla->setFixedSize(annulla->sizeHint());
    layoutPulsanti->addWidget(annulla);

    informazioniAggiuntive = new QLabel;

    layout->addLayout(layoutInfo);
    layout->addWidget(informazioniAggiuntive);
    layout->addLayout(layoutPulsanti);

    setLayout(layout);

    connect(conferma, &QPushButton::clicked, this, &InfoFileWidget::controlloModifiche);

    connect(annulla, &QPushButton::clicked, [=]{
        hide();
    });
}

void InfoFileWidget::visualizzaFile(int indiceAccount, int indiceFile) {

    fileAperto = controller->getAccount(indiceAccount)->getListaFile()[indiceFile].getPuntatore();
    setWindowIcon(fileAperto->getIcona());
    nome->setText(fileAperto->getNome());
    nomeOriginale = QString(nome->text());
    QString stringaEstensione = fileAperto->getEstensione();
    estensione->setText("." + stringaEstensione.remove('.'));
    float percentuale = (fileAperto->getDimensione()*100)/(controller->getAccount(indiceAccount)->getSpazioFornito()*1024);
    QString stringaDimensione = QString(QString::number(fileAperto->getDimensione())+" MB ("+QString::number(percentuale)+"% dello spazio a disposizione)");
    dimensione->setText(stringaDimensione);
    dataCreazione->setText(fileAperto->getDataCreazione().toString());
    dataInserimento->setText(fileAperto->getDataCaricamento().toString());
    descrizione->setText(fileAperto->getDescrizione());
    descrizioneOriginale = QString(descrizione->text());
    informazioniAggiuntive->setText(fileAperto->getInformazioniFile());

    setFixedSize(sizeHint());
    setVisible(true);
}

void InfoFileWidget::controlloModifiche() {
    if(nome->text() == "") {
        QMessageBox::warning(this, tr("Errore"), tr("Nome del file non valido."), QMessageBox::Ok);
    }
    else if(nomeOriginale != nome->text() || descrizioneOriginale != descrizione->text()) {
        QMessageBox messageBox(QMessageBox::Question, tr("Modifica file"), tr("Salvare le modifiche effettuate?"), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes) {
            fileAperto->setNome(nome->text());
            fileAperto->setDescrizione(descrizione->text());
            controller->setModificato(true);
        }
    }
    descrizione->setText("");
    hide();
    emit fileModificato();
}

void InfoFileWidget::closeEvent(QCloseEvent *event) {
    descrizione->setText("");
}

InfoFileWidget::~InfoFileWidget() = default;
