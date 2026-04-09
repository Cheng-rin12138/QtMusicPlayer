#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIcon>

#include<QPixmap>
#include<QPalette>

#include<QDir>
#include<QFile>
#include<QFileInfo>

#include<QCoreApplication>

#include<QMessageBox>
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
    setButtonStyle(ui->nextBtn,":/Icon/next.png");
    setButtonStyle(ui->tailBtn,":/Icon/tail.png");
    setButtonStyle(ui->volBtn,":/Icon/volume.png");
    setButtonStyle(ui->list,":/Icon/playlist.png");
}
void MainWindow::handlePlaySlot()
{
    if(m_player->playbackState()==QMediaPlayer::PlayingState)
    {
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/Icon/play.png"));
    }
    else
    {
        m_player->play();
        ui->playBtn->setIcon(QIcon(":/Icon/pause.png"));
    }
}
void MainWindow::listvisible()
{
    listisvisible=!listisvisible;
    ui->musicList->setVisible(listisvisible);
}
void MainWindow::loadAppointMusicDir(const QString&filepath)
{
    QDir dir(filepath);
    if(dir.exists()==false)
    {
        QMessageBox::warning(this,"文件夹","文件夹不存在");
    }
    QFileInfoList filelist=dir.entryInfoList(QDir::Files);
    ui->musicList->clear();
    m_musicpath.clear();
    for(auto element:filelist)
    {
        if(element.suffix()=="mp3")
        {
            ui->musicList->addItem(element.fileName());
            m_musicpath.append(element.absoluteFilePath());
        }
    }
}
void MainWindow::playSelectMusic(QListWidgetItem * item)
{
    if(!item)return;
    int index=ui->musicList->row(item);
    QString path=m_musicpath.at(index);

    m_player->setSource(QUrl::fromLocalFile(path));
    m_player->play();
}
QString getCorrectMusicDir()
{
    //exe 同级（打包后用）
    QString dir1 = QCoreApplication::applicationDirPath() + "/music/";
    if (QDir(dir1).exists()) return dir1;

    //从 build 目录回退到项目根目录（调试用）
    // 你的 exe 在 build/debug/，回退3级就是项目根目录
    QString dir2 = QCoreApplication::applicationDirPath() + "/../../music/";
    if (QDir(dir2).exists()) return dir2;

    //兜底：直接写项目根目录
    return "C:/QTproject/MusicPlayer/MusicPlayer/music/";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("uma音乐播放器");
    m_player=new QMediaPlayer(this);
    m_audiooutput=new QAudioOutput(this);
    m_player->setAudioOutput(m_audiooutput); // 强制绑定
    m_audiooutput->setVolume(0.2); // 设置默认音量（0.0~1.0）
    setFixedSize(1100,660);//固定尺寸
    setbackground(":/background/bg1.png");
    initbutton();
    QString musicDir=getCorrectMusicDir();
    qDebug() << "实际查找路径：" << musicDir;
    qDebug() << "文件夹是否存在：" << QDir(musicDir).exists();

    loadAppointMusicDir(musicDir);
    connect(ui->playBtn,&QPushButton::clicked,this,&MainWindow::handlePlaySlot);
    connect(ui->list,&QPushButton::clicked,this,&MainWindow::listvisible);
    connect(ui->musicList,&QListWidget::itemClicked,this,&MainWindow::playSelectMusic);
}




MainWindow::~MainWindow()
{
    delete ui;
}
