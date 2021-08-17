#ifndef GUIDAWIDGET_H
#define GUIDAWIDGET_H

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QShortcut>

class GuidaWidget: public QWidget {
    Q_OBJECT

public:
    GuidaWidget(QWidget *parent = nullptr);
};

#endif // GUIDAWIDGET_H
