#ifndef NVRREPLAYWGT_H
#define NVRREPLAYWGT_H

#include <QWidget>
#include <QListWidgetItem>
#include <QUdpSocket>
#include <QDir>
#include <QTableView>
#include <QStandardItemModel>
#include <QTreeWidget>
#include "cytglobaltype.h"

#define VIDEO_CHANNEL_NUMBER 4

using namespace  std;

namespace Ui {
class NVRReplayWgt;
}

//typedef struct hisiRECT_S {
//    int s32X;
//    int s32Y;
//    int u32Width;
//    int u32Height;
//} hisiRECT;


//typedef struct _HisiInterCommunication
//{
//    int iInfoId;
//    int s32VideoNum;
//    int s32VideoChnIndex[IPC_VIDEO_NUM];
//    hisiRECT stVideoParam[IPC_VIDEO_NUM];
//    int iCurrentReplayPos;
//    int iReplayState;//1:开始播放 2:暂停 3:继续播放 4：快放 5：慢放
//}HisiInterCommunication;


class NVRReplayWgt : public QWidget
{
    Q_OBJECT

public:
    explicit NVRReplayWgt(QWidget *parent = nullptr);
    ~NVRReplayWgt();

public:
    void Init();
    void SetReplaySliderCurrentValue(int iValue);
    void ChangeReplayPushButtonState(int iPbIndex);
    bool DeleteDir(const QString &dirName);
    void StopReplay();
    void GetDiskSpace(char *szPath, uint32_t &u32TotalSize, uint32_t &u32AvailableSize);
    int DeleteOldestFiles(char *FilePath,int iFilterFlag = 0);
    void GetAllFiles(string path, std::list<string>& files);
    void ManageDiskSpace();
private:
//    QUdpSocket *m_pUdpSocketNVR;
    QHostAddress     m_dstRadarCtrlAddr;
    quint16 m_detPort;
    HIMSG_PARAM_S m_stInterCommunication;
    long m_lCurrentReplayTotalFrame;
    int m_iCurrentSliderValue;
    QTreeWidgetItem *m_rootTreeWidgetItem[VIDEO_CHANNEL_NUMBER];
    int m_iChannelID;

private slots:
    void on_pbVideoReplay_clicked();

    void on_pbMapReplay_clicked();

    void on_pbLog_clicked();

//    void on_pbExit_clicked();

    void on_pbVideoPlay_clicked();

    void on_pbVideoPause_clicked();

    void on_pbVideoStop_clicked();

    void on_pbVideoSlowPlay_clicked();

    void on_pbVideoPause_clicked(bool checked);

    void on_ReplaySlider_valueChanged(int value);

    void on_ReplaySlider_sliderReleased();
    
    void on_pbVideoFind_clicked();

    void on_pbVideoClear_clicked();

    void on_lWgtMapFile_currentTextChanged(const QString &currentText);

    void on_pbMagnify_clicked();

    void on_pbShrink_clicked();

    void on_pbRotate_clicked();
    void on_pbTurnLeft_clicked();

    void on_pbTurnRight_clicked();

    void on_pbTurnUp_clicked();

    void on_pbTurnDown_clicked();

    void on_pbMapFind_clicked();

    void on_pbMapClear_clicked();

    void on_lWgtLogFile_itemDoubleClicked(QListWidgetItem *item);

    void on_lWgtMapFile_itemDoubleClicked(QListWidgetItem *item);

    void on_pbLogFind_clicked();

    void on_pbLogClear_clicked();

    void slotReadUdpData();
    void on_pbVideoFastPlay_clicked(bool checked);

    void on_pbVideoSlowPlay_clicked(bool checked);

    void slotItemClicked(QTreeWidgetItem *item,int index);
    void on_pbQJVideoRestore_clicked(bool checked);

    void on_ReplaySlider_sliderPressed();

    void on_ReplaySlider_actionTriggered(int action);

    void on_pbFileCpy_clicked();

    void on_pbFileCpyMap_clicked();

    void on_pbFileCpyLog_clicked();

    void on_lWgtLogFile_itemClicked(QListWidgetItem *item);

    void on_lWgtMapFile_itemClicked(QListWidgetItem *item);

private:
    QImage *m_loadImage;
    QImage m_processedImage;//处理后的图片

//    QStandardItemModel *m_stdItemModel;
    QStringList m_strListLabels;

    QUdpSocket *m_pUdpSocketNVR;
    bool m_bPaulseReplayFlag;
    int m_iProcessWidth,m_iProcessHeight;

    QString m_strCurrentSelVideoFile;
    QString m_strSelCurrentFile;
    bool m_bCurrentReplyState;
    long m_lCurrentReplayTime;
    QTreeWidgetItem *LastSelectitem;
    QString m_strSelMapFileName;
    QString m_strSelLogFileName;
    int LastSelectIndex;
private:
    Ui::NVRReplayWgt *ui;
};

#endif // NVRREPLAYWGT_H
