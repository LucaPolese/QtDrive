#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QListWidget>
#include <QToolButton>
#include <QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>

#include "guidawidget.h"
#include "infowidget.h"
#include "accountwidget.h"
#include "nuovofilewidget.h"
#include "infofilewidget.h"
#include <QFileDialog>
#include <QFile>
#include <QScrollArea>

#include "Model/account.h"
#include "Model/deepptr.h"
#include "Model/container.h"
#include "Model/xmlify.h"

// Classi per i grafici
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalPercentBarSeries>
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QWidget{
    Q_OBJECT

private:
    Controller* controller;
    Container<Deepptr<Account>> accountsUtente; //Lista degli account dell'utente

    // Elementi prima scheda
    QTableWidget* tabellaAccount;
    QVBoxLayout* layoutInfoAccount;
    QWidget* informazioniAccount;
    QBarSet* set0;
    QBarSet* set1;
    QBarSet* set2;
    QBarSet* set3;
    QBarSet* set4;
    QHorizontalPercentBarSeries *series;
    QChart *chart;
    QChartView *chartView;
    QLineEdit* emailAccount;
    QLineEdit* passwordAccount;
    QLabel* numeroFile;
    QLabel* spazioRimanente;
    QPushButton* modificaAccount;
    QPushButton* eliminaAccount;
    QPushButton* chiudiAccount;
    AccountWidget* accountWidget;

    // Elementi seconda scheda
    QTableWidget* tabellaFile;
    QVBoxLayout* layoutInfoFile;
    QPushButton* nuovoFile;
    QPushButton* eliminaFile;
    QPushButton* chiudiListaFile;
    QWidget* informazioniFile;
    NuovoFileWidget* fileWidget;
    QTreeWidget* listaFile;
    InfoFileWidget* infoFileWidget;

    // Elementi terza scheda
    QLineEdit* inputRicerca;
    QCheckBox* ricercaPerNome;
    QCheckBox* ricercaPerDescrizione;
    QTreeWidget* listaRicerca;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent (QCloseEvent *event);
public slots:
    void visualizzaInfoAccount();
    void aggiungiAccount();
    void visualizzaAccount();

    void visualizzaAccountRidotto();
    void visualizzaListaFile();
    void visualizzaFile();

    void ricerca(const QString);
    void visualizzaFileDrive();
};

#endif
