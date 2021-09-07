#include "mainwindow.h"
#include "splash.h"

Splash::Splash() : QSplashScreen(){
     setCursor(Qt::BusyCursor);
}

void Splash::execute(QApplication& app, QWidget& w){
    QMovie* video = new QMovie(":res/icons/Intro.gif");
    QLabel* label = new QLabel;

    label->setMovie(video);
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->setFixedSize(500,500);
    label->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,label->size(),qApp->desktop()->availableGeometry()));
    video->start();
    label->show();

    app.processEvents(QEventLoop::AllEvents);

    QTimer::singleShot(5000,label,SLOT(close()));
    QTimer::singleShot(5000,&w,SLOT(show()));
}
