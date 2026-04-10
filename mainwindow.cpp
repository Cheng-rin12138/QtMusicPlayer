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

QString MainWindow::getBackgroundDir()
{
    // exe同级目录（打包后用）
    QString dir1 = QCoreApplication::applicationDirPath() + "/background/";
    if (QDir(dir1).exists()) return dir1;

    // 从build目录回退到项目根目录
    QString dir2 = QCoreApplication::applicationDirPath() + "/../../background/";
    if (QDir(dir2).exists()) return dir2;

    // 用工作目录（你已经改了工作目录为项目根目录）
    return QDir::currentPath() + "/background/";
}
void MainWindow::setbackground()
{
    QString bgDir = getBackgroundDir();
    QDir dir(bgDir);

    // 筛选图片格式：png、jpg、jpeg、bmp
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    if (fileList.isEmpty()) {
        qDebug() << "背景文件夹为空，使用默认背景";
        return;
    }

    // 取第一张图片作为默认背景
    QString firstBgPath = fileList.first().absoluteFilePath();
    QPixmap pixmap(firstBgPath);

    if (pixmap.isNull()) {
        qDebug() << "背景图片加载失败:" << firstBgPath;
        return;
    }

    //QPixmap pixmap(filename);
    QSize windowSize=this->size();
    QPixmap scalePixmap=pixmap.scaled(windowSize,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
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
    m_currentIndex = index;
    playByIndex(index);
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

// 通用播放函数：根据索引播放歌曲
void MainWindow::playByIndex(int index)
{
    // 越界保护，避免崩溃
    if (index < 0 || index >= m_musicpath.size())
        return;

    // 更新当前索引
    m_currentIndex = index;

    // 播放歌曲
    QString path = m_musicpath.at(index);
    m_player->setSource(QUrl::fromLocalFile(path));
    m_player->play();

    // 列表自动高亮当前播放的歌曲
    ui->musicList->setCurrentRow(index);
}

void MainWindow::prevmusic()
{
    if (m_musicpath.isEmpty()) return; // 歌单为空，直接返回

    m_currentIndex--;
    // 循环播放：到第一首再点上一曲，跳到最后一首
    if (m_currentIndex < 0) {
        m_currentIndex = m_musicpath.size() - 1;
    }

    playByIndex(m_currentIndex); // 调用通用播放函数
}

// 下一曲
void MainWindow::nextmusic()
{
    if (m_musicpath.isEmpty()) return; // 歌单为空，直接返回

    m_currentIndex++;
    // 循环播放：到最后一首再点下一曲，跳到第一首
    if (m_currentIndex >= m_musicpath.size()) {
        m_currentIndex = 0;
    }

    playByIndex(m_currentIndex); // 调用通用播放函数
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
    setbackground();
    initbutton();
    QString musicDir=getCorrectMusicDir();
    qDebug() << "实际查找路径：" << musicDir;
    qDebug() << "文件夹是否存在：" << QDir(musicDir).exists();

    loadAppointMusicDir(musicDir);
    connect(ui->playBtn,&QPushButton::clicked,this,&MainWindow::handlePlaySlot);
    connect(ui->list,&QPushButton::clicked,this,&MainWindow::listvisible);
    connect(ui->musicList,&QListWidget::itemClicked,this,&MainWindow::playSelectMusic);
    connect(ui->prevBtn, &QPushButton::clicked, this, &MainWindow::prevmusic);
    connect(ui->nextBtn, &QPushButton::clicked, this, &MainWindow::nextmusic);
}




MainWindow::~MainWindow()
{
    delete ui;
}
