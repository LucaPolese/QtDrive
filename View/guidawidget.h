#ifndef GUIDAWIDGET_H
#define GUIDAWIDGET_H

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QShortcut>
#include <QIcon>

class GuidaWidget: public QWidget {
    Q_OBJECT

public:
    GuidaWidget(QWidget *parent = nullptr);
};

#endif // GUIDAWIDGET_H
