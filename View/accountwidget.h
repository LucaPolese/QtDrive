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
#include "../Control/controller.h"

class AccountWidget: public QWidget {
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
    AccountWidget(QWidget *parent = nullptr);

public slots:
    void aggiungi();
};

#endif // ACCOUNTWIDGET_H
