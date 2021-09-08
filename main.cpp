#include "View/mainwindow.h"
#include "View/intro.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow view;
    Intro intro;
    intro.execute(a, view);
    return a.exec();
}
