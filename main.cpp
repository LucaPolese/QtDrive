#include "View/mainwindow.h"

#include <QApplication>
#include "Model/filevideo.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //FileVideo f = FileVideo("titolo", "mkv", 1204, QDate(2020,1,1), QDate(2020,1,1), "descrizione", FileMedia::compressione::lossless, "mpeg", 100000, 1024, 720, 29, FileAudio())
    return a.exec();
}
