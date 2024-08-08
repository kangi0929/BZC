#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include "CfgFile.h"
#include "Message.h"
#include "parse_json.h"
#include <QBitmap>
#include <QCursor>
#include <QFile>
#include <QScreen>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BtnHealthLed->hide();
    ui->BtnHealthState->hide();
    ui->btnQJ1->setVisible(false);
    ui->btnQJ2->setVisible(false);
    ui->btnZoomRestore->setVisible(false);
    ui->horizontalScrollBar->setVisible(false);

    InitControl();

    //显示时间
    m_tmUpdateTime = new QTimer(this);
    connect(m_tmUpdateTime, SIGNAL(timeout()), this, SLOT(SltUpdateDataTime()));
    m_tmUpdateTime->start(1000);

//    //鼠标优化部分
//    QBitmap bmap(10, 10);
//    bmap.fill(Qt::color0);
//    setCursor(QCursor(bmap, bmap));
//    m_thd = new QThread(this);
//    m_thd->start();
//    m_mmOpt = new MouseMoveOptimize();
//    m_mmOpt->moveToThread(m_thd);

    m_detectFault = new QTimer(this);
    connect(m_detectFault, &QTimer::timeout, this, &MainWindow::sltFlagPlus);
    m_detectFault->start(10000);

    m_qjZoom = new QjZoomArea(ui->centralwidget);
    //m_qjZoom->move(0, 0);
    m_qjZoom->resize(1600, 1144);
    m_qjZoom->hide();

    m_udp = new QUdpSocket;

}

MainWindow::~MainWindow()
{
    m_thd->exit();
    delete m_mmOpt;
    delete m_udp;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  //  QPainter painter(this);
  //  painter.fillRect(this->rect(), QColor(255, 255, 255, 1));
//        static int num = 0;
//        qDebug() << "MainWindow::paintEvent " << num++;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_1:
        {
            OnClickedBtnMainWgt();
            break;
        }
        case Qt::Key_2:
        {
            on_BtnQuanjing_clicked();
            break;
        }
        case Qt::Key_3:
        {
            OnClickedBtnZhouShi();
            break;
        }
        case Qt::Key_4:
        {
            on_BtnNVR_clicked();
            break;
        }
        case Qt::Key_5:
        {
            OnClickedBtnExit();
            break;
        }
    }
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void MainWindow::InitControl()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    // setWindowFlags(Qt::WindowTitleHint | Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);

    showFullScreen();

    m_QMainWgt = new QWgtMain(this);

    m_QMainWgt->move(0, 0);

    m_QMainWgt->show();

    //20220809   新增信号槽
    connect(this, &MainWindow::signalLog, this, &MainWindow::SlotWriteLog);

    connect(m_QMainWgt, SIGNAL(signal_WgtMain_operateNo(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));

    connect(m_QMainWgt, SIGNAL(signalLog(LogInfo)), this,
            SLOT(SlotWriteLog(LogInfo)));

    m_QZhouShiWgt = new QWgtZhouShi(this);
    m_QZhouShiWgt->move(0, 0);
    m_QZhouShiWgt->hide();

    connect(m_QZhouShiWgt, SIGNAL(signal_WgtZhouShi_operateNo(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));
    connect(m_QZhouShiWgt, SIGNAL(signalLog(LogInfo)), this,
            SLOT(SlotWriteLog(LogInfo)));

    m_qNVRReplayWgt = new NVRReplayWgt(this);
    m_qNVRReplayWgt->Init();
    m_qNVRReplayWgt->move(0,0);
    m_qNVRReplayWgt->hide();

    m_tmOperateDelayTime = new QTimer(this);
    connect(m_tmOperateDelayTime, SIGNAL(timeout()), this, SLOT(SltOperateDelayTime()));

    m_qCameraPanComport = new QInfraredComport(this);
    m_qCameraPanComport->InitParameter("/dev/ttyAMA2", 9600);
    m_qCameraPanComport->start();


    connect(m_qCameraPanComport, SIGNAL(signal_InfraredComport_operate(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));

    m_qCameraComport = new QInfraredComport(this);
    m_qCameraComport->InitParameter("/dev/ttyAMA4", 19200);
    m_qCameraComport->start();
    connect(m_qCameraComport, SIGNAL(signal_InfraredComport_operate(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));

    m_qJoyStickComport = new QJoyStickComport(this);
    //m_qJoyStickComport->InitParameter("/dev/ttyAMA3", 9600);
    m_qJoyStickComport->InitParameter("/dev/ttyAMA1", 9600);
    m_qJoyStickComport->start();

    connect(m_qJoyStickComport, SIGNAL(signal_JoyStickComport_operate(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));

    m_iCurrentWindowID           = 1;
    m_iCameraMainWgtDeviceAdd    = 1;  // 1:可见光 2：红外
    m_iCameraZhouShiWgtDeviceAdd = 1;  // 1:可见光 2：红外
    //    connect(m_qCameraComport,SIGNAL(signal_InfraredComport_operate(int,int,int,int)),this,SLOT(SltRecvOperateNo(int,int,int,int)));
    //    ui->centralwidget->layout()->add

    //网络部分感觉还要重新整理下
    string strIp(""), strPort("");
    strIp             = QCfgFile::GetInst()->GetNVR_IP();
    strPort           = QCfgFile::GetInst()->GetNVR_Port();
    QString qStr_Ip   = QString::fromStdString(strIp);
    QString qStr_Port = QString::fromStdString(strPort);

    strIp              = QCfgFile::GetInst()->GetInterCommu_IP();
    strPort            = QCfgFile::GetInst()->GetInterCommu_Port();
    QString qStr_Ip2   = QString::fromStdString(strIp);
    QString qStr_Port2 = QString::fromStdString(strPort);

    Message::get_instance()->init(qStr_Ip, qStr_Port.toInt(), qStr_Ip2, qStr_Port2.toInt());
    Message::get_instance()->start_socket();

    // 这个是发送云台转动信息的udp，主要是后面两个参数
    Message::get_instance()->init(qStr_Ip, qStr_Port.toInt(), "192.168.0.10", 20002);
    Message::get_instance()->start_socket();

    connect(Message::get_instance(),
            SIGNAL(signal_orientation_data(const QString &, const QJsonObject &)), this,
            SLOT(slots_prase_orientation_data(const QString &, const QJsonObject &)));

    //测试用
    Message::get_instance()->init(qStr_Ip, qStr_Port.toInt(), "192.168.1.74", 10000);
    Message::get_instance()->start_socket();

    Logger::InitLog(LOG_NAME, "NVR_log");

//    LOG_LEVEL eLevel = static_cast<LOG_LEVEL>(LL_INFO);
//    Logger::SetLevel(LOG_NAME, eLevel);


}

void MainWindow::slots_prase_orientation_data(const QString &id, const QJsonObject &data)
{

    // qDebug() << "********************receive data************************ : ";  //<<
    // LES_Util_Json::json_object_to_string(data);

    int result = 1;
    horizontal = 0.0;
    vertical   = 0.0;

    if (LES_Util_Json::get_json_value_by_key(data, JSON_KEY_RESULT, result))
    {
        if (result == 0)
        {
            if (!LES_Util_Json::get_json_value_by_key(data, JSON_KEY_HORIZONTAL, horizontal))
            {
                return;
            }
            if (!LES_Util_Json::get_json_value_by_key(data, JSON_KEY_VERTICAL, vertical))
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    //    qDebug() << "result = " << result;
    //    qDebug() << "horizontal = " << horizontal;
    //    qDebug() << "vertical = " << vertical;
    //    qDebug() << "********************receive data**************** : ";  //<< LES_Util_Json::json_object_to_string(data);

    //在每次转动之前，先停止一下，这样可以立刻执行下次转动。
    m_qCameraPanComport->Infrared_ComparameterSetting(1, 0, 0, 0);

    //串口控制云台转换 水平
    m_qCameraPanComport->Infrared_ComparameterSetting(1, 11, 0, (unsigned short)horizontal * 100);

    //串口控制云台转换 垂直
    if (vertical < 0)
    {
        vertical = -vertical * 100;
    }
    else if (vertical > 0)
    {
        vertical = 36000 - vertical * 100;
    }
    m_qCameraPanComport->Infrared_ComparameterSetting(1, 12, 0, (unsigned short)vertical);
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明: 单击首页响应函数
 **************************************************************************/
void MainWindow::OnClickedBtnMainWgt()
{

    m_qNVRReplayWgt->StopReplay();

    m_QZhouShiWgt->hide();
    m_qNVRReplayWgt->hide();
    m_qjZoom->restoreInit();  //2022-08-09 就添加了这一行


    m_QMainWgt->show();
    m_iCurrentWindowID = 1;

    ui->btnQJ1->setVisible(false);
    ui->btnQJ2->setVisible(false);
    ui->btnZoomRestore->setVisible(false);
    ui->horizontalScrollBar->setVisible(false);

    m_qjZoom->hide();

    LogInfo lg;
    lg.operationCode = "打开首页";
    emit signalLog(lg);
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:单击周视响应函数
 **************************************************************************/
void MainWindow::OnClickedBtnZhouShi()
{
    m_qNVRReplayWgt->StopReplay();
    m_QMainWgt->hide();
    m_qNVRReplayWgt->hide();


    m_QZhouShiWgt->show();
    m_iCurrentWindowID = 2;

    ui->btnQJ1->setVisible(false);
    ui->btnQJ2->setVisible(false);
    ui->btnZoomRestore->setVisible(false);

    m_qjZoom->hide();

    LogInfo lg;
    lg.operationCode = "打开周视";
    emit signalLog(lg);
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明: 单击退出响应函数
 **************************************************************************/
void MainWindow::OnClickedBtnExit()
{
   if(QMessageBox::information(NULL, "退出", "是否确认退出！", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
   {
       QUdpSocket *socket_send;
       socket_send = new QUdpSocket(this);
       HIMSG_PARAM_S hsmsg;
       memset(&hsmsg,0,sizeof(hsmsg));
       hsmsg.iInfoId                   = APP_EXIT;
       hsmsg.videoNum                  = 1;
       auto pHs                        = (char *)&hsmsg;
       auto len = socket_send->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
       if (len == -1)
       {
           qDebug() << "send Error";
       }
       qDebug() << "软件退出";
      // sleep(5);
      // close();

       LogInfo lg;
       lg.operationCode = "应用退出";
       emit signalLog(lg);
   }
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void MainWindow::SltUpdateDataTime()
{
    QDateTime DateTime = QDateTime::currentDateTime();

    QString strText = DateTime.toString("yyyy-MM-dd HH:mm:ss");

    ui->lbDateTime->setText(strText);
}

void MainWindow::SltOperateDelayTime()
{
    m_tmOperateDelayTime->stop();
    if (1 == m_iCameraDeviceNo)
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
        m_qCameraComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
    }
    else
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
        m_qCameraComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
    }
}

//写日志信息
void MainWindow::SlotWriteLog(LogInfo stlogInfo)
{
    //信息
     LOG_INFO(LOG_NAME, stlogInfo.operationCode.toStdString());
     qDebug() << "Write Log!";
//     //告警
//     LOG_WARN(LOG_NAME, stlogInfo.operationCode.toStdString());
//     //故障
//     LOG_ERROR(LOG_NAME, stlogInfo.operationCode.toStdString());
}

void MainWindow::SltRecvOperateNo(int iOperateNo, int iParam0, int iParam1, int iParam2)
{
    //qDebug() << "iOperatoNO:   " << iOperateNo;
    switch (iOperateNo)
    {
    case Mainwidow_OperateNo0:  // send camera and cameraPan stop
    {
        m_iCameraDeviceNo = iParam0;
        m_tmOperateDelayTime->start(200);
    }
        break;
    case Mainwidow_OperateNo1:  // CameraPan 云台控制
    {
        //        m_iCameraDeviceNo = iParam0;
        m_qCameraPanComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
        break;
    case Mainwidow_OperateNo2:  // Camera 摄像头控制
    {
        m_qCameraComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
        break;
    case Mainwidow_OperateNo3:  //全景云台设置
    {
        m_QMainWgt->setCameraPanSpeed(iParam1, iParam2);
    }
        break;
    case Mainwidow_OperateNo4:  //周视云台设置
    {
        m_QZhouShiWgt->setCameraPanSpeed(iParam1, iParam2);
    }
        break;
    case Mainwidow_OperateNo5:  //云台和摄像头方位设置
    {
        m_QMainWgt->setCameraPanAzimuthParam(iParam0);
        m_QZhouShiWgt->setCameraPanAzimuthParam(iParam0);
    }
        break;
    case Mainwidow_OperateNo6:  //云台和摄像头俯仰
    {
        m_QMainWgt->setCameraPanPitchParam(iParam0);
        m_QZhouShiWgt->setCameraPanPitchParam(iParam0);
    }
        break;
    case Mainwidow_OperateNo7:  //摇杆云台控制
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
        break;
    case Mainwidow_OperateNo8:  //摇杆摄像头控制
    {
        if (m_iCurrentWindowID == 1)
        {
            m_qCameraComport->Infrared_ComparameterSetting(m_iCameraMainWgtDeviceAdd, iParam1,
                                                           iParam2, 0);
        }
        else if (m_iCurrentWindowID == 2)
        {
            m_qCameraComport->Infrared_ComparameterSetting(m_iCameraZhouShiWgtDeviceAdd,
                                                           iParam1, iParam2, 0);
        }
    }
        break;
    case Mainwidow_OperateNo9:  //可见光和红外切换
    {
        if (iParam0 == 1)
        {
            m_iCameraZhouShiWgtDeviceAdd = iParam1;  // 1:可见光 2：红外
        }
        else if (iParam0 == 2)
        {
            m_iCameraMainWgtDeviceAdd = iParam1;  // 1:可见光 2：红外
        }
    }
        break;
    case Mainwidow_OperateNo10:  //故障报文
    {
        m_flag = m_beat;
        if (iParam0 != 0)//可见光故障
        {
            m_QMainWgt->setState(0, iParam0);
        }
        else
        {
            m_QMainWgt->setState(0, 0);
        }

        if(iParam1 != 0)//红外热像故障
        {
            m_QMainWgt->setState(1, iParam1);
        }
        else
        {
            m_QMainWgt->setState(1, 0);
        }
    }
        break;
    case Mainwidow_OperateNo11:
    {
        m_qCameraComport->Infrared_ComparameterSetting(iParam0, iParam1, 0, 0);

    }
        break;
    case Mainwidow_OperateNo12:
    {
        if(iParam0 == 1)
        {
            m_qJoyStickComport->JoystickUpdate();
        }
        else if(iParam0 == 2)
        {
            m_qJoyStickComport->JoystickReset();
        }
    }
        break;
    default:
        break;
    }
}

//截图
void MainWindow::on_btnCapture_clicked()
{
//    QScreen *screen         = QGuiApplication::primaryScreen();
//    QDateTime DateTime      = QDateTime::currentDateTime();
//    QString dateTime        = DateTime.toString("yyyy_MM_dd_HH_mm_ss");
////    QString imgFilePathName = "./CapImage/Cap" + dateTime + ".png";
//    QString imgFilePathName = "/mnt/map/" + dateTime + ".png";
//    qDebug() << "imgFilePathName" << imgFilePathName;
//    if (!screen->grabWindow(0).save(imgFilePathName))
//    {
//        qDebug() << "截图失败。。。";
//    }

    system("./yuv2jpg");
    LogInfo lg;
    lg.operationCode = "截图";
    emit signalLog(lg);
}

//显示NVR界面
void MainWindow::on_BtnNVR_clicked()
{
    m_QZhouShiWgt->hide();
    m_QMainWgt->hide();
    m_qNVRReplayWgt->show();

    ui->btnQJ1->setVisible(false);
    ui->btnQJ2->setVisible(false);
    ui->btnZoomRestore->setVisible(false);

    m_qjZoom->hide();
    LogInfo lg;
    lg.operationCode = " 打开NVR";
    emit signalLog(lg);
}

void MainWindow::on_btnQJ1_clicked(bool checked)
{
    m_qjZoom->setTag(QjZoomArea::QJ1);
    m_qjNum = 0;
    //要让滚动条恢复到最初始的状态，保持跟画面同步
    ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->minimum());
    if (checked)
    {
        InterfaceChange::getInstance()->change(QJ1ZoomIn);
        ui->btnQJ2->setChecked(false);
        LogInfo lg;
        lg.operationCode = "全景1放大";
        emit signalLog(lg);
    }
    else
    {
        ui->btnQJ1->setChecked(true);
    }
}

void MainWindow::on_btnQJ2_clicked(bool checked)
{
    m_qjZoom->setTag(QjZoomArea::QJ2);
    m_qjNum = 1;
    //要让滚动条恢复到最初始的状态，保持跟画面同步
    ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->minimum());
    if (checked)
    {
        InterfaceChange::getInstance()->change(QJ2ZoomIn);
        ui->btnQJ1->setChecked(false);
        LogInfo lg;
        lg.operationCode = "全景2放大";
        emit signalLog(lg);
    }
    else
    {
        ui->btnQJ2->setChecked(true);
    }
}

void MainWindow::on_BtnQuanjing_clicked()
{
    if (m_qNVRReplayWgt->isVisible())
    {
        m_qNVRReplayWgt->StopReplay();
        m_qNVRReplayWgt->hide();
    }

    ui->btnQJ1->setVisible(true);
    ui->btnQJ2->setVisible(true);
    ui->btnZoomRestore->setVisible(true);
    ui->horizontalScrollBar->setVisible(true);

    if (m_QMainWgt->isVisible())
        m_QMainWgt->hide();
    if (m_QZhouShiWgt->isVisible())
        m_QZhouShiWgt->hide();


    InterfaceChange::getInstance()->change(QJ1ZoomIn);
    ui->btnQJ2->setChecked(false);

    m_qjZoom->move(0, 0);
    m_qjZoom->setTag(QjZoomArea::QJ1);  //默认是全景1
    m_qjNum = 0;
    m_qjZoom->show();

    //要让滚动条恢复到最初始的状态，保持跟画面同步
    printf("@@@@ %d\n", ui->horizontalScrollBar->minimum());
    ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->minimum());

    LogInfo lg;
    lg.operationCode = " 打开全景";
    emit signalLog(lg);
}

void MainWindow::sltFlagPlus()
{
    if (m_flag == m_beat)
    {
        m_flag++;
    }
    else
    {
        m_QMainWgt->setState(0, 1);
        m_QMainWgt->setState(1, 1);
    }
}


void MainWindow::on_btnRestore_clicked()
{
//    m_qjZoom->restore();
//    //要让滚动条恢复到最初始的状态，保持跟画面同步
//    ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->minimum());
//    LogInfo lg;
//    lg.operationCode = "放大恢复";
//    emit signalLog(lg);
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    int startX = (m_qj_width - QJ_WIDTH) * (qreal(value) / ui->horizontalScrollBar->maximum());

    m_qjZoom->setStartX(startX);
    HIMSG_PARAM_S hsmsg;
    hsmsg.iInfoId                   = _QJ_Inter_;
    hsmsg.videoNum                  = 1;
    hsmsg.videoChnIndex[0]          = m_qjNum;
    hsmsg.stVideoParam[0].s32X      = startX;
    hsmsg.stVideoParam[0].s32Y      = 0;
    hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
    hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
    auto pHs                        = (char *)&hsmsg;
    auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
    if (len == -1)
    {
        qDebug() << "send Error";
    }
}


void MainWindow::on_btnZoomRestore_clicked(bool checked)
{
    if (checked)
    {
        ui->btnZoomRestore->setText("恢复");
        //放大
        m_qjZoom->setZoomFunc(true);
    }
    else
    {
        ui->btnZoomRestore->setText("放大");
        //恢复
        m_qjZoom->setZoomFunc(false);
        m_qjZoom->restore();
        //要让滚动条恢复到最初始的状态，保持跟画面同步
        ui->horizontalScrollBar->setValue(ui->horizontalScrollBar->minimum());
        LogInfo lg;
        lg.operationCode = "放大恢复";
        emit signalLog(lg);
    }
}
