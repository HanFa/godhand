#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEFALUTFONT "Times New Roman" //default font

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QFont>
#include <QImage>
#include <QPoint>
#include <QRect>
#include <QTime>
#include <QList>
#include <QStringList>
#include <QListWidgetItem>
#include <QTranslator>
#include <QtDebug>

class QMessageBox;
class QPixmap;
class QPainter;
class QPen;
class QFont;
class QImage;
class QPoint;
class QTime;

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

    void on_addFont_clicked();

    void on_remoteFont_clicked();

private:
    Ui::MainWindow *ui;
    QList <QImage*> pageList;
    QList <QFont> fontList;
    QTranslator *translator;
    /*show img in Preview area*/
    void outPreview(QString *);
    /*draw a charactere and raturn it's image*/
    QImage drawCharacter(QString character,int CharacterSpace,int characterSize);

    void generateExp();//generate exmaple character
    void ifErrorDig(bool, QString);
    void generateOutPage();
};

#endif // MAINWINDOW_H
