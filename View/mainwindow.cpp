#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), controller(new Controller()), accountWidget(new AccountWidget(controller)), fileWidget(new NuovoFileWidget(controller)), modificaAccountWidget(new ModificaAccountWidget(controller)), infoFileWidget(new InfoFileWidget(controller)) {
    setWindowTitle("QtDrive");
    setMinimumSize(1024, 800);

    //Layout Pagina Principale
    QVBoxLayout* pagina = new QVBoxLayout();

    // Scheda ACCOUNT
    QWidget* paginaAccount = new QWidget;
    QVBoxLayout* layoutInfo1 = new QVBoxLayout; // Layout contenente le informazioni testuali della prima scheda ed i tre layout successivi
    QHBoxLayout* layoutScheda1 = new QHBoxLayout; // Layout contenente la struttura della prima scheda
    QVBoxLayout* layoutAccount = new QVBoxLayout; // Layout contenente la tabella degli account
    layoutInfoAccount = new QVBoxLayout; // Layout per la visualizzazione delle informazioni dell'account

    // Contenuto testuale scheda 1
    QLabel* informazioni1 = new QLabel("Da questa scheda è possibile visualizzare le informazioni relative agli account registrati.<br>Per cominciare, carica un file tramite <b>Profilo > Apri</b> oppure inserisci un nuovo account tramite il pulsante <b>Aggiungi account</b>. <br> Per ulteriori informazioni, premi <b>Ctrl+H</b> per aprire la guida in linea.");
    informazioni1->adjustSize();

    // Definizione tabella account
    tabellaAccount = new QTableWidget;
    tabellaAccount->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabellaAccount->setColumnCount(4);
    QStringList headers1;
    headers1 << "Servizio" << "Email" << "Password" << "Spazio fornito";
    tabellaAccount->setHorizontalHeaderLabels(headers1);
    tabellaAccount->verticalHeader()->hide();
    tabellaAccount->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabellaAccount->setSelectionMode(QAbstractItemView::SingleSelection);
    tabellaAccount->setAlternatingRowColors(true);
    tabellaAccount->setStyleSheet("selection-background-color: lightblue");
    tabellaAccount->horizontalHeader()->setSectionsClickable(false);
    tabellaAccount->setSortingEnabled(false);
    tabellaAccount->resizeRowsToContents();
    tabellaAccount->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabellaAccount->setFocusPolicy(Qt::NoFocus);

    layoutInfo1->addWidget(informazioni1);
    layoutScheda1->addWidget(tabellaAccount);
    layoutInfo1->addLayout(layoutScheda1);
    layoutInfo1->addLayout(layoutAccount);

    // Elementi della finestra Informazioni account

    QFormLayout* layoutInformazioni = new QFormLayout;
    layoutInformazioni->addRow("", new QWidget); // Aggiunge spazio sotto al grafico

    emailAccount = new QLabel;
    layoutInformazioni->addRow("Email:", emailAccount);

    passwordAccount = new QLabel;
    layoutInformazioni->addRow("Password:", passwordAccount);

    numeroFile = new QLabel; numeroFile->setAlignment(Qt::AlignRight);
    layoutInformazioni->addRow("File contenuti:", numeroFile);

    QLabel* lArchivio = new QLabel;
    lArchivio->setPixmap(QPixmap(":res/icons/file/FileArchivio16.png"));
    lArchivio->setAlignment(Qt::AlignRight);
    QLabel* lTesto = new QLabel;
    lTesto->setPixmap(QPixmap(":res/icons/file/FileTesto16.png"));
    lTesto->setAlignment(Qt::AlignRight);
    QLabel* lImmagine = new QLabel;
    lImmagine->setPixmap(QPixmap(":res/icons/file/FileImmagine16.png"));
    lImmagine->setAlignment(Qt::AlignRight);
    QLabel* lAudio = new QLabel;
    lAudio->setPixmap(QPixmap(":res/icons/file/FileAudio16.png"));
    lAudio->setAlignment(Qt::AlignRight);
    QLabel* lVideo = new QLabel;
    lVideo->setPixmap(QPixmap(":res/icons/file/FileVideo16.png"));
    lVideo->setAlignment(Qt::AlignRight);
    numeroFileArchivio = new QLabel;
    numeroFileTesto = new QLabel;
    numeroFileImmagine = new QLabel;
    numeroFileAudio = new QLabel;
    numeroFileVideo = new QLabel;

    QFormLayout* layoutNumero = new QFormLayout;
    layoutNumero->addRow(lArchivio, numeroFileArchivio);
    layoutNumero->addRow(lTesto, numeroFileTesto);
    layoutNumero->addRow(lImmagine, numeroFileImmagine);
    layoutNumero->addRow(lAudio, numeroFileAudio);
    layoutNumero->addRow(lVideo, numeroFileVideo);
    layoutInformazioni->addRow("", layoutNumero);

    layoutInformazioni->setVerticalSpacing(30);
    layoutInfoAccount->addLayout(layoutInformazioni);

    QFormLayout* layoutSpazioOccupato = new QFormLayout;
    spazioRimanente = new QLabel("spazio GB"); spazioRimanente->setAlignment(Qt::AlignRight);
    layoutSpazioOccupato->addRow("Spazio occupato:", spazioRimanente);
    layoutInfoAccount->addLayout(layoutSpazioOccupato);

    barraOccupazione = new QProgressBar;
    barraOccupazione->setRange(0, 100);
    barraOccupazione->setStyleSheet("QProgressBar{border: 1px solid grey;text-align:center}"
                                   "QProgressBar::chunk{background-color:lightblue;}");
    layoutInfoAccount->addWidget(barraOccupazione);
    layoutInfoAccount->addSpacing(300);

    QHBoxLayout* layoutPulsanti1 = new QHBoxLayout;
    modificaAccount = new QPushButton(QIcon(":res/icons/pulsanti/modifica.png"), "Modifica"); modificaAccount->setFixedSize(modificaAccount->sizeHint());
    eliminaAccount = new QPushButton(QIcon(":res/icons/pulsanti/elimina.png"), "Elimina"); eliminaAccount->setFixedSize(eliminaAccount->sizeHint());
    chiudiAccount = new QPushButton("Chiudi"); chiudiAccount->setFixedSize(chiudiAccount->sizeHint());
    layoutPulsanti1->addWidget(modificaAccount);
    layoutPulsanti1->addWidget(eliminaAccount);
    layoutPulsanti1->addWidget(chiudiAccount, 0, Qt::AlignRight);
    layoutInfoAccount->addLayout(layoutPulsanti1);

    // Pulsante "Aggiungi account"
    QPushButton* pulsanteAggiungiAccount = new QPushButton(QIcon(":res/icons/pulsanti/aggiungiAccount.png"), "Aggiungi account");
    pulsanteAggiungiAccount->setFixedSize(pulsanteAggiungiAccount->sizeHint());
    layoutAccount->addWidget(pulsanteAggiungiAccount);
    paginaAccount->setLayout(layoutInfo1);

    // Definizione layout per informazioni dell'account
    informazioniAccount = new QWidget;
    informazioniAccount->setLayout(layoutInfoAccount);
    informazioniAccount->hide();
    layoutScheda1->addWidget(informazioniAccount);
    layoutScheda1->setAlignment(informazioniAccount, Qt::AlignHCenter);

    // Finestra inserimento nuovo account
    accountWidget->setWindowModality(Qt::ApplicationModal);
    pagina->addLayout(layoutInfo1);


    // Finestra modifica account
    modificaAccountWidget->setWindowModality(Qt::ApplicationModal);

    // Scheda FILE
    QWidget* paginaFile = new QWidget;
    QVBoxLayout* layoutInfo2 = new QVBoxLayout; // Layout contenente le informazioni della seconda scheda
    QHBoxLayout* layoutScheda2 = new QHBoxLayout; // Layout contenente la struttura della seconda scheda
    QVBoxLayout* layoutFile = new QVBoxLayout; // Layout contenente il tree widget dei file
    layoutInfoFile = new QVBoxLayout; // Layout per la visualizzazione delle informazioni dei file

    // Contenuto testuale scheda 2
    QLabel* informazioni2 = new QLabel("Da questa scheda è possibile visualizzare i file associati ad ogni account ed effettuare l'inserimento di nuovi file.<br>Clicca su un account per vedere i relativi file. Clicca su un file per visualizzare ulteriori informazioni ed accedere alle funzioni di modifica.<br>Clicca il pulsante <b>Nuovo file</b> per inserire un nuovo file nell'acccount correntemente selezionato. <br> Per ulteriori informazioni, premi <b>Ctrl+H</b> per aprire la guida in linea.");
    informazioni2->adjustSize();

    // Tabella con nome del servizio e indirizzo email associato
    tabellaFile = new QTableWidget;
    tabellaFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabellaFile->setColumnCount(2);
    QStringList headers2;
    headers2 << "Servizio" << "Email";
    tabellaFile->setHorizontalHeaderLabels(headers2);
    tabellaFile->verticalHeader()->hide();
    tabellaFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabellaFile->setSelectionMode(QAbstractItemView::SingleSelection);
    tabellaFile->setAlternatingRowColors(true);
    tabellaFile->setStyleSheet("selection-background-color: lightblue");
    tabellaFile->horizontalHeader()->setSectionsClickable(false);
    tabellaFile->setSortingEnabled(false);
    tabellaFile->resizeRowsToContents();
    tabellaFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabellaFile->setFocusPolicy(Qt::NoFocus);

    // TreeWidget per la visualizzazione dei file
    listaFile = new QTreeWidget;
    QStringList headersFile;
    headersFile << "" << "Tipo" << "Nome" << "Estensione" << "Dimensione" << "Descrizione";
    listaFile->setHeaderLabels(headersFile);
    listaFile->hideColumn(0);
    listaFile->resizeColumnToContents(1);
    listaFile->resizeColumnToContents(2);
    listaFile->resizeColumnToContents(3);
    listaFile->resizeColumnToContents(4);
    listaFile->resizeColumnToContents(5);
    listaFile->setSortingEnabled(false);

    layoutScheda2->addWidget(tabellaFile);

    QHBoxLayout* layoutPulsanti2 = new QHBoxLayout;
    nuovoFile = new QPushButton(QIcon(":res/icons/file/file.png"), "Nuovo file");
    eliminaFile = new QPushButton(QIcon(":res/icons/pulsanti/elimina.png"), "Elimina");
    eliminaFile->setDisabled(true);
    chiudiListaFile = new QPushButton("Chiudi");
    layoutPulsanti2->addWidget(nuovoFile); nuovoFile->setFixedSize(nuovoFile->sizeHint());
    layoutPulsanti2->addWidget(eliminaFile); eliminaFile->setFixedSize(eliminaFile->sizeHint());
    layoutPulsanti2->addWidget(chiudiListaFile, 0, Qt::AlignRight); chiudiListaFile->setFixedSize(chiudiListaFile->sizeHint());
    layoutInfo2->addWidget(informazioni2);
    layoutScheda2->addLayout(layoutFile);
    layoutInfo2->addLayout(layoutScheda2);
    layoutInfoFile->addWidget(listaFile);
    layoutInfoFile->addLayout(layoutPulsanti2);
    paginaFile->setLayout(layoutInfo2);
    informazioniFile = new QWidget; // Widget per gestire la comparsa e scomparsa della finestra dei file
    informazioniFile->setLayout(layoutInfoFile);
    informazioniFile->hide();
    layoutScheda2->addWidget(informazioniFile);

    // Form inserimento nuovo file
    fileWidget->setWindowModality(Qt::ApplicationModal);
    infoFileWidget->setWindowModality(Qt::ApplicationModal);


    // Scheda RICERCA
    QWidget* paginaRicerca = new QWidget();

    QVBoxLayout* layoutInfo3 = new QVBoxLayout; // Layout contenente le informazioni testuali della terza scheda
    QVBoxLayout* layoutRicerca = new QVBoxLayout;
    QHBoxLayout* layoutCheckbox = new QHBoxLayout;

    QLabel* informazioni3 = new QLabel("Da questa scheda è possibile effettuare ricerche di file all'interno di tutti gli account registrati.<br>Inizia a digitare nell'apposita barra per filtrare i file. Per ulteriori informazioni, premi <b>Ctrl+H</b> per aprire la guida in linea.");
    layoutInfo3->addWidget(informazioni3);

    layoutRicerca->addWidget(new QLabel("Impostazioni ricerca:"));
    ricercaPerNome = new QCheckBox("Nome");
    layoutCheckbox->addWidget(ricercaPerNome);
    ricercaPerDescrizione = new QCheckBox("Descrizione");
    layoutCheckbox->addWidget(ricercaPerDescrizione);
    ricercaAvanzata = new QCheckBox("Informazioni aggiuntive");
    layoutCheckbox->addWidget(ricercaAvanzata);
    ricercaCaseSensitive = new QCheckBox("Case-sensitive");
    layoutCheckbox->addWidget(ricercaCaseSensitive);
    layoutRicerca->addLayout(layoutCheckbox);

    inputRicerca = new QLineEdit;
    inputRicerca->setPlaceholderText("Digitare qui per iniziare una ricerca...");
    layoutRicerca->addWidget(inputRicerca);

    listaRicerca = new QTreeWidget;
    listaRicerca->setHeaderLabels(headersFile<<""<<""<<"Informazioni aggiuntive");
    listaRicerca->hideColumn(0);
    listaRicerca->hideColumn(6);
    listaRicerca->hideColumn(7);
    listaRicerca->setSortingEnabled(true);
    layoutRicerca->addWidget(listaRicerca);

    layoutInfo3->addLayout(layoutRicerca);

    paginaRicerca->setLayout(layoutInfo3);


    // Menubar
    QMenuBar *menu = new QMenuBar();
        // File
        QMenu *menuFile = new QMenu("Profilo", menu);
            QAction *nuovo = new QAction("Nuovo", menuFile); nuovo->setShortcut(Qt::CTRL | Qt::Key_N);
            nuovo->setIcon(QIcon(":/res/icons/menubar/nuovo.png"));
            QAction *apriFile = new QAction("Apri", menuFile); apriFile->setShortcut(Qt::CTRL | Qt::Key_O);
            apriFile->setIcon(QIcon(":/res/icons/menubar/apri.png"));
            QAction *salvaFile = new QAction("Salva", menuFile); salvaFile->setShortcut(Qt::CTRL | Qt::Key_S);
            salvaFile->setIcon(QIcon(":/res/icons/menubar/salva.png"));
            QAction *salvaNuovoFile = new QAction("Salva con nome", menuFile); salvaNuovoFile->setShortcut(Qt::CTRL | Qt::SHIFT |Qt::Key_S);
            salvaNuovoFile->setIcon(QIcon(":/res/icons/menubar/sovrascrivi.png"));
            QAction *chiudiApplicazione = new QAction("Esci", menuFile); chiudiApplicazione->setShortcut(Qt::CTRL | Qt::Key_Q);
            chiudiApplicazione->setIcon(QIcon(":/res/icons/menubar/esci.png"));
            menu->addMenu(menuFile);
                menuFile->addAction(nuovo);
                menuFile->addAction(apriFile);
                menuFile->addAction(salvaFile);
                menuFile->addAction(salvaNuovoFile);
                menuFile->addSeparator();
                menuFile->addAction(chiudiApplicazione);
        // Aiuto
        QMenu *menuAiuto = new QMenu("Aiuto", menu);
            QAction *guida = new QAction("Guida", menuAiuto); guida->setShortcut(Qt::CTRL | Qt::Key_H);
            guida->setIcon(QIcon(":/res/icons/menubar/guida.png"));
            QAction *info = new QAction("Informazioni su...", menuAiuto); info->setShortcut(Qt::CTRL | Qt::Key_I);
            info->setIcon(QIcon(":/res/icons/menubar/info.png"));
            menu->addMenu(menuAiuto);
                menuAiuto->addAction(guida);
                menuAiuto->addAction(info);


    //Tabs
    tabs = new QTabWidget();
    tabs->insertTab(0, paginaAccount, QIcon(":/res/icons/tabs/tab1.png"), "Account");
    tabs->insertTab(1, paginaFile, QIcon(":/res/icons/tabs/tab2.png"), "File");
    tabs->insertTab(2, paginaRicerca, QIcon(":/res/icons/tabs/tab3.png"), "Ricerca");
    tabs->setCurrentIndex(0);

        visualizzaAccount();
        visualizzaAccountRidotto();
        visualizzaFileDrive();

    //Aggiunta dei Widget e dei Layout al frame principale
    pagina->addWidget(menu);
    pagina->addWidget(tabs);

    // Connessione a "Guida"
    connect(guida, &QAction::triggered, [=]() {
        GuidaWidget* guidaWidget = new GuidaWidget();
        guidaWidget->setAttribute(Qt::WA_DeleteOnClose);
        guidaWidget->setWindowModality(Qt::ApplicationModal);
        guidaWidget->show();
    });

    // https://medium.com/genymobile/how-c-lambda-expressions-can-improve-your-qt-code-8cd524f4ed9f
    // https://stackoverflow.com/questions/21105169/is-there-any-difference-betwen-and-in-lambda-functions
    // Connessione a "Informazioni su QtDrive"
    connect(info, &QAction::triggered, [=]() {
        InfoWidget* infoWidget = new InfoWidget();
        infoWidget->setWindowModality(Qt::ApplicationModal); // Quando la finestra è aperta, le altre non possono essere selezionate
        infoWidget->setAttribute(Qt::WA_DeleteOnClose);
        infoWidget->show();
    });

    // Connessioni
    connect(modificaAccount, &QPushButton::pressed, this, &MainWindow::modificaDellAccount);
    connect(eliminaAccount, &QPushButton::pressed, this, &MainWindow::eliminazioneDellAccount);
    connect(chiudiAccount, &QPushButton::pressed, this, &MainWindow::chiusuraDellAccount);
    connect(tabellaAccount, &QTableWidget::cellClicked, this, &MainWindow::visualizzaInfoAccount);
    connect(accountWidget, &AccountWidget::accountAggiunto, this, &MainWindow::visualizzaAccount);
    connect(modificaAccountWidget, &ModificaAccountWidget::accountModificato, this, &MainWindow::visualizzaAccount);
    connect(tabellaFile, &QTableWidget::cellClicked, this, &MainWindow::visualizzaFile);
    connect(fileWidget, &NuovoFileWidget::fileAggiunto, this, &MainWindow::visualizzaListaFile);
    connect(tabellaFile, &QTableWidget::cellClicked, this, &MainWindow::visualizzaListaFile);
    connect(nuovoFile, &QPushButton::pressed, this, &MainWindow::creaNuovoFile);
    connect(eliminaFile, &QPushButton::pressed, this, &MainWindow::eliminazioneDelFile);
    connect(chiudiListaFile, &QPushButton::pressed, this, &MainWindow::chiusuraListaFile);
    connect(listaFile, &QTreeWidget::clicked, this, &MainWindow::attivaEliminaFile);
    connect(infoFileWidget, &InfoFileWidget::fileModificato, this, &MainWindow::refreshDati);
    connect(listaFile, &QTreeWidget::itemDoubleClicked, this, &MainWindow::visualizzaInformazioniAggiuntiveFile);
    connect(inputRicerca, &QLineEdit::textChanged, this, &MainWindow::ricerca);
    connect(tabs, &QTabWidget::tabBarClicked, this, &MainWindow::visualizzaAccount);
    connect(tabs, &QTabWidget::tabBarClicked, this, &MainWindow::visualizzaAccountRidotto);
    connect(tabs, &QTabWidget::tabBarClicked, this, &MainWindow::visualizzaFileDrive);
    connect(tabs, &QTabWidget::tabBarClicked, this, &MainWindow::selezioneTab);
    connect(tabellaFile, &QTableWidget::currentCellChanged, this, &MainWindow::selezioneAltroAccount);
    connect(nuovo, &QAction::triggered, this, &MainWindow::apriNuovoFile);
    connect(apriFile, &QAction::triggered, this, &MainWindow::apriIlFile);
    connect(salvaFile, &QAction::triggered, this, &MainWindow::salvaIlFile);
    connect(salvaNuovoFile, &QAction::triggered, this, &MainWindow::salvaIlNuovoFile);
    connect(pulsanteAggiungiAccount, &QPushButton::clicked, this, &MainWindow::aggiungiAccount);
    connect(chiudiApplicazione, &QAction::triggered, this, &MainWindow::close);
    connect(listaRicerca, &QTreeWidget::doubleClicked, this, &MainWindow::fileTrovato);

    connect(ricercaPerNome, &QCheckBox::stateChanged, this, &MainWindow::checkboxSelezionato);
    connect(ricercaPerDescrizione, &QCheckBox::stateChanged, this, &MainWindow::checkboxSelezionato);
    connect(ricercaAvanzata, &QCheckBox::stateChanged, this, &MainWindow::checkboxSelezionato);
    connect(ricercaCaseSensitive, &QCheckBox::stateChanged, this, &MainWindow::checkboxSelezionato);

    connect(ricercaPerNome, &QCheckBox::stateChanged, this, &MainWindow::controlloCheckbox);
    connect(ricercaPerDescrizione, &QCheckBox::stateChanged, this, &MainWindow::controlloCheckbox);
    connect(ricercaAvanzata, &QCheckBox::stateChanged, this, &MainWindow::controlloCheckbox);


    setLayout(pagina);
}

void MainWindow::modificaDellAccount(){
    modificaAccountWidget->show();
    modificaAccountWidget->visualizzaInfo(tabellaAccount->currentRow(), emailAccount->text(), passwordAccount->text());
}

void MainWindow::eliminazioneDellAccount(){
    QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Eliminare l'account selezionato?\nIl suo contenuto non sarà più gestibile da questa applicazione."), QMessageBox::Yes | QMessageBox::No, this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes) {
        controller->eliminaAccount(tabellaAccount->currentRow());
        controller->setModificato(true);
        informazioniAccount->hide();
        visualizzaAccount();
    }
}

void MainWindow::chiusuraDellAccount(){
    tabellaAccount->clearSelection();
    informazioniAccount->hide();
}

void MainWindow::visualizzaInfoAccount() {
    int i = tabellaAccount->currentRow(); // indice account selezionato

    numeroFile->setText(QString::number(controller->getAccount(i)->getListaFile().numeroElementi()));

    Account a = *controller->getAccount(i);

    emailAccount->setText(a.getEmail()); emailAccount->setAlignment(Qt::AlignRight);
    passwordAccount->setText(a.getPassword()); passwordAccount->setAlignment(Qt::AlignRight);
    float spazioOccupato = a.getSpazioOccupato() / 1024; // Spazio occupato in GB
    QString spazio = QString::number(spazioOccupato, 'f', 2)+"/"+QString::number(a.getSpazioFornito())+" GB";
    spazioRimanente->setText(spazio);
    numeroFileArchivio->setText(" File archivio: " + QString::number(a.contaFile<FileArchivio>()));
    numeroFileTesto->setText(" File di testo: " + QString::number(a.contaFile<FileTesto>()));
    numeroFileImmagine->setText(" Immagini: " + QString::number(a.contaFile<FileImmagine>()));
    numeroFileAudio->setText(" Audio: " + QString::number(a.contaFile<FileAudio>()));
    numeroFileVideo->setText(" Video: " + QString::number(a.contaFile<FileVideo>()));
    barraOccupazione->setValue(spazioOccupato*100/a.getSpazioFornito());

    informazioniAccount->show();
}

void MainWindow::visualizzaFile() {
    informazioniFile->show();
}

void MainWindow::visualizzaListaFile() {
    listaFile->clear();
    Container<Deepptr<File>> lista = controller->getAccount(tabellaFile->currentRow())->getListaFile();
    for(auto it = lista.begin(); it != lista.end(); ++it) {
        QTreeWidgetItem* nuovo = new QTreeWidgetItem;
        nuovo->setIcon(1, QIcon(":res/icons/file/"+it->getPuntatore()->getTipoFile()+".png")); nuovo->setTextAlignment(1, Qt::AlignCenter);
        nuovo->setText(2, it->getPuntatore()->getNome());
        QString estensione = it->getPuntatore()->getEstensione();
        nuovo->setText(3, "." + estensione.remove('.')); nuovo->setTextAlignment(3, Qt::AlignCenter);
        nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
        nuovo->setText(5, it->getPuntatore()->getDescrizione());
        listaFile->addTopLevelItem(nuovo);
    }
    listaFile->resizeColumnToContents(2);
}

void MainWindow::creaNuovoFile(){
    fileWidget->setAccountSelezionato(tabellaFile->currentRow());
    fileWidget->show();
    controller->setModificato(true);
}

void MainWindow::eliminazioneDelFile(){
    QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Eliminare il file selezionato?"), QMessageBox::Yes | QMessageBox::No, this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes) {
        QModelIndex index = listaFile->currentIndex();
        controller->eliminaFile(tabellaFile->currentRow(), index.row());
        controller->setModificato(true);
        informazioniAccount->hide();
        visualizzaAccountRidotto();
        eliminaFile->setDisabled(true);
        listaFile->clearSelection();
    }
}

void MainWindow::chiusuraListaFile(){
    tabellaFile->clearSelection();
    listaFile->clearSelection();
    eliminaFile->setDisabled(true);
    informazioniFile->hide();
}

void MainWindow::attivaEliminaFile(){
    eliminaFile->setEnabled(true);
}

void MainWindow::refreshDati(){
    listaFile->clearSelection();
    visualizzaListaFile();
}

void MainWindow::visualizzaInformazioniAggiuntiveFile(){
    QModelIndex index = listaFile->currentIndex();
    infoFileWidget->visualizzaFile(tabellaFile->currentRow(), index.row());
}

void MainWindow::ricerca(const QString input){
    listaRicerca->clear();
    if(!ricercaPerNome->isChecked() && !ricercaPerDescrizione->isChecked() && !ricercaAvanzata->isChecked())
        ricercaPerNome->setChecked(true);
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if(ricercaCaseSensitive->isChecked())
        cs = Qt::CaseSensitive;
    for(int i = 0; i < controller->getNumeroAccount(); i++) {
        Container<Deepptr<File>> lista = controller->getAccount(i)->getListaFile();
        for(auto it = lista.begin(); it != lista.end(); ++it) {
            bool ok = false, ok1 = false, ok2 = false, ok3 = false;
            if(ricercaPerNome->isChecked()) ok1 = it->getPuntatore()->ricercaNome(input, cs);
            if(ricercaPerDescrizione->isChecked()) ok2 = it->getPuntatore()->ricercaDescrizione(input, cs);
            if(ricercaAvanzata->isChecked()) ok3 = it->getPuntatore()->ricercaAvanzata(input, cs);
            ok = ok1 || ok2 || ok3;
            if(ok) {
                QTreeWidgetItem* nuovo = new QTreeWidgetItem;
                nuovo->setIcon(1, QIcon(":res/icons/file/"+it->getPuntatore()->getTipoFile()+".png"));
                nuovo->setText(2, it->getPuntatore()->getNome());
                QString estensione = it->getPuntatore()->getEstensione();
                nuovo->setText(3, "." + estensione.remove('.')); nuovo->setTextAlignment(3, Qt::AlignCenter);
                nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
                nuovo->setText(5, it->getPuntatore()->getDescrizione());
                nuovo->setText(6, QString::number(controller->getAccount(i)->getHost()));
                nuovo->setText(7, controller->getAccount(i)->getEmail());
                nuovo->setText(8, it->getPuntatore()->getInformazioniFile().replace("\n", ". "));
                listaRicerca->addTopLevelItem(nuovo);
            }
        }
    }

    listaRicerca->resizeColumnToContents(1);
    listaRicerca->resizeColumnToContents(2);
    listaRicerca->resizeColumnToContents(3);
    listaRicerca->resizeColumnToContents(4);
}

void MainWindow::visualizzaAccount() {
    informazioniAccount->hide();
    tabellaAccount->setRowCount(0);
    QString servizio;
    for(int i = 0; i < controller->getNumeroAccount(); i++) {
        tabellaAccount->insertRow(tabellaAccount->rowCount());
        Account* a = controller->getAccount(i);
        switch(a->getHost()) {
            case 0: servizio = "AmazonDrive"; break;
            case 1: servizio = "Box"; break;
            case 2: servizio = "Dropbox"; break;
            case 3: servizio = "GDrive"; break;
            case 4: servizio = "iCloud"; break;
            case 5: servizio = "Mediafire"; break;
            case 6: servizio = "Mega"; break;
            case 7: servizio = "Next"; break;
            case 8: servizio = "OneDrive"; break;
            case 9: servizio = "Qihoo360"; break;
        }
        QTableWidgetItem* itemServizio = new QTableWidgetItem(servizio); itemServizio->setTextAlignment(Qt::AlignCenter);
        tabellaAccount->setItem(i, 0, itemServizio);
        QTableWidgetItem* itemEmail = new QTableWidgetItem(a->getEmail()); itemEmail->setTextAlignment(Qt::AlignCenter);
        tabellaAccount->setItem(i, 1, itemEmail);
        QTableWidgetItem* itemPassword = new QTableWidgetItem(a->getPassword()); itemPassword->setTextAlignment(Qt::AlignCenter);
        tabellaAccount->setItem(i, 2, itemPassword);
        QString spazio = QString::number(a->getSpazioFornito()).append(" GB");
        QTableWidgetItem* itemSpazio = new QTableWidgetItem(spazio); itemSpazio->setTextAlignment(Qt::AlignCenter);
        tabellaAccount->setItem(i, 3, itemSpazio);
    }
}

void MainWindow::visualizzaAccountRidotto() {
    informazioniFile->hide();
    tabellaFile->setRowCount(0);
    QString servizio;
    for(int i = 0; i < controller->getNumeroAccount(); i++) {
        tabellaFile->insertRow(tabellaFile->rowCount());
        Account* a = controller->getAccount(i);
        switch(a->getHost()) {
            case 0: servizio = "AmazonDrive"; break;
            case 1: servizio = "Box"; break;
            case 2: servizio = "Dropbox"; break;
            case 3: servizio = "GDrive"; break;
            case 4: servizio = "iCloud"; break;
            case 5: servizio = "Mediafire"; break;
            case 6: servizio = "Mega"; break;
            case 7: servizio = "Next"; break;
            case 8: servizio = "OneDrive"; break;
            case 9: servizio = "Qihoo360"; break;
        }
        QTableWidgetItem* itemServizio = new QTableWidgetItem(servizio); itemServizio->setTextAlignment(Qt::AlignCenter);
        tabellaFile->setItem(i, 0, itemServizio);
        QTableWidgetItem* itemEmail = new QTableWidgetItem(a->getEmail()); itemEmail->setTextAlignment(Qt::AlignCenter);
        tabellaFile->setItem(i, 1, itemEmail);
    }
}

void MainWindow::visualizzaFileDrive() {
    listaRicerca->clear();
    for(int i = 0; i < controller->getNumeroAccount(); i++) {
        Container<Deepptr<File>> lista = controller->getAccount(i)->getListaFile();
        for(auto it = lista.begin(); it != lista.end(); ++it) {
            QTreeWidgetItem* nuovo = new QTreeWidgetItem;
            nuovo->setIcon(1, QIcon(":res/icons/file/"+it->getPuntatore()->getTipoFile()+".png"));
            nuovo->setText(2, it->getPuntatore()->getNome());
            QString estensione = it->getPuntatore()->getEstensione();
            nuovo->setText(3, "." + estensione.remove('.')); nuovo->setTextAlignment(3, Qt::AlignCenter);
            nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
            nuovo->setText(5, it->getPuntatore()->getDescrizione());
            nuovo->setText(6, QString::number(controller->getAccount(i)->getHost()));
            nuovo->setText(7, controller->getAccount(i)->getEmail());
            nuovo->setText(8, it->getPuntatore()->getInformazioniFile().replace("\n", ". "));
            listaRicerca->addTopLevelItem(nuovo);
        }
    }
    listaRicerca->resizeColumnToContents(1);
    listaRicerca->resizeColumnToContents(2);
    listaRicerca->resizeColumnToContents(3);
    listaRicerca->resizeColumnToContents(4);
}

void MainWindow::selezioneTab(){
    eliminaFile->setDisabled(true);
}

void MainWindow::selezioneAltroAccount(){
    eliminaFile->setDisabled(true);
}

void MainWindow::apriNuovoFile(){
    //Se c'è una modifica prima devo vedere se l'utente vuole salvarla,
    //solo a quel punto posso azzerare il contenuto del file
    if(controller->getModificato()){
        QMessageBox* messaggio = new QMessageBox(QMessageBox::Question, tr("QtDrive"), tr("Vuoi salvare le modifiche prima di aprire il nuovo file?"), QMessageBox::Yes | QMessageBox::No, this);
        messaggio->setButtonText(QMessageBox::Yes, tr("Sì"));
        messaggio->setButtonText(QMessageBox::No, tr("No"));
        if(messaggio->exec() == QMessageBox::Yes) salvaIlFile();
        else controller->setModificato(false);

    }
    //Se non è stata effettuata alcuna modifica, oppure se il salvataggio è avvenuto con successo allora azzera il contenuto
    if(!controller->getModificato()){
       controller->azzeraContenutoAccount();
       controller->aggiornaPercorso("");
       visualizzaAccount();
       visualizzaAccountRidotto();
       visualizzaFileDrive();
    }

}

void MainWindow::apriIlFile(){
    //Se non ho aperto alcun file, ma ho aggiunto manualmente degli account
    //oppure se il file che ho precedentemente aperto ha subito modifiche
    //Allora l'utente potrebbe voler salvare l'informazione prima di aprire un nuovo profilo(.xml)
    if((!controller->getListaAccount().empty() && controller->getXml().percorsoVuoto()) || controller->getModificato()){
        QMessageBox profiloDaSalvare(QMessageBox::Question, tr("QtDrive"), tr("Il tuo profilo ha subito delle modifiche, vuoi salvarle?"), QMessageBox::Yes | QMessageBox::No, this);
            profiloDaSalvare.setButtonText(QMessageBox::Yes, tr("Sì"));
            profiloDaSalvare.setButtonText(QMessageBox::No, tr("No"));
            if(profiloDaSalvare.exec() == QMessageBox::Yes) {
                    salvaIlFile();
            }else controller->setModificato(false);
    }
    if(!controller->getModificato()){
        QString fileScelto = QFileDialog::getOpenFileName(this, "Apri account", "./", "Account (*.xml)");
        if (!fileScelto.isEmpty()){
            controller->aggiornaPercorso(fileScelto);
            controller->aggiornaAccount();
            visualizzaAccount();
            visualizzaAccountRidotto();
            visualizzaFileDrive();
        }
    }

}

void MainWindow::salvaIlFile(){
    //Se clicco su salva e non ho aperto in precedenza alcun file, allora chiamo salvaIlNuovoFile
    if (controller->getXml().percorsoVuoto()){
        salvaIlNuovoFile();
    }else{
        //Controllo se l'informazione
        if(controller->getXml().controllaSeXml()){
            try{
                if(controller->salvataggioAccount() == true){
                    //Se il salvataggio è avvenuto correttamente,non ci sono ulteriori modifiche da salvare
                    controller->setModificato(false);
                }
            }catch(QString e){
                QMessageBox* errore = new QMessageBox(QMessageBox::Critical, "Errore",
                                                     QString("Attenzione: il file selezionato per la scrittura ha subito un errore.").arg(e),
                                                     QMessageBox::Ok);
                errore->exec();
            }
        }else{
            QMessageBox* noXml = new QMessageBox(QMessageBox::Critical, "Errore",
                                                 "Attenzione: il file che hai selezionato non è un file XML.",
                                                 QMessageBox::Ok);
            noXml->exec();
        }
    }
}

void MainWindow::salvaIlNuovoFile(){
    QString fileSalvataggio = QFileDialog::getSaveFileName(this, "Salva account", "./", "Account (*.xml)");
    if (!controller->getXml().percorsoVuoto()){
        if(controller->getXml().controllaSeXml()){
            try{
                controller->aggiornaPercorso(fileSalvataggio);
                if(controller->salvataggioAccount() == true){
                    //Il salvataggio è avvenuto correttamente, quindi non ci sono ulteriori modifiche da salvare
                    controller->setModificato(false);
                }
            }catch(QString e){
                QMessageBox* errore = new QMessageBox(QMessageBox::Critical, "Errore",
                                                     QString("Attenzione: il file selezionato per la scrittura ha subito un errore.").arg(e),
                                                     QMessageBox::Ok);
                errore->exec();
            }
        }else{
            QMessageBox* noXml = new QMessageBox(QMessageBox::Critical, "Errore",
                                                 "Attenzione: il file che hai selezionato non è un file XML.",
                                                 QMessageBox::Ok);
            noXml->exec();
        }
    }else{
        try{
            controller->aggiornaPercorso(fileSalvataggio);
            if(controller->salvataggioAccount() == true){
                //Il salvataggio è avvenuto correttamente, quindi non ci sono ulteriori modifiche da salvare
                controller->setModificato(false);
            }
        }catch(QString e){
            QMessageBox* errore = new QMessageBox(QMessageBox::Critical, "Errore",
                                                 QString("Attenzione: il file selezionato per la scrittura ha subito un errore.").arg(e),
                                                 QMessageBox::Ok);
            errore->exec();
        }
    }
}

void MainWindow::aggiungiAccount() {
    accountWidget->show();
}

void MainWindow::fileTrovato() {
    tabs->setCurrentIndex(1);
    for(int i = 0; i < tabellaFile->rowCount(); i++) {
        QTableWidgetItem* servizio = tabellaFile->item(i, 0);
        QTableWidgetItem* email = tabellaFile->item(i, 1);
        QString s;
        switch(listaRicerca->currentItem()->text(6).toInt()) {
            case 0: s = "AmazonDrive"; break;
            case 1: s = "Box"; break;
            case 2: s = "Dropbox"; break;
            case 3: s = "GDrive"; break;
            case 4: s = "iCloud"; break;
            case 5: s = "Mediafire"; break;
            case 6: s = "Mega"; break;
            case 7: s = "Next"; break;
            case 8: s = "OneDrive"; break;
            case 9: s = "Qihoo360"; break;
        }
        if(servizio->text() == s && email->text() == listaRicerca->currentItem()->text(7)) {
            tabellaFile->setCurrentCell(i, 0);
            emit tabellaFile->cellClicked(i, 0);
            QTreeWidgetItemIterator it(listaFile);
            while(*it) {
                if((*it)->text(2) == listaRicerca->currentItem()->text(2) && (*it)->text(3) == listaRicerca->currentItem()->text(3)) {
                    (*it)->setSelected(true);
                    listaFile->setCurrentItem(*it);
                    QModelIndex index = listaFile->currentIndex();
                    visualizzaInformazioniAggiuntiveFile();
                }
                ++it;
            }
        }
    }
}

void MainWindow::checkboxSelezionato(int state) {
    emit inputRicerca->textChanged(inputRicerca->text());
}

void MainWindow::controlloCheckbox() {
    if(!ricercaPerNome->isChecked() && !ricercaPerDescrizione->isChecked() && !ricercaAvanzata->isChecked())
        ricercaPerNome->setChecked(true);
}

void MainWindow::closeEvent (QCloseEvent *event) {
    QMessageBox* messaggio;
    if(controller->getModificato()){
        messaggio = new QMessageBox(QMessageBox::Question, tr("QtDrive"), tr("Vuoi salvare le modifiche prima di uscire dall'applicazione"),
                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, this);
        messaggio->setButtonText(QMessageBox::Yes, tr("Sì"));
        messaggio->setButtonText(QMessageBox::No, tr("No"));
        messaggio->setButtonText(QMessageBox::Cancel, tr("Annulla"));
        messaggio->setWindowFlags(messaggio->windowFlags() & ~Qt::WindowCloseButtonHint);

        int ret = messaggio->exec();

        if(ret == QMessageBox::Yes) {
            salvaIlFile();
            //Se ho salvato effettivamente il file -> modificato sarà false.
            //Altrimenti modificato continua ad avere valore true
            //Se chiudessi perderei tutta l'informazione
            if(controller->getModificato()) event->ignore();
            else event->accept();
        }else if(ret == QMessageBox::No) {
            event->accept();
        }else {
            event->ignore();
        }
    }else{
        QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Uscire dall'applicazione?"), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        if(messageBox.exec() == QMessageBox::Yes)
            event->accept();
        else event->ignore();
    }

}

MainWindow::~MainWindow() {
}
