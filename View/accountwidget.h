#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QDebug>
#include <QMessageBox>
#include "../Control/controller.h"

class AccountWidget: public QWidget {
    Q_OBJECT

private:
    QVBoxLayout* layout;
    QFormLayout* formLayout;
    QLineEdit* email;
    QLineEdit* password;
    QComboBox* servizio;
    QSpinBox* spazioFornito;
    QHBoxLayout* buttonLayout;
    QPushButton* aggiungiAccount;
    QPushButton* annulla;
    Controller* controller;

public:
    AccountWidget(Controller *controller_, QWidget *parent = nullptr);
    ~AccountWidget();
    void closeEvent (QCloseEvent *event);

signals:
    void accountAggiunto();

public slots:
    void controlloEmail();
            void aggiungi();
};

#endif // ACCOUNTWIDGET_H
