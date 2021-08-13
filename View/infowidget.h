#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QTextLayout>
#include <QTextEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class InfoWidget : public QMainWindow{
    Q_OBJECT

public:
    InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();
};

#endif // INFOWIDGET_H
