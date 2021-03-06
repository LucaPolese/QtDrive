#include "nuovofilewidget.h"

NuovoFileWidget::NuovoFileWidget(Controller *controller_, QWidget *parent): QWidget(parent), controller(controller_) {
    setWindowTitle("Inserisci nuovo file");
    setWindowIcon(QIcon(":res/icons/file/file.png"));

    layout = new QVBoxLayout;
    formLayout = new QFormLayout;

    nome = new QLineEdit;
    nome->setMaxLength(50);
    formLayout->addRow(tr("Nome file:"), nome);

    estensione = new QLineEdit;
    estensione->setMaxLength(5);
    formLayout->addRow(tr("Estensione file:"), estensione);

    descrizione = new QLineEdit;
    descrizione->setMaxLength(255);
    formLayout->addRow(tr("Descrizione:"), descrizione);

    dimensione = new QSpinBox();
    dimensione->setAlignment(Qt::AlignRight);
    dimensione->setMaximum(10000);
    formLayout->addRow(tr("Dimensione (MB):"), dimensione);

    dataCreazione = new QCalendarWidget;
    dataCreazione->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    dataCreazione->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    dataCreazione->setCurrentPage(2021, 1);
    formLayout->addRow(tr("Data creazione:"), dataCreazione);

    tipo = new QComboBox;
    tipo->addItem("Archivio"); tipo->setItemIcon(0, QIcon(":res/icons/file/FileArchivio.png"));
    tipo->addItem("Testo"); tipo->setItemIcon(1, QIcon(":res/icons/file/FileTesto.png"));
    tipo->addItem("Audio"); tipo->setItemIcon(2, QIcon(":res/icons/file/FileAudio.png"));
    tipo->addItem("Immagine"); tipo->setItemIcon(3, QIcon(":res/icons/file/FileImmagine.png"));
    tipo->addItem("Video"); tipo->setItemIcon(4, QIcon(":res/icons/file/FileVideo.png"));
    formLayout->addRow(tr("Tipo file:"), tipo);

    layout->addLayout(formLayout);

    layoutInfo = new QStackedLayout;

    // Archivio
    QWidget* archivioWidget = new QWidget;
    layoutArchivio = new QFormLayout;

    dimensioneOriginale = new QSpinBox;
    dimensioneOriginale->setAlignment(Qt::AlignRight);
    dimensioneOriginale->setMaximum(10000);
    layoutArchivio->addRow(tr("Dimensione originale (MB):"), dimensioneOriginale);

    numeroDiFile = new QSpinBox;
    numeroDiFile->setAlignment(Qt::AlignRight);
    numeroDiFile->setMaximum(10000);
    layoutArchivio->addRow(tr("Numero file contenuti:"), numeroDiFile);

    protetto = new QCheckBox("Protetto da password");
    layoutArchivio->addRow(tr(""), protetto);

    archivioWidget->setLayout(layoutArchivio);
    layoutInfo->addWidget(archivioWidget);

    // Testo
    QWidget* testoWidget = new QWidget;
    layoutTesto = new QFormLayout;

    numeroCaratteri = new QSpinBox;
    numeroCaratteri->setAlignment(Qt::AlignRight);
    numeroCaratteri->setMaximum(100000);
    layoutTesto->addRow(tr("Numero caratteri:"), numeroCaratteri);

    numeroParole = new QSpinBox;
    numeroParole->setAlignment(Qt::AlignRight);
    numeroParole->setMaximum(10000);
    layoutTesto->addRow(tr("Numero parole:"), numeroParole);

    testoWidget->setLayout(layoutTesto);
    layoutInfo->addWidget(testoWidget);

    layoutInfo->setCurrentWidget(testoWidget);

    // Audio
    QWidget* audioWidget = new QWidget;
    layoutAudio = new QFormLayout;

    compressioneA = new QButtonGroup;
    nessunaA = new QRadioButton("Nessuna"); nessunaA->setChecked(true); compressioneA->addButton(nessunaA, 0);
    losslessA = new QRadioButton("Lossless"); compressioneA->addButton(losslessA, 1);
    lossyA = new QRadioButton("Lossy"); compressioneA->addButton(lossyA, 1);
    layoutAudio->addRow(tr("Compressione:"), nessunaA);
    layoutAudio->addRow(tr(""), losslessA);
    layoutAudio->addRow(tr(""), lossyA);

    bitrate = new QSpinBox;
    bitrate->setAlignment(Qt::AlignRight);
    bitrate->setMaximum(18000);
    layoutAudio->addRow(tr("Bitrate (kbit/s):"), bitrate);

    durataA = new QSpinBox;
    durataA->setAlignment(Qt::AlignRight);
    durataA->setMaximum(3600);
    layoutAudio->addRow(tr("Durata (secondi):"), durataA);

    audioWidget->setLayout(layoutAudio);
    layoutInfo->addWidget(audioWidget);

    // Immagine
    QWidget* immagineWidget = new QWidget;
    layoutImmagine = new QFormLayout;

    compressioneI = new QButtonGroup;
    nessunaI = new QRadioButton("Nessuna"); nessunaI->setChecked(true); compressioneI->addButton(nessunaI, 0);
    losslessI = new QRadioButton("Lossless"); compressioneI->addButton(losslessI, 1);
    lossyI = new QRadioButton("Lossy"); compressioneI->addButton(lossyI, 2);
    layoutImmagine->addRow(tr("Compressione:"), nessunaI);
    layoutImmagine->addRow(tr(""), losslessI);
    layoutImmagine->addRow(tr(""), lossyI);

    tipoImmagine = new QButtonGroup;
    raster = new QRadioButton("Raster"); raster->setChecked(true); tipoImmagine->addButton(raster, 0);
    vettoriale = new QRadioButton("Vettoriale"); tipoImmagine->addButton(vettoriale, 1);
    layoutImmagine->addRow("Tipo immagine:", raster);
    layoutImmagine->addRow("", vettoriale);

    larghezzaI = new QSpinBox;
    larghezzaI->setAlignment(Qt::AlignRight);
    larghezzaI->setMaximum(34560);
    layoutImmagine->addRow(tr("Larghezza (px):"), larghezzaI);

    altezzaI = new QSpinBox;
    altezzaI->setAlignment(Qt::AlignRight);
    altezzaI->setMaximum(61440);
    layoutImmagine->addRow(tr("Altezza (px):"), altezzaI);

    immagineWidget->setLayout(layoutImmagine);
    layoutInfo->addWidget(immagineWidget);

    // Video
    QWidget* videoWidget = new QWidget;
    layoutVideo = new QFormLayout;

    compressioneV = new QButtonGroup;
    nessunaV = new QRadioButton("Nessuna"); nessunaV->setChecked(true); compressioneV->addButton(nessunaV);
    losslessV = new QRadioButton("Lossless"); compressioneV->addButton(losslessV);
    lossyV = new QRadioButton("Lossy"); compressioneV->addButton(lossyV);
    layoutVideo->addRow(tr("Compressione:"), nessunaV);
    layoutVideo->addRow(tr(""), losslessV);
    layoutVideo->addRow(tr(""), lossyV);

    codec = new QLineEdit;
    codec->setMaxLength(10);
    layoutVideo->addRow(tr("Codec:"), codec);

    durataV = new QSpinBox;
    durataV->setAlignment(Qt::AlignRight);
    durataV->setMaximum(600);
    layoutVideo->addRow(tr("Durata (minuti):"), durataV);

    larghezzaV = new QSpinBox;
    larghezzaV->setAlignment(Qt::AlignRight);
    larghezzaV->setMaximum(4320);
    layoutVideo->addRow(tr("Larghezza (px):"), larghezzaV);

    altezzaV = new QSpinBox;
    altezzaV->setAlignment(Qt::AlignRight);
    altezzaV->setMaximum(7680);
    layoutVideo->addRow(tr("Altezza (px):"), altezzaV);

    fps = new QSpinBox;
    fps->setAlignment(Qt::AlignRight);
    fps->setMaximum(300);
    layoutVideo->addRow(tr("Frame al secondo:"), fps);

    videoWidget->setLayout(layoutVideo);
    layoutInfo->addWidget(videoWidget);


    layout->addLayout(layoutInfo);
    layoutInfo->setCurrentIndex(0);
    buttonLayout = new QHBoxLayout;
    aggiungi  = new QPushButton("Aggiungi");
    annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(aggiungi);
    buttonLayout->addWidget(annulla);
    layout->addLayout(buttonLayout);
    setLayout(layout);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    // Form dinamici
    connect(tipo, QOverload<int>::of(&QComboBox::activated), [=](int index){
        switch(index){
            case 0: layoutInfo->setCurrentIndex(0); break; // Archivio
            case 1: layoutInfo->setCurrentIndex(1); break; // Testo
            case 2: layoutInfo->setCurrentIndex(2); break; // Audio
            case 3: layoutInfo->setCurrentIndex(3); break; // Immagine
            case 4: layoutInfo->setCurrentIndex(4); break; // Video
        }
    });


    // Connessione "Aggiungi"
    connect(aggiungi, &QPushButton::clicked, this, &NuovoFileWidget::aggiungiNuovoFile);

    // Connessione "Annulla"
    connect(annulla, &QPushButton::clicked, [=]() {
        resetForm();
        this->hide();
    });
}

void NuovoFileWidget::resetForm() {
    // Se l'utente chiude il form premendo la X della finestra, il form viene resettato
    nome->clear();
    estensione->clear();
    descrizione->clear();
    dimensione->setValue(0);
    dataCreazione->setCurrentPage(2021, 1);
    tipo->setCurrentIndex(0);
    layoutInfo->setCurrentIndex(0);

    // Pulizia archivio
    dimensioneOriginale->setValue(0);
    numeroDiFile->setValue(0);
    protetto->setChecked(false);

    // Pulizia testo
    numeroCaratteri->setValue(0);
    numeroParole->setValue(0);

    // Pulizia audio
    nessunaA->setChecked(true);
    bitrate->setValue(0);
    durataA->setValue(0);

    // Pulizia immagine
    nessunaI->setChecked(true);
    raster->setChecked(true);
    altezzaI->setValue(0);
    larghezzaI->setValue(0);

    // Pulizia video
    nessunaV->setChecked(true);
    codec->clear();
    durataV->setValue(0);
    altezzaV->setValue(0);
    larghezzaV->setValue(0);
    fps->setValue(0);
}

void NuovoFileWidget::setAccountSelezionato(int i) {
    accountSelezionato = i;
}

void NuovoFileWidget::aggiungiNuovoFile() {
    bool ok = true;
    if(nome->text() == "") {
        QMessageBox::warning(this, tr("Errore"), tr("Nome del file non valido."), QMessageBox::Ok);
        ok = false;
    }
    else if(estensione->text() == "") {
        QMessageBox::warning(this, tr("Errore"), tr("Estensione del file non valida."), QMessageBox::Ok);
        ok = false;
    }
    else if(dimensione->value() == 0) {
        QMessageBox::warning(this, tr("Errore"), tr("Dimensione del file non valida."), QMessageBox::Ok);
        ok = false;
    }
    if(controller->getAccount(accountSelezionato)->getSpazioOccupato()+dimensione->value() > controller->getAccount(accountSelezionato)->getSpazioFornito()*1024) {
        QMessageBox::warning(this, tr("Errore"), tr("File troppo grande per essere inserito."), QMessageBox::Ok);
        ok = false;
    }
    if(!controller->getAccount(accountSelezionato)->checkFile(nome->text(), estensione->text())) {
        QMessageBox::warning(this, tr("Errore"), tr("File gi?? presente all'interno dell'account."), QMessageBox::Ok);
        ok = false;
    }
    if(ok) {
        QString nomeFile = nome->text();
        QString estensioneFile = estensione->text();
        unsigned int dimensioneFile = dimensione->value();
        QString descrizioneFile = descrizione->text();
        QDate dataCreazioneFile = dataCreazione->selectedDate();
        FileMedia::compressione compressioneFile;
        switch(tipo->currentIndex()) {
            // Archivio
            case 0:{
                FileArchivio *file = new FileArchivio(nomeFile, estensioneFile, dimensioneFile, dataCreazioneFile, QDate::currentDate(), descrizioneFile, dimensioneOriginale->value(), numeroDiFile->value(), protetto->isChecked());
                controller->aggiungiFile(accountSelezionato, file);
                break;
            }
            // Testo
            case 1:{
                FileTesto *file = new FileTesto(nomeFile, estensioneFile, dimensioneFile, dataCreazioneFile, QDate::currentDate(), descrizioneFile, numeroCaratteri->value(), numeroParole->value());
                controller->aggiungiFile(accountSelezionato, file);
                break;
            }
            // Audio
            case 2:{
                compressioneFile = FileMedia::compressione(compressioneA->checkedId());
                FileAudio *file = new FileAudio(nomeFile, estensioneFile, dimensioneFile, dataCreazioneFile, QDate::currentDate(), descrizioneFile, compressioneFile, bitrate->value(), durataA->value());
                controller->aggiungiFile(accountSelezionato, file);
                break;
            }
            // Immagine
            case 3:{
                compressioneFile = FileMedia::compressione(compressioneI->checkedId());
                FileImmagine::tipo tipoImmagineFile = FileImmagine::tipo(tipoImmagine->checkedId());
                FileImmagine *file = new FileImmagine(nomeFile, estensioneFile, dimensioneFile, dataCreazioneFile, QDate::currentDate(), descrizioneFile, compressioneFile, tipoImmagineFile, larghezzaI->value(), altezzaI->value());
                controller->aggiungiFile(accountSelezionato, file);
                break;
            }
            // Video
            case 4:{
                compressioneFile = FileMedia::compressione(compressioneV->checkedId());
                FileVideo *file = new FileVideo(nomeFile, estensioneFile, dimensioneFile, dataCreazioneFile, QDate::currentDate(), descrizioneFile, compressioneFile, codec->text(), durataV->value(), larghezzaV->value(), altezzaV->value(), fps->value());
                controller->aggiungiFile(accountSelezionato, file);
                break;
            }
        }
        hide();
        resetForm();
        emit fileAggiunto();
    }
}

void NuovoFileWidget::closeEvent(QCloseEvent *event) {
    resetForm();
}

NuovoFileWidget::~NuovoFileWidget() = default;
