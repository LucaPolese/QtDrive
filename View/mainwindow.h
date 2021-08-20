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
#include <QFileDialog>
#include <QFile>
#include <QScrollArea>

#include "Model/account.h"
#include "Model/deepptr.h"
#include "Model/container.h"
class MainWindow : public QWidget{
    Q_OBJECT

private:
    Container<Deepptr<Account>> accountsUtente; //Lista degli account dell'utente
    QTableWidget* tabellaFile;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void visualizzaFile(int riga) const;
    void closeEvent (QCloseEvent *event);
};

#endif
