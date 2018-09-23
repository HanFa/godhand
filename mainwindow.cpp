#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simplepage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setRandSource();
    translator = new QTranslator;
    translator->load("./godhand_zh_CN.qm");
    qApp->installTranslator(translator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outPreview(QString *fileName)//load output picture
{
    QImage *img = new QImage;
    ifErrorDig(img->load(*fileName),
               "An error occur when we load image!");
    ui->PreviewLab->setPixmap(QPixmap::fromImage(*img));
}

QImage MainWindow::drawCharacter(QString character,int CharacterSpace,int characterSize)
{
    //get requirement input by user
    int penWidth= ui->PenWidthSbx->text().toInt();
    //In order to ensure next character font is different than previous one. character number will be store
    static int preCharacterNum = 0;
    int totalFont = fontList.length();
    QFont *font = new QFont;

    if(totalFont==0){
        font->setFamily(DEFALUTFONT);
    }
    else{
        int fontnum;
        do{
            fontnum = qrand()%totalFont;
        }while(fontnum==preCharacterNum&&totalFont!=1);

        //set font
        font->setFamily(fontList.at(fontnum).family());
    }
    font->setPixelSize(characterSize);//set font size
    font->setWeight(penWidth);

    //set image size
    QFontMetrics fm(*font);
    int charWidth = fm.width(character);
    int charHeight = fm.height();
    QSize imgSize(charWidth+CharacterSpace,charHeight+CharacterSpace);

    QImage img(imgSize,QImage::Format_ARGB32);//Create a img

    img.fill(Qt::transparent);//fill a transparent background
    QPainter painter(&img);//create a painter
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);//set CompositionMode to paint a draw

    //get a pen, set font and ready to draw
    QPen pen = painter.pen();
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    painter.setFont(*font);

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
        font->setWeight(randPenWidth);
        painter.setFont(*font);
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

void MainWindow::generateOutPage()
{
    //delete exist page
    while(!pageList.isEmpty()){
        pageList.removeLast();
    }
    //load backgronud and prepare
    pageList.append(new QImage(":/img/BackgroundA4.png"));
    QPainter painter(pageList.at(0));

    //get font size
    QFont font;
    font.setPixelSize(ui->CharacterSizeTxt->text().toInt());
    if(fontList.length()==0){
        font.setFamily("宋体");
    }
    else{
        font.setFamily(fontList.at(0).family());
    }
    QFontMetrics fm(font);
    //ready a page map
    Simplepage pageMap(pageList.at(0)->size(),
                       ui->topMargainTxt->text().toInt(),ui->bottemMargainTxt->text().toInt(),
                       ui->leftMargainTxt->text().toInt(),ui->rightMargainTxt->text().toInt(),
                       ui->columnSpacingTxt->text().toInt(),ui->lineSpacingTxt->text().toInt(),
                       fm.width("例")+ui->CharacterSpaceTxt->text().toInt(),fm.height()+ui->CharacterSpaceTxt->text().toInt());

    //draw
    QPixmap pix;
    QImage charImage;
    int iLoop = 0;
    int totalMamber = ui->textEdit->document()->toPlainText().length();
    for(iLoop=0;iLoop<totalMamber;iLoop++){
        if(ui->textEdit->document()->toPlainText().mid(iLoop,1)=="\n")
        {
            pageMap.firstColumn();
            pageMap.netLine();
        }
        else
        {
            charImage = drawCharacter(ui->textEdit->document()->toPlainText().mid(iLoop,1),
                                      ui->CharacterSpaceTxt->text().toInt(),
                                      ui->CharacterSizeTxt->text().toInt());
            painter.drawPixmap(pageMap.atPixel(),QPixmap::fromImage(charImage));
            //...if full
            pageMap.nextPoint();
        }
    }
    ui->PreviewLab->setPixmap(QPixmap::fromImage(*pageList.at(0)));
}
/*******************************ui botten*******************************/
void MainWindow::on_ShowImg_triggered()//when push ShowImg
{
    generateOutPage();
    pageList.at(0)->save("./output.png","png",100);
}


void MainWindow::on_Generate_triggered()
{
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

void MainWindow::on_addFont_clicked()
{
    //record font and add fontListViw. all fontfamliy are show to user
    fontList.append(ui->fontCbx->currentFont());
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(ui->fontCbx->currentFont().family());
    item->setFont(ui->fontCbx->currentFont());
    ui->fontListViw->addItem(item);
}


void MainWindow::on_remoteFont_clicked()
{
    //ensure row is between 0 to length, otherwise program will crash
    int row = ui->fontListViw->currentRow();
    int length = ui->fontListViw->count();
    if(length ==0)
        return ;
    if(row<0){
        row = 0;
        ui->fontListViw->setCurrentRow(row);
    }
    else if(row>=length)
    {
        row = length-1;
        ui->fontListViw->setCurrentRow(row);
    }

    //remove item and font in fontList
    fontList.removeAll(ui->fontListViw->currentItem()->font());
    ui->fontListViw->takeItem(ui->fontListViw->currentRow());

    //set selected item
    if(row==length-1)
    {
        ui->fontListViw->setCurrentRow(row-1);
    }

}
