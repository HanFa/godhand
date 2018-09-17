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
#include <QPoint>
#include <QRect>
#include <QTime>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void setRandSource();
    int getRandnum(int);
protected:

private slots:
    void on_ShowImg_triggered();

    void on_Generate_triggered();

    void on_PenWidthSbx_editingFinished();

    void on_CharacterFamilyTxt_editingFinished();

    void on_CharacterSizeTxt_editingFinished();

    void on_CharacterSpaceTxt_editingFinished();

    void on_CharacterExample_editingFinished();

    void on_RandOffsetTxt_editingFinished();

    void on_RandPenWidthSbx_editingFinished();

    void on_RandomScaleTxt_editingFinished();

    void on_randRotateTxt_editingFinished();

private:
    Ui::MainWindow *ui;
    /*show img in Preview area*/
    void outPreview(QString *);
    /*draw a charactere and raturn it's image*/
    QImage drawCharacter(QString,int ,int);
    void generateExp();
    void ifErrorDig(bool, QString);
};

#endif // MAINWINDOW_H
