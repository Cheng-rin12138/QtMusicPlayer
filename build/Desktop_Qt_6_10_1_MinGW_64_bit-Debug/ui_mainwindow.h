/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *buttonbar;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *headBtn;
    QPushButton *prevBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *tailBtn;
    QPushButton *volBtn;
    QPushButton *list;
    QListWidget *musicList;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1153, 691);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        buttonbar = new QWidget(centralwidget);
        buttonbar->setObjectName("buttonbar");
        buttonbar->setGeometry(QRect(0, 500, 1141, 161));
        buttonbar->setStyleSheet(QString::fromUtf8("background-color: rgba(230, 230,230, 0.9);\n"
"border-top: 1px solid rgba(255,255,255,0.1);"));
        horizontalLayout_2 = new QHBoxLayout(buttonbar);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        headBtn = new QPushButton(buttonbar);
        headBtn->setObjectName("headBtn");

        horizontalLayout->addWidget(headBtn);

        prevBtn = new QPushButton(buttonbar);
        prevBtn->setObjectName("prevBtn");

        horizontalLayout->addWidget(prevBtn);

        playBtn = new QPushButton(buttonbar);
        playBtn->setObjectName("playBtn");

        horizontalLayout->addWidget(playBtn);

        nextBtn = new QPushButton(buttonbar);
        nextBtn->setObjectName("nextBtn");

        horizontalLayout->addWidget(nextBtn);

        tailBtn = new QPushButton(buttonbar);
        tailBtn->setObjectName("tailBtn");

        horizontalLayout->addWidget(tailBtn);

        volBtn = new QPushButton(buttonbar);
        volBtn->setObjectName("volBtn");

        horizontalLayout->addWidget(volBtn);

        list = new QPushButton(buttonbar);
        list->setObjectName("list");

        horizontalLayout->addWidget(list);


        horizontalLayout_2->addLayout(horizontalLayout);

        musicList = new QListWidget(centralwidget);
        musicList->setObjectName("musicList");
        musicList->setGeometry(QRect(800, 90, 256, 421));
        MainWindow->setCentralWidget(centralwidget);
        musicList->raise();
        buttonbar->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1153, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        headBtn->setText(QString());
        prevBtn->setText(QString());
        playBtn->setText(QString());
        nextBtn->setText(QString());
        tailBtn->setText(QString());
        volBtn->setText(QString());
        list->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
