#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include <QTimer>
#include "WgtMain.h"
#include "WgtZhouShi.h"
#include "InfraredComport.h"
#include "JoyStickComport.h"
#include <QPainter>

#include <QUdpSocket>
#include "cytglobaltype.h"
//#include "mousemovethread.h"
#include "mousemoveoptimize.h"
#include "NVRReplayWgt.h"
#include "Logger.h"

#include "interfacechange.h"
#include "qjzoomarea.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
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
    void InitControl();

protected:
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *);

private slots:

    void OnClickedBtnExit();  //退出

    void OnClickedBtnZhouShi();  //周视

    void OnClickedBtnMainWgt();  //主页

    void SltUpdateDataTime();

    void SltOperateDelayTime();  //云台和摄像头调焦等操作，添加延时发送停止操作指令

    void SltRecvOperateNo(int iOperateNo, int iParam0, int iParam1, int iParam2);

    void slots_prase_orientation_data(const QString &id, const QJsonObject &data);

    void on_btnCapture_clicked();

    void on_BtnNVR_clicked();

    void SlotWriteLog(LogInfo logInfo);

    void on_btnQJ1_clicked(bool checked);

    void on_btnQJ2_clicked(bool checked);

    void on_BtnQuanjing_clicked();

    void sltFlagPlus();

    void on_btnRestore_clicked();
    //
    void on_horizontalScrollBar_valueChanged(int value);
    
    void on_btnZoomRestore_clicked(bool checked);

signals:
    void signalLog(LogInfo lg);

private:
    QWgtMain *m_QMainWgt;
    int m_iCurrentWindowID;
    QjZoomArea *m_qjZoom;

    QWgtZhouShi *m_QZhouShiWgt;
    NVRReplayWgt *m_qNVRReplayWgt;

    QTimer *m_tmUpdateTime;
    QTimer *m_tmOperateDelayTime;
    QTimer *m_detectFault;
    // QTimer *m_mouseLocate;
    //MouseMoveThread *m_mmth;

    int m_iCameraDeviceNo;
    int m_iCameraMainWgtDeviceAdd;          // 1:可见光 2：红外
    int m_iCameraZhouShiWgtDeviceAdd;       // 1:可见光 2：红外
    QInfraredComport *m_qCameraPanComport;  //云台
    QInfraredComport *m_qCameraComport;     //摄像头
    QJoyStickComport *m_qJoyStickComport;   //摇杆
    double horizontal;
    double vertical;

    QThread * m_thd;
    MouseMoveOptimize *m_mmOpt;

    unsigned int m_beat = 10;
    unsigned int m_flag = 10;

    //视频图像的固定长宽
    const int m_qj_width = VIDEO_WIDTH;
    const int m_qj_height = VIDEO_HEIGHT;
    //记录当前是第几个全景
    int m_qjNum = 0; //默认全景1
    QUdpSocket * m_udp;

private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
