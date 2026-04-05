#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setbackground(const QString&filename);
    void initbutton();
    void setButtonStyle(QPushButton * button,const QString&filename);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
