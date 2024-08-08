/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <timersetter.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    TimerSetter *lbDateTime;
    QPushButton *btnCapture;
    QPushButton *btnQJ1;
    QPushButton *btnQJ2;
    QPushButton *btnZoomRestore;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnHealthLed;
    QPushButton *BtnHealthState;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *BtnMainWgt;
    QPushButton *BtnQuanjing;
    QPushButton *BtnZhouShi;
    QPushButton *BtnNVR;
    QPushButton *BtnExit;
    QScrollBar *horizontalScrollBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1600, 1200);
        MainWindow->setWindowOpacity(1.000000000000000);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 1160, 1600, 40));
        widget->setMinimumSize(QSize(0, 40));
        widget->setMaximumSize(QSize(16777215, 40));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(76,76,76);"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        lbDateTime = new TimerSetter(widget);
        lbDateTime->setObjectName("lbDateTime");
        lbDateTime->setMinimumSize(QSize(250, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        lbDateTime->setFont(font);

        horizontalLayout->addWidget(lbDateTime);

        btnCapture = new QPushButton(widget);
        btnCapture->setObjectName("btnCapture");

        horizontalLayout->addWidget(btnCapture);

        btnQJ1 = new QPushButton(widget);
        btnQJ1->setObjectName("btnQJ1");
        btnQJ1->setCheckable(true);
        btnQJ1->setChecked(true);

        horizontalLayout->addWidget(btnQJ1);

        btnQJ2 = new QPushButton(widget);
        btnQJ2->setObjectName("btnQJ2");
        btnQJ2->setCheckable(true);
        btnQJ2->setChecked(false);

        horizontalLayout->addWidget(btnQJ2);

        btnZoomRestore = new QPushButton(widget);
        btnZoomRestore->setObjectName("btnZoomRestore");
        btnZoomRestore->setCheckable(true);

        horizontalLayout->addWidget(btnZoomRestore);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnHealthLed = new QPushButton(widget);
        BtnHealthLed->setObjectName("BtnHealthLed");
        BtnHealthLed->setMinimumSize(QSize(30, 30));
        BtnHealthLed->setMaximumSize(QSize(30, 30));
        BtnHealthLed->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/green.png);"));

        horizontalLayout->addWidget(BtnHealthLed);

        BtnHealthState = new QPushButton(widget);
        BtnHealthState->setObjectName("BtnHealthState");
        BtnHealthState->setEnabled(true);
        BtnHealthState->setMinimumSize(QSize(110, 0));
        BtnHealthState->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\351\273\221\344\275\223")});
        font1.setPointSize(14);
        BtnHealthState->setFont(font1);
        BtnHealthState->setStyleSheet(QString::fromUtf8("color:rgb(255,255,255);\n"
"border:0px;\n"
""));

        horizontalLayout->addWidget(BtnHealthState);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        BtnMainWgt = new QPushButton(widget);
        BtnMainWgt->setObjectName("BtnMainWgt");
        BtnMainWgt->setMinimumSize(QSize(100, 0));
        BtnMainWgt->setMaximumSize(QSize(16777215, 40));
        BtnMainWgt->setFont(font1);
        BtnMainWgt->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    color:rgb(0,0,0);\n"
"     border-image: url(:/resource/button1.png);\n"
"} "));

        horizontalLayout->addWidget(BtnMainWgt);

        BtnQuanjing = new QPushButton(widget);
        BtnQuanjing->setObjectName("BtnQuanjing");
        BtnQuanjing->setMinimumSize(QSize(100, 0));
        BtnQuanjing->setMaximumSize(QSize(16777215, 40));
        BtnQuanjing->setFont(font1);
        BtnQuanjing->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    color:rgb(0,0,0);\n"
"     border-image: url(:/resource/button1.png);\n"
"}  "));

        horizontalLayout->addWidget(BtnQuanjing);

        BtnZhouShi = new QPushButton(widget);
        BtnZhouShi->setObjectName("BtnZhouShi");
        BtnZhouShi->setMinimumSize(QSize(100, 0));
        BtnZhouShi->setMaximumSize(QSize(16777215, 40));
        BtnZhouShi->setFont(font1);
        BtnZhouShi->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    color:rgb(0,0,0);\n"
"     border-image: url(:/resource/button1.png);\n"
"} "));

        horizontalLayout->addWidget(BtnZhouShi);

        BtnNVR = new QPushButton(widget);
        BtnNVR->setObjectName("BtnNVR");
        BtnNVR->setMinimumSize(QSize(100, 0));
        BtnNVR->setMaximumSize(QSize(16777215, 40));
        BtnNVR->setFont(font1);
        BtnNVR->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    color:rgb(0,0,0);\n"
"     border-image: url(:/resource/button1.png);\n"
"} "));

        horizontalLayout->addWidget(BtnNVR);

        BtnExit = new QPushButton(widget);
        BtnExit->setObjectName("BtnExit");
        BtnExit->setMinimumSize(QSize(100, 0));
        BtnExit->setMaximumSize(QSize(16777215, 40));
        BtnExit->setFont(font1);
        BtnExit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    color:rgb(0,0,0);\n"
"     border-image: url(:/resource/button1.png);\n"
"} "));

        horizontalLayout->addWidget(BtnExit);

        horizontalScrollBar = new QScrollBar(centralwidget);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setGeometry(QRect(0, 1145, 1600, 15));
        horizontalScrollBar->setStyleSheet(QString::fromUtf8("background-color: rgb(95, 95, 95);"));
        horizontalScrollBar->setMinimum(1);
        horizontalScrollBar->setMaximum(100);
        horizontalScrollBar->setSingleStep(5);
        horizontalScrollBar->setPageStep(25);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(BtnMainWgt, SIGNAL(clicked()), MainWindow, SLOT(OnClickedBtnMainWgt()));
        QObject::connect(BtnZhouShi, SIGNAL(clicked()), MainWindow, SLOT(OnClickedBtnZhouShi()));
        QObject::connect(BtnExit, SIGNAL(clicked()), MainWindow, SLOT(OnClickedBtnExit()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbDateTime->setText(QCoreApplication::translate("MainWindow", "2021-10-29  18:00:05", nullptr));
        btnCapture->setText(QCoreApplication::translate("MainWindow", "\346\210\252\345\233\276", nullptr));
        btnQJ1->setText(QCoreApplication::translate("MainWindow", "\345\205\250\346\231\2571", nullptr));
        btnQJ2->setText(QCoreApplication::translate("MainWindow", "\345\205\250\346\231\2572", nullptr));
        btnZoomRestore->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
        BtnHealthLed->setText(QString());
        BtnHealthState->setText(QCoreApplication::translate("MainWindow", "\345\201\245 \345\272\267 \347\212\266 \346\200\201", nullptr));
        BtnMainWgt->setText(QCoreApplication::translate("MainWindow", "\351\246\226   \351\241\265", nullptr));
        BtnQuanjing->setText(QCoreApplication::translate("MainWindow", "\345\205\250   \346\231\257", nullptr));
        BtnZhouShi->setText(QCoreApplication::translate("MainWindow", "\345\221\250    \350\247\206", nullptr));
        BtnNVR->setText(QCoreApplication::translate("MainWindow", "NVR", nullptr));
        BtnExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200    \345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
