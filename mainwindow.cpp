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
    QString character = ui->textEdit->toPlainText();
    QFont font;

    font.setPixelSize(ui->CharacterSizeTxt->text().toInt());//set font size
    font.setFamily(ui->CharacterFamilyTxt->text());//set family
    font.setWeight(ui->PenWidthTxt->text().toInt());

    //get size
    QFontMetrics fm(font);
    int adSpacee =ui->CharacterSpaceTxt->text().toInt();
    int charWidth = fm.width(character);
    int charHeight = fm.height();
    QSize imgSize(charWidth+adSpacee,charHeight+adSpacee);

    QImage img(imgSize,QImage::Format_ARGB32);//Create a img

    img.fill(Qt::transparent);//fill a transparent background
    QPainter painter(&img);//create a painter
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);//set CompositionMode to paint a draw

    //get a pen, set font and ready to draw
    QPen pen = painter.pen();
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    painter.setFont(font);

    painter.drawText(img.rect(),Qt::AlignCenter,character);

    //save img
    ifErrorDig(img.save("./imgOutput.png","png",100),
               "An error occur when we save img!");
     return ;
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

void MainWindow::on_ShowImg_triggered()//when push ShowImg
{
    QString fileName = "./imgOutput.png";
    this->outPutImg(&fileName);
}


void MainWindow::on_Generate_triggered()
{
    drawCharacter();
    QString fileName = "./imgOutput.png";
    this->outPutImg(&fileName);
}
