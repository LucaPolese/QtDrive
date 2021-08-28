#ifndef XMLIFYCOPIA_H
#define XMLIFYCOPIA_H
#include "deepptr.h"
#include "account.h"
#include "container.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
class XmlifyCopia{
private:
    QString account;
public:
    XmlifyCopia(const QString &);
    bool salvaFile(const File* fileDaSalvare1, const File* fileDaSalvare2) const;
};
#endif // XMLIFYCOPIA_H
