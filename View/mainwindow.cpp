#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("QtDrive");
    setMinimumSize(1024, 720);

    //Layout Pagina Principale
    QVBoxLayout* pagina = new QVBoxLayout();

    //Layout delle Tabs
    QWidget* paginaFile = new QWidget;
    QHBoxLayout* layoutContenitore = new QHBoxLayout;
    tabellaFile = new QTableWidget;
    tabellaFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabellaFile->setRowCount(10);
    tabellaFile->setColumnCount(4);
    QStringList headers;
    headers << "Servizio" << "Email" << "Password" << "Spazio fornito";
    tabellaFile->setHorizontalHeaderLabels(headers);
    tabellaFile->verticalHeader()->hide();
    tabellaFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabellaFile->setSelectionMode(QAbstractItemView::SingleSelection);
    tabellaFile->setAlternatingRowColors(true);
    tabellaFile->horizontalHeader()->setSectionsClickable(false);
    tabellaFile->setSortingEnabled(false);
    tabellaFile->resizeRowsToContents();
    tabellaFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QTreeWidget* listaFile = new QTreeWidget;
    layoutContenitore->addWidget(tabellaFile);
    layoutContenitore->addWidget(listaFile);
    paginaFile->setLayout(layoutContenitore);
    connect(tabellaFile, SIGNAL(cellClicked(int,int)), this, SLOT(visualizzaFile(int)));

    QWidget* paginaAccount = new QWidget();
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
    tabs->insertTab(0, paginaAccount, QIcon(":/res/styles/icons/home.svg"), "Account");
    tabs->insertTab(1, paginaFile, QIcon(":/res/styles/icons/services.svg"), "File per Account");
    tabs->insertTab(2, paginaRicerca, QIcon(":/res/styles/icons/nodes.svg"), "Ricerca File");

    /*tabs->setTabEnabled(1, false);
    tabs->setTabEnabled(2, false);*/

    //Aggiunta dei Widget e dei Layout al frame principale
    //layoutMenu->addWidget(menu);

    pagina->addWidget(menu);
    pagina->addWidget(tabs);

    tabs->setCurrentIndex(1);

    // Connessione a "Apri"
    connect(apriFile, &QAction::triggered,  [=]() {
        QString fileScelto = QFileDialog::getOpenFileName(this, "Apri account", "./", "Account (*.xml)");
        if (fileScelto.isEmpty()) return;
        else{
            QFile file(fileScelto);
            //bool success;
            //Caricare le informazione sul widget.
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


    //CONNESSIONE DI PROVA PER INSERIMENTO ACCOUNT
    connect(info, &QAction::triggered, [=]() {
        AccountWidget* infoWidget = new AccountWidget();
        infoWidget->setWindowModality(Qt::ApplicationModal); // Quando la finestra è aperta, le altre non possono essere selezionate
        infoWidget->setAttribute(Qt::WA_DeleteOnClose);
        infoWidget->show();
    });

    // Inizializzazione file di default, se non esiste viene creato
    QFile file("account.json");
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

void MainWindow::visualizzaFile(int riga) const{
    tabellaFile->selectedItems();
    qDebug() << tabellaFile->selectionModel()->currentIndex().row();
}

MainWindow::~MainWindow() {
}
