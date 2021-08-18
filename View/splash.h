#ifndef SPLASH_H
#define SPLASH_H

#include <QSplashScreen>
#include <QMovie>
#include <QLabel>
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include <QTimer>
class Splash: public QSplashScreen{
public:
    Splash();
    ~Splash() = default;
    void execute(QApplication&, QWidget&);
};

#endif // SPLASH_H
