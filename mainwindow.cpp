#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIcon>
#include<QPixmap>
#include<QPalette>
void MainWindow::setbackground(const QString&filename)
{
    QPixmap pixmap(filename);
    QSize windowSize=this->size();
    QPixmap scalePixmap=pixmap.scaled(windowSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Window,QBrush(scalePixmap));
    this->setPalette(palette);
}
void MainWindow::setButtonStyle(QPushButton * button,const QString&filename)
{
    button->setFixedSize(50,50);
    button->setIcon(QIcon(filename));
    button->setStyleSheet("background-color:transparent");
    button->setIconSize(QSize(button->width(),button->height()));
}
void MainWindow::initbutton()
{
    setButtonStyle(ui->headBtn,":/Icon/head.png");
    setButtonStyle(ui->prevBtn,":/Icon/prev.png");
    setButtonStyle(ui->playBtn,":/Icon/play.png");
    setButtonStyle(ui->pauseBtn,":/Icon/pause.png");
    setButtonStyle(ui->nextBtn,":/Icon/next.png");
    setButtonStyle(ui->tailBtn,":/Icon/tail.png");
    setButtonStyle(ui->volBtn,":/Icon/volume.png");
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("uma音乐播放器");
    setFixedSize(1100,660);//固定尺寸
    setbackground(":/background/bg1.png");
    initbutton();

}




MainWindow::~MainWindow()
{
    delete ui;
}
