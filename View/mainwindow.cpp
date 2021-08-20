#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("QtDrive");
    setMinimumSize(1024, 720);

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
    this->layout()->setMenuBar(menu);

    // Connessione a "Apri"
    connect(apriFile, &QAction::triggered,  [=]() {
        QString fileScelto = QFileDialog::getOpenFileName(this, "Apri account", "./", "Account (*.xml)");
        if (fileScelto.isEmpty()) return;
        else{
            QFile file(fileScelto);
            bool success;
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

MainWindow::~MainWindow() {
}

