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

QString formatTime(qint64 ms)
{
    int totalSeconds = ms / 1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}

// 实时更新进度条和当前时间
void MainWindow::updateProgress(qint64 position)
{
    // 如果正在拖拽，不更新进度条，避免冲突抖动
    if (m_isSliderBeingDragged)
        return;

    // 设置进度条值
    ui->progressSlider->setValue(position);
    // 更新当前时间
    ui->currentlabel->setText(formatTime(position));
}

// 更新总时长
void MainWindow::updateDuration(qint64 duration)
{
    // 设置进度条最大值
    ui->progressSlider->setRange(0, duration);
    // 更新总时间
    ui->totallabel->setText(formatTime(duration));
}

// 拖拽进度条跳转播放
void MainWindow::onSliderMoved(int position)
{
    // 跳转到指定位置
    m_player->setPosition(position);
    // 更新当前时间
    ui->currentlabel->setText(formatTime(position));
}
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

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) {
            m_player->setPosition(0);  // 回到歌曲开头
            m_player->play();          // 继续播放
            //nextmusic();
        }
    });
    // 1. 播放位置变化 → 更新进度条
    connect(m_player, &QMediaPlayer::positionChanged,this, &MainWindow::updateProgress);
    // 2. 媒体时长变化 → 更新总时长
    connect(m_player, &QMediaPlayer::durationChanged,this, &MainWindow::updateDuration);
    // 3. 进度条被拖拽 → 跳转播放
    connect(ui->progressSlider, &QSlider::sliderMoved,this, &MainWindow::onSliderMoved);
    // 4. 标记拖拽状态（避免更新冲突，防止进度条抖动）
    connect(ui->progressSlider, &QSlider::sliderPressed,[this]() { m_isSliderBeingDragged = true ;});
    connect(ui->progressSlider, &QSlider::sliderReleased,[this]() { m_isSliderBeingDragged = false ;});
    // 初始化时间显示
    ui->currentlabel->setText("00:00");
    ui->totallabel->setText("00:00");
    ui->progressSlider->setValue(0);
}




MainWindow::~MainWindow()
{
    delete ui;
}
