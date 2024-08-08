#include "WgtZhouShi.h"
#include "ui_WgtZhouShi.h"

#include "CfgFile.h"

QWgtZhouShi::QWgtZhouShi(QWidget *parent) : QWidget(parent), ui(new Ui::QWgtZhouShi)
{
    ui->setupUi(this);

    InitControl();

    InitWgtChange();
    m_udp = new QUdpSocket(this);
}

QWgtZhouShi::~QWgtZhouShi()
{
    delete ui;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtZhouShi::InitControl()
{
    //    m_QZsKjgPlayer = QPlayer::CreateLibrary(ui->ZsKjgWgt);
    //    m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());
    //    //m_QZsKjgPlayer->PlayStart("/opt/Taylor.mp4");

    //    m_QZsHwPlayer = QPlayer::CreateLibrary(ui->ZsHwWgt);
    //    m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());

    //    m_QZsKjgPlayer = new QPlayer(ui->ZsKjgWgt);
    //    m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());
    //    //m_QZsKjgPlayer->PlayStart("/opt/Taylor.mp4");

    //    m_QZsHwPlayer = new QPlayer(ui->ZsHwWgt);
    //    m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());
    // m_QZsHwPlayer->PlayStart("/opt/Taylor.mp4");

    m_tmOperateDelayTime = new QTimer(this);
    connect(m_tmOperateDelayTime, SIGNAL(timeout()), this, SLOT(SltOperateDelayTime()));
    //    m_tmOperateDelayTime->start(1000);
    //    m_qCameraPanComport = new QInfraredComport(this);
    //    m_qCameraPanComport->InitParameter("/dev/ttyUSB0",9600);
    //    m_qCameraPanComport->start();

    //    m_qCameraComport = new QInfraredComport(this);
    //    m_qCameraComport->InitParameter("/dev/ttyUSB1",19200);
    //    m_qCameraComport->start();
    m_iCameraPanSpeed = CameraPan_speed_low;
    m_iCameraSpeed    = CameraPan_speed_low;
    ui->radio_low->setChecked(true);

    m_iCurrentCameraDevice = Camera_device_number;

    QString strTemp = QString("%1°/S").arg(CameraPan_speed_low_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
}

void QWgtZhouShi::InitWgtChange()
{
    ui->BtnVideoChange->setCheckable(true);
    connect(ui->BtnVideoChange, SIGNAL(clicked(bool)), this, SLOT(slot_BtnVideoChange_clicked(bool)));
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtZhouShi::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);

    //    m_QZsHwPlayer->PlayStop();
    //    m_QZsKjgPlayer->PlayStop();

    //    if (nullptr != m_QZsHwPlayer)
    //    {
    //        m_QZsHwPlayer->PlayStop();
    //        delete m_QZsHwPlayer;
    //        m_QZsHwPlayer = nullptr;
    //    }
    //    if (nullptr != m_QZsKjgPlayer)
    //    {
    //        m_QZsKjgPlayer->PlayStop();
    //        delete m_QZsKjgPlayer;
    //        m_QZsKjgPlayer = nullptr;
    //    }

    // m_bShow = false;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtZhouShi::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    // 2路
    HIMSG_PARAM_S hsmsg;
    hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
    hsmsg.videoNum                  = 2;
    hsmsg.videoChnIndex[0]          = HWVIDEO;
    hsmsg.videoChnIndex[1]          = KJGVIDEO;
    hsmsg.stVideoParam[0].s32X      = 0;
    hsmsg.stVideoParam[0].s32Y      = 902;
    hsmsg.stVideoParam[0].u32Width  = 450;
    hsmsg.stVideoParam[0].u32Height = 256;
    hsmsg.stVideoParam[1].s32X      = 0;
    hsmsg.stVideoParam[1].s32Y      = 0;
    hsmsg.stVideoParam[1].u32Width  = 1600;
    hsmsg.stVideoParam[1].u32Height = 900;
    auto pHs                        = (char *)&hsmsg;
    auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
    if (len == -1)
    {
        qDebug() << "send Error";
    }

    //    if(m_bShow)
    //    {
    //        m_bShow = true;
    //        return;
    //    }

    //    m_QZsKjgPlayer = new QPlayer(ui->ZsKjgWgt);
    //    m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());

    //    m_QZsHwPlayer = new QPlayer(ui->ZsHwWgt);
    //    m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());
}

void QWgtZhouShi::SltOperateDelayTime()
{
    m_tmOperateDelayTime->stop();
    m_qCameraPanComport->Infrared_ComparameterSetting(CameraPan_device_number, 0, 0, 0);
}

void QWgtZhouShi::on_btn_up_pressed()
{
    //    m_qCameraPanComport->Infrared_ComparameterSetting(CameraPan_device_number,1,CameraPan_speed_low);
    emit signal_WgtZhouShi_operateNo(1, CameraPan_device_number, 1, m_iCameraPanSpeed);
}

void QWgtZhouShi::on_btn_up_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, CameraPan_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "云台向上转动";
    emit signalLog(lg);
}

void QWgtZhouShi::on_btn_down_pressed()
{
    //    m_qCameraPanComport->Infrared_ComparameterSetting(CameraPan_device_number,2,CameraPan_speed_low);
    emit signal_WgtZhouShi_operateNo(1, CameraPan_device_number, 2, m_iCameraPanSpeed);
}

void QWgtZhouShi::on_btn_down_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, CameraPan_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = " 云台向下转动";
    emit signalLog(lg);
}

void QWgtZhouShi::on_btn_left_pressed()
{
    //    m_qCameraPanComport->Infrared_ComparameterSetting(CameraPan_device_number,3,CameraPan_speed_low);
    emit signal_WgtZhouShi_operateNo(1, CameraPan_device_number, 3, m_iCameraPanSpeed);
}

void QWgtZhouShi::on_btn_left_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, CameraPan_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = " 云台向左转动";
    emit signalLog(lg);
}

void QWgtZhouShi::on_btn_right_pressed()
{
    //    m_qCameraPanComport->Infrared_ComparameterSetting(CameraPan_device_number,4,CameraPan_speed_low);
    emit signal_WgtZhouShi_operateNo(1, CameraPan_device_number, 4, m_iCameraPanSpeed);
}

void QWgtZhouShi::on_btn_right_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, CameraPan_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "云台向右转动";
    emit signalLog(lg);
}

void QWgtZhouShi::on_BtnZoomAdd_pressed()
{
    //    m_qCameraComport->Infrared_ComparameterSetting(Camera_device_number,5,0x20);
    emit signal_WgtZhouShi_operateNo(2, m_iCurrentCameraDevice, 5, m_iCameraSpeed);
}

void QWgtZhouShi::on_BtnZoomAdd_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, m_iCurrentCameraDevice, 0, 0);
    LogInfo lg;
    lg.operationCode = "变倍+";
    emit signalLog(lg);
}

void QWgtZhouShi::on_btnZoomSub_pressed()
{
    //    m_qCameraComport->Infrared_ComparameterSetting(Camera_device_number,6,0x20);
    emit signal_WgtZhouShi_operateNo(2, m_iCurrentCameraDevice, 6, m_iCameraSpeed);
}

void QWgtZhouShi::on_btnZoomSub_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, m_iCurrentCameraDevice, 0, 0);
    LogInfo lg;
    lg.operationCode = "变倍-";
    emit signalLog(lg);
}

void QWgtZhouShi::on_BtnFocusAdd_pressed()
{
    //    m_qCameraComport->Infrared_ComparameterSetting(Camera_device_number,7,0x20);
    emit signal_WgtZhouShi_operateNo(2, m_iCurrentCameraDevice, 7, m_iCameraSpeed);
}

void QWgtZhouShi::on_BtnFocusAdd_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, m_iCurrentCameraDevice, 0, 0);
    LogInfo lg;
    lg.operationCode = "焦距+";
    emit signalLog(lg);
}

void QWgtZhouShi::on_BtnFocusSub_pressed()
{
    //    m_qCameraComport->Infrared_ComparameterSetting(Camera_device_number,8,0x20);
    emit signal_WgtZhouShi_operateNo(2, m_iCurrentCameraDevice, 8, m_iCameraSpeed);
}

void QWgtZhouShi::on_BtnFocusSub_released()
{
    //    m_tmOperateDelayTime->start(1000);
    emit signal_WgtZhouShi_operateNo(0, m_iCurrentCameraDevice, 0, 0);
    LogInfo lg;
    lg.operationCode = "焦距-";
    emit signalLog(lg);
}

void QWgtZhouShi::on_radio_low_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_low;
    m_iCameraSpeed    = Camera_speed_low;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_low_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtZhouShi_operateNo(3, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = "设置云台低速";
    emit signalLog(lg);
}

void QWgtZhouShi::on_radio_mid_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_mid;
    m_iCameraSpeed    = Camera_speed_mid;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_mid_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtZhouShi_operateNo(3, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = "设置云台中速";
    emit signalLog(lg);
}

void QWgtZhouShi::on_radio_high_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_high;
    m_iCameraSpeed    = Camera_speed_high;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_high_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtZhouShi_operateNo(3, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = " 设置云台高速";
    emit signalLog(lg);
}

void QWgtZhouShi::slot_BtnVideoChange_clicked(bool flag)
{
    LogInfo lg;
    lg.operationCode = "可见光红外切换";
    emit signalLog(lg);
    if (flag)
    {
        ui->ZsKjgWgt->setGeometry(0, 902, 450, 256);
        ui->ZsHwWgt->setGeometry(0, 0, 1600, 900);

        m_iCurrentCameraDevice = Camera_infrared_device_number;
        emit signal_WgtZhouShi_operateNo(Mainwidow_OperateNo9, 1, 2, 0);

        // 2路
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
        hsmsg.videoNum                  = 2;
        hsmsg.videoChnIndex[0]          = KJGVIDEO;
        hsmsg.videoChnIndex[1]          = HWVIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 902;
        hsmsg.stVideoParam[0].u32Width  = 450;
        hsmsg.stVideoParam[0].u32Height = 256;
        hsmsg.stVideoParam[1].s32X      = 0;
        hsmsg.stVideoParam[1].s32Y      = 0;
        hsmsg.stVideoParam[1].u32Width  = 1600;
        hsmsg.stVideoParam[1].u32Height = 900;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "send Error";
        }
    }
    else
    {
        ui->ZsKjgWgt->setGeometry(0, 0, 1600, 900);
        ui->ZsHwWgt->setGeometry(0, 902, 450, 256);

        m_iCurrentCameraDevice = Camera_device_number;
        emit signal_WgtZhouShi_operateNo(Mainwidow_OperateNo9, 1, 1, 0);

        // 2路
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
        hsmsg.videoNum                  = 2;
        hsmsg.videoChnIndex[0]          = HWVIDEO;
        hsmsg.videoChnIndex[1]          = KJGVIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 902;
        hsmsg.stVideoParam[0].u32Width  = 450;
        hsmsg.stVideoParam[0].u32Height = 256;
        hsmsg.stVideoParam[1].s32X      = 0;
        hsmsg.stVideoParam[1].s32Y      = 0;
        hsmsg.stVideoParam[1].u32Width  = 1600;
        hsmsg.stVideoParam[1].u32Height = 900;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "send Error";
        }
    }
}

void QWgtZhouShi::setCameraPanSpeed(int iCameraSpeed, int iCameraPanSpeed)
{
    m_iCameraPanSpeed = iCameraPanSpeed;
    m_iCameraSpeed    = iCameraSpeed;
    QString strTemp;
    switch (iCameraPanSpeed)
    {
        case CameraPan_speed_low:
        {
            ui->radio_low->setChecked(true);
            ui->radio_mid->setChecked(false);
            ui->radio_high->setChecked(false);
            strTemp = QString("%1°/S").arg(CameraPan_speed_low_Display, 3, 'f', 2, QLatin1Char('0'));
            ui->label_speed->setText(strTemp);
        }
        break;
        case CameraPan_speed_mid:
        {
            ui->radio_low->setChecked(false);
            ui->radio_mid->setChecked(true);
            ui->radio_high->setChecked(false);
            strTemp = QString("%1°/S").arg(CameraPan_speed_mid_Display, 3, 'f', 2, QLatin1Char('0'));
            ui->label_speed->setText(strTemp);
        }
        break;
        case CameraPan_speed_high:
        {
            ui->radio_low->setChecked(false);
            ui->radio_mid->setChecked(false);
            ui->radio_high->setChecked(true);
            strTemp = QString("%1°/S").arg(CameraPan_speed_high_Display, 3, 'f', 2, QLatin1Char('0'));
            ui->label_speed->setText(strTemp);
        }
        break;
        default:
            break;
    }
}

void QWgtZhouShi::setCameraPanAzimuthParam(int iAzimuth)
{
    double dTemp    = iAzimuth / 100.0;
    QString strTemp = QString("%1°").arg(dTemp, 3, 'f', 2, QLatin1Char('0'));
    ui->label_orientation->setText(strTemp);
}

void QWgtZhouShi::setCameraPanPitchParam(int iPitch)
{
    double dTemp;
    int iTemp;
    QString strTemp;
    if (iPitch > 10000)
    {
        iTemp   = 36000 - iPitch;
        dTemp   = iTemp / 100.0;
        strTemp = QString("%1°").arg(dTemp, 3, 'f', 2, QLatin1Char('0'));
        ui->label_pitch->setText(strTemp);
    }
    else if (iPitch < 3000)
    {
        iTemp   = iPitch;
        dTemp   = iTemp / 100.0;
        strTemp = QString("-%1°").arg(dTemp, 3, 'f', 2, QLatin1Char('0'));
        ui->label_pitch->setText(strTemp);
    }
}

void QWgtZhouShi::on_btnAutoLight_clicked()
{
    emit signal_WgtZhouShi_operateNo(11, 1, 17, 0);
    LogInfo lg;
    lg.operationCode = "自动补光";
    emit signalLog(lg);
}

void QWgtZhouShi::on_btnManualLight_clicked(bool checked)
{
    if (checked)
    {
        emit signal_WgtZhouShi_operateNo(11, 1, 18, 0);
        ui->btnManualLight->setText("关闭补光");
        LogInfo lg;
        lg.operationCode = "手动打开补光";
        emit signalLog(lg);
    }
    else
    {
        emit signal_WgtZhouShi_operateNo(11, 1, 19, 0);
        ui->btnManualLight->setText("手动补光");
        LogInfo lg;
        lg.operationCode = "手动关闭补光";
        emit signalLog(lg);
    }
}
