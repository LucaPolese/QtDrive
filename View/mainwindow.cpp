#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), controller(new Controller()), accountWidget(new AccountWidget(controller)), fileWidget(new NuovoFileWidget(controller)) {
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
    QLabel* informazioni1 = new QLabel("Da questa scheda è possibile visualizzare le informazioni relative agli account registrati.<br>Per cominciare, carica un file tramite <b>File > Apri</b> oppure inserisci un nuovo account tramite il pulsante <b>Aggiungi account</b>. Per ulteriori informazioni, premi <b>Ctrl+H</b> per aprire la guida in linea.");

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
    *set0 << 50;
    *set1 << 40;
    *set2 << 30;
    *set3 << 01;
    *set4 << 02;

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

    connect(modificaAccount, &QPushButton::pressed, [=]{
        QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Salvare le modifiche effettuate?"), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes) {
            controller->salvaModificaAccount(tabellaAccount->currentRow(), emailAccount->text(), passwordAccount->text());
            informazioniAccount->hide();
            visualizzaAccount();
        }
        else {
             tabellaAccount->selectRow(tabellaAccount->currentRow());
             visualizzaInfoAccount();
        }
    });

    connect(eliminaAccount, &QPushButton::pressed, [=]{
        QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Eliminare l'account selezionato?\nIl suo contenuto non sarà più gestibile da questa applicazione."), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes) {
            controller->eliminaAccount(tabellaAccount->currentRow());
            informazioniAccount->hide();
            visualizzaAccount();
        }
    });

    connect(chiudiAccount, &QPushButton::pressed, [=]{
        tabellaAccount->clearSelection();
        informazioniAccount->hide();
    });

    connect(tabellaAccount, SIGNAL(cellClicked(int,int)), this, SLOT(visualizzaInfoAccount()));

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
    connect(accountWidget, &AccountWidget::accountAggiunto, this, &MainWindow::visualizzaAccount);
    pagina->addLayout(layoutInfo1);

    // Scheda FILE
    QWidget* paginaFile = new QWidget;
    QVBoxLayout* layoutInfo2 = new QVBoxLayout; // Layout contenente le informazioni della seconda scheda
    QHBoxLayout* layoutScheda2 = new QHBoxLayout; // Layout contenente la struttura della seconda scheda
    QVBoxLayout* layoutFile = new QVBoxLayout; // Layout contenente il tree widget dei file
    layoutInfoFile = new QVBoxLayout; // Layout per la visualizzazione delle informazioni dei file

    // Contenuto testuale scheda 2
    QLabel* informazioni2 = new QLabel("Da questa scheda è possibile visualizzare i file associati ad ogni account ed effettuare l'inserimento di nuovi file.<br>Clicca su un account per vedere i relativi file. Clicca su un file per visualizzare ulteriori informazioni ed accedere alle funzioni di modifica.<br>Clicca il pulsante <b>Nuovo file</b> per inserire un nuovo file nell'acccount correntemente selezionato. Per ulteriori informazioni, premi <b>Ctrl+H</b> per aprire la guida in linea.");

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
    //layoutScheda2->addWidget(listaFile);
    connect(tabellaFile, SIGNAL(cellClicked(int,int)), this, SLOT(visualizzaFile()));

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
    connect(fileWidget, &NuovoFileWidget::fileAggiunto, this, &MainWindow::visualizzaListaFile);

    connect(tabellaFile, SIGNAL(cellClicked(int,int)), this, SLOT(visualizzaListaFile()));

    connect(nuovoFile, &QPushButton::pressed, [=]{
        fileWidget->setAccountSelezionato(tabellaFile->currentRow());
        fileWidget->show();
    });

    connect(eliminaFile, &QPushButton::pressed, [=]{
        QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Eliminare il file selezionato?"), QMessageBox::Yes | QMessageBox::No, this);
        messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
        messageBox.setButtonText(QMessageBox::No, tr("No"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes) {
            QModelIndex index = listaFile->currentIndex();
            controller->eliminaFile(tabellaFile->currentRow(), index.row());
            informazioniAccount->hide();
            visualizzaAccountRidotto();
            eliminaFile->setDisabled(true);
            listaFile->clearSelection();
        }
    });

    connect(chiudiListaFile, &QPushButton::pressed, [=]{
        tabellaFile->clearSelection();
        listaFile->clearSelection();
        eliminaFile->setDisabled(true);
        informazioniFile->hide();
    });

    connect(listaFile, &QTreeWidget::clicked, [=](const QModelIndex &index) {
        eliminaFile->setEnabled(true);
        qDebug() << index.row();
    });

    // Scheda RICERCA
    QWidget* paginaRicerca = new QWidget();








    // Menubar
    QMenuBar *menu = new QMenuBar();
        // File
        QMenu *menuFile = new QMenu("File", menu);
            QAction *apriFile = new QAction("Apri", menuFile); apriFile->setShortcut(Qt::CTRL | Qt::Key_O);
            apriFile->setIcon(QIcon(":/res/icons/menubar/apri.png"));
            QAction *salvaFile = new QAction("Salva", menuFile); salvaFile->setShortcut(Qt::CTRL | Qt::Key_S);
            salvaFile->setIcon(QIcon(":/res/icons/menubar/salva.png"));
            QAction *chiudiApplicazione = new QAction("Esci", menuFile); chiudiApplicazione->setShortcut(Qt::CTRL | Qt::Key_Q);
            chiudiApplicazione->setIcon(QIcon(":/res/icons/menubar/esci.png"));
            menu->addMenu(menuFile);
                menuFile->addAction(apriFile);
                menuFile->addAction(salvaFile);
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
    QTabWidget* tabs = new QTabWidget();
    tabs->insertTab(0, paginaAccount, QIcon(":/res/icons/tabs/tab1.png"), "Account");
    tabs->insertTab(1, paginaFile, QIcon(":/res/icons/tabs/tab2.png"), "File");
    tabs->insertTab(2, paginaRicerca, QIcon(":/res/icons/tabs/tab3.png"), "Ricerca");
    tabs->setCurrentIndex(0);

    connect(tabs, SIGNAL(tabBarClicked(int)), this, SLOT(visualizzaAccount()));
    connect(tabs, SIGNAL(tabBarClicked(int)), this, SLOT(visualizzaAccountRidotto()));

    //Aggiunta dei Widget e dei Layout al frame principale
    //layoutMenu->addWidget(menu);

    pagina->addWidget(menu);
    pagina->addWidget(tabs);

    // Connessione a "Apri"
    connect(apriFile, &QAction::triggered,  [=]() {
        QString fileScelto = QFileDialog::getOpenFileName(this, "Apri account", "./", "Account (*.xml)");
        if (fileScelto.isEmpty()) return;
        else{
            Xmlify xml(fileScelto);
            controller->aggiornaAccount(xml.acquisisciAccount());
            visualizzaAccount();
        }
    });

    // Connessione a "Salva"
    connect(salvaFile, &QAction::triggered,  [=]() {

    });

    // Connessione a "Esci"
    connect(chiudiApplicazione, &QAction::triggered,  [=]() {
        close();
    });

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

    // Connessione a "Aggiungi account"
    connect(pulsanteAggiungiAccount, &QPushButton::clicked, this, &MainWindow::aggiungiAccount);

    // Inizializzazione file di default, se non esiste viene creato
    QFile file("account.xml");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.close();

    setLayout(pagina);
}

void MainWindow::closeEvent (QCloseEvent *event) {
    QMessageBox messageBox(QMessageBox::Question, tr("QtDrive"), tr("Uscire dall'applicazione?"), QMessageBox::Yes | QMessageBox::No, this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Sì"));
    messageBox.setButtonText(QMessageBox::No, tr("No"));
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes)
        event->accept();
    else event->ignore();
}

void MainWindow::aggiungiAccount() {
    accountWidget->show();
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
    int spazioOccupato = a.getSpazioOccupato() / 1024; // Spazio occupato in GB
    QString spazio = QString::number(spazioOccupato)+"/"+QString::number(a.getSpazioFornito())+" GB";
    spazioRimanente->setText(spazio);

    informazioniAccount->show();
}

void MainWindow::visualizzaListaFile() {
    listaFile->clear();
    Container<Deepptr<File>> lista = controller->getAccount(tabellaFile->currentRow())->getListaFile();
    for(auto it = lista.begin(); it != lista.end(); ++it) {
        QTreeWidgetItem* nuovo = new QTreeWidgetItem;
        nuovo->setIcon(1, it->getPuntatore()->getIcona()); nuovo->setTextAlignment(1, Qt::AlignCenter);
        nuovo->setText(2, it->getPuntatore()->getNome()); nuovo->setTextAlignment(2, Qt::AlignCenter);
        nuovo->setText(3, "."+it->getPuntatore()->getEstensione()); nuovo->setTextAlignment(3, Qt::AlignCenter);
        nuovo->setText(4, QString::number(it->getPuntatore()->getDimensione()).append(" MB")); nuovo->setTextAlignment(4, Qt::AlignCenter);
        nuovo->setText(5, it->getPuntatore()->getDescrizione());
        listaFile->addTopLevelItem(nuovo);
    }
}

void MainWindow::visualizzaFile() {
   // tabellaFile->selectedItems();
    informazioniFile->show();
}

MainWindow::~MainWindow() {
}
