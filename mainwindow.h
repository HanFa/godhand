#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPixmap>
#include <QString>
#include <QImage>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void loadImg(QString *);
};

#endif // MAINWINDOW_H
