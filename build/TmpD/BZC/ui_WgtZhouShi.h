/********************************************************************************
** Form generated from reading UI file 'WgtZhouShi.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTZHOUSHI_H
#define UI_WGTZHOUSHI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWgtZhouShi
{
public:
    QWidget *ZsKjgWgt;
    QWidget *ZsHwWgt;
    QWidget *PtzWgt;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_pitch;
    QLabel *label_orientation;
    QLabel *label_speed;
    QRadioButton *radio_mid;
    QRadioButton *radio_high;
    QRadioButton *radio_low;
    QWidget *widget;
    QPushButton *btn_right;
    QPushButton *btn_down;
    QPushButton *btn_left;
    QPushButton *btn_up;
    QWidget *TitileWgt_2;
    QLabel *label_6;
    QPushButton *BtnVideoChange;
    QPushButton *BtnZoomAdd;
    QPushButton *btnZoomSub;
    QPushButton *BtnFocusAdd;
    QPushButton *BtnFocusSub;
    QWidget *widget_2;
    QPushButton *btnAutoLight;
    QPushButton *btnManualLight;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *QWgtZhouShi)
    {
        if (QWgtZhouShi->objectName().isEmpty())
            QWgtZhouShi->setObjectName("QWgtZhouShi");
        QWgtZhouShi->resize(1600, 1160);
        QWgtZhouShi->setStyleSheet(QString::fromUtf8(""));
        ZsKjgWgt = new QWidget(QWgtZhouShi);
        ZsKjgWgt->setObjectName("ZsKjgWgt");
        ZsKjgWgt->setGeometry(QRect(0, 0, 1600, 900));
        ZsHwWgt = new QWidget(QWgtZhouShi);
        ZsHwWgt->setObjectName("ZsHwWgt");
        ZsHwWgt->setGeometry(QRect(0, 902, 450, 256));
        ZsHwWgt->setAutoFillBackground(false);
        ZsHwWgt->setStyleSheet(QString::fromUtf8(""));
        PtzWgt = new QWidget(QWgtZhouShi);
        PtzWgt->setObjectName("PtzWgt");
        PtzWgt->setGeometry(QRect(1144, 900, 456, 260));
        PtzWgt->setStyleSheet(QString::fromUtf8("	background-color: rgb(152, 152, 152);"));
        label_3 = new QLabel(PtzWgt);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 48, 24));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(12);
        label_3->setFont(font);
        label_4 = new QLabel(PtzWgt);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 220, 48, 24));
        label_4->setFont(font);
        label_5 = new QLabel(PtzWgt);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 180, 48, 24));
        label_5->setFont(font);
        label_pitch = new QLabel(PtzWgt);
        label_pitch->setObjectName("label_pitch");
        label_pitch->setGeometry(QRect(80, 180, 71, 24));
        label_pitch->setFont(font);
        label_pitch->setAlignment(Qt::AlignCenter);
        label_orientation = new QLabel(PtzWgt);
        label_orientation->setObjectName("label_orientation");
        label_orientation->setGeometry(QRect(80, 140, 71, 24));
        label_orientation->setFont(font);
        label_orientation->setAlignment(Qt::AlignCenter);
        label_speed = new QLabel(PtzWgt);
        label_speed->setObjectName("label_speed");
        label_speed->setGeometry(QRect(80, 220, 71, 24));
        label_speed->setFont(font);
        label_speed->setAlignment(Qt::AlignCenter);
        radio_mid = new QRadioButton(PtzWgt);
        radio_mid->setObjectName("radio_mid");
        radio_mid->setGeometry(QRect(260, 220, 51, 26));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font1.setPointSize(10);
        radio_mid->setFont(font1);
        radio_high = new QRadioButton(PtzWgt);
        radio_high->setObjectName("radio_high");
        radio_high->setGeometry(QRect(320, 220, 51, 26));
        radio_high->setFont(font1);
        radio_low = new QRadioButton(PtzWgt);
        radio_low->setObjectName("radio_low");
        radio_low->setGeometry(QRect(190, 220, 51, 26));
        radio_low->setFont(font1);
        widget = new QWidget(PtzWgt);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(200, 50, 150, 150));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/round.png);"));
        btn_right = new QPushButton(widget);
        btn_right->setObjectName("btn_right");
        btn_right->setGeometry(QRect(110, 50, 28, 55));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_right->sizePolicy().hasHeightForWidth());
        btn_right->setSizePolicy(sizePolicy);
        btn_right->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/btn_right_hover.png);\n"
"background:transparent;\n"
"}\n"
"QPushButton:pressed\n"
"{	\n"
"	border-image: url(:/resource/btn_right_press.png);\n"
"}\n"
""));
        btn_down = new QPushButton(widget);
        btn_down->setObjectName("btn_down");
        btn_down->setGeometry(QRect(50, 110, 55, 28));
        sizePolicy.setHeightForWidth(btn_down->sizePolicy().hasHeightForWidth());
        btn_down->setSizePolicy(sizePolicy);
        btn_down->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/btn_down_hover.png);\n"
"background:transparent;\n"
"}\n"
"QPushButton:pressed\n"
"{	\n"
"	border-image: url(:/resource/btn_down_press.png);\n"
"}\n"
""));
        btn_left = new QPushButton(widget);
        btn_left->setObjectName("btn_left");
        btn_left->setGeometry(QRect(15, 50, 28, 55));
        sizePolicy.setHeightForWidth(btn_left->sizePolicy().hasHeightForWidth());
        btn_left->setSizePolicy(sizePolicy);
        btn_left->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/btn_left_hover.png);\n"
"background:transparent;\n"
"}\n"
"QPushButton:pressed\n"
"{	\n"
"	border-image: url(:/resource/btn_left_press.png);\n"
"}\n"
""));
        btn_up = new QPushButton(widget);
        btn_up->setObjectName("btn_up");
        btn_up->setGeometry(QRect(50, 20, 55, 28));
        sizePolicy.setHeightForWidth(btn_up->sizePolicy().hasHeightForWidth());
        btn_up->setSizePolicy(sizePolicy);
        btn_up->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border-image: url(:/resource/btn_up_hover.png);\n"
"background:transparent;\n"
"}\n"
"QPushButton:pressed\n"
"{	\n"
"	border-image: url(:/resource/btn_up_press.png);\n"
"}\n"
""));
        TitileWgt_2 = new QWidget(PtzWgt);
        TitileWgt_2->setObjectName("TitileWgt_2");
        TitileWgt_2->setGeometry(QRect(0, 0, 456, 31));
        TitileWgt_2->setStyleSheet(QString::fromUtf8("background-color:rgb(76,76,76);"));
        label_6 = new QLabel(TitileWgt_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 91, 30));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(225, 225, 225);"));
        label_6->setAlignment(Qt::AlignCenter);
        BtnVideoChange = new QPushButton(PtzWgt);
        BtnVideoChange->setObjectName("BtnVideoChange");
        BtnVideoChange->setGeometry(QRect(0, 40, 82, 30));
        sizePolicy.setHeightForWidth(BtnVideoChange->sizePolicy().hasHeightForWidth());
        BtnVideoChange->setSizePolicy(sizePolicy);
        BtnVideoChange->setFont(font);
        BtnVideoChange->setStyleSheet(QString::fromUtf8("QPushButton#BtnVideoChange\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        widget->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_pitch->raise();
        label_orientation->raise();
        label_speed->raise();
        radio_mid->raise();
        radio_high->raise();
        radio_low->raise();
        TitileWgt_2->raise();
        BtnVideoChange->raise();
        BtnZoomAdd = new QPushButton(QWgtZhouShi);
        BtnZoomAdd->setObjectName("BtnZoomAdd");
        BtnZoomAdd->setGeometry(QRect(1060, 910, 82, 30));
        sizePolicy.setHeightForWidth(BtnZoomAdd->sizePolicy().hasHeightForWidth());
        BtnZoomAdd->setSizePolicy(sizePolicy);
        BtnZoomAdd->setFont(font);
        BtnZoomAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnZoomAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btnZoomSub = new QPushButton(QWgtZhouShi);
        btnZoomSub->setObjectName("btnZoomSub");
        btnZoomSub->setGeometry(QRect(1060, 950, 82, 30));
        sizePolicy.setHeightForWidth(btnZoomSub->sizePolicy().hasHeightForWidth());
        btnZoomSub->setSizePolicy(sizePolicy);
        btnZoomSub->setFont(font);
        btnZoomSub->setStyleSheet(QString::fromUtf8("QPushButton#btnZoomSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnFocusAdd = new QPushButton(QWgtZhouShi);
        BtnFocusAdd->setObjectName("BtnFocusAdd");
        BtnFocusAdd->setGeometry(QRect(1060, 990, 82, 30));
        sizePolicy.setHeightForWidth(BtnFocusAdd->sizePolicy().hasHeightForWidth());
        BtnFocusAdd->setSizePolicy(sizePolicy);
        BtnFocusAdd->setFont(font);
        BtnFocusAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnFocusAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnFocusSub = new QPushButton(QWgtZhouShi);
        BtnFocusSub->setObjectName("BtnFocusSub");
        BtnFocusSub->setGeometry(QRect(1060, 1030, 82, 30));
        sizePolicy.setHeightForWidth(BtnFocusSub->sizePolicy().hasHeightForWidth());
        BtnFocusSub->setSizePolicy(sizePolicy);
        BtnFocusSub->setFont(font);
        BtnFocusSub->setStyleSheet(QString::fromUtf8("QPushButton#BtnFocusSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        widget_2 = new QWidget(QWgtZhouShi);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(450, 900, 701, 261));
        widget_2->setStyleSheet(QString::fromUtf8("	background-color: rgb(152, 152, 152);"));
        btnAutoLight = new QPushButton(widget_2);
        btnAutoLight->setObjectName("btnAutoLight");
        btnAutoLight->setGeometry(QRect(610, 170, 82, 30));
        sizePolicy.setHeightForWidth(btnAutoLight->sizePolicy().hasHeightForWidth());
        btnAutoLight->setSizePolicy(sizePolicy);
        btnAutoLight->setFont(font);
        btnAutoLight->setStyleSheet(QString::fromUtf8("QPushButton#btnAutoLight\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}\n"
""));
        btnManualLight = new QPushButton(widget_2);
        btnManualLight->setObjectName("btnManualLight");
        btnManualLight->setGeometry(QRect(610, 210, 82, 30));
        sizePolicy.setHeightForWidth(btnManualLight->sizePolicy().hasHeightForWidth());
        btnManualLight->setSizePolicy(sizePolicy);
        btnManualLight->setFont(font);
        btnManualLight->setStyleSheet(QString::fromUtf8("QPushButton#btnManualLight\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btnManualLight->setCheckable(true);
        line = new QFrame(QWgtZhouShi);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 900, 1600, 2));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(QWgtZhouShi);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 1158, 1600, 2));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        widget_2->raise();
        ZsKjgWgt->raise();
        ZsHwWgt->raise();
        PtzWgt->raise();
        BtnZoomAdd->raise();
        btnZoomSub->raise();
        BtnFocusAdd->raise();
        BtnFocusSub->raise();
        line->raise();
        line_2->raise();

        retranslateUi(QWgtZhouShi);

        QMetaObject::connectSlotsByName(QWgtZhouShi);
    } // setupUi

    void retranslateUi(QWidget *QWgtZhouShi)
    {
        QWgtZhouShi->setWindowTitle(QCoreApplication::translate("QWgtZhouShi", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("QWgtZhouShi", "\346\226\271\344\275\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("QWgtZhouShi", "\350\275\254\351\200\237\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("QWgtZhouShi", "\344\277\257\344\273\260\357\274\232", nullptr));
        label_pitch->setText(QString());
        label_orientation->setText(QString());
        label_speed->setText(QString());
        radio_mid->setText(QCoreApplication::translate("QWgtZhouShi", "\344\270\255\351\200\237", nullptr));
        radio_high->setText(QCoreApplication::translate("QWgtZhouShi", "\351\253\230\351\200\237", nullptr));
        radio_low->setText(QCoreApplication::translate("QWgtZhouShi", "\344\275\216\351\200\237", nullptr));
        btn_right->setText(QString());
        btn_down->setText(QString());
        btn_left->setText(QString());
        btn_up->setText(QString());
        label_6->setText(QCoreApplication::translate("QWgtZhouShi", "\344\272\221\345\217\260\346\216\247\345\210\266", nullptr));
        BtnVideoChange->setText(QCoreApplication::translate("QWgtZhouShi", "\345\210\207\346\215\242", nullptr));
        BtnZoomAdd->setText(QCoreApplication::translate("QWgtZhouShi", "\345\217\230\345\200\215 +", nullptr));
        btnZoomSub->setText(QCoreApplication::translate("QWgtZhouShi", "\345\217\230\345\200\215 -", nullptr));
        BtnFocusAdd->setText(QCoreApplication::translate("QWgtZhouShi", "\347\204\246\350\267\235 +", nullptr));
        BtnFocusSub->setText(QCoreApplication::translate("QWgtZhouShi", "\347\204\246\350\267\235 -", nullptr));
        btnAutoLight->setText(QCoreApplication::translate("QWgtZhouShi", "\350\207\252\345\212\250\350\241\245\345\205\211", nullptr));
        btnManualLight->setText(QCoreApplication::translate("QWgtZhouShi", "\346\211\213\345\212\250\350\241\245\345\205\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWgtZhouShi: public Ui_QWgtZhouShi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTZHOUSHI_H
