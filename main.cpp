#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator *translator = new QTranslator;
    QLocale location;
    if(location.language()==QLocale::Language::Chinese)
    {
        translator->load("./godhand_zh_CN.qm");
    }
    qApp->installTranslator(translator);
    MainWindow w;
    w.show();
    return a.exec();
}
