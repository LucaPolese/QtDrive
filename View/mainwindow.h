#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include "guidawidget.h"
#include "infowidget.h"
#include "accountwidget.h"
#include "nuovofilewidget.h"
#include <QFileDialog>
#include <QFile>
#include <QHeaderView>
#include <QToolButton>
#include <QTableWidget>
#include <QTreeWidget>
#include <QScrollArea>

class MainWindow : public QMainWindow{
    Q_OBJECT
private:

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent (QCloseEvent *event);
};

#endif
