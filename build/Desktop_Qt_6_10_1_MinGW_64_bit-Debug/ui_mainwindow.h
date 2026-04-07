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
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *headBtn;
    QPushButton *prevBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *tailBtn;
    QPushButton *volBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(958, 613);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 510, 611, 121));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        headBtn = new QPushButton(widget);
        headBtn->setObjectName("headBtn");

        horizontalLayout->addWidget(headBtn);

        prevBtn = new QPushButton(widget);
        prevBtn->setObjectName("prevBtn");

        horizontalLayout->addWidget(prevBtn);

        playBtn = new QPushButton(widget);
        playBtn->setObjectName("playBtn");

        horizontalLayout->addWidget(playBtn);

        nextBtn = new QPushButton(widget);
        nextBtn->setObjectName("nextBtn");

        horizontalLayout->addWidget(nextBtn);

        tailBtn = new QPushButton(widget);
        tailBtn->setObjectName("tailBtn");

        horizontalLayout->addWidget(tailBtn);

        volBtn = new QPushButton(widget);
        volBtn->setObjectName("volBtn");

        horizontalLayout->addWidget(volBtn);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 958, 22));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
