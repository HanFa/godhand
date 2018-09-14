#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>//
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

    void loadImg(QString *);

private slots:
    void on_ShowImg_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
