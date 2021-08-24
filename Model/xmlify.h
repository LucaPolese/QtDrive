#ifndef XMLIFY_H
#define XMLIFY_H

#include "deepptr.h"
#include "account.h"
#include "container.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>

class Xmlify{
private:
    QString account;
public:
    Xmlify(const QString &);
    bool salvaAccount(const Container<Deepptr<Account>>& listaAccount) const;
    Container<Deepptr<Account>> acquisisciAccount() const;
};

#endif // XMLIFY_H
