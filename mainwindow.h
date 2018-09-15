#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QChar>
#include <QFont>
#include <QImage>
#include <QRect>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawCharacter();
protected:

private slots:
    void on_ShowImg_triggered();

private:
    Ui::MainWindow *ui;
    void outPutImg(QString *);
    void ifErrorDig(bool, QString);
};

#endif // MAINWINDOW_H
