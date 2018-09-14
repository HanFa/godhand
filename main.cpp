#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QString fileName = ":/img/output.png";
    w.loadImg(&fileName);
    return a.exec();
}
