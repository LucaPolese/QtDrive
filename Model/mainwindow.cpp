#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("QtDrive");

    // Menubar
    QMenuBar *menu = new QMenuBar();
        // File
        QMenu *menuFile = new QMenu("File", menu);
            QAction *apriFile = new QAction("Apri", menuFile); apriFile->setShortcut(Qt::CTRL | Qt::Key_O);
            QAction *salvaFile = new QAction("Salva", menuFile); salvaFile->setShortcut(Qt::CTRL | Qt::Key_S);
            QAction *chiudiApplicazione = new QAction("Esci", menuFile); chiudiApplicazione->setShortcut(Qt::CTRL | Qt::Key_Q);
            menu->addMenu(menuFile);
                menuFile->addAction(apriFile);
                menuFile->addAction(salvaFile);
                menuFile->addSeparator();
                menuFile->addAction(chiudiApplicazione);
        // Aiuto
        QMenu *menuAiuto = new QMenu("Aiuto", menu);
            QAction *guida = new QAction("Guida", menuAiuto); guida->setShortcut(Qt::CTRL | Qt::Key_H);
            QAction *info = new QAction("Info", menuAiuto); info->setShortcut(Qt::CTRL | Qt::Key_I);
            menu->addMenu(menuAiuto);
                menuAiuto->addAction(guida);
                menuAiuto->addAction(info);
   // menu->setVisible(true);
}



MainWindow::~MainWindow(){
}

