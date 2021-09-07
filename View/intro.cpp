#include "mainwindow.h"
#include "intro.h"

Intro::Intro() : QSplashScreen(){
    setCursor(Qt::BusyCursor);
}

Intro::~Intro() = default;

void Intro::execute(QApplication& app, QWidget& w){
    QMovie* video = new QMovie(":res/icons/Intro.gif");
    QLabel* label = new QLabel;

    label->setMovie(video);
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->setFixedSize(500,500);
    label->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,label->size(),qApp->desktop()->availableGeometry()));
    video->start();
    label->show();

    app.processEvents(QEventLoop::AllEvents);

    QTimer::singleShot(3500,label,SLOT(close()));
    QTimer::singleShot(3500,&w,SLOT(show()));

}
