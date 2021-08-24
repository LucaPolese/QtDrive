#include "nuovofilewidget.h"

NuovoFileWidget::NuovoFileWidget(Controller *controller_, QWidget *parent): QWidget(parent), controller(controller_) {
    setWindowTitle("Inserisci nuovo file");

    layout = new QVBoxLayout;
    formLayout = new QFormLayout;

    nome = new QLineEdit;
    formLayout->addRow(tr("Nome file:"), nome);

    estensione = new QLineEdit;
    formLayout->addRow(tr("Estensione file:"), estensione);

    descrizione = new QLineEdit;
    formLayout->addRow(tr("Descrizione:"), descrizione);

    dimensione = new QSpinBox();
    dimensione->setAlignment(Qt::AlignRight);
    formLayout->addRow(tr("Dimensione (MB):"), dimensione);

    dataCreazione = new QCalendarWidget;
    dataCreazione->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
    dataCreazione->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    formLayout->addRow(tr("Data creazione:"), dataCreazione);

    tipo = new QComboBox;
    tipo->addItem("Archivio"); tipo->setItemIcon(0, QIcon(":res/icons/file/archivio.png"));
    tipo->addItem("Testo"); tipo->setItemIcon(1, QIcon(":res/icons/file/testo.png"));
    tipo->addItem("Audio"); tipo->setItemIcon(2, QIcon(":res/icons/file/audio.png"));
    tipo->addItem("Immagine"); tipo->setItemIcon(3, QIcon(":res/icons/file/immagine.png"));
    tipo->addItem("Video"); tipo->setItemIcon(4, QIcon(":res/icons/file/video.png"));
    formLayout->addRow(tr("Tipo file:"), tipo);

    layout->addLayout(formLayout);

    layoutInfo = new QStackedLayout;

    // Archivio
    QWidget* archivioWidget = new QWidget;
    layoutArchivio = new QFormLayout;

    dimensioneOriginale = new QSpinBox;
    dimensioneOriginale->setAlignment(Qt::AlignRight);
    layoutArchivio->addRow(tr("Dimensione originale (MB):"), dimensioneOriginale);

    numeroDiFile = new QSpinBox;
    numeroDiFile->setAlignment(Qt::AlignRight);
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
    layoutTesto->addRow(tr("Numero caratteri:"), numeroCaratteri);

    numeroParole = new QSpinBox;
    numeroParole->setAlignment(Qt::AlignRight);
    layoutTesto->addRow(tr("Numero parole:"), numeroParole);

    testoWidget->setLayout(layoutTesto);
    layoutInfo->addWidget(testoWidget);

    layoutInfo->setCurrentWidget(testoWidget);

    // Audio
    QWidget* audioWidget = new QWidget;
    layoutAudio = new QFormLayout;

    compressioneA = new QButtonGroup;
    nessunaA = new QRadioButton("Nessuna"); nessunaA->setChecked(true); compressioneA->addButton(nessunaA);
    losslessA = new QRadioButton("Lossless"); compressioneA->addButton(losslessA);
    lossyA = new QRadioButton("Lossy"); compressioneA->addButton(lossyA);
    layoutAudio->addRow(tr("Compressione:"), nessunaA);
    layoutAudio->addRow(tr(""), losslessA);
    layoutAudio->addRow(tr(""), lossyA);

    bitrate = new QSpinBox;
    bitrate->setAlignment(Qt::AlignRight);
    layoutAudio->addRow(tr("Bitrate:"), bitrate);

    durataA = new QSpinBox;
    durataA->setAlignment(Qt::AlignRight);
    layoutAudio->addRow(tr("Durata (secondi):"), durataA);

    audioWidget->setLayout(layoutAudio);
    layoutInfo->addWidget(audioWidget);

    // Immagine
    QWidget* immagineWidget = new QWidget;
    layoutImmagine = new QFormLayout;

    compressioneI = new QButtonGroup;
    nessunaI = new QRadioButton("Nessuna"); nessunaI->setChecked(true); compressioneI->addButton(nessunaI);
    losslessI = new QRadioButton("Lossless"); compressioneI->addButton(losslessI);
    lossyI = new QRadioButton("Lossy"); compressioneI->addButton(lossyI);
    layoutImmagine->addRow(tr("Compressione:"), nessunaI);
    layoutImmagine->addRow(tr(""), losslessI);
    layoutImmagine->addRow(tr(""), lossyI);

    tipoImmagine = new QButtonGroup;
    raster = new QRadioButton("Raster"); raster->setChecked(true); tipoImmagine->addButton(raster);
    vettoriale = new QRadioButton("Vettoriale"); tipoImmagine->addButton(vettoriale);
    layoutImmagine->addRow("Tipo immagine:", raster);
    layoutImmagine->addRow("", vettoriale);

    altezzaI = new QSpinBox;
    altezzaI->setAlignment(Qt::AlignRight);
    layoutImmagine->addRow(tr("Altezza (px):"), altezzaI);

    larghezzaI = new QSpinBox;
    larghezzaI->setAlignment(Qt::AlignRight);
    layoutImmagine->addRow(tr("Larghezza (px):"), larghezzaI);

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
    layoutVideo->addRow(tr("Codec:"), codec);

    durataV = new QSpinBox;
    durataV->setAlignment(Qt::AlignRight);
    layoutVideo->addRow(tr("Durata (minuti):"), durataV);

    altezzaV = new QSpinBox;
    altezzaV->setAlignment(Qt::AlignRight);
    layoutVideo->addRow(tr("Altezza (px):"), altezzaV);

    larghezzaV = new QSpinBox;
    larghezzaV->setAlignment(Qt::AlignRight);
    layoutVideo->addRow(tr("Larghezza (px):"), larghezzaV);

    fps = new QSpinBox;
    fps->setAlignment(Qt::AlignRight);
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
    connect(aggiungi, &QPushButton::clicked, [=]() {
       });

    // Connessione "Annulla"
    connect(annulla, &QPushButton::clicked, [=]() {
        emit this->close();
    });
}

void NuovoFileWidget::closeEvent(QCloseEvent *event) {
    nome->clear();
    estensione->clear();
    descrizione->clear();
    dimensione->clear();
    //dataCreazione->;
    tipo->setCurrentIndex(0);
}

NuovoFileWidget::~NuovoFileWidget() = default;
