/********************************************************************************
** Form generated from reading UI file 'WgtMain.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WGTMAIN_H
#define UI_WGTMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWgtMain
{
public:
    QWidget *QuanJing1Wgt;
    QWidget *QuanJing2Wgt;
    QWidget *ZsKjgWgt;
    QWidget *ZsHwWgt;
    QWidget *SetWgt;
    QWidget *TitileWgt;
    QLabel *label_2;
    QToolBox *toolBox;
    QWidget *page_3;
    QPushButton *BtnInfraredFocusAdd;
    QPushButton *BtnInfraredFocusSub;
    QPushButton *BtnInfraredZoomAdd;
    QPushButton *BtnInfraredZoomSub;
    QWidget *page_4;
    QPushButton *BtnZoomSub;
    QPushButton *BtnZoomAdd;
    QPushButton *BtnFocusSub;
    QPushButton *BtnFocusAdd;
    QFrame *frame;
    QPushButton *btn_add_1;
    QPushButton *btn_add_2;
    QTableView *tableView;
    QWidget *PtzWgt;
    QLabel *label_3;
    QPushButton *btn_Trace;
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
    QPushButton *btn_Change;
    QPushButton *btn_debug;
    QPushButton *btn_record;
    QPushButton *btn_Zero;
    QPushButton *btn_SetZero;
    QPushButton *btn_JoyStick_update;
    QPushButton *btn_JoyStick_reset;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;

    void setupUi(QWidget *QWgtMain)
    {
        if (QWgtMain->objectName().isEmpty())
            QWgtMain->setObjectName("QWgtMain");
        QWgtMain->resize(1600, 1160);
        QuanJing1Wgt = new QWidget(QWgtMain);
        QuanJing1Wgt->setObjectName("QuanJing1Wgt");
        QuanJing1Wgt->setGeometry(QRect(0, 0, 1600, 310));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(QuanJing1Wgt->sizePolicy().hasHeightForWidth());
        QuanJing1Wgt->setSizePolicy(sizePolicy);
        QuanJing1Wgt->setMaximumSize(QSize(16777215, 400));
        QuanJing1Wgt->setStyleSheet(QString::fromUtf8(""));
        QuanJing2Wgt = new QWidget(QWgtMain);
        QuanJing2Wgt->setObjectName("QuanJing2Wgt");
        QuanJing2Wgt->setGeometry(QRect(-10, 310, 1600, 310));
        sizePolicy.setHeightForWidth(QuanJing2Wgt->sizePolicy().hasHeightForWidth());
        QuanJing2Wgt->setSizePolicy(sizePolicy);
        QuanJing2Wgt->setMaximumSize(QSize(16777215, 500));
        ZsKjgWgt = new QWidget(QWgtMain);
        ZsKjgWgt->setObjectName("ZsKjgWgt");
        ZsKjgWgt->setGeometry(QRect(0, 624, 782, 534));
        ZsKjgWgt->setMinimumSize(QSize(0, 0));
        ZsKjgWgt->setMaximumSize(QSize(1000, 1000));
        ZsKjgWgt->setStyleSheet(QString::fromUtf8(""));
        ZsHwWgt = new QWidget(QWgtMain);
        ZsHwWgt->setObjectName("ZsHwWgt");
        ZsHwWgt->setGeometry(QRect(784, 894, 422, 264));
        ZsHwWgt->setStyleSheet(QString::fromUtf8(""));
        SetWgt = new QWidget(QWgtMain);
        SetWgt->setObjectName("SetWgt");
        SetWgt->setGeometry(QRect(1208, 624, 392, 269));
        SetWgt->setStyleSheet(QString::fromUtf8("background-color:rgb(76,76,76);"));
        TitileWgt = new QWidget(SetWgt);
        TitileWgt->setObjectName("TitileWgt");
        TitileWgt->setGeometry(QRect(0, 0, 381, 31));
        label_2 = new QLabel(TitileWgt);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 50, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(225, 225, 225);"));
        label_2->setAlignment(Qt::AlignCenter);
        toolBox = new QToolBox(SetWgt);
        toolBox->setObjectName("toolBox");
        toolBox->setGeometry(QRect(0, 30, 391, 205));
        toolBox->setStyleSheet(QString::fromUtf8("QToolBoxButton\n"
"{\n"
"	min-height:20px;\n"
"}\n"
"QToolBox#toolBox::tab\n"
"{		\n"
"	color:rgb(255,255,255);\n"
"}\n"
"QToolBox#toolBox::tab:selected\n"
"{\n"
"	color:rgb(63,63,63);\n"
"	background-color:rgb(200,200,200);\n"
"}"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        page_3->setGeometry(QRect(0, 0, 391, 141));
        BtnInfraredFocusAdd = new QPushButton(page_3);
        BtnInfraredFocusAdd->setObjectName("BtnInfraredFocusAdd");
        BtnInfraredFocusAdd->setGeometry(QRect(7, 5, 89, 26));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(BtnInfraredFocusAdd->sizePolicy().hasHeightForWidth());
        BtnInfraredFocusAdd->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Ubuntu")});
        font1.setPointSize(11);
        BtnInfraredFocusAdd->setFont(font1);
        BtnInfraredFocusAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnInfraredFocusAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnInfraredFocusSub = new QPushButton(page_3);
        BtnInfraredFocusSub->setObjectName("BtnInfraredFocusSub");
        BtnInfraredFocusSub->setGeometry(QRect(101, 5, 90, 26));
        sizePolicy1.setHeightForWidth(BtnInfraredFocusSub->sizePolicy().hasHeightForWidth());
        BtnInfraredFocusSub->setSizePolicy(sizePolicy1);
        BtnInfraredFocusSub->setFont(font1);
        BtnInfraredFocusSub->setStyleSheet(QString::fromUtf8("QPushButton#BtnInfraredFocusSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnInfraredZoomAdd = new QPushButton(page_3);
        BtnInfraredZoomAdd->setObjectName("BtnInfraredZoomAdd");
        BtnInfraredZoomAdd->setGeometry(QRect(196, 5, 89, 26));
        sizePolicy1.setHeightForWidth(BtnInfraredZoomAdd->sizePolicy().hasHeightForWidth());
        BtnInfraredZoomAdd->setSizePolicy(sizePolicy1);
        BtnInfraredZoomAdd->setFont(font1);
        BtnInfraredZoomAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnInfraredZoomAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnInfraredZoomSub = new QPushButton(page_3);
        BtnInfraredZoomSub->setObjectName("BtnInfraredZoomSub");
        BtnInfraredZoomSub->setGeometry(QRect(290, 5, 89, 26));
        sizePolicy1.setHeightForWidth(BtnInfraredZoomSub->sizePolicy().hasHeightForWidth());
        BtnInfraredZoomSub->setSizePolicy(sizePolicy1);
        BtnInfraredZoomSub->setFont(font1);
        BtnInfraredZoomSub->setStyleSheet(QString::fromUtf8("QPushButton#BtnInfraredZoomSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resource/green.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(page_3, icon, QString::fromUtf8("\347\272\242\345\244\226"));
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        page_4->setGeometry(QRect(0, 0, 391, 141));
        BtnZoomSub = new QPushButton(page_4);
        BtnZoomSub->setObjectName("BtnZoomSub");
        BtnZoomSub->setGeometry(QRect(300, 0, 90, 26));
        sizePolicy1.setHeightForWidth(BtnZoomSub->sizePolicy().hasHeightForWidth());
        BtnZoomSub->setSizePolicy(sizePolicy1);
        BtnZoomSub->setFont(font1);
        BtnZoomSub->setStyleSheet(QString::fromUtf8("QPushButton#BtnZoomSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnZoomAdd = new QPushButton(page_4);
        BtnZoomAdd->setObjectName("BtnZoomAdd");
        BtnZoomAdd->setGeometry(QRect(200, 0, 90, 26));
        sizePolicy1.setHeightForWidth(BtnZoomAdd->sizePolicy().hasHeightForWidth());
        BtnZoomAdd->setSizePolicy(sizePolicy1);
        BtnZoomAdd->setFont(font1);
        BtnZoomAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnZoomAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnFocusSub = new QPushButton(page_4);
        BtnFocusSub->setObjectName("BtnFocusSub");
        BtnFocusSub->setGeometry(QRect(100, 0, 90, 26));
        sizePolicy1.setHeightForWidth(BtnFocusSub->sizePolicy().hasHeightForWidth());
        BtnFocusSub->setSizePolicy(sizePolicy1);
        BtnFocusSub->setFont(font1);
        BtnFocusSub->setStyleSheet(QString::fromUtf8("QPushButton#BtnFocusSub\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        BtnFocusAdd = new QPushButton(page_4);
        BtnFocusAdd->setObjectName("BtnFocusAdd");
        BtnFocusAdd->setGeometry(QRect(0, 0, 90, 26));
        sizePolicy1.setHeightForWidth(BtnFocusAdd->sizePolicy().hasHeightForWidth());
        BtnFocusAdd->setSizePolicy(sizePolicy1);
        BtnFocusAdd->setFont(font1);
        BtnFocusAdd->setStyleSheet(QString::fromUtf8("QPushButton#BtnFocusAdd\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}\n"
""));
        toolBox->addItem(page_4, icon, QString::fromUtf8("\345\217\257\350\247\201\345\205\211"));
        frame = new QFrame(SetWgt);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 240, 391, 31));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(152, 152, 152);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btn_add_1 = new QPushButton(frame);
        btn_add_1->setObjectName("btn_add_1");
        btn_add_1->setGeometry(QRect(0, 0, 90, 26));
        btn_add_1->setStyleSheet(QString::fromUtf8("QPushButton#btn_add_1\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btn_add_1->setCheckable(true);
        btn_add_1->setChecked(false);
        btn_add_2 = new QPushButton(frame);
        btn_add_2->setObjectName("btn_add_2");
        btn_add_2->setGeometry(QRect(90, 0, 90, 26));
        btn_add_2->setStyleSheet(QString::fromUtf8("QPushButton#btn_add_2\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btn_add_2->setCheckable(true);
        tableView = new QTableView(QWgtMain);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(782, 655, 426, 239));
        tableView->setMaximumSize(QSize(500, 300));
        tableView->setStyleSheet(QString::fromUtf8("background-color: rgb(152, 152, 152);"));
        PtzWgt = new QWidget(QWgtMain);
        PtzWgt->setObjectName("PtzWgt");
        PtzWgt->setGeometry(QRect(1208, 893, 453, 293));
        PtzWgt->setStyleSheet(QString::fromUtf8("	background-color: rgb(152, 152, 152);"));
        label_3 = new QLabel(PtzWgt);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 140, 48, 24));
        label_3->setFont(font);
        btn_Trace = new QPushButton(PtzWgt);
        btn_Trace->setObjectName("btn_Trace");
        btn_Trace->setGeometry(QRect(0, 30, 91, 30));
        sizePolicy1.setHeightForWidth(btn_Trace->sizePolicy().hasHeightForWidth());
        btn_Trace->setSizePolicy(sizePolicy1);
        btn_Trace->setFont(font);
        btn_Trace->setStyleSheet(QString::fromUtf8("QPushButton#btn_Trace\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btn_Trace->setCheckable(true);
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
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font2.setPointSize(10);
        radio_mid->setFont(font2);
        radio_high = new QRadioButton(PtzWgt);
        radio_high->setObjectName("radio_high");
        radio_high->setGeometry(QRect(320, 220, 51, 26));
        radio_high->setFont(font2);
        radio_low = new QRadioButton(PtzWgt);
        radio_low->setObjectName("radio_low");
        radio_low->setGeometry(QRect(190, 220, 51, 26));
        radio_low->setFont(font2);
        widget = new QWidget(PtzWgt);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(200, 50, 150, 150));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/round.png);"));
        btn_right = new QPushButton(widget);
        btn_right->setObjectName("btn_right");
        btn_right->setGeometry(QRect(110, 50, 28, 55));
        sizePolicy1.setHeightForWidth(btn_right->sizePolicy().hasHeightForWidth());
        btn_right->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(btn_down->sizePolicy().hasHeightForWidth());
        btn_down->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(btn_left->sizePolicy().hasHeightForWidth());
        btn_left->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(btn_up->sizePolicy().hasHeightForWidth());
        btn_up->setSizePolicy(sizePolicy1);
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
        TitileWgt_2->setGeometry(QRect(0, 0, 391, 31));
        TitileWgt_2->setStyleSheet(QString::fromUtf8("background-color:rgb(76,76,76);"));
        label_6 = new QLabel(TitileWgt_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 91, 30));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(225, 225, 225);"));
        label_6->setAlignment(Qt::AlignCenter);
        btn_Change = new QPushButton(PtzWgt);
        btn_Change->setObjectName("btn_Change");
        btn_Change->setGeometry(QRect(0, 70, 91, 30));
        sizePolicy1.setHeightForWidth(btn_Change->sizePolicy().hasHeightForWidth());
        btn_Change->setSizePolicy(sizePolicy1);
        btn_Change->setFont(font);
        btn_Change->setStyleSheet(QString::fromUtf8("QPushButton#btn_Change\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}\n"
""));
        btn_Change->setCheckable(false);
        btn_debug = new QPushButton(PtzWgt);
        btn_debug->setObjectName("btn_debug");
        btn_debug->setGeometry(QRect(110, 30, 89, 25));
        btn_debug->setCheckable(true);
        btn_record = new QPushButton(PtzWgt);
        btn_record->setObjectName("btn_record");
        btn_record->setEnabled(false);
        btn_record->setGeometry(QRect(110, 60, 89, 25));
        btn_Zero = new QPushButton(PtzWgt);
        btn_Zero->setObjectName("btn_Zero");
        btn_Zero->setGeometry(QRect(0, 110, 91, 30));
        sizePolicy1.setHeightForWidth(btn_Zero->sizePolicy().hasHeightForWidth());
        btn_Zero->setSizePolicy(sizePolicy1);
        btn_Zero->setFont(font);
        btn_Zero->setStyleSheet(QString::fromUtf8("QPushButton#btn_Zero\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	border-image: url(:/resource/button1.png);\n"
"}"));
        btn_Zero->setCheckable(false);
        btn_SetZero = new QPushButton(PtzWgt);
        btn_SetZero->setObjectName("btn_SetZero");
        btn_SetZero->setGeometry(QRect(110, 90, 89, 25));
        btn_SetZero->setCheckable(true);
        btn_JoyStick_update = new QPushButton(PtzWgt);
        btn_JoyStick_update->setObjectName("btn_JoyStick_update");
        btn_JoyStick_update->setGeometry(QRect(100, 150, 101, 25));
        btn_JoyStick_update->setCheckable(true);
        btn_JoyStick_reset = new QPushButton(PtzWgt);
        btn_JoyStick_reset->setObjectName("btn_JoyStick_reset");
        btn_JoyStick_reset->setGeometry(QRect(110, 120, 89, 25));
        btn_JoyStick_reset->setCheckable(true);
        widget->raise();
        label_3->raise();
        btn_Trace->raise();
        label_4->raise();
        label_5->raise();
        label_pitch->raise();
        label_orientation->raise();
        label_speed->raise();
        radio_mid->raise();
        radio_high->raise();
        radio_low->raise();
        TitileWgt_2->raise();
        btn_Change->raise();
        btn_debug->raise();
        btn_record->raise();
        btn_Zero->raise();
        btn_SetZero->raise();
        btn_JoyStick_update->raise();
        btn_JoyStick_reset->raise();
        label = new QLabel(QWgtMain);
        label->setObjectName("label");
        label->setGeometry(QRect(782, 624, 426, 31));
        QFont font3;
        font3.setPointSize(12);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("background-color:rgb(76,76,76);\n"
"color: rgb(225, 225, 225);"));
        line = new QFrame(QWgtMain);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 311, 1600, 2));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(QWgtMain);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 623, 1600, 2));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_3 = new QFrame(QWgtMain);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(782, 624, 2, 535));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        line_4 = new QFrame(QWgtMain);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(0, 1158, 1600, 2));
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_5 = new QFrame(QWgtMain);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(1206, 624, 2, 535));
        line_5->setLineWidth(1);
        line_5->setMidLineWidth(1);
        line_5->setFrameShape(QFrame::Shape::VLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(QWgtMain);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QWgtMain);
    } // setupUi

    void retranslateUi(QWidget *QWgtMain)
    {
        QWgtMain->setWindowTitle(QCoreApplication::translate("QWgtMain", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("QWgtMain", "\350\256\276\347\275\256", nullptr));
        BtnInfraredFocusAdd->setText(QCoreApplication::translate("QWgtMain", "\347\204\246\350\267\235+", nullptr));
        BtnInfraredFocusSub->setText(QCoreApplication::translate("QWgtMain", "\347\204\246\350\267\235-", nullptr));
        BtnInfraredZoomAdd->setText(QCoreApplication::translate("QWgtMain", "\345\217\230\345\200\215+", nullptr));
        BtnInfraredZoomSub->setText(QCoreApplication::translate("QWgtMain", "\345\217\230\345\200\215-", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_3), QCoreApplication::translate("QWgtMain", "\347\272\242\345\244\226", nullptr));
        BtnZoomSub->setText(QCoreApplication::translate("QWgtMain", "\345\217\230\345\200\215-", nullptr));
        BtnZoomAdd->setText(QCoreApplication::translate("QWgtMain", "\345\217\230\345\200\215+", nullptr));
        BtnFocusSub->setText(QCoreApplication::translate("QWgtMain", "\347\204\246\350\267\235-", nullptr));
        BtnFocusAdd->setText(QCoreApplication::translate("QWgtMain", "\347\204\246\350\267\235+", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QCoreApplication::translate("QWgtMain", "\345\217\257\350\247\201\345\205\211", nullptr));
        btn_add_1->setText(QCoreApplication::translate("QWgtMain", "\350\255\246\346\210\222\345\214\2721", nullptr));
        btn_add_2->setText(QCoreApplication::translate("QWgtMain", "\350\255\246\346\210\222\345\214\2722", nullptr));
        label_3->setText(QCoreApplication::translate("QWgtMain", "\346\226\271\344\275\215\357\274\232", nullptr));
        btn_Trace->setText(QCoreApplication::translate("QWgtMain", "\350\260\203\350\275\254\350\267\237\350\270\252", nullptr));
        label_4->setText(QCoreApplication::translate("QWgtMain", "\350\275\254\351\200\237\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("QWgtMain", "\344\277\257\344\273\260\357\274\232", nullptr));
        label_pitch->setText(QString());
        label_orientation->setText(QString());
        label_speed->setText(QString());
        radio_mid->setText(QCoreApplication::translate("QWgtMain", "\344\270\255\351\200\237", nullptr));
        radio_high->setText(QCoreApplication::translate("QWgtMain", "\351\253\230\351\200\237", nullptr));
        radio_low->setText(QCoreApplication::translate("QWgtMain", "\344\275\216\351\200\237", nullptr));
        btn_right->setText(QString());
        btn_down->setText(QString());
        btn_left->setText(QString());
        btn_up->setText(QString());
        label_6->setText(QCoreApplication::translate("QWgtMain", "\344\272\221\345\217\260\346\216\247\345\210\266", nullptr));
        btn_Change->setText(QCoreApplication::translate("QWgtMain", "\345\210\207\346\215\242", nullptr));
        btn_debug->setText(QCoreApplication::translate("QWgtMain", "\345\274\200\345\247\213\350\260\203\350\257\225", nullptr));
        btn_record->setText(QCoreApplication::translate("QWgtMain", "\350\256\260\345\275\225", nullptr));
        btn_Zero->setText(QCoreApplication::translate("QWgtMain", "\344\272\221\345\217\260\345\275\222\351\233\266", nullptr));
        btn_SetZero->setText(QCoreApplication::translate("QWgtMain", "\345\210\235\345\247\213\345\214\226\345\275\222\351\233\266", nullptr));
        btn_JoyStick_update->setText(QCoreApplication::translate("QWgtMain", "\346\221\207\346\235\206\346\233\264\346\226\260\350\256\276\347\275\256", nullptr));
        btn_JoyStick_reset->setText(QCoreApplication::translate("QWgtMain", "\346\221\207\346\235\206\345\244\215\344\275\215", nullptr));
        label->setText(QCoreApplication::translate("QWgtMain", "   \345\276\256 \350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWgtMain: public Ui_QWgtMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WGTMAIN_H
