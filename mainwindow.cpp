#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outPutImg(QString *fileName)//load output picture
{
    QImage *img = new QImage;
    ifErrorDig(img->load(*fileName),
               "An error occur when we load image!");
    ui->OutPhotoLab->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::drawCharacter()
{
    QString character = "A";
    QFont font;
    //set font size
    font.setPixelSize(100);
    font.setFamily("liguofu");

    //get size
    QFontMetrics fm(font);
    int charWidth = fm.width(character);
    int charHeight = fm.height();
    QSize imgSize(charWidth+2,charHeight+2);

    QImage img(imgSize,QImage::Format_ARGB32);//Create a img

    img.fill(Qt::white);//fill a transparent background
    QPainter painter(&img);//create a painter
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);//set CompositionMode to paint a draw

    //get a pen, set font and ready to draw
    QPen pen = painter.pen();
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    painter.setFont(font);

    painter.drawText(img.rect(),Qt::AlignCenter,character);

    ifErrorDig(img.save("./imgOutput1.png","png",100),
               "An error occur when we save img!");
     return ;
}

void MainWindow::on_ShowImg_triggered()//when push ShowImg
{
    QString fileName = ":/img/imgTest.png";
    this->outPutImg(&fileName);
}



void MainWindow::ifErrorDig(bool result, QString tital)
{
    if(!result)
    {
        QMessageBox megBox;//show a messageBox to alarm
        megBox.setWindowTitle(tr("Error"));
        megBox.setIcon(QMessageBox::Critical);//Question,Information,Warning,Critical
        megBox.setText(tital);
        megBox.addButton(tr("(╯‵□′)╯︵┻━┻"),QMessageBox::YesRole);
        megBox.exec();
        return ;
    }
}
