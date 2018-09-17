#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setRandSource();
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

QImage MainWindow::drawCharacter(QString character,int CharacterSpace,int characterSize)
{
    //get requirement input by user
//    QString character = ui->textEdit->toPlainText();
    QString characterFamily = ui->CharacterFamilyTxt->text();
//    int characterSize = ui->CharacterSizeTxt->text().toInt();
    int penWidth= ui->PenWidthSbx->text().toInt();
//    int CharacterSpace =ui->CharacterSpaceTxt->text().toInt();

    //set font
    QFont font;
    font.setPixelSize(characterSize);//set font size
    font.setFamily(characterFamily);//set family
    font.setWeight(penWidth);

    //set image size
    QFontMetrics fm(font);
    int charWidth = fm.width(character);
    int charHeight = fm.height();
    QSize imgSize(charWidth+CharacterSpace,charHeight+CharacterSpace);
//    QSize imgSize(charWidth,charHeight);

    QImage img(imgSize,QImage::Format_ARGB32);//Create a img

    img.fill(Qt::transparent);//fill a transparent background
    QPainter painter(&img);//create a painter
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);//set CompositionMode to paint a draw

    //get a pen, set font and ready to draw
    QPen pen = painter.pen();
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    painter.setFont(font);

    //calculate draw position and move coordinate to that
    QPoint drawPosition = img.rect().bottomLeft();
    drawPosition.setX(drawPosition.x()+CharacterSpace/2);
    drawPosition.setY(drawPosition.y()-characterSize/8-CharacterSpace/2);
    painter.translate(drawPosition);

    /*******random change before draw*******/

    //random offset
    int randoffNum = ui->RandOffsetTxt->text().toInt();
    int offsetX = 0;
    int offsetY = 0;
    if(randoffNum != 0){
    offsetX = getRandnum(randoffNum);
    offsetY = getRandnum(randoffNum);
    }

    //rand pend width. PenWidth mast between 0 and 99, otherwise program will crash
    int randPenWidth = ui->RandPenWidthSbx->text().toInt();
    if(randPenWidth != 0)
    {
        randPenWidth += penWidth + getRandnum(randPenWidth);
        if(randPenWidth>99)//make sure randPenWidth between 0 and 99
            randPenWidth = 99;
        else if(randPenWidth<0)
            randPenWidth = 0;
        font.setWeight(randPenWidth);
        painter.setFont(font);
    }

    //random rotate
    int randRotateAngel = ui->randRotateTxt->text().toInt();
    if(randRotateAngel != 0){
        qreal randRotate = (qreal)(randRotateAngel*rand()*1./(RAND_MAX));
        painter.rotate(randRotate);
    }

    //random scale. x and y will bcome 1/x~x and 1/y~y
    float randScale = ui->RandomScaleTxt->text().toFloat();
    if(randScale>0){
        qreal randScaleX = (qreal)(rand()*(randScale-1./randScale)*1./(RAND_MAX)+(1./randScale));
        qreal randScaleY = (qreal)(rand()*(randScale-1./randScale)*1./(RAND_MAX)+(1./randScale));
        ui->testTxt->setText(QString::number(randScaleX));
        painter.scale(randScaleX,randScaleY);
    }

    /******************draw******************/
    painter.drawText(offsetX,offsetY,character);
//    painter.drawText(img.rect(),Qt::AlignCenter,character);

//    ifErrorDig(img.save("./imgOutput.png","png",100),
//               "An error occur when we save img!");
     return img;
}

void MainWindow::generateExp()
{
    QImage img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example1->setPixmap(QPixmap::fromImage(img));
        ifErrorDig(img.save("./imgOutput.png","png",100),
                      "An error occur when we save img!");
    img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example2->setPixmap(QPixmap::fromImage(img));
    img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example3->setPixmap(QPixmap::fromImage(img));
    img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example4->setPixmap(QPixmap::fromImage(img));
    img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example5->setPixmap(QPixmap::fromImage(img));
    img = drawCharacter(ui->CharacterExample->text(),10,40);
    ui->Example6->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::ifErrorDig(bool result, QString tital)
{
    if(!result)
    {
        QMessageBox megBox;//show a messageBox to alarm
        megBox.setWindowTitle(tr("Σ(っ°Д°;)っ ERROR"));
        megBox.setIcon(QMessageBox::Critical);//Question,Information,Warning,Critical
        megBox.setText(tital);
        megBox.addButton(tr("(╯‵□′)╯︵┻━┻"),QMessageBox::YesRole);
        megBox.exec();
        return ;
    }
}

void MainWindow::setRandSource()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

int MainWindow::getRandnum(int mod)
{
    int outnum = (qrand()%mod)-mod/2;
    return outnum;
}
/*******************************ui botten*******************************/
void MainWindow::on_ShowImg_triggered()//when push ShowImg
{
    QString fileName = "./imgOutput.png";
    this->outPutImg(&fileName);
}


void MainWindow::on_Generate_triggered()
{
//    QImage img = drawCharacter(ui->CharacterSizeTxt->text().toInt());
//    ifErrorDig(img.save("./imgOutput.png","png",100),
//                  "An error occur when we save img!");
//    QString fileName = "./imgOutput.png";
//    this->outPutImg(&fileName);
    generateExp();
}
void MainWindow::on_PenWidthSbx_editingFinished()
{
    generateExp();
}
void MainWindow::on_CharacterFamilyTxt_editingFinished()
{
    generateExp();
}
void MainWindow::on_CharacterSizeTxt_editingFinished()
{
    generateExp();
}
void MainWindow::on_CharacterSpaceTxt_editingFinished()
{
    generateExp();
}
void MainWindow::on_CharacterExample_editingFinished()
{
    generateExp();
}
void MainWindow::on_RandOffsetTxt_editingFinished()
{
    generateExp();
}
void MainWindow::on_RandPenWidthSbx_editingFinished()
{
    generateExp();
}
void MainWindow::on_RandomScaleTxt_editingFinished()
{
    generateExp();
}
void MainWindow::on_randRotateTxt_editingFinished()
{
    generateExp();
}
