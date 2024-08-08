/********************************************************************************
** Form generated from reading UI file 'NVRReplayWgt.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NVRREPLAYWGT_H
#define UI_NVRREPLAYWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NVRReplayWgt
{
public:
    QWidget *videoReplayWgt;
    QGroupBox *groupBox;
    QLabel *label_3;
    QDateEdit *dateEdit_video;
    QPushButton *pbVideoFind;
    QPushButton *pbVideoClear;
    QLabel *label_6;
    QComboBox *combVideoFindOption;
    QPushButton *pbFileCpy;
    QTreeWidget *treeWidgetVideo;
    QWidget *mapRelayWgt;
    QLabel *labMapDisplay;
    QGroupBox *groupBox_3;
    QListWidget *lWgtMapFile;
    QGroupBox *groupBox_4;
    QLabel *label_4;
    QDateEdit *dateEdit_map;
    QPushButton *pbMapFind;
    QPushButton *pbMapClear;
    QComboBox *combMapFindOption;
    QLabel *label_7;
    QPushButton *pbFileCpyMap;
    QPushButton *pbMagnify;
    QPushButton *pbShrink;
    QPushButton *pbRotate;
    QWidget *logWgt;
    QGroupBox *groupBox_5;
    QListWidget *lWgtLogFile;
    QGroupBox *groupBox_6;
    QLabel *label_5;
    QDateEdit *dateEdit_log;
    QPushButton *pbLogFind;
    QPushButton *pbLogClear;
    QComboBox *combLogFindOption;
    QLabel *label_8;
    QPushButton *pbFileCpyLog;
    QTableWidget *logTableWgt;
    QLabel *labVideoDisplay;
    QWidget *NVRMainwgt;
    QPushButton *pbVideoReplay;
    QPushButton *pbLog;
    QPushButton *pbMapReplay;
    QWidget *ReplayCtrlwgt;
    QPushButton *pbVideoSlowPlay;
    QPushButton *pbVideoFastPlay;
    QPushButton *pbVideoStop;
    QPushButton *pbVideoPause;
    QSlider *ReplaySlider;
    QPushButton *pbVideoPlay;
    QLabel *labReplayTime;
    QLabel *labReplayTotalTime;
    QPushButton *pbQJVideoRestore;

    void setupUi(QWidget *NVRReplayWgt)
    {
        if (NVRReplayWgt->objectName().isEmpty())
            NVRReplayWgt->setObjectName("NVRReplayWgt");
        NVRReplayWgt->resize(1600, 1160);
        NVRReplayWgt->setStyleSheet(QString::fromUtf8(""));
        videoReplayWgt = new QWidget(NVRReplayWgt);
        videoReplayWgt->setObjectName("videoReplayWgt");
        videoReplayWgt->setGeometry(QRect(1269, 100, 331, 1061));
        videoReplayWgt->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        groupBox = new QGroupBox(videoReplayWgt);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 10, 291, 131));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(44, 60, 33, 17));
        dateEdit_video = new QDateEdit(groupBox);
        dateEdit_video->setObjectName("dateEdit_video");
        dateEdit_video->setGeometry(QRect(100, 55, 151, 26));
        pbVideoFind = new QPushButton(groupBox);
        pbVideoFind->setObjectName("pbVideoFind");
        pbVideoFind->setGeometry(QRect(40, 95, 71, 25));
        pbVideoClear = new QPushButton(groupBox);
        pbVideoClear->setObjectName("pbVideoClear");
        pbVideoClear->setGeometry(QRect(120, 95, 71, 25));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(43, 26, 33, 17));
        combVideoFindOption = new QComboBox(groupBox);
        combVideoFindOption->addItem(QString());
        combVideoFindOption->addItem(QString());
        combVideoFindOption->setObjectName("combVideoFindOption");
        combVideoFindOption->setGeometry(QRect(100, 20, 151, 25));
        pbFileCpy = new QPushButton(groupBox);
        pbFileCpy->setObjectName("pbFileCpy");
        pbFileCpy->setGeometry(QRect(200, 95, 71, 25));
        treeWidgetVideo = new QTreeWidget(videoReplayWgt);
        treeWidgetVideo->setObjectName("treeWidgetVideo");
        treeWidgetVideo->setGeometry(QRect(20, 160, 291, 881));
        mapRelayWgt = new QWidget(NVRReplayWgt);
        mapRelayWgt->setObjectName("mapRelayWgt");
        mapRelayWgt->setGeometry(QRect(0, 100, 1600, 1061));
        mapRelayWgt->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        labMapDisplay = new QLabel(mapRelayWgt);
        labMapDisplay->setObjectName("labMapDisplay");
        labMapDisplay->setGeometry(QRect(20, 20, 1221, 891));
        labMapDisplay->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/bk.jpg);"));
        groupBox_3 = new QGroupBox(mapRelayWgt);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(1277, 160, 291, 791));
        lWgtMapFile = new QListWidget(groupBox_3);
        lWgtMapFile->setObjectName("lWgtMapFile");
        lWgtMapFile->setGeometry(QRect(0, 22, 291, 768));
        groupBox_4 = new QGroupBox(mapRelayWgt);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(1277, 10, 291, 131));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(34, 61, 33, 17));
        dateEdit_map = new QDateEdit(groupBox_4);
        dateEdit_map->setObjectName("dateEdit_map");
        dateEdit_map->setGeometry(QRect(90, 56, 151, 26));
        pbMapFind = new QPushButton(groupBox_4);
        pbMapFind->setObjectName("pbMapFind");
        pbMapFind->setGeometry(QRect(36, 93, 71, 25));
        pbMapClear = new QPushButton(groupBox_4);
        pbMapClear->setObjectName("pbMapClear");
        pbMapClear->setGeometry(QRect(116, 93, 71, 25));
        combMapFindOption = new QComboBox(groupBox_4);
        combMapFindOption->addItem(QString());
        combMapFindOption->addItem(QString());
        combMapFindOption->setObjectName("combMapFindOption");
        combMapFindOption->setGeometry(QRect(91, 23, 151, 25));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(34, 29, 33, 17));
        pbFileCpyMap = new QPushButton(groupBox_4);
        pbFileCpyMap->setObjectName("pbFileCpyMap");
        pbFileCpyMap->setGeometry(QRect(196, 93, 71, 25));
        pbMagnify = new QPushButton(mapRelayWgt);
        pbMagnify->setObjectName("pbMagnify");
        pbMagnify->setGeometry(QRect(592, 920, 61, 31));
        pbShrink = new QPushButton(mapRelayWgt);
        pbShrink->setObjectName("pbShrink");
        pbShrink->setGeometry(QRect(662, 920, 61, 31));
        pbRotate = new QPushButton(mapRelayWgt);
        pbRotate->setObjectName("pbRotate");
        pbRotate->setGeometry(QRect(732, 920, 61, 31));
        logWgt = new QWidget(NVRReplayWgt);
        logWgt->setObjectName("logWgt");
        logWgt->setGeometry(QRect(0, 100, 1600, 1061));
        logWgt->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        groupBox_5 = new QGroupBox(logWgt);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(1277, 160, 291, 791));
        lWgtLogFile = new QListWidget(groupBox_5);
        lWgtLogFile->setObjectName("lWgtLogFile");
        lWgtLogFile->setGeometry(QRect(0, 22, 291, 768));
        groupBox_6 = new QGroupBox(logWgt);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(1277, 10, 291, 131));
        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 62, 33, 17));
        dateEdit_log = new QDateEdit(groupBox_6);
        dateEdit_log->setObjectName("dateEdit_log");
        dateEdit_log->setGeometry(QRect(86, 57, 151, 26));
        pbLogFind = new QPushButton(groupBox_6);
        pbLogFind->setObjectName("pbLogFind");
        pbLogFind->setGeometry(QRect(39, 94, 71, 25));
        pbLogClear = new QPushButton(groupBox_6);
        pbLogClear->setObjectName("pbLogClear");
        pbLogClear->setGeometry(QRect(121, 94, 71, 25));
        combLogFindOption = new QComboBox(groupBox_6);
        combLogFindOption->addItem(QString());
        combLogFindOption->addItem(QString());
        combLogFindOption->setObjectName("combLogFindOption");
        combLogFindOption->setGeometry(QRect(86, 26, 151, 25));
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 32, 33, 17));
        pbFileCpyLog = new QPushButton(groupBox_6);
        pbFileCpyLog->setObjectName("pbFileCpyLog");
        pbFileCpyLog->setGeometry(QRect(204, 94, 71, 25));
        logTableWgt = new QTableWidget(logWgt);
        logTableWgt->setObjectName("logTableWgt");
        logTableWgt->setGeometry(QRect(20, 20, 1221, 931));
        labVideoDisplay = new QLabel(NVRReplayWgt);
        labVideoDisplay->setObjectName("labVideoDisplay");
        labVideoDisplay->setGeometry(QRect(0, 100, 1269, 981));
        labVideoDisplay->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/bk.jpg);"));
        NVRMainwgt = new QWidget(NVRReplayWgt);
        NVRMainwgt->setObjectName("NVRMainwgt");
        NVRMainwgt->setGeometry(QRect(0, 0, 1600, 100));
        NVRMainwgt->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        pbVideoReplay = new QPushButton(NVRMainwgt);
        pbVideoReplay->setObjectName("pbVideoReplay");
        pbVideoReplay->setGeometry(QRect(1326, 6, 81, 81));
        pbLog = new QPushButton(NVRMainwgt);
        pbLog->setObjectName("pbLog");
        pbLog->setGeometry(QRect(1500, 7, 81, 81));
        pbMapReplay = new QPushButton(NVRMainwgt);
        pbMapReplay->setObjectName("pbMapReplay");
        pbMapReplay->setGeometry(QRect(1413, 6, 81, 81));
        ReplayCtrlwgt = new QWidget(NVRReplayWgt);
        ReplayCtrlwgt->setObjectName("ReplayCtrlwgt");
        ReplayCtrlwgt->setGeometry(QRect(0, 1081, 1269, 80));
        ReplayCtrlwgt->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        pbVideoSlowPlay = new QPushButton(ReplayCtrlwgt);
        pbVideoSlowPlay->setObjectName("pbVideoSlowPlay");
        pbVideoSlowPlay->setGeometry(QRect(354, 13, 71, 31));
        pbVideoFastPlay = new QPushButton(ReplayCtrlwgt);
        pbVideoFastPlay->setObjectName("pbVideoFastPlay");
        pbVideoFastPlay->setGeometry(QRect(278, 14, 71, 31));
        pbVideoStop = new QPushButton(ReplayCtrlwgt);
        pbVideoStop->setObjectName("pbVideoStop");
        pbVideoStop->setGeometry(QRect(198, 14, 71, 30));
        pbVideoPause = new QPushButton(ReplayCtrlwgt);
        pbVideoPause->setObjectName("pbVideoPause");
        pbVideoPause->setGeometry(QRect(110, 14, 81, 31));
        ReplaySlider = new QSlider(ReplayCtrlwgt);
        ReplaySlider->setObjectName("ReplaySlider");
        ReplaySlider->setGeometry(QRect(23, 52, 1061, 16));
        ReplaySlider->setOrientation(Qt::Horizontal);
        pbVideoPlay = new QPushButton(ReplayCtrlwgt);
        pbVideoPlay->setObjectName("pbVideoPlay");
        pbVideoPlay->setGeometry(QRect(23, 14, 81, 31));
        labReplayTime = new QLabel(ReplayCtrlwgt);
        labReplayTime->setObjectName("labReplayTime");
        labReplayTime->setGeometry(QRect(1093, 50, 71, 17));
        labReplayTotalTime = new QLabel(ReplayCtrlwgt);
        labReplayTotalTime->setObjectName("labReplayTotalTime");
        labReplayTotalTime->setGeometry(QRect(1160, 50, 71, 17));
        pbQJVideoRestore = new QPushButton(ReplayCtrlwgt);
        pbQJVideoRestore->setObjectName("pbQJVideoRestore");
        pbQJVideoRestore->setGeometry(QRect(430, 13, 71, 31));
        NVRMainwgt->raise();
        labVideoDisplay->raise();
        ReplayCtrlwgt->raise();
        videoReplayWgt->raise();
        logWgt->raise();
        mapRelayWgt->raise();

        retranslateUi(NVRReplayWgt);

        QMetaObject::connectSlotsByName(NVRReplayWgt);
    } // setupUi

    void retranslateUi(QWidget *NVRReplayWgt)
    {
        NVRReplayWgt->setWindowTitle(QCoreApplication::translate("NVRReplayWgt", "Form", nullptr));
        groupBox->setTitle(QString());
        label_3->setText(QCoreApplication::translate("NVRReplayWgt", "\346\227\245\346\234\237", nullptr));
        pbVideoFind->setText(QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242", nullptr));
        pbVideoClear->setText(QCoreApplication::translate("NVRReplayWgt", "\346\270\205\347\251\272", nullptr));
        label_6->setText(QCoreApplication::translate("NVRReplayWgt", "\351\200\211\351\241\271", nullptr));
        combVideoFindOption->setItemText(0, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\346\211\200\346\234\211", nullptr));
        combVideoFindOption->setItemText(1, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\345\275\223\345\244\251", nullptr));

        pbFileCpy->setText(QCoreApplication::translate("NVRReplayWgt", "\346\213\267\350\264\235", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetVideo->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("NVRReplayWgt", "\350\247\206\351\242\221\351\200\211\346\213\251\345\210\227\350\241\250", nullptr));
        labMapDisplay->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("NVRReplayWgt", "\345\233\276\347\211\207\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        groupBox_4->setTitle(QString());
        label_4->setText(QCoreApplication::translate("NVRReplayWgt", "\346\227\245\346\234\237", nullptr));
        pbMapFind->setText(QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242", nullptr));
        pbMapClear->setText(QCoreApplication::translate("NVRReplayWgt", "\346\270\205\347\251\272", nullptr));
        combMapFindOption->setItemText(0, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\346\211\200\346\234\211", nullptr));
        combMapFindOption->setItemText(1, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\345\275\223\345\244\251", nullptr));

        label_7->setText(QCoreApplication::translate("NVRReplayWgt", "\351\200\211\351\241\271", nullptr));
        pbFileCpyMap->setText(QCoreApplication::translate("NVRReplayWgt", "\346\213\267\350\264\235", nullptr));
        pbMagnify->setText(QCoreApplication::translate("NVRReplayWgt", "\346\224\276\345\244\247", nullptr));
        pbShrink->setText(QCoreApplication::translate("NVRReplayWgt", "\347\274\251\345\260\217", nullptr));
        pbRotate->setText(QCoreApplication::translate("NVRReplayWgt", "\347\277\273\350\275\254", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("NVRReplayWgt", "\345\233\276\347\211\207\346\226\207\344\273\266\345\210\227\350\241\250", nullptr));
        groupBox_6->setTitle(QString());
        label_5->setText(QCoreApplication::translate("NVRReplayWgt", "\346\227\245\346\234\237", nullptr));
        pbLogFind->setText(QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242", nullptr));
        pbLogClear->setText(QCoreApplication::translate("NVRReplayWgt", "\346\270\205\347\251\272", nullptr));
        combLogFindOption->setItemText(0, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\346\211\200\346\234\211", nullptr));
        combLogFindOption->setItemText(1, QCoreApplication::translate("NVRReplayWgt", "\346\237\245\350\257\242\345\275\223\345\244\251", nullptr));

        label_8->setText(QCoreApplication::translate("NVRReplayWgt", "\351\200\211\351\241\271", nullptr));
        pbFileCpyLog->setText(QCoreApplication::translate("NVRReplayWgt", "\346\213\267\350\264\235", nullptr));
        labVideoDisplay->setText(QString());
        pbVideoReplay->setText(QCoreApplication::translate("NVRReplayWgt", "\350\247\206\351\242\221\345\233\236\346\224\276", nullptr));
        pbLog->setText(QCoreApplication::translate("NVRReplayWgt", "\346\227\245\345\277\227\346\237\245\347\234\213", nullptr));
        pbMapReplay->setText(QCoreApplication::translate("NVRReplayWgt", "\345\233\276\345\203\217\345\233\236\346\224\276", nullptr));
        pbVideoSlowPlay->setText(QCoreApplication::translate("NVRReplayWgt", "\346\205\242\346\224\276", nullptr));
        pbVideoFastPlay->setText(QCoreApplication::translate("NVRReplayWgt", "\345\277\253\346\224\276", nullptr));
        pbVideoStop->setText(QCoreApplication::translate("NVRReplayWgt", "\345\201\234\346\255\242", nullptr));
        pbVideoPause->setText(QCoreApplication::translate("NVRReplayWgt", "\346\232\202\345\201\234", nullptr));
        pbVideoPlay->setText(QCoreApplication::translate("NVRReplayWgt", "\346\222\255\346\224\276", nullptr));
        labReplayTime->setText(QCoreApplication::translate("NVRReplayWgt", "00:00:00", nullptr));
        labReplayTotalTime->setText(QCoreApplication::translate("NVRReplayWgt", "/00:00:00", nullptr));
        pbQJVideoRestore->setText(QCoreApplication::translate("NVRReplayWgt", "\350\277\230\345\216\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NVRReplayWgt: public Ui_NVRReplayWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NVRREPLAYWGT_H
