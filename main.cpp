#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString characte = "2";
    w.show();
    w.drawCharacter();
    return a.exec();
}
