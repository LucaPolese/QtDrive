#ifndef GUIDAWIDGET_H
#define GUIDAWIDGET_H

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QShortcut>
#include <QIcon>
#include <QTextBrowser>

class GuidaWidget: public QWidget {
    Q_OBJECT

public:
    GuidaWidget(QWidget *parent = nullptr);
    ~GuidaWidget();
};

#endif // GUIDAWIDGET_H
