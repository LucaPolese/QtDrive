#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QTextLayout>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QShortcut>

class InfoWidget: public QWidget{
    Q_OBJECT

public:
    InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();
};

#endif // INFOWIDGET_H
