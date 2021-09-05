#include "View/mainwindow.h"
#include "View/splash.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow view;
    Splash splash;
    splash.execute(a, view);
    return a.exec();
}
