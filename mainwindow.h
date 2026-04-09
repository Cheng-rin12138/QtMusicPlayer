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
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setbackground(const QString&filename);
    void initbutton();
    void setButtonStyle(QPushButton * button,const QString&filename);
    void loadAppointMusicDir(const QString&filepath);
    void playSelectMusic(QListWidgetItem * item);
    Ui::MainWindow *ui;
    bool listisvisible=true;
    QMediaPlayer * m_player;
    QAudioOutput * m_audiooutput;
    QStringList m_musicpath;
};
#endif // MAINWINDOW_H
