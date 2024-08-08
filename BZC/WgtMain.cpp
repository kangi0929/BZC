#include "WgtMain.h"
#include "ui_WgtMain.h"
#include "CfgFile.h"
#include <QDebug>
#include <QJsonArray>
#include <QTimer>
#include <sys/time.h>
#include "Message.h"
#include <QFile>

QWgtMain::QWgtMain(QWidget *parent) : QWidget(parent), ui(new Ui::QWgtMain)
{
    ui->setupUi(this);

    InitControl();
    myInit();  // cyt

    //是否开启debug模式
    QFile inFile("./Data/debug.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "debug.txt文件打开失败!";
    }
    char ch[10];
    inFile.readLine(ch, sizeof(ch));
    QString str(ch);
    if (str.toInt() == 1)
    {
        ui->btn_debug->setVisible(true);
        ui->btn_record->setVisible(true);
        ui->btn_SetZero->setVisible(true);
        ui->btn_JoyStick_reset->setVisible(true);
        ui->btn_JoyStick_update->setVisible(true);
    }
    else
    {
        ui->btn_debug->setVisible(false);
        ui->btn_record->setVisible(false);
        ui->btn_SetZero->setVisible(false);
        ui->btn_JoyStick_reset->setVisible(false);
        ui->btn_JoyStick_update->setVisible(false);
    }

    //获取微表数据
    connect(Message::get_instance(),
            SIGNAL(signal_weibiao_data(const QString &, const QJsonObject &)), this,
            SLOT(slots_weibiao_data(const QString &, const QJsonObject &)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    m_timer->start(50);

//    m_timer2 = new QTimer(this);
//    connect(m_timer2, &QTimer::timeout, this, &QWgtMain::writeToTable);
//    m_timer2->start(1000);

    m_udp = new QUdpSocket(this);

    //ui->toolBox->removeItem(0);
    //ui->toolBox->removeItem(0);
//    ui->toolBox->setCurrentIndex(0);
//    ui->toolBox->currentWidget()->hide();
//    ui->toolBox->setCurrentIndex(1);
//    ui->toolBox->currentWidget()->hide();
}

void QWgtMain::parseDetectInfoJsObj(const QJsonObject &jsObj)
{
    if (jsObj.contains("data") && jsObj["data"].isArray())
    {
        QJsonArray jsArr = jsObj["data"].toArray();
        for (int var = 0; var < jsArr.size(); ++var)
        {
            // qDebug() << jsArr.size();  实际情况都是1
            if (jsArr[var].isObject())
            {
                QJsonObject jsObj2 = jsArr[var].toObject();
                QString ip         = jsObj2["panorama_ip"].toString();

                if (jsObj2.contains("target_info") && jsObj2["target_info"].isArray())
                {
                    QJsonArray jsArr2 = jsObj2["target_info"].toArray();
                    //一个视频框里的所有目标
                    for (int i = 0; i < jsArr2.size(); ++i)
                    {
                        // bool isNew = true;
                        //一个具体的目标，对应m_mapDetect里的一项
                        if (jsArr2[i].isObject())
                        {
                            QJsonObject target = jsArr2[i].toObject();
                            int targetId       = target["target_id"].toInt();
                            auto item          = m_mapDetect.find(targetId);
                            if (item != m_mapDetect.end())
                            {
                                //进行赋值
                                //说明map里已经有对应的目标了, 重置lifeTime
                                item.value()->panorama_ip = ip;
                                item.value()->orientation = target["orientation"].toInt();
                                item.value()->area_id     = target["area_id"].toInt();
                                item.value()->type        = target["type"].toInt();
                                QJsonObject position      = target["position"].toObject();
                                item.value()->order_no    = position["order_no"].toInt();
                                item.value()->x_pos       = position["x_pos"].toInt();
                                item.value()->y_pos       = position["y_pos"].toInt();
                                item.value()->width       = position["width"].toInt();
                                item.value()->high        = position["high"].toInt();
                                item.value()->lifeTime    = 20;
                            }
                            else
                            {
                                DetectInfo *dtInf    = new DetectInfo;
                                dtInf->panorama_ip   = ip;
                                dtInf->orientation   = target["orientation"].toInt();
                                dtInf->area_id       = target["area_id"].toInt();
                                dtInf->type          = target["type"].toInt();
                                dtInf->target_id     = target["target_id"].toInt();
                                QJsonObject position = target["position"].toObject();
                                dtInf->order_no      = position["order_no"].toInt();
                                dtInf->x_pos         = position["x_pos"].toInt();
                                dtInf->y_pos         = position["y_pos"].toInt();
                                dtInf->width         = position["width"].toInt();
                                dtInf->high          = position["high"].toInt();

                                m_mapDetect.insert(dtInf->target_id, dtInf);
                            }
#if 0
                            for (auto ite = m_mapDetect.begin(); ite != m_mapDetect.end(); ++ite)
                            {
                                if (ite.key() == target["target_id"].toInt())
                                {
                                    //说明map里已经有对应的目标了, 重置lifeTime
                                    ite.value()->panorama_ip = ip;
                                    ite.value()->orientation = target["orientation"].toInt();
                                    ite.value()->area_id     = target["area_id"].toInt();
                                    ite.value()->type        = target["type"].toInt();
                                    QJsonObject position     = target["position"].toObject();
                                    ite.value()->order_no    = position["order_no"].toInt();
                                    ite.value()->x_pos       = position["x_pos"].toInt();
                                    ite.value()->y_pos       = position["y_pos"].toInt();
                                    ite.value()->width       = position["width"].toInt();
                                    ite.value()->high        = position["high"].toInt();
                                    ite.value()->lifeTime    = 20;
                                    isNew                    = false;
                                    break;
                                }
                            }
                            if (isNew)
                            {
                                DetectInfo *dtInf    = new DetectInfo;
                                dtInf->panorama_ip   = ip;
                                dtInf->orientation   = target["orientation"].toInt();
                                dtInf->area_id       = target["area_id"].toInt();
                                dtInf->type          = target["type"].toInt();
                                dtInf->target_id     = target["target_id"].toInt();
                                QJsonObject position = target["position"].toObject();
                                dtInf->order_no      = position["order_no"].toInt();
                                dtInf->x_pos         = position["x_pos"].toInt();
                                dtInf->y_pos         = position["y_pos"].toInt();
                                dtInf->width         = position["width"].toInt();
                                dtInf->high          = position["high"].toInt();

                                m_mapDetect.insert(dtInf->target_id, dtInf);
                            }
#endif
                        }
                    }
                }
            }
        }
    }
    isFirstChooseFromNewTable = true;
}

void QWgtMain::writeToTable()
{
    //qDebug() << "writetotable&&&&&&&&&&&&&&&&&&&&&&&&";
    isRowsRemoved = true;
    theModel->removeRows(0, theModel->rowCount());

    int row = 0;
    for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
    {
        QStandardItem *stdItem;
        stdItem = new QStandardItem(QString::number(ite.value()->area_id));
        stdItem->setTextAlignment(Qt::AlignCenter);
        theModel->setItem(row, 0, stdItem);
        stdItem = new QStandardItem(QString::number(ite.key()));
        stdItem->setTextAlignment(Qt::AlignCenter);
        theModel->setItem(row, 1, stdItem);
        stdItem = new QStandardItem(QString::number(ite.value()->type));
        stdItem->setTextAlignment(Qt::AlignCenter);
        theModel->setItem(row, 2, stdItem);
        stdItem = new QStandardItem(QString::number(ite.value()->orientation));
        stdItem->setTextAlignment(Qt::AlignCenter);
        theModel->setItem(row, 3, stdItem);
        ++row;
    }
    isRowsRemoved = false;
}

void QWgtMain::drawRect()
{
    //初始化m_rectplayer,程序第一次载入微表数据 没问题
    if (m_rectplayerOne.isEmpty())
    {
        for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
        {
            if (ite.value()->panorama_ip == m_urlOne)
            {
                RectInfo *rectInfo    = new RectInfo();
                rectInfo->x_pos       = ite.value()->x_pos;
                rectInfo->y_pos       = ite.value()->y_pos;
                rectInfo->width       = ite.value()->width;
                rectInfo->high        = ite.value()->high;
                rectInfo->target_id   = ite.value()->target_id;
                rectInfo->panorama_ip = ite.value()->panorama_ip;

                m_rectplayerOne.append(rectInfo);
            }
        }
    }
    if (m_rectplayerTwo.isEmpty())
    {
        for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
        {
            if (ite.value()->panorama_ip == m_urlTwo)
            {
                RectInfo *rectInfo    = new RectInfo();
                rectInfo->x_pos       = ite.value()->x_pos;
                rectInfo->y_pos       = ite.value()->y_pos;
                rectInfo->width       = ite.value()->width;
                rectInfo->high        = ite.value()->high;
                rectInfo->target_id   = ite.value()->target_id;
                rectInfo->panorama_ip = ite.value()->panorama_ip;

                m_rectplayerTwo.append(rectInfo);
            }
        }
    }

    //先根据新的微表数据，更新要画的矩形框的数据, 把m_rectplayerOne & Two里过时的信息给删除掉
    //若有新的数据(目标)则插入到m_rectpalyer里
    // playerOne
    for (int i = 0; i < m_rectplayerOne.size(); ++i)
    {
        bool isExist = false;
        for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
        {
            if (ite.value()->panorama_ip == m_rectplayerOne[i]->panorama_ip
                && ite.value()->target_id == m_rectplayerOne[i]->target_id)
            {
                isExist                   = true;
                m_rectplayerOne[i]->x_pos = ite.value()->x_pos;
                m_rectplayerOne[i]->y_pos = ite.value()->y_pos;
                m_rectplayerOne[i]->width = ite.value()->width;
                m_rectplayerOne[i]->high  = ite.value()->high;
                break;
            }
        }
        if (!isExist)
        {
            delete m_rectplayerOne[i];
            m_rectplayerOne.removeAt(i);
        }
    }  //新数据插入
    for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
    {
        if (ite.value()->panorama_ip == m_urlOne)
        {
            bool isNew = true;
            for (int i = 0; i < m_rectplayerOne.size(); ++i)
            {
                if (ite.value()->target_id == m_rectplayerOne[i]->target_id)
                {
                    isNew = false;
                }
            }
            if (isNew)
            {
                RectInfo *rectInfo    = new RectInfo();
                rectInfo->x_pos       = ite.value()->x_pos;
                rectInfo->y_pos       = ite.value()->y_pos;
                rectInfo->width       = ite.value()->width;
                rectInfo->high        = ite.value()->high;
                rectInfo->target_id   = ite.value()->target_id;
                rectInfo->panorama_ip = ite.value()->panorama_ip;

                m_rectplayerOne.append(rectInfo);
            }
        }
    }

    // playerTwo
    for (int i = 0; i < m_rectplayerTwo.size(); ++i)
    {
        bool isExist = false;
        for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
        {
            if (ite.value()->panorama_ip == m_rectplayerTwo[i]->panorama_ip
                && m_rectplayerTwo[i]->target_id == ite.value()->target_id)
            {
                isExist                   = true;
                m_rectplayerTwo[i]->x_pos = ite.value()->x_pos;
                m_rectplayerTwo[i]->y_pos = ite.value()->y_pos;
                m_rectplayerTwo[i]->width = ite.value()->width;
                m_rectplayerTwo[i]->high  = ite.value()->high;
                break;
            }
        }
        if (!isExist)
        {
            delete m_rectplayerTwo[i];
            m_rectplayerTwo.removeAt(i);
        }
    }
    for (auto ite = m_mapDetect.cbegin(); ite != m_mapDetect.cend(); ++ite)
    {
        if (ite.value()->panorama_ip == m_urlTwo)
        {
            bool isNew = true;
            for (int i = 0; i < m_rectplayerTwo.size(); ++i)
            {
                if (ite.value()->target_id == m_rectplayerTwo[i]->target_id)
                {
                    isNew = false;
                }
            }
            if (isNew)
            {
                RectInfo *rectInfo    = new RectInfo();
                rectInfo->x_pos       = ite.value()->x_pos;
                rectInfo->y_pos       = ite.value()->y_pos;
                rectInfo->width       = ite.value()->width;
                rectInfo->high        = ite.value()->high;
                rectInfo->target_id   = ite.value()->target_id;
                rectInfo->panorama_ip = ite.value()->panorama_ip;

                m_rectplayerTwo.append(rectInfo);
            }
        }
    }


    //if (!m_rectplayerOne.isEmpty())
    //{
        emit sendRectToPlayerOne(m_rectplayerOne);
    //}
//    if (m_QQj1Player != nullptr)
//    {
//        m_QQj1Player->slotsReceiveRect(m_rectplayerOne);
//    }
    //if (!m_rectplayerTwo.isEmpty())
    //{
        emit sendRectToPlayerTwo(m_rectplayerTwo);
    //}
//    if (m_QQj2Player != nullptr)
//    {
//        m_QQj2Player->slotsReceiveRect(m_rectplayerTwo);
//    }
}

void QWgtMain::on_updateSelection(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (isFirstChooseFromNewTable)
    {
        m_mmap.clear();
        isFirstChooseFromNewTable = false;
    }
    if (!isRowsRemoved)
    {
        QModelIndex index;
        QModelIndexList items = selected.indexes();
        foreach (index, items)
        {
            m_mmap.insert(index.row(), index.column());
        }

        items = deselected.indexes();
        foreach (index, items)
        {
            m_mmap.remove(index.row(), index.column());
        }
        showFocusedTarget();
    }
}

void QWgtMain::showFocusedTarget()
{
    //被选中的行的集合
    //分别处理两个player
    auto uniKeyList = m_mmap.uniqueKeys();
    for (int i = 0; i < m_rectplayerOne.size(); ++i)
    {
        int key;
        bool isSel = false;
        foreach (key, uniKeyList)
        {
            //获取某一行第二列的数据,就是target_id
            QModelIndex index = theModel->index(key, 1);
            int tarid         = theModel->data(index).toInt();

            if (m_rectplayerOne.at(i)->target_id == tarid)
            {
                m_rectplayerOne.at(i)->isSelected = true;
                isSel                             = true;
                break;
            }
        }
        if (!isSel)
        {
            m_rectplayerOne.at(i)->isSelected = false;
        }
    }

    for (int i = 0; i < m_rectplayerTwo.size(); ++i)
    {
        int key;
        bool isSel = false;
        foreach (key, uniKeyList)
        {
            QModelIndex index = theModel->index(key, 1);
            int tarid         = theModel->data(index).toInt();
            if (m_rectplayerTwo.at(i)->target_id == tarid)
            {
                m_rectplayerTwo.at(i)->isSelected = true;
                isSel                             = true;
                break;
            }
        }
        if (!isSel)
        {
            m_rectplayerTwo.at(i)->isSelected = false;
        }
    }
}

// void QWgtMain::slotsReceiveJsObj()
//{
//    // struct timeval tv1, tv2, tv3, tv4, tv5;
//    // gettimeofday(&tv1, NULL);
//    // makeupJsObj(m_jsObj, 20);
//    // gettimeofday(&tv2, NULL);
//    // int diff = (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec) / 1000;
//    // printf("time pass1: %d msec\n", diff);

////    parseDetectInfoJsObj(m_jsObj);
////    writeToTable();
////    drawRect();
//}

QWgtMain::~QWgtMain()
{

    //    if (nullptr != m_QQj1Player)
    //    {
    //        m_QQj1Player->PlayStop();
    //        delete m_QQj1Player;
    //        m_QQj1Player = nullptr;
    //    }
    //    if (nullptr != m_QQj2Player)
    //    {
    //        m_QQj2Player->PlayStop();
    //        delete m_QQj2Player;
    //        m_QQj2Player = nullptr;
    //    }
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
    delete ui;
    delete theModel;
    // delete theSelection;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtMain::InitControl()
{
    m_iCameraPanSpeed = CameraPan_speed_low;
    m_iCameraSpeed    = Camera_speed_low;
    ui->radio_low->setChecked(true);

    QString strTemp = QString("%1°/S").arg(CameraPan_speed_low_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtMain::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    if (nullptr != m_QQj1Player)
    {
        delete m_QQj1Player;
        m_QQj1Player = nullptr;
    }

    if (nullptr != m_QQj2Player)
    {
        delete m_QQj2Player;
        m_QQj2Player = nullptr;
    }

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
    // m_bShow = true;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
void QWgtMain::showEvent(QShowEvent *event)
{
    // Q_UNUSED(event);

    m_QQj1Player = new QPlayer(ui->QuanJing1Wgt);
    m_QQj1Player->setFixedSize(ui->QuanJing1Wgt->width(), ui->QuanJing1Wgt->height());
    string strUrl = QCfgFile::GetInst()->GetQj1RtspUrl();  //根据url来区分是来自那个全景。
    QString qStr_url = QString::fromStdString(strUrl);
    m_QQj1Player->setRtspUrl(qStr_url);
    m_QQj1Player->setScale();
    m_QQj1Player->show();


    m_QQj2Player = new QPlayer(ui->QuanJing2Wgt);
    m_QQj2Player->setFixedSize(ui->QuanJing2Wgt->width(), ui->QuanJing2Wgt->height());
    strUrl = QCfgFile::GetInst()->GetQj2RtspUrl();
    qStr_url = QString::fromStdString(strUrl);
    m_QQj2Player->setRtspUrl(qStr_url);
    m_QQj2Player->setScale();
    m_QQj2Player->show();



    // 4路
    HIMSG_PARAM_S hsmsg;
    hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
    hsmsg.videoNum                  = 4;
    hsmsg.videoChnIndex[0]          = QJ1VIDEO;
    hsmsg.videoChnIndex[1]          = QJ2VIDEO;
    hsmsg.videoChnIndex[2]          = HWVIDEO;
    hsmsg.videoChnIndex[3]          = KJGVIDEO;
    hsmsg.stVideoParam[0].s32X      = 0;
    hsmsg.stVideoParam[0].s32Y      = 0;
    hsmsg.stVideoParam[0].u32Width  = 1600;
    hsmsg.stVideoParam[0].u32Height = 310;
    hsmsg.stVideoParam[1].s32X      = 0;
    hsmsg.stVideoParam[1].s32Y      = 312;
    hsmsg.stVideoParam[1].u32Width  = 1600;
    hsmsg.stVideoParam[1].u32Height = 310;
    hsmsg.stVideoParam[2].s32X      = 784;
    hsmsg.stVideoParam[2].s32Y      = 894;
    hsmsg.stVideoParam[2].u32Width  = 422;
    hsmsg.stVideoParam[2].u32Height = 264;
    hsmsg.stVideoParam[3].s32X      = 0;
    hsmsg.stVideoParam[3].s32Y      = 624;
    hsmsg.stVideoParam[3].u32Width  = 782;
    hsmsg.stVideoParam[3].u32Height = 534;
    auto pHs                        = (char *)&hsmsg;
    auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
    if (len == -1)
    {
        qDebug() << "send Error";
    }

    ui->btn_Trace->setChecked(false);
    ui->btn_Trace->setText("调转跟踪");
    //    m_QZsKjgPlayer = new QPlayer(ui->ZsKjgWgt);
    //    m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());
    //    //m_QZsKjgPlayer->PlayStart("/opt/Taylor.mp4");

    //    m_QZsHwPlayer = new QPlayer(ui->ZsHwWgt);
    //    m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());

    connect(this, SIGNAL(sendRectToPlayerOne(QList<RectInfo *> &)), m_QQj1Player,
            SLOT(slotsReceiveRect(QList<RectInfo *> &)));

    connect(this, SIGNAL(sendRectToPlayerTwo(QList<RectInfo *> &)), m_QQj2Player,
            SLOT(slotsReceiveRect(QList<RectInfo *> &)));

    ui->btn_add_1->setChecked(false);
    ui->btn_add_1->setText("警戒区1");
    ui->btn_add_2->setChecked(false);
    ui->btn_add_2->setText("警戒区2");

}

void QWgtMain::slots_weibiao_data(const QString &id, const QJsonObject &data)
{
    parseDetectInfoJsObj(data);
    writeToTable();
    drawRect();
    //static int cnt = 0;
    //qDebug() << "slots_weibiao_data : " << cnt++;
}

void QWgtMain::updateMap()
{
    auto begin = m_mapDetect.begin();
    auto end   = m_mapDetect.end();
    while (begin != end)
    {
        --begin.value()->lifeTime;
        if (begin.value()->lifeTime == 0)
        {
            delete begin.value();
            begin = m_mapDetect.erase(begin);
            writeToTable();
            drawRect();
        }
        else
        {
            ++begin;
        }
    }
}

void QWgtMain::on_btn_up_pressed()
{
    emit signal_WgtMain_operateNo(1, CameraPan_device_number, 1, m_iCameraPanSpeed);
}

void QWgtMain::on_btn_up_released()
{
    emit signal_WgtMain_operateNo(0, CameraPan_device_number, 0, 0);
    //发送日志
    LogInfo lg;
    lg.operationCode = "云台向上转动";
    emit signalLog(lg);
}

void QWgtMain::on_btn_down_pressed()
{
    emit signal_WgtMain_operateNo(1, CameraPan_device_number, 2, m_iCameraPanSpeed);
}

void QWgtMain::on_btn_down_released()
{
    emit signal_WgtMain_operateNo(0, CameraPan_device_number, 0, 0);
    //发送日志
    LogInfo lg;
    lg.operationCode = "云台向下转动";
    emit signalLog(lg);
}

void QWgtMain::on_btn_left_pressed()
{
    emit signal_WgtMain_operateNo(1, CameraPan_device_number, 3, m_iCameraPanSpeed);
}

void QWgtMain::on_btn_left_released()
{
    emit signal_WgtMain_operateNo(0, CameraPan_device_number, 0, 0);
    //发送日志
    LogInfo lg;
    lg.operationCode = "云台向左转动";
    emit signalLog(lg);
}

void QWgtMain::on_btn_right_pressed()
{
    emit signal_WgtMain_operateNo(1, CameraPan_device_number, 4, m_iCameraPanSpeed);
}

void QWgtMain::on_btn_right_released()
{
    emit signal_WgtMain_operateNo(0, CameraPan_device_number, 0, 0);
    //发送日志
    LogInfo lg;
    lg.operationCode = "云台向右转动";
    emit signalLog(lg);
}

void QWgtMain::on_radio_low_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_low;
    m_iCameraSpeed    = Camera_speed_low;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_low_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtMain_operateNo(4, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = "设置云台低速";
    emit signalLog(lg);
}

void QWgtMain::on_radio_mid_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_mid;
    m_iCameraSpeed    = Camera_speed_mid;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_mid_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtMain_operateNo(4, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = "设置云台中速";
    emit signalLog(lg);
}

void QWgtMain::on_radio_high_clicked()
{
    m_iCameraPanSpeed = CameraPan_speed_high;
    m_iCameraSpeed    = Camera_speed_high;
    QString strTemp = QString("%1°/S").arg(CameraPan_speed_high_Display, 3, 'f', 2, QLatin1Char('0'));
    ui->label_speed->setText(strTemp);
    emit signal_WgtMain_operateNo(4, 0, m_iCameraSpeed, m_iCameraPanSpeed);
    LogInfo lg;
    lg.operationCode = "设置云台高速";
    emit signalLog(lg);
}

void QWgtMain::slot_wgt_change(bool flag)
{
    if (flag)
    {
        ui->ZsKjgWgt->setGeometry(785, 900, 421, 251);
        //        m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());
        ui->ZsHwWgt->setGeometry(5, 650, 771, 511);
        //        m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());
        emit signal_WgtMain_operateNo(Mainwidow_OperateNo9, 2, 2, 0);
    }
    else
    {
        ui->ZsKjgWgt->setGeometry(5, 650, 771, 511);
        //        m_QZsKjgPlayer->setFixedSize(ui->ZsKjgWgt->width(), ui->ZsKjgWgt->height());
        ui->ZsHwWgt->setGeometry(785, 900, 421, 251);
        //        m_QZsHwPlayer->setFixedSize(ui->ZsHwWgt->width(), ui->ZsHwWgt->height());
        emit signal_WgtMain_operateNo(Mainwidow_OperateNo9, 2, 1, 0);
    }
}

void QWgtMain::setCameraPanSpeed(int iCameraSpeed, int iCameraPanSpeed)
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

void QWgtMain::setCameraPanAzimuthParam(int iAzimuth)
{
    double dTemp    = iAzimuth / 100.0;
    if (iAzimuth == 36000)
    {
        ui->label_orientation->setText("0.00°");
    }
    else
    {
        QString strTemp = QString("%1°").arg(dTemp, 3, 'f', 2, QLatin1Char('0'));
        ui->label_orientation->setText(strTemp);
    }
}

void QWgtMain::setCameraPanPitchParam(int iPitch)
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

void QWgtMain::setState(int device, int state)
{
    //device 0 : optical
    //       1 : infrared
    //state 0 : 正常
    //      1 : 故障
    if (device == 0)
    {
        if (state == 0)
        {
            int index = ui->toolBox->indexOf(ui->page_4);
            ui->toolBox->setItemIcon(index, QIcon(":/resource/green.png"));
        }
        else
        {
            int index = ui->toolBox->indexOf(ui->page_4);
            ui->toolBox->setItemIcon(index, QIcon(":/resource/red.png"));
        }
    }
    if (device == 1)
    {
        if (state == 0)
        {
            int index = ui->toolBox->indexOf(ui->page_3);
            ui->toolBox->setItemIcon(index, QIcon(":/resource/green.png"));
        }
        else
        {
            int index = ui->toolBox->indexOf(ui->page_3);
            ui->toolBox->setItemIcon(index, QIcon(":/resource/red.png"));
        }
    }
}

void QWgtMain::myInit()
{
    initTable();
}

void QWgtMain::initTable()
{
    theModel     = new QStandardItemModel(1, 4, this);
    theSelection = new QItemSelectionModel(theModel);

    connect(theSelection, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(on_updateSelection(QItemSelection, QItemSelection)));

    ui->tableView->setModel(theModel);               //设置数据模型
    ui->tableView->setSelectionModel(theSelection);  //设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑

    QStringList header = QString("区域号, 批号, 类型, 方位").simplified().split(",");
    theModel->setHorizontalHeaderLabels(header);
}

void QWgtMain::on_BtnFocusAdd_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_device_number, 7, m_iCameraSpeed);
}

void QWgtMain::on_BtnFocusAdd_released()
{
    emit signal_WgtMain_operateNo(0, Camera_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "可见光焦距+";
    emit signalLog(lg);
}

void QWgtMain::on_BtnFocusSub_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_device_number, 8, m_iCameraSpeed);
}

void QWgtMain::on_BtnFocusSub_released()
{
    emit signal_WgtMain_operateNo(0, Camera_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "可见光焦距-";
    emit signalLog(lg);
}

void QWgtMain::on_BtnZoomAdd_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_device_number, 5, m_iCameraSpeed);
}

void QWgtMain::on_BtnZoomAdd_released()
{
    emit signal_WgtMain_operateNo(0, Camera_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "可见光变倍+";
    emit signalLog(lg);
}

void QWgtMain::on_BtnZoomSub_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_device_number, 6, m_iCameraSpeed);
}

void QWgtMain::on_BtnZoomSub_released()
{
    emit signal_WgtMain_operateNo(0, Camera_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "可见光变倍-";
    emit signalLog(lg);
}

void QWgtMain::on_BtnInfraredFocusAdd_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_infrared_device_number, 7, m_iCameraSpeed);
}

void QWgtMain::on_BtnInfraredFocusAdd_released()
{
    emit signal_WgtMain_operateNo(0, Camera_infrared_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "红外焦距+";
    emit signalLog(lg);
}

void QWgtMain::on_BtnInfraredFocusSub_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_infrared_device_number, 8, m_iCameraSpeed);
}

void QWgtMain::on_BtnInfraredFocusSub_released()
{
    emit signal_WgtMain_operateNo(0, Camera_infrared_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "红外焦距-";
    emit signalLog(lg);
}

void QWgtMain::on_BtnInfraredZoomAdd_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_infrared_device_number, 5, m_iCameraSpeed);
}

void QWgtMain::on_BtnInfraredZoomAdd_released()
{
    emit signal_WgtMain_operateNo(0, Camera_infrared_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "红外变倍+";
    emit signalLog(lg);
}

void QWgtMain::on_BtnInfraredZoomSub_pressed()
{
    emit signal_WgtMain_operateNo(2, Camera_infrared_device_number, 6, m_iCameraSpeed);
}

void QWgtMain::on_BtnInfraredZoomSub_released()
{
    emit signal_WgtMain_operateNo(0, Camera_infrared_device_number, 0, 0);
    LogInfo lg;
    lg.operationCode = "红外变倍-";
    emit signalLog(lg);
}

template <class Key, class T> void QWgtMain::clearQMap(QMap<Key, T> &map)
{
    if (!map.isEmpty())
    {
        auto begin = map.begin();
        auto end   = map.end();
        while (begin != end)
        {
            delete begin.value();
            begin = map.erase(begin);
        }
    }
}

void QWgtMain::on_btn_add_1_clicked(bool checked)
{
    if (checked)
    {
        ui->btn_add_1->setText("清除");
        m_QQj1Player->setAlarmArea(true);
        //m_QQj1Player->setPixmapSize(m_QQj1Player->width(), m_QQj1Player->height());
        LogInfo lg;
        lg.operationCode = "增加警戒区1";
        emit signalLog(lg);
    }
    else
    {
        ui->btn_add_1->setText("警戒区1");
        m_QQj1Player->setAlarmArea(false);
        m_QQj1Player->clear();
        LogInfo lg;
        lg.operationCode = "删除警戒区1";
        emit signalLog(lg);
    }
}

void QWgtMain::on_btn_add_2_clicked(bool checked)
{
    if (checked)
    {
        ui->btn_add_2->setText("清除");
        m_QQj2Player->setAlarmArea(true);
        //m_QQj2Player->setPixmapSize(m_QQj2Player->width(), m_QQj2Player->height());
        LogInfo lg;
        lg.operationCode = "增加警戒区2";
        emit signalLog(lg);
    }
    else
    {
        ui->btn_add_2->setText("警戒区2");
        m_QQj2Player->setAlarmArea(false);
        m_QQj2Player->clear();
        LogInfo lg;
        lg.operationCode = "删除警戒区2";
        emit signalLog(lg);
    }
}

void QWgtMain::on_btn_Trace_clicked(bool checked)
{
    if (checked)
    {
        ui->btn_Trace->setText("取消调转");
        m_QQj1Player->setCamMoved(true);
        m_QQj2Player->setCamMoved(true);
        LogInfo lg;
        lg.operationCode = "调转跟踪";
        emit signalLog(lg);
    }
    else
    {
        LogInfo lg;
        lg.operationCode = "取消调转跟踪";
        emit signalLog(lg);
        ui->btn_Trace->setText("调转跟踪");
        m_QQj1Player->setCamMoved(false);
        m_QQj2Player->setCamMoved(false);
    }
}

void QWgtMain::on_btn_Change_clicked()
{
    LogInfo lg;
    lg.operationCode = "红外可见光切换";
    emit signalLog(lg);
    static bool exchg = true;
    if (exchg)
    {
        ui->ZsKjgWgt->setGeometry(784, 894, 422, 264);
        ui->ZsHwWgt->setGeometry(0, 624, 782, 534);
        emit signal_WgtMain_operateNo(Mainwidow_OperateNo9, 2, 2, 0);
        exchg = false;

        // kjg <-> hw
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
        hsmsg.videoNum                  = 4;
        hsmsg.videoChnIndex[0]          = QJ1VIDEO;
        hsmsg.videoChnIndex[1]          = QJ2VIDEO;
        hsmsg.videoChnIndex[2]          = KJGVIDEO;
        hsmsg.videoChnIndex[3]          = HWVIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = 1600;
        hsmsg.stVideoParam[0].u32Height = 310;
        hsmsg.stVideoParam[1].s32X      = 0;
        hsmsg.stVideoParam[1].s32Y      = 312;
        hsmsg.stVideoParam[1].u32Width  = 1600;
        hsmsg.stVideoParam[1].u32Height = 310;
        hsmsg.stVideoParam[2].s32X      = 784;
        hsmsg.stVideoParam[2].s32Y      = 894;
        hsmsg.stVideoParam[2].u32Width  = 422;
        hsmsg.stVideoParam[2].u32Height = 264;
        hsmsg.stVideoParam[3].s32X      = 0;
        hsmsg.stVideoParam[3].s32Y      = 624;
        hsmsg.stVideoParam[3].u32Width  = 782;
        hsmsg.stVideoParam[3].u32Height = 534;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "send Error";
        }
    }
    else
    {
        ui->ZsKjgWgt->setGeometry(0, 624, 782, 534);
        ui->ZsHwWgt->setGeometry(784, 894, 422, 264);
        emit signal_WgtMain_operateNo(Mainwidow_OperateNo9, 2, 1, 0);
        exchg = true;

        // kjg <-> hw
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId                   = VIDEO_PARAMETER_SETTING_FUNCTION;
        hsmsg.videoNum                  = 4;
        hsmsg.videoChnIndex[0]          = QJ1VIDEO;
        hsmsg.videoChnIndex[1]          = QJ2VIDEO;
        hsmsg.videoChnIndex[2]          = HWVIDEO;
        hsmsg.videoChnIndex[3]          = KJGVIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = 1600;
        hsmsg.stVideoParam[0].u32Height = 310;
        hsmsg.stVideoParam[1].s32X      = 0;
        hsmsg.stVideoParam[1].s32Y      = 312;
        hsmsg.stVideoParam[1].u32Width  = 1600;
        hsmsg.stVideoParam[1].u32Height = 310;
        hsmsg.stVideoParam[2].s32X      = 784;
        hsmsg.stVideoParam[2].s32Y      = 894;
        hsmsg.stVideoParam[2].u32Width  = 422;
        hsmsg.stVideoParam[2].u32Height = 264;
        hsmsg.stVideoParam[3].s32X      = 0;
        hsmsg.stVideoParam[3].s32Y      = 624;
        hsmsg.stVideoParam[3].u32Width  = 782;
        hsmsg.stVideoParam[3].u32Height = 534;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "send Error";
        }
    }
}

//调试
QFile recoFile("./debugRes.txt");
void QWgtMain::on_btn_debug_clicked(bool checked)
{
    if (checked)
    {
        connect(m_QQj1Player, SIGNAL(lastQj(int)), this, SLOT(slot_getId(int)));
        connect(m_QQj2Player, SIGNAL(lastQj(int)), this, SLOT(slot_getId(int)));
        ui->btn_debug->setText("结束调试");
        if (!recoFile.open(QFile::WriteOnly | QFile::Append))
        {
            qDebug() << "文件打开失败！！！！！！！！！！！！！！！";
            qDebug() << "文件真的打开失败了！！！！！！！！！！！！！！！";
            qDebug() << "文件打开失败， 请相信我！！！！！！！！！！！！！！！";
        }
        m_QQj1Player->clear();
        m_QQj1Player->setPixmapSize(m_QQj1Player->width(), m_QQj1Player->height());
        m_QQj2Player->clear();
        m_QQj2Player->setPixmapSize(m_QQj2Player->width(), m_QQj2Player->height());
    }
    else
    {
        disconnect(m_QQj1Player, SIGNAL(lastQj(int)), this, SLOT(slot_getId(int)));
        disconnect(m_QQj2Player, SIGNAL(lastQj(int)), this, SLOT(slot_getId(int)));
        m_QQj1Player->clear();
        m_QQj2Player->clear();
        ui->btn_debug->setText("开始调试");

        recoFile.close();
    }

    //根据checked的值决定是开始调试还是结束调试。
    //可以开始记录了位置，方位，俯仰信息了
    ui->btn_record->setEnabled(checked);
    //设置player中的bool变量，让两个全景player开始进入调试模式
    m_QQj1Player->setDebug(checked);
    m_QQj2Player->setDebug(checked);
}

void QWgtMain::on_btn_record_clicked()
{
    //"rtsp://192.168.0.10:8554/video" 1
    //"rtsp://192.168.0.10:8564/video" 2
    //获得坐标点
    if (m_id == 1)
    {
        QPoint pos  = m_QQj1Player->getCurrnetPoint();
        QString ori = ui->label_orientation->text();
        ori.chop(1);
        QString pit = ui->label_pitch->text();
        pit.chop(1);
        QString inputData = QString::number(pos.x()) + "  " + QString::number(pos.y()) + "  "
                            + QString::number(ori.toDouble()) + "  "
                            + QString::number(pit.toDouble()) + "\n";
        QByteArray ba = inputData.toLocal8Bit();
        recoFile.write(ba);
    }
    else if (m_id == 2)
    {
        QPoint pos  = m_QQj2Player->getCurrnetPoint();
        QString ori = ui->label_orientation->text();
        ori.chop(1);
        QString pit = ui->label_pitch->text();
        pit.chop(1);
        QString inputData = QString::number(pos.x() + 1920) + "  " + QString::number(pos.y()) + "  "
                            + QString::number(ori.toDouble()) + "  "
                            + QString::number(pit.toDouble()) + "\n";
        QByteArray ba = inputData.toLocal8Bit();
        recoFile.write(ba);
    }
}

void QWgtMain::slot_getId(int id)
{
    m_id = id;
}

//控制状态灯颜色变化的测试代码
// void QWgtMain::on_pushButton_clicked()
//{
//    static int cnt = 1;
//    if (cnt % 3 == 1)
//    {
//        ui->toolBox->setItemIcon(3, QIcon("./StateIcon/red.png"));
//    }
//    if (cnt % 3 == 2)
//    {
//        ui->toolBox->setItemIcon(3, QIcon("./StateIcon/grey.png"));
//    }
//    if (cnt % 3 == 0)
//    {
//        ui->toolBox->setItemIcon(3, QIcon("./StateIcon/green.png"));
//    }
//    cnt++;
//}

void QWgtMain::on_btn_Zero_clicked()
{
    emit signal_WgtMain_operateNo(1, 1, 15, 0);
    LogInfo lg;
    lg.operationCode = "云台归零";
    emit signalLog(lg);
}

//这个是初始化云台零位，一般就执行一次
void QWgtMain::on_btn_SetZero_clicked()
{
    emit signal_WgtMain_operateNo(1, 1, 16, 0);
}

//摇杆复位
void QWgtMain::on_btn_JoyStick_reset_clicked()
{
    emit signal_WgtMain_operateNo(12, 2, 0, 0);
}

//摇杆设置更新时间
void QWgtMain::on_btn_JoyStick_update_clicked()
{
    emit signal_WgtMain_operateNo(12, 1, 0, 0);
}
