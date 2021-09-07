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
#include <QProgressBar>

#include "guidawidget.h"
#include "infowidget.h"
#include "accountwidget.h"
#include "nuovofilewidget.h"
#include "infofilewidget.h"
#include "modificaaccountwidget.h"
#include <QFileDialog>
#include <QFile>
#include <QScrollArea>

#include "Model/account.h"
#include "Model/deepptr.h"
#include "Model/container.h"
#include "Model/xmlify.h"

class MainWindow : public QWidget{
    Q_OBJECT

private:
    Controller* controller;
    Container<Deepptr<Account>> accountsUtente; //Lista degli account dell'utente

    QTabWidget* tabs;

    // Elementi prima scheda
    QTableWidget* tabellaAccount;
    QVBoxLayout* layoutInfoAccount;
    QWidget* informazioniAccount;
    QLabel* emailAccount;
    QLabel* passwordAccount;
    QLabel* numeroFile;
    QLabel* spazioRimanente;
    QPushButton* modificaAccount;
    QPushButton* eliminaAccount;
    QPushButton* chiudiAccount;
    AccountWidget* accountWidget;
    ModificaAccountWidget* modificaAccountWidget;
    QLabel* numeroFileArchivio;
    QLabel* numeroFileTesto;
    QLabel* numeroFileImmagine;
    QLabel* numeroFileAudio;
    QLabel* numeroFileVideo;
    QProgressBar* barraOccupazione;

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
    QCheckBox* ricercaAvanzata;
    QCheckBox* ricercaCaseSensitive;
    QTreeWidget* listaRicerca;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent (QCloseEvent *event);
public slots:
    void modificaDellAccount();
    void eliminazioneDellAccount();
    void chiusuraDellAccount();
    void visualizzaInfoAccount();
    void visualizzaFile();
    void visualizzaListaFile();
    void creaNuovoFile();
    void eliminazioneDelFile();
    void chiusuraListaFile();
    void attivaEliminaFile();
    void refreshDati();
    void visualizzaInformazioniAggiuntiveFile();
    void ricerca(const QString);
    void visualizzaAccount();
    void visualizzaAccountRidotto();
    void visualizzaFileDrive();
    void selezioneTab();
    void selezioneAltroAccount();
    void apriNuovoFile();
    void apriIlFile();
    void salvaIlFile();
    void salvaIlNuovoFile();
    void aggiungiAccount();
    void fileTrovato();
    void checkboxSelezionato(int);
    void controlloCheckbox();
};

#endif
