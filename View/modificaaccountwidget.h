#ifndef MODIFICAACCOUNTWIDGET_H
#define MODIFICAACCOUNTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "../Control/controller.h"

class ModificaAccountWidget: public QWidget {
    Q_OBJECT

private:
    Controller* controller;
    QLineEdit* nuovaEmail;
    QLineEdit* nuovaPassword;
    QPushButton* salva;
    QPushButton* annulla;
    int indiceAccountAperto;

public:
    ModificaAccountWidget(Controller *controller_, QWidget *parent = nullptr);
    void visualizzaInfo(int, QString, QString);

    ~ModificaAccountWidget();

signals:
    void accountModificato();

public slots:
    void salvaModifiche();
    void annullaModifiche();
};

#endif // MODIFICAACCOUNTWIDGET_H
