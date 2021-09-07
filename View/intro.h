#ifndef INTRO_H
#define INTRO_H

#include <QSplashScreen>
#include <QMovie>
#include <QLabel>
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include <QTimer>

class Intro: public QSplashScreen{
public:
    Intro();
    ~Intro();
    void execute(QApplication&, QWidget&);
};

#endif // INTRO_H
