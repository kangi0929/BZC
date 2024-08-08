#ifndef WGTZHOUSHI_H
#define WGTZHOUSHI_H

#include <QWidget>
//#include "Player.h"
#include "InfraredComport.h"
#include <QTimer>
#include "globalvar.h"
#include <QUdpSocket>

#include "cytglobaltype.h"

namespace Ui
{
class QWgtZhouShi;
}

class QWgtZhouShi : public QWidget
{
    Q_OBJECT

public:
    explicit QWgtZhouShi(QWidget *parent = nullptr);

    ~QWgtZhouShi();

private:
    void InitControl();
    void InitWgtChange();  // zhouxiao

signals:
    void signal_WgtZhouShi_operateNo(int iOperateNo, int iParam0, int iParam1, int iParam2);
    void signalLog(LogInfo lg);

protected:
    void hideEvent(QHideEvent *event);

    void showEvent(QShowEvent *event);

private slots:

    void SltOperateDelayTime();  //云台和摄像头调焦等操作，添加延时发送停止操作指令

    void on_btn_up_pressed();

    void on_btn_up_released();

    void on_btn_down_pressed();

    void on_btn_down_released();

    void on_btn_left_pressed();

    void on_btn_left_released();

    void on_btn_right_pressed();

    void on_btn_right_released();

    void on_BtnZoomAdd_pressed();

    void on_BtnZoomAdd_released();

    void on_btnZoomSub_pressed();

    void on_btnZoomSub_released();

    void on_BtnFocusAdd_pressed();

    void on_BtnFocusAdd_released();

    void on_BtnFocusSub_pressed();

    void on_BtnFocusSub_released();

    void on_radio_low_clicked();

    void on_radio_mid_clicked();

    void on_radio_high_clicked();

    void slot_BtnVideoChange_clicked(bool flag);

    void on_btnAutoLight_clicked();

    void on_btnManualLight_clicked(bool checked);

public:
    void setCameraPanSpeed(int iCameraSpeed, int iCameraPanSpeed);
    void setCameraPanAzimuthParam(int iAzimuth);
    void setCameraPanPitchParam(int iAzimuth);

private:
    // bool  m_bShow = false;

    // QPlayer* m_QZsKjgPlayer;
    // QPlayer* m_QZsHwPlayer;
    QUdpSocket *m_udp;

    int m_iInfraredFd;                      //红外接口
    QInfraredComport *m_qCameraPanComport;  //云台
    QInfraredComport *m_qCameraComport;     //摄像头
    QTimer *m_tmOperateDelayTime;

    int m_iCameraPanSpeed;
    int m_iCameraSpeed;
    int m_iCurrentCameraDevice;

private:
    Ui::QWgtZhouShi *ui;
};

#endif  // WGTZHOUSHI_H
