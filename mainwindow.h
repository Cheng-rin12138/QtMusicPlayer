#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void handlePlaySlot();
    void listvisible();
    void prevmusic();
    void nextmusic();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString getBackgroundDir();
    void setbackground();
    void initbutton();
    void setButtonStyle(QPushButton * button,const QString&filename);
    void loadAppointMusicDir(const QString&filepath);
    void playSelectMusic(QListWidgetItem * item);
    void playByIndex(int index);
    Ui::MainWindow *ui;
    bool listisvisible=true;
    QMediaPlayer * m_player=nullptr;
    QAudioOutput * m_audiooutput=nullptr;
    QStringList m_musicpath;
    int m_currentIndex = -1;
};
#endif // MAINWINDOW_H
