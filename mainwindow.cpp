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

void MainWindow::loadImg(QString *fileName)
{
    QImage *img = new QImage;
    if(!(img->load(*fileName))){
        QMessageBox megBox;
        megBox.setWindowTitle(tr("Error"));
        megBox.setIcon(QMessageBox::Critical);//Question,Information,Warning,Critical
        megBox.setText(tr("An error occur when we load image!"));
        megBox.addButton(tr("Oh NO!"),QMessageBox::YesRole);
        megBox.exec();
        return ;
    }
    ui->OutPhotoLab->setPixmap(QPixmap::fromImage(*img));
}

void MainWindow::on_ShowImg_triggered()
{
    QString fileName = ":/img/img/imgOutput.png";
    this->loadImg(&fileName);
}
