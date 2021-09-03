#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), controller(new Controller()), accountWidget(new AccountWidget(controller)), fileWidget(new NuovoFileWidget(controller)), infoFileWidget(new InfoFileWidget(controller)) {
    setWindowTitle("QtDrive");
    setMinimumSize(1024, 720);

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
    set0 = new QBarSet("Archivio");
    set1 = new QBarSet("Testo");
    set2 = new QBarSet("Audio");
    set3 = new QBarSet("Immagine");
    set4 = new QBarSet("Video");
    series = new QHorizontalPercentBarSeries();

    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("white")));

    QStringList categories;
    categories << "";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisY(axis, series);

    chart->legend()->setVisible(true);
    chart->axisX()->setLabelsVisible(false);
    chart->axisX()->setGridLineVisible(false);
    chart->axisX()->setLineVisible(false);
    chart->axisY()->setGridLineVisible(false);
    chart->axisY()->setLineVisible(false);
    chart->legend()->setAlignment(Qt::AlignTop);

    chartView = new QChartView(chart);
    chartView->setFixedSize(QSize(400, 100));
    chartView->setRenderHint(QPainter::Antialiasing);
    layoutInfoAccount->addWidget(chartView);

    QFormLayout* layoutInformazioni = new QFormLayout;
    layoutInformazioni->addRow("", new QWidget); // Aggiunge spazio sotto al grafico

    emailAccount = new QLineEdit;
    layoutInformazioni->addRow("Email:", emailAccount);

    passwordAccount = new QLineEdit;
    layoutInformazioni->addRow("Password:", passwordAccount);

    numeroFile = new QLabel; numeroFile->setAlignment(Qt::AlignRight);
    layoutInformazioni->addRow("File contenuti:", numeroFile);

    spazioRimanente = new QLabel("spazio GB"); spazioRimanente->setAlignment(Qt::AlignRight);
    layoutInformazioni->addRow("Spazio occupato:", spazioRimanente);

    layoutInformazioni->setVerticalSpacing(30);
    layoutInfoAccount->addLayout(layoutInformazioni);

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

    QLabel* informazioni3 = new QLabel("Da questa scheda è possibile effettuare una ricerca di file all'interno di tutti gli account registrati.");
    layoutInfo3->addWidget(informazioni3);

    inputRicerca = new QLineEdit;
    inputRicerca->setPlaceholderText("Digitare qui per iniziare una ricerca...");
    layoutRicerca->addWidget(inputRicerca);

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

    listaRicerca = new QTreeWidget;
    listaRicerca->setHeaderLabels(headersFile<<""<<"");
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
            QAction *apriFile = new QAction("Apri", menuFile); apriFile->setShortcut(Qt::CTRL | Qt::Key_O);
            apriFile->setIcon(QIcon(":/res/icons/menubar/apri.png"));
            QAction *salvaFile = new QAction("Salva", menuFile); salvaFile->setShortcut(Qt::CTRL | Qt::Key_S);
            salvaFile->setIcon(QIcon(":/res/icons/menubar/salva.png"));
            QAction *salvaNuovoFile = new QAction("Salva con nome", menuFile); salvaNuovoFile->setShortcut(Qt::CTRL | Qt::SHIFT |Qt::Key_S);
            salvaNuovoFile->setIcon(QIcon(":/res/icons/menubar/sovrascrivi.png"));
            QAction *chiudiApplicazione = new QAction("Esci", menuFile); chiudiApplicazione->setShortcut(Qt::CTRL | Qt::Key_Q);
            chiudiApplicazione->setIcon(QIcon(":/res/icons/menubar/esci.png"));
            menu->addMenu(menuFile);
                menuFile->addAction(apriFile);
                menuFile->addAction(salvaFile);
                menuFile->addAction(salvaNuovoFile);
                menuFile->addSeparator();
                menuFile->addAction(chiudiApplicazione);
        // Aiuto
        QMenu *menuAiuto = new QMenu("Aiuto", menu);
            QAction *guida = new QAction("Guida", menuAiuto); guida->setShortcut(Qt::CTRL | Qt::Key_H);
            guida->setIcon(QIcon(":/res/icons/menubar/guida.png"));
            QAction *info = new QAction("Informazioni su QtDrive", menuAiuto); info->setShortcut(Qt::CTRL | Qt::Key_I);
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

    // Inizializzazione file di default, se non esiste viene creato
    QFile file("account.xml");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.close();

    // Connessioni
    connect(modificaAccount, &QPushButton::pressed, this, &MainWindow::modificaDellAccount);
    connect(eliminaAccount, &QPushButton::pressed, this, &MainWindow::eliminazioneDellAccount);
    connect(chiudiAccount, &QPushButton::pressed, this, &MainWindow::chiusuraDellAccount);
    connect(tabellaAccount, &QTableWidget::cellClicked, this, &MainWindow::visualizzaInfoAccount);
    connect(accountWidget, &AccountWidget::accountAggiunto, this, &MainWindow::visualizzaAccount);
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
    connect(apriFile, &QAction::triggered, this, &MainWindow::apriIlFile);
    connect(salvaFile, &QAction::triggered, this, &MainWindow::salvaIlFile);
    connect(salvaNuovoFile, &QAction::triggered, this, &MainWindow::salvaIlNuovoFile);
    connect(pulsanteAggiungiAccount, &QPushButton::clicked, this, &MainWindow::aggiungiAccount);
    connect(chiudiApplicazione, &QAction::triggered, this, &MainWindow::close);

    connect(listaRicerca, &QTreeWidget::doubleClicked, this, &MainWindow::fileTrovato);

    setLayout(pagina);
}

void MainWindow::modificaDellAccount(){
    QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Salvare le modifiche effettuate?"), QMessageBox::Yes | QMessageBox::No, this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes) {
        controller->salvaModificaAccount(tabellaAccount->currentRow(), emailAccount->text(), passwordAccount->text());
        controller->setModificato(true);
        informazioniAccount->hide();
        visualizzaAccount();
    }
    else {
         tabellaAccount->selectRow(tabellaAccount->currentRow());
         visualizzaInfoAccount();
    }
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
    series->clear();
    set0 = new QBarSet("Archivio");
    set1 = new QBarSet("Testo");
    set2 = new QBarSet("Audio");
    set3 = new QBarSet("Immagine");
    set4 = new QBarSet("Video");
    // Numero di file
    *set0 << controller->getAccount(i)->contaFile<FileArchivio>();
    *set1 << controller->getAccount(i)->contaFile<FileTesto>();
    *set2 << controller->getAccount(i)->contaFile<FileAudio>();
    *set3 << controller->getAccount(i)->contaFile<FileImmagine>();
    *set4 << controller->getAccount(i)->contaFile<FileVideo>();

    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    chartView->update();

    numeroFile->setText(QString::number(controller->getAccount(i)->getListaFile().numeroElementi()));

    Account a = *controller->getAccount(i);

    emailAccount->setText(a.getEmail()); emailAccount->setAlignment(Qt::AlignRight);
    passwordAccount->setText(a.getPassword()); passwordAccount->setAlignment(Qt::AlignRight);
    float spazioOccupato = a.getSpazioOccupato() / 1024; // Spazio occupato in GB
    QString spazio = QString::number(spazioOccupato, 'f', 2)+"/"+QString::number(a.getSpazioFornito())+" GB";
    spazioRimanente->setText(spazio);

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
        nuovo->setIcon(1, it->getPuntatore()->getIcona()); nuovo->setTextAlignment(1, Qt::AlignCenter);
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
                qDebug() << controller->getAccount(i)->getHost()<< " - "<<controller->getAccount(i)->getEmail();
                nuovo->setIcon(1, it->getPuntatore()->getIcona());
                nuovo->setText(2, it->getPuntatore()->getNome());
                QString estensione = it->getPuntatore()->getEstensione();
                nuovo->setText(3, "." + estensione.remove('.')); nuovo->setTextAlignment(3, Qt::AlignCenter);
                nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
                nuovo->setText(5, it->getPuntatore()->getDescrizione());
                nuovo->setText(6, QString::number(controller->getAccount(i)->getHost()));
                nuovo->setText(7, controller->getAccount(i)->getEmail());
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
            nuovo->setIcon(1, it->getPuntatore()->getIcona());
            nuovo->setText(2, it->getPuntatore()->getNome());
            QString estensione = it->getPuntatore()->getEstensione();
            nuovo->setText(3, "." + estensione.remove('.')); nuovo->setTextAlignment(3, Qt::AlignCenter);
            nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
            nuovo->setText(5, it->getPuntatore()->getDescrizione());
            nuovo->setText(6, QString::number(controller->getAccount(i)->getHost()));
            nuovo->setText(7, controller->getAccount(i)->getEmail());
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

void MainWindow::apriIlFile(){
    //Se non ho aperto alcun file, ma ho aggiunto manualmente degli account
    //oppure se il file che ho precedentemente aperto ha subito modifiche
    //Allora l'utente potrebbe voler salvare l'informazione prima di aprire un nuovo profilo(.xml)
    if((!controller->getListaAccount().empty() && controller->getXml().percorsoVuoto()) || controller->getModificato()){
        QMessageBox profiloDaSalvare(QMessageBox::Question, tr("QtDrive"), tr("Il tuo profilo ha subito delle modifiche, vuoi salvarle?"), QMessageBox::Yes | QMessageBox::No, this);
            profiloDaSalvare.setButtonText(QMessageBox::Yes, tr("Sì"));
            profiloDaSalvare.setButtonText(QMessageBox::No, tr("No"));
            if(profiloDaSalvare.exec() == QMessageBox::Yes) {
                while(controller->getModificato()){
                    if(controller->getXml().percorsoVuoto()) salvaIlNuovoFile();
                    else salvaIlFile();
                }
            }
    }
    QString fileScelto = QFileDialog::getOpenFileName(this, "Apri account", "./", "Account (*.xml)");
    if (fileScelto.isEmpty()){
        QMessageBox* alert = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: non hai scelto alcun file da aprire!",
                                             QMessageBox::Ok);
        alert->exec();
    }else{
        controller->aggiornaPercorso(fileScelto);
        controller->aggiornaAccount();
        controller->setModificato(false);
        visualizzaAccount();
        visualizzaAccountRidotto();
        visualizzaFileDrive();
    }

}

void MainWindow::salvaIlFile(){
    //QString fileSalvataggio = QFileDialog::getOpenFileName(this, "Salva account", "./", "Account (*.xml)");
    if (controller->getXml().percorsoVuoto()){
        QMessageBox* vuoto = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: non hai scelto alcun file su cui effettuare il salvataggio!",
                                             QMessageBox::Ok);
        vuoto->exec();
        salvaIlNuovoFile();
    }else{
        if(controller->getXml().controllaSeXml()){
            try{
                controller->salvataggioAccount();
                //Il salvataggio è avvenuto correttamente, quindi non ci sono ulteriori modifiche da salvare
                controller->setModificato(false);
            }catch(QString e){
                QMessageBox* errore = new QMessageBox(QMessageBox::Critical, "Errore",
                                                     QString("Attenzione: il file selezionato per la scrittura non può essere salvato per un errore.").arg(e),
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
    QString fileSalvataggio = QFileDialog::getOpenFileName(this, "Salva account", "./", "Account (*.xml)");
    if (controller->getXml().percorsoVuoto()){
        QMessageBox* vuoto = new QMessageBox(QMessageBox::Critical, "Errore",
                                             "Attenzione: non hai scelto alcun file su cui effettuare il salvataggio!"
                                             "<br>Il tuo profilo non può essere salvato.",
                                             QMessageBox::Ok);
        vuoto->exec();
    }else{
        if(controller->getXml().controllaSeXml()){
            try{
                controller->salvataggioAccount();
                //Il salvataggio è avvenuto correttamente, quindi non ci sono ulteriori modifiche da salvare
                controller->setModificato(false);
            }catch(QString e){
                QMessageBox* errore = new QMessageBox(QMessageBox::Critical, "Errore",
                                                     QString("Attenzione: il file selezionato per la scrittura non può essere salvato per un errore.").arg(e),
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
                    QModelIndex index = listaFile->currentIndex();
                    //emit listaFile->itemDoubleClicked(*it, listaFile->indexOfTopLevelItem(*it));
                    visualizzaInformazioniAggiuntiveFile();
                }
                ++it;
            }
        }
    }
}

void MainWindow::closeEvent (QCloseEvent *event) {
    QMessageBox* messaggio;
    qDebug() << controller->getModificato();
    if(controller->getModificato()){
        messaggio = new QMessageBox(QMessageBox::Question, tr("QtDrive"), tr("Vuoi salvare le modifiche prima di uscire dall'applicazione"), QMessageBox::Yes | QMessageBox::No, this);
        messaggio->setButtonText(QMessageBox::Yes, tr("Sì"));
        messaggio->setButtonText(QMessageBox::No, tr("No"));
        if(messaggio->exec() == QMessageBox::Yes){
            while(controller->getModificato()){
                if(controller->getXml().percorsoVuoto()) salvaIlNuovoFile();
                salvaIlFile();
            }
        }
        event->accept();
    }else{
        QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Uscire dall'applicazione?"), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes)
            event->accept();
        else event->ignore();
    }

}

MainWindow::~MainWindow() {
}
