#include "NVRReplayWgt.h"
#include "ui_NVRReplayWgt.h"
#include <QDebug>
#include "Logger.h"
#include <sys/statfs.h>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <list>
#include <QMessageBox>

NVRReplayWgt::NVRReplayWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NVRReplayWgt)
{
    ui->setupUi(this);

    ui->videoReplayWgt->show();
    ui->mapRelayWgt->hide();
    ui->logWgt->hide();

//    this->setAutoFillBackground(true);
//    this->setWindowOpacity(1);

    ui->dateEdit_video->setDisplayFormat("yyyy.MM.dd");
    ui->dateEdit_map->setDisplayFormat("yyyy.MM.dd");
    ui->dateEdit_log->setDisplayFormat("yyyy.MM.dd");

    QDateTime DateTime      = QDateTime::currentDateTime();
//    QString dateTime        = DateTime.toString("yyyy_MM_dd_HH_mm_ss");
    ui->dateEdit_video->setDateTime(DateTime);
    ui->dateEdit_map->setDateTime(DateTime);
    ui->dateEdit_log->setDateTime(DateTime);
    LastSelectitem = NULL;
    m_strSelMapFileName = "";
    m_strSelLogFileName = "";
}

NVRReplayWgt::~NVRReplayWgt()
{
    delete ui;
}

void NVRReplayWgt::Init()
{
    m_iCurrentSliderValue = 0;
    qDebug() << "NVR Init()";
    m_pUdpSocketNVR = new QUdpSocket(this);
//    m_dstRadarCtrlAddr = QHostAddress("127.0.0.1");
    m_detPort = 8888;
//    qDebug() << "m_detPort = 6666;";
    ui->pbVideoPause->setCheckable(true);
    ui->pbVideoPlay->setCheckable(true);
    ui->pbVideoSlowPlay->setCheckable(true);
    ui->pbVideoFastPlay->setCheckable(true);
    ui->pbQJVideoRestore->setCheckable(true);
    ui->pbQJVideoRestore->setEnabled(false);
    ui->ReplaySlider->setEnabled(true);
    ChangeReplayPushButtonState(3);

    ui->ReplaySlider->setMaximum(100);
    ui->ReplaySlider->setMinimum(0);
    ui->ReplaySlider->setTickInterval(1);
    m_loadImage = new QImage;

//    qDebug() << "m_loadImage = new QImage;";
//    ui->logTable->setShowGrid(1);
//    ui->logTable->setGridStyle(Qt::DotLine);
    ui->logTableWgt->setShowGrid(1);
    ui->logTableWgt->setGridStyle(Qt::DotLine);
//    m_stdItemModel = new QStandardItemModel();
//    m_stdItemModel->setColumnCount(2);
    ui->logTableWgt->setColumnCount(1);
//    ui->logTableWgt->setColumnWidth(0,100);
    ui->logTableWgt->setColumnWidth(0,800);

//    qDebug() << "ui->logTable->setColumnWidth(1,500);";
    m_strListLabels = QString("日志内容,序号").simplified().split(",");
//    m_stdItemModel->setHorizontalHeaderLabels(m_strListLabels);
//    ui->logTableWgt.setm(m_stdItemModel);
    ui->logTableWgt->setHorizontalHeaderLabels(m_strListLabels);
//    ui->logTable->setModel(m_stdItemModel);

//    ui->logTable->setColumnWidth(0,100);
//    ui->logTable->setColumnWidth(1,500);
//    ui->logTable->show();
//    qDebug() << "ui->logTable->show();";

    bool bRet = m_pUdpSocketNVR->bind(QHostAddress("127.0.0.1"),NVR_NET_PORT,QUdpSocket::ShareAddress |QUdpSocket::ReuseAddressHint);
    qDebug() << "m_pUdpSocketNVR->bind：" << bRet;
    connect(m_pUdpSocketNVR,SIGNAL(readyRead()),this,SLOT(slotReadUdpData()));

    m_bPaulseReplayFlag = false;
    m_bCurrentReplyState = false;
    m_lCurrentReplayTime = 0;

    memset(&m_stInterCommunication,0,sizeof (m_stInterCommunication));

    m_lCurrentReplayTotalFrame = 1;

    ui->treeWidgetVideo->setColumnCount(1);//设置列
    ui->treeWidgetVideo->setHeaderLabel(tr("视频选择列表"));//设置标题
    for (int i = 0;i < VIDEO_CHANNEL_NUMBER;i++) {
         m_rootTreeWidgetItem[i] = new QTreeWidgetItem(ui->treeWidgetVideo);
         QString strTempName;
         strTempName.sprintf("%d通道视频",i);
         switch (i) {
         case 0:
         {
             strTempName = "全景视频1";
         }break;
         case 1:
         {
             strTempName = "全景视频2";
         }break;
         case 2:
         {
             strTempName = "周视红外";
         }break;
         case 3:
         {
             strTempName = "周视可见光";
         }break;
         default:
         {
             strTempName = "其他";
         }
             break;
         }
         m_rootTreeWidgetItem[i]->setText(0,strTempName);
         ui->treeWidgetVideo->addTopLevelItem(m_rootTreeWidgetItem[i]);
    }
    connect(ui->treeWidgetVideo,SIGNAL(itemClicked(QTreeWidgetItem *,int)),this,SLOT(slotItemClicked(QTreeWidgetItem *,int)));
    m_strCurrentSelVideoFile = "";
    m_strSelCurrentFile = "";

    ManageDiskSpace();

    m_iChannelID = -1;

//    QString strConfigFile = "/mnt/video/test.txt";
//    QFile replayConfigFile(strConfigFile);
//    if (!replayConfigFile.open(QFile::ReadOnly))
//    {
//        qDebug() << "can not open the file!";
//    }
//    else {
//        char cBuff[1024];
//        memset(cBuff,0,1024 * sizeof(char));
//        Replay_Config_File_Parameter stReplay_Config_File_Parameter;
//        memset(&stReplay_Config_File_Parameter,0,sizeof(stReplay_Config_File_Parameter));
//        replayConfigFile.read(cBuff,sizeof(stReplay_Config_File_Parameter));
//        memcpy(&stReplay_Config_File_Parameter,cBuff,sizeof(stReplay_Config_File_Parameter));
//        qDebug() << "stReplay_Config_File_Parameter:"<<stReplay_Config_File_Parameter.lReplayRecordFrameTotal;
//        replayConfigFile.close();
//    }
}

void NVRReplayWgt::ChangeReplayPushButtonState(int iPbIndex)
{
    switch (iPbIndex) {
    case 1://播放
    {
//        ui->pbVideoPlay->setEnabled(false);
//        ui->pbVideoPlay->setChecked(true);
        m_bCurrentReplyState = true;
        ui->pbVideoPause->setChecked(false);
        ui->pbVideoPause->setText("暂停");
        ui->pbVideoPause->setEnabled(true);
        ui->pbVideoFastPlay->setEnabled(true);
        ui->pbVideoFastPlay->setChecked(false);
        ui->pbVideoSlowPlay->setEnabled(true);
        ui->pbVideoSlowPlay->setChecked(false);
        ui->ReplaySlider->setEnabled(false);
        QString strChannelName,strTempName;
        if(!m_strCurrentSelVideoFile.isEmpty())
        {
            strTempName = m_strCurrentSelVideoFile;
            strChannelName = strTempName.left(strTempName.length() - 4);
            strChannelName = strChannelName.right(1);
            int iChannelNum = strChannelName.toInt();
            if(iChannelNum >= 0 && iChannelNum < 2)
            {
                ui->pbQJVideoRestore->setEnabled(true);
            }
        }
    }break;
    case 2://暂停
    {
//        ui->pbVideoPlay->setEnabled(true);
//        ui->pbVideoPlay->setChecked(false);
//        ui->pbVideoFastPlay->setEnabled(true);
//        ui->pbVideoFastPlay->setChecked(false);
//        ui->pbVideoSlowPlay->setEnabled(true);
//        ui->pbVideoSlowPlay->setChecked(false);

        //ui->pbVideoPause;
    }break;
    case 3://停止
    {
        m_bCurrentReplyState = false;
        ui->pbVideoPlay->setEnabled(true);
        ui->pbVideoPlay->setChecked(false);
        ui->pbVideoFastPlay->setEnabled(false);
        ui->pbVideoFastPlay->setChecked(false);
        ui->pbVideoSlowPlay->setEnabled(false);
        ui->pbVideoSlowPlay->setChecked(false);
        ui->pbVideoPause->setEnabled(false);
        ui->pbVideoPause->setChecked(false);
        ui->pbVideoPause->setText("暂停");

        m_iCurrentSliderValue = 0;
        ui->ReplaySlider->setValue(0);
        m_lCurrentReplayTime = 0;
        ui->labReplayTime->setText("00:00:00");
        ui->labReplayTotalTime->setText("/00:00:00");
        ui->pbQJVideoRestore->setEnabled(false);
        ui->pbQJVideoRestore->setText("还原");
        ui->pbQJVideoRestore->setChecked(false);
        ui->ReplaySlider->setEnabled(true);
    }break;
    case 4://快放
    {
//        ui->pbVideoPlay->setEnabled(true);
//        ui->pbVideoPlay->setChecked(false);
//        ui->pbVideoFastPlay->setEnabled(true);
//        ui->pbVideoFastPlay->setChecked(false);
        ui->pbVideoSlowPlay->setEnabled(true);
        ui->pbVideoSlowPlay->setChecked(false);
        ui->pbVideoPause->setChecked(false);
        ui->pbVideoPause->setText("暂停");
    }break;
    case 5://慢放
    {
//        ui->pbVideoPlay->setEnabled(true);
//        ui->pbVideoPlay->setChecked(false);
        ui->pbVideoFastPlay->setEnabled(true);
        ui->pbVideoFastPlay->setChecked(false);
//        ui->pbVideoSlowPlay->setEnabled(true);
//        ui->pbVideoSlowPlay->setChecked(false);
        ui->pbVideoPause->setChecked(false);
        ui->pbVideoPause->setText("暂停");
    }break;
    default:
        break;
    }
}

void NVRReplayWgt::slotReadUdpData()
{
    QHostAddress sender;

        quint16 senderPort;

        while(m_pUdpSocketNVR->hasPendingDatagrams())
        {
            QByteArray datagram;

            qint64 nSize = m_pUdpSocketNVR->pendingDatagramSize();
            datagram.resize(static_cast<int>(nSize));

            m_pUdpSocketNVR->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);

            QString str =  datagram.data();
            QString peer = "[From" + sender.toString() + ": " + QString::number(senderPort) + "]";
            qDebug() << peer;
            char *pChar = datagram.data();
            HIMSG_PARAM_S stHIMSG_PARAM_S;
            char cSendBuff[8000];
            QHostAddress     dstRadarCtrlAddr = QHostAddress("127.0.0.1");
            memset(cSendBuff,0,8000);
            memcpy(&stHIMSG_PARAM_S,pChar,sizeof (stHIMSG_PARAM_S));
            switch (stHIMSG_PARAM_S.iInfoId) {
            case REPLAY_CURRENT_POSE:
            {
               qDebug() << "REPLAY_CURRENT_POSE";
               double dCurrentPos = (stHIMSG_PARAM_S.lCurrentReplayPos * 1.0) / (m_lCurrentReplayTotalFrame * 1.0) * 100.0;
               int iCurrentPos = (int)(dCurrentPos);
               qDebug() << "stHIMSG_PARAM_S.lCurrentReplayPos:"<<stHIMSG_PARAM_S.lCurrentReplayPos;
               qDebug() << "m_lCurrentReplayTotalFrame:"<<m_lCurrentReplayTotalFrame;
               qDebug() << "iCurrentPos:"<<iCurrentPos;
               SetReplaySliderCurrentValue(iCurrentPos);

               int iTimeMin = (int)(stHIMSG_PARAM_S.lCurrentReplayPos /60 / 25);
               int iTimeSecond = (int)(stHIMSG_PARAM_S.lCurrentReplayPos /25 % 60);
               QString strDisplayTime;
               strDisplayTime.sprintf("%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
               ui->labReplayTime->setText(strDisplayTime);
            }break;
            case REPLAY_COMPLETE:
            {
                qDebug() << "REPLAY_COMPLETE";
                ChangeReplayPushButtonState(3);

//                char cSendBuff[8000];
//                memset(cSendBuff,0,8000);
//                //    m_stInterCommunication;
//                m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
//                m_stInterCommunication.iReplayState              = 6;
//                memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
//                m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );

            }break;
            case RECORD_CHANGE:
            {
                ManageDiskSpace();
            }break;
            default:
                break;
            }
        }
}

void NVRReplayWgt::on_pbVideoReplay_clicked()
{
    ui->videoReplayWgt->show();
    ui->labVideoDisplay->show();
    ui->ReplayCtrlwgt->show();
    ui->mapRelayWgt->hide();
    ui->logWgt->hide();
}

void NVRReplayWgt::on_pbMapReplay_clicked()
{
    ui->videoReplayWgt->hide();
    ui->labVideoDisplay->hide();
    ui->ReplayCtrlwgt->hide();
    ui->mapRelayWgt->show();
    ui->logWgt->hide();
}

void NVRReplayWgt::on_pbLog_clicked()
{
    ui->videoReplayWgt->hide();
    ui->labVideoDisplay->hide();
    ui->ReplayCtrlwgt->hide();
    ui->mapRelayWgt->hide();
    ui->logWgt->show();
}

//void NVRReplayWgt::on_pbExit_clicked()
//{
//    this->hide();
//}

//播放
void NVRReplayWgt::on_pbVideoPlay_clicked()
{

    QListWidgetItem listWidgetItem;
//    int iCurrentRow = ui->lWgtVideoFile->currentRow();
//    QString strTemp = VIDEO_FILE_PATH + ui->lWgtVideoFile->item(iCurrentRow)->text();
//    QTreeWidgetItem* curItem=ui->treeWidgetVideo->currentItem();
    if(m_strCurrentSelVideoFile.isEmpty())
    {
        qDebug() << "选择文件为空";
        ui->pbVideoPlay->setEnabled(true);
        ui->pbVideoPlay->setChecked(false);
        return;
    }
    qDebug() << "m_strCurrentSelVideoFile" << m_strCurrentSelVideoFile;
    ChangeReplayPushButtonState(1);
//    QString strTemp = VIDEO_FILE_PATH + curItem->text(0) + ".264";
    QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;// + ".264";

    char cSendBuff[8000];
    memset(cSendBuff,0,8000);
//    if(m_bPaulseReplayFlag)
//    {
//        m_stInterCommunication;
//    }
//    else
//    {
//        m_stInterCommunication;
//    }

    ui->labVideoDisplay->hide();

    memset(m_stInterCommunication.cURL_Name,0,1024*sizeof(char));
    m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
    m_stInterCommunication.iReplayState              = 1;
    m_stInterCommunication.lSelReplyStartPos    = m_lCurrentReplayTime;
    m_stInterCommunication.videoNum = 1;
    m_stInterCommunication.stVideoParam[0].s32X = 0;
    m_stInterCommunication.stVideoParam[0].s32Y = 100;
    m_stInterCommunication.stVideoParam[0].u32Width = 1270;
    m_stInterCommunication.stVideoParam[0].u32Height = 982;
    m_stInterCommunication.videoChnIndex[0] = 4;
qDebug() << "m_stInterCommunication.iReplayState：" << m_stInterCommunication.iReplayState;
    memcpy(m_stInterCommunication.cURL_Name,strTemp.toLatin1().data(),512*sizeof(char));
    memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
    m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );

    ui->pbVideoPlay->setEnabled(false);

    m_bPaulseReplayFlag = false;
//    ui->pbVideoPlay
////    QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;
    QString strConfigFile = strTemp.left(strTemp.length()-4) + ".txt";
    QFile replayConfigFile(strConfigFile);
    if (!replayConfigFile.open(QFile::ReadOnly))
    {
        m_lCurrentReplayTotalFrame = 25 * 60 * 30;
    }
    else {
        char cBuff[1024];
        memset(cBuff,0,1024 * sizeof(char));
        Replay_Config_File_Parameter stReplay_Config_File_Parameter;
        memset(&stReplay_Config_File_Parameter,0,sizeof(stReplay_Config_File_Parameter));
        replayConfigFile.read(cBuff,sizeof(stReplay_Config_File_Parameter));
        memcpy(&stReplay_Config_File_Parameter,cBuff,sizeof(stReplay_Config_File_Parameter));
        m_lCurrentReplayTotalFrame = stReplay_Config_File_Parameter.lReplayRecordFrameTotal;
        if(m_lCurrentReplayTotalFrame == 0)
        {
            m_lCurrentReplayTotalFrame = 25 * 60 * 30;
        }
//        replayConfigFile.readLine(ch, sizeof(ch));
//        QString strValue(ch);
//        m_lCurrentReplayTotalFrame = strValue.toULong();
        replayConfigFile.close();
    }

    int iTimeMin = (int)(m_lCurrentReplayTotalFrame /60 / 25);
    int iTimeSecond = (int)(m_lCurrentReplayTotalFrame /25 % 60);
    QString strDisplayTime;
    strDisplayTime.sprintf("/%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
    qDebug() << "1strDisplayTime：" << strDisplayTime;

    ui->labReplayTotalTime->setText(strDisplayTime);
}

//暂停
void NVRReplayWgt::on_pbVideoPause_clicked()
{
//    m_bPaulseReplayFlag = true;
//    char cSendBuff[8000];
//    memset(cSendBuff,0,8000);
//    m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
//    m_stInterCommunication.iReplayState              = 1;
////    m_stInterCommunication;
//    memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
//    m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );
}

void NVRReplayWgt::StopReplay()
{
    ui->labVideoDisplay->show();
    on_pbVideoStop_clicked();
}

//停止
void NVRReplayWgt::on_pbVideoStop_clicked()
{
    ChangeReplayPushButtonState(3);
    char cSendBuff[8000];
    memset(cSendBuff,0,8000);
    //    m_stInterCommunication;
    m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
    m_stInterCommunication.iReplayState              = 6;
    memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
    m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );

    ui->pbVideoPlay->setEnabled(true);
    ui->pbVideoPlay->setChecked(false);
}

void NVRReplayWgt::on_pbVideoFastPlay_clicked(bool checked)
{
    ChangeReplayPushButtonState(4);
    char cSendBuff[8000];
    memset(cSendBuff,0,8000);

    //    m_stInterCommunication;
    m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
    if(checked == true)
    {
        m_stInterCommunication.iReplayState              = 4;
    }
    else
    {
        m_stInterCommunication.iReplayState              = 7;
    }
    memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
    m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );
}

void NVRReplayWgt::on_pbVideoSlowPlay_clicked(bool checked)
{
    ChangeReplayPushButtonState(5);
    char cSendBuff[8000];
    memset(cSendBuff,0,8000);
    //    m_stInterCommunication;
    m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
    if(checked == true)
    {
        m_stInterCommunication.iReplayState              = 5;
    }
    else
    {
        m_stInterCommunication.iReplayState              = 7;       
    }
    memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
    m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );


}

void NVRReplayWgt::on_pbVideoSlowPlay_clicked()
{
}

void NVRReplayWgt::on_pbVideoPause_clicked(bool checked)
{
    ChangeReplayPushButtonState(2);
    if(checked == true)
    {
        m_bPaulseReplayFlag = false;
        ui->pbVideoPause->setText("继续");
        char cSendBuff[8000];
        memset(cSendBuff,0,8000);
        m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
        m_stInterCommunication.iReplayState              = 2;
        memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
        m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );
    }
    else
    {
        m_bPaulseReplayFlag = true;
        ui->pbVideoPause->setText("暂停");
        char cSendBuff[8000];
        memset(cSendBuff,0,8000);
        m_stInterCommunication.iInfoId                   = REPLAY_CONTRL_FUNCITON;
        m_stInterCommunication.iReplayState              = 3;
        memcpy(cSendBuff,&m_stInterCommunication,sizeof(m_stInterCommunication));
        m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(m_stInterCommunication), m_dstRadarCtrlAddr, m_detPort );
    }
}

void NVRReplayWgt::SetReplaySliderCurrentValue(int iValue)
{
    ui->ReplaySlider->setValue(iValue);
}

void NVRReplayWgt::on_ReplaySlider_sliderReleased()
{
//    m_iCurrentSliderValue = ui->ReplaySlider->value();
//    qDebug() << "m_iCurrentSliderValue:" <<m_iCurrentSliderValue;
//    double dCurrentReplayTime;
//    dCurrentReplayTime = m_lCurrentReplayTotalFrame * m_iCurrentSliderValue / 100.0;

//    long lCurrentReplayTime = long(dCurrentReplayTime + 0.5);
//    int iTimeMin = (int)(lCurrentReplayTime /60 / 25);
//    int iTimeSecond = (int)(lCurrentReplayTime /25 % 60);
//    QString strDisplayTime;
//    strDisplayTime.sprintf("%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
//    qDebug() << "strDisplayTime：" << strDisplayTime;

//    ui->labReplayTime->setText(strDisplayTime);
}

void NVRReplayWgt::on_ReplaySlider_valueChanged(int value)
{
    ui->ReplaySlider->setValue(value);
    qDebug() << "on_ReplaySlider_valueChanged:" << value;
    if(m_bCurrentReplyState == false)
    {
        m_iCurrentSliderValue = ui->ReplaySlider->value();
        qDebug() << "m_iCurrentSliderValue:" <<m_iCurrentSliderValue;
        double dCurrentReplayTime;
        dCurrentReplayTime = m_lCurrentReplayTotalFrame * m_iCurrentSliderValue / 100.0;

        m_lCurrentReplayTime = long(dCurrentReplayTime + 0.5);
        int iTimeMin = (int)(m_lCurrentReplayTime /60 / 25);
        int iTimeSecond = (int)(m_lCurrentReplayTime /25 % 60);
        QString strDisplayTime;
        strDisplayTime.sprintf("%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
        qDebug() << "2strDisplayTime：" << strDisplayTime;

        ui->labReplayTime->setText(strDisplayTime);
    }
}

void NVRReplayWgt::on_pbVideoFind_clicked()
{
//    ui->lWgtVideoFile
//    QDir videoDir("./videos/");
//    QStringList logFileNames = videoDir.entryList(QStringList("*.264"), QDir::Files, QDir::Time);
//    ui->lWgtVideoFile->addItems(logFileNames);

//    QString format("yyyyMMdd_hhmmss");
//    QDateTime::fromString("",format);
//    QDir videoDir("./videos/");
//    ui->lWgtVideoFile->clear();
    QDateTime CurrentDateTime      = QDateTime::currentDateTime();

    ui->treeWidgetVideo->clear();
    for (int i = 0;i < VIDEO_CHANNEL_NUMBER;i++) {
         m_rootTreeWidgetItem[i] = new QTreeWidgetItem(ui->treeWidgetVideo);
         QString strTempName;
//         strTempName.sprintf("%d通道视频",i);
         switch (i) {
         case 0:
         {
             strTempName = "全景视频1";
         }break;
         case 1:
         {
             strTempName = "全景视频2";
         }break;
         case 2:
         {
             strTempName = "周视红外";
         }break;
         case 3:
         {
             strTempName = "周视可见光";
         }break;
         default:
         {
             strTempName = "其他";
         }break;
         }
         m_rootTreeWidgetItem[i]->setText(0,strTempName);
         ui->treeWidgetVideo->addTopLevelItem(m_rootTreeWidgetItem[i]);
    }
//    qDebug() << "clear tree";
    QDir videoDir(VIDEO_FILE_PATH);
    QFileInfo fileInfo;
    QStringList strlistFilter;
    strlistFilter << QStringList("*.264") << QStringList("*.avi");
    QFileInfoList fileInfoList = videoDir.entryInfoList(strlistFilter, QDir::Files, QDir::Time);//QStringList("*.264")

    QDateTime lastModifiedTime(QDate(0,0,0));

    int iFindOptionIndex = ui->combVideoFindOption->currentIndex();
//    lastModifiedTime = fileInfoList.first().lastModified().toLocalTime();
    QDateTime tempDateTime = ui->dateEdit_video->dateTime();
    QDate tempDate = tempDateTime.date();
    int i = 0;
    QStringList strListfileName;
    QString strTempName,strChannelName;
    QString strChannelNum;
    qint64 intervalTime;
    bool bFilterFlag;


    while(i < fileInfoList.length())
    {
        fileInfo = fileInfoList.at(i);
        qDebug() <<"filename:" <<  fileInfo.fileName();
        lastModifiedTime = fileInfo.lastModified().toLocalTime();
        intervalTime = lastModifiedTime.secsTo(CurrentDateTime);//lqr 20220427
        qDebug() << "intervalTime:" << intervalTime;
        bFilterFlag = true;
        if((intervalTime < 1800) && (intervalTime >= 0))
        {
            QByteArray qbyteArr;
            strTempName = VIDEO_FILE_PATH + fileInfo.fileName();
            qbyteArr.append(strTempName);
            const char *cFileNme = qbyteArr.data();
            FILE* pFile;
            if ((pFile = fopen(cFileNme, "rb")) != NULL)
            {
                qDebug() << "FilterFile:" << strTempName;
                bFilterFlag = false;
                fclose(pFile);
            }
        }
        if((tempDate == lastModifiedTime.date() || iFindOptionIndex == 0) && (bFilterFlag))
        {
            strListfileName.append(fileInfo.fileName());
            strTempName = fileInfo.fileName();
            strChannelName = strTempName;
            strChannelName = strTempName.left(strTempName.length() - 4);
            strChannelNum = strChannelName.right(1);
            int iChannelNum = strChannelNum.toInt();
            if(iChannelNum >= 0 && iChannelNum < VIDEO_CHANNEL_NUMBER)
            {
//                qDebug() << "iChannelNum:" << iChannelNum;
                QTreeWidgetItem *iTem = new QTreeWidgetItem();
//                qDebug() << "strTempName:" << strTempName;
                iTem->setText(0,strTempName);
//                qDebug() << "iTem:" << iTem->text(0);
                m_rootTreeWidgetItem[iChannelNum]->addChild(iTem);
//                qDebug() << "addChild(iTem)";
            }
        }
        i++;
    }

//    if(!strListfileName.isEmpty())
//    {
////        ui->lWgtVideoFile->addItems(strListfileName);
//        ;
//    }
}

void NVRReplayWgt::on_pbVideoClear_clicked()
{
//    ui->lWgtVideoFile->clear();
    ui->treeWidgetVideo->clear();
    for (int i = 0;i < VIDEO_CHANNEL_NUMBER;i++) {
         m_rootTreeWidgetItem[i] = new QTreeWidgetItem(ui->treeWidgetVideo);
         QString strTempName;
         strTempName.sprintf("%d通道视频",i);
         m_rootTreeWidgetItem[i]->setText(0,strTempName);
         ui->treeWidgetVideo->addTopLevelItem(m_rootTreeWidgetItem[i]);
    }

    //删除item
//    QTreeWidgetItem* curItem=treeWidget->currentItem();
//    curItem->parent()->removeChild(treeWidget->currentItem());
}

void NVRReplayWgt::on_lWgtMapFile_itemDoubleClicked(QListWidgetItem *item)
{
//    QString fileName = "./maps/" + item->text() +".jpg"; +".png"
    QString fileName = MAP_FILE_PATH + item->text();

    if(!(m_loadImage->load(fileName)))
    {
        qDebug() << "can not load map!";
        return;
    }
    m_iProcessWidth = ui->labMapDisplay->width();
    m_iProcessHeight = ui->labMapDisplay->height();
    *m_loadImage = m_loadImage->scaled(m_iProcessWidth,m_iProcessHeight,Qt::KeepAspectRatio);
    m_processedImage = *m_loadImage;
//    QImage *scaledImage;
//    *scaledImage = image->scaled(640,480,Qt::KeepAspectRatio);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
}

void NVRReplayWgt::on_lWgtMapFile_currentTextChanged(const QString &currentText)
{
//    QString fileName = "./maps/" +currentText +".jpg";

//    if(!(m_loadImage->load(fileName)))
//    {
//        return;
//    }
//    m_processedImage = *m_loadImage;
////    QImage *scaledImage;
////    *scaledImage = image->scaled(640,480,Qt::KeepAspectRatio);
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*scaledImage)));

//    //水平翻转
//    *m_loadImage = m_loadImage->mirrored(true,false);
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
//    //垂直翻转
//    *m_loadImage = m_loadImage->mirrored(false,true);
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
//    //旋转90度
//    QMatrix matrix;
//    matrix.rotate(90.0);
//    *m_loadImage = m_loadImage->transformed(matrix,Qt::FastTransformation);
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
//    //逆时针旋转45度
////    QMatrix matrix;
//    matrix.rotate(-45.0);
//    *m_loadImage = m_loadImage->transformed(matrix,Qt::FastTransformation);
//    ui->labMapDisplay->setPixmap(QPixmap::fromImage((*m_loadImage)));
}

//放大
void NVRReplayWgt::on_pbMagnify_clicked()
{
    if(m_processedImage.isNull())
    {
        return;
    }
//    int iWidth = m_processedImage.width();
//    int iHeight = m_processedImage.height();
//    qDebug() << "iWidth:" << iWidth << " iHeight:" << iHeight;
//    iWidth = iWidth+20;
//    iHeight =iHeight+20;
//    if(iWidth > 1600)
//    {
//        iWidth = 1600;
//    }
//    if(iHeight > 1200)
//    {
//        iHeight = 1200;
//    }
    QImage Image;
    m_iProcessWidth = m_iProcessWidth + 20;
    m_iProcessHeight = m_iProcessHeight + 20;
    qDebug() << "m_iProcessWidth" << m_iProcessWidth;
    qDebug() << "m_iProcessHeight" << m_iProcessHeight;
    if(m_iProcessWidth > 1600)
    {
        m_iProcessWidth = 1600;
    }
    if(m_iProcessHeight > 1200)
    {
        m_iProcessHeight = 1200;
    }
    m_processedImage= m_loadImage->scaled(m_iProcessWidth,m_iProcessHeight,Qt::KeepAspectRatio);

//    //高宽均为原来的2倍
//    QMatrix matrix;
//    matrix.scale(2,2);
//    m_processedImage = m_processedImage.transformed(matrix);

    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

//缩小
void NVRReplayWgt::on_pbShrink_clicked()
{
    if(m_processedImage.isNull())
    {
        return;
    }
//    int iWidth = m_processedImage.width();
//    int iHeight = m_processedImage.height();
//    qDebug() << "iWidth:" << iWidth << " iHeight:" << iHeight;
//    iWidth = iWidth-20;
//    iHeight =iHeight-20;
//    if(iWidth < 640)
//    {
//        iWidth = 640;
//    }
//    if(iHeight < 480)
//    {
//        iHeight = 480;
//    }
    QImage Image;
    m_iProcessWidth = m_iProcessWidth - 20;
    m_iProcessHeight = m_iProcessHeight - 20;
    qDebug() << "m_iProcessWidth" << m_iProcessWidth;
    qDebug() << "m_iProcessHeight" << m_iProcessHeight;
    if(m_iProcessWidth < 640)
    {
        m_iProcessWidth = 640;
    }
    if(m_iProcessHeight < 480)
    {
        m_iProcessHeight = 480;
    }
    m_processedImage= m_loadImage->scaled(m_iProcessWidth,m_iProcessHeight,Qt::KeepAspectRatio);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

//翻转
void NVRReplayWgt::on_pbRotate_clicked()
{
    if(m_processedImage.isNull())
    {
        return;
    }
    QMatrix matrix;
    //逆时针旋转45度
//    matrix.rotate(-45.0);
    //旋转90度
    matrix.rotate(90.0);
    m_processedImage = m_processedImage.transformed(matrix,Qt::FastTransformation);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

void NVRReplayWgt::on_pbTurnLeft_clicked()
{
    if(m_processedImage.isNull())
    {
        qDebug() << "TurnLeft_m_processedImageisNull";
        return;
    }
    //平移
    QMatrix matrix;
    matrix.translate(35,0);
    m_processedImage = m_processedImage.transformed(matrix);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
    qDebug() << "TurnLeft_clicked()";
//    ui->labMapDisplay->move(35,0)
}

void NVRReplayWgt::on_pbTurnRight_clicked()
{
    //平移
    QMatrix matrix;
    matrix.translate(-5,0);
    m_processedImage = m_processedImage.transformed(matrix);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

void NVRReplayWgt::on_pbTurnUp_clicked()
{
    //平移
    QMatrix matrix;
    matrix.translate(0,5);
    m_processedImage = m_processedImage.transformed(matrix);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

void NVRReplayWgt::on_pbTurnDown_clicked()
{
    //平移
    QMatrix matrix;
    matrix.translate(0,-5);
    m_processedImage = m_processedImage.transformed(matrix);
    ui->labMapDisplay->setPixmap(QPixmap::fromImage((m_processedImage)));
}

void NVRReplayWgt::on_pbMapFind_clicked()
{
    ui->lWgtMapFile->clear();
//    QDir videoDir("./maps/");
    QDir videoDir(MAP_FILE_PATH);
    QFileInfo fileInfo;
    QFileInfoList fileInfoList = videoDir.entryInfoList(QStringList("*.jpg"), QDir::Files, QDir::Time);

    QDateTime lastModifiedTime(QDate(0,0,0));

    int iFindOptionIndex = ui->combMapFindOption->currentIndex();
//    lastModifiedTime = fileInfoList.first().lastModified().toLocalTime();
    QDateTime tempDateTime = ui->dateEdit_map->dateTime();
    QDate tempDate = tempDateTime.date();
    int i = 0;
    QStringList strListfileName;
    while(i < fileInfoList.length())
    {
        fileInfo = fileInfoList.at(i);
//        fileInfo.fileName();
        lastModifiedTime = fileInfo.lastModified().toLocalTime();
        if(tempDate == lastModifiedTime.date() || iFindOptionIndex == 0)
        {
            strListfileName.append(fileInfo.fileName());
        }
        i++;
    }

    if(!strListfileName.isEmpty())
    {
        ui->lWgtMapFile->addItems(strListfileName);
    }
}

void NVRReplayWgt::on_pbMapClear_clicked()
{
    ui->lWgtMapFile->clear();
}

void NVRReplayWgt::on_lWgtLogFile_itemDoubleClicked(QListWidgetItem *item)
{
//    QString strTempFileName = "./logs/" +item->text()+".log";
    QString strTempFileName = LOG_FILE_PATH +item->text();//+".log"
    qDebug() << "strTempFileName" << strTempFileName;
    QFile logFile(strTempFileName);
//    logFile.open(QIODevice::ReadOnly);

//    //读取最后一行
//    int iLen = logFile.size();
//    int i = 3;
//    logFile.seek(iLen -i);
//    while (!QString(logFile.readLine()).compare("\n") == 0) {
//        i++;
//        logFile.seek(iLen - i);
//    }
//    QString strlastLine = logFile.readLine().trimmed();
//    int data2 = strlastLine.split(",")[1].toInt();
    if(logFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ui->logTableWgt->clearContents();
//        int iRowCount = ui->logTableWgt->rowCount();
//        m_stdItemModel->clear();
//        m_stdItemModel->setHorizontalHeaderLabels(m_strListLabels);
//        ui->logTable->setModel(m_stdItemModel);
//        ui->logTableWgt->setHorizontalHeaderLabels(m_strListLabels);
        int iRow = 0;
        QString strDataLine;
        QTextStream in(&logFile);//用文件构造流
//        QStandardItem *stdItem;
        strDataLine = in.readLine();//读取一行放到字符串里
        qDebug() << "strDataLine" << strDataLine;

        while (!strDataLine.isNull()) {
//            stdItem = new QStandardItem(strDataLine);
//            m_stdItemModel->setItem(iRow, 1, stdItem);
            if(iRow > (ui->logTableWgt->rowCount() -1))
            {
                ui->logTableWgt->insertRow(iRow);
            }
//            ui->logTableWgt->setItem(iRow,0,new QTableWidgetItem(QString::number(iRow)));
            ui->logTableWgt->setItem(iRow,0,new QTableWidgetItem(strDataLine));
            strDataLine = in.readLine();
            qDebug() << "strDataLine2" << strDataLine;
            iRow++;
        }
    }
    logFile.close();
}

void NVRReplayWgt::on_pbLogFind_clicked()
{
    ui->lWgtLogFile->clear();
    QString strTemp = {"查询操作！"};
//    LOG_INFO("Device_log", "strTemp.toStdString()");
    QByteArray ba = QString::fromLatin1("查询操作！").toLatin1();
    LOG_INFO("Device_log", ba.data());
    int iFindOptionIndex = ui->combLogFindOption->currentIndex();
//    Logger::flush();
//    QDir videoDir("./logs/");
    QDir videoDir(LOG_FILE_PATH);
    QFileInfo fileInfo;
    QFileInfoList fileInfoList = videoDir.entryInfoList(QStringList("*"), QDir::Files, QDir::Time);

    QDateTime lastModifiedTime(QDate(0,0,0));

//    lastModifiedTime = fileInfoList.first().lastModified().toLocalTime();
    QDateTime tempDateTime = ui->dateEdit_log->dateTime();
    QDate tempDate = tempDateTime.date();
    int i = 0;
    QStringList strListfileName;
    while(i < fileInfoList.length())
    {
        fileInfo = fileInfoList.at(i);
//        fileInfo.fileName();
        lastModifiedTime = fileInfo.lastModified().toLocalTime();
        qDebug() << "fileInfo.fileName() :" << fileInfo.fileName();
        if(tempDate == lastModifiedTime.date() || iFindOptionIndex == 0)
        {
            strListfileName.append(fileInfo.fileName());
        }
        i++;
    }

    if(!strListfileName.isEmpty())
    {
        ui->lWgtLogFile->addItems(strListfileName);
    }
}

void NVRReplayWgt::on_pbLogClear_clicked()
{
    ui->lWgtLogFile->clear();
}

bool NVRReplayWgt::DeleteDir(const QString &dirName)
{
    QDir directory(dirName);
    if(!directory.exists())
    {
        return true;
    }
    QString srcPath=QDir::toNativeSeparators(dirName);
    if(!srcPath.endsWith(QDir::separator()))
    {
        srcPath +=QDir::separator();
    }
    QStringList fileNames=directory.entryList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::Hidden);
    bool error=false;
    for(QStringList::size_type i=0;i!=fileNames.size();++i)
    {
        QString filepath=srcPath+fileNames.at(i);
        QFileInfo fileInfo(filepath);
        if(fileInfo.isFile()||fileInfo.isSymLink())
        {
            QFile::setPermissions(filepath,QFile::WriteOwner);
            if(!QFile::remove(filepath))
            {
                //qDebug()<<"remove "<<filepath<<"failed";
                error=true;
            }
//            QFile::copy();// 拷贝文件
        }
        else if(fileInfo.isDir())
        {
            if(!DeleteDir(filepath))
            {
                error=true;
            }
        }
    }
    if(!directory.rmdir(QDir::toNativeSeparators(directory.path())))
    {
        //qDebug()<<"remove dir"<<directory.path()<<"failed";
         error=true;
    }
    return !error;
}

void NVRReplayWgt::slotItemClicked(QTreeWidgetItem *item,int index)
{
    QTreeWidgetItem *parent = NULL;
    m_strCurrentSelVideoFile = "";
    parent = item->parent();
    LastSelectitem = item;
    LastSelectIndex = index;
    if(NULL != parent)
    {
        m_strCurrentSelVideoFile = item->text(index);

        if(m_bCurrentReplyState == false)
        {
            QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;
            QString strConfigFile = strTemp.left(strTemp.length()-4) + ".txt";
            QFile replayConfigFile(strConfigFile);
            qDebug() << "strConfigFile" << strConfigFile;

            if (!replayConfigFile.open(QFile::ReadOnly))
            {
                m_lCurrentReplayTotalFrame = 25 * 60 * 30;
            }
            else {
                char cBuff[1024];
                memset(cBuff,0,1024 * sizeof(char));
                Replay_Config_File_Parameter stReplay_Config_File_Parameter;
                memset(&stReplay_Config_File_Parameter,0,sizeof(stReplay_Config_File_Parameter));
                replayConfigFile.read(cBuff,sizeof(stReplay_Config_File_Parameter));
                memcpy(&stReplay_Config_File_Parameter,cBuff,sizeof(stReplay_Config_File_Parameter));
                m_lCurrentReplayTotalFrame = stReplay_Config_File_Parameter.lReplayRecordFrameTotal;
                if(m_lCurrentReplayTotalFrame == 0)
                {
                    m_lCurrentReplayTotalFrame = 25 * 60 * 30;
                }
                //        replayConfigFile.readLine(ch, sizeof(ch));
                //        QString strValue(ch);
                //        m_lCurrentReplayTotalFrame = strValue.toULong();
                replayConfigFile.close();
            }

            int iTimeMin = (int)(m_lCurrentReplayTotalFrame /60 / 25);
            int iTimeSecond = (int)(m_lCurrentReplayTotalFrame /25 % 60);
            QString strDisplayTime;
            strDisplayTime.sprintf("/%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
            qDebug() << "3strDisplayTime：" << strDisplayTime;

            ui->labReplayTotalTime->setText(strDisplayTime);

            ui->ReplaySlider->setValue(0);
            m_lCurrentReplayTime = 0;
        }
    }
}

/**************************************************************************
*函数名称:
*函数输入:
*函数输出:
*返 回 值:
*函数说明: 可用空间大小 以MB为单位
**************************************************************************/
void NVRReplayWgt::GetDiskSpace(char *szPath, uint32_t &u32TotalSize, uint32_t &u32AvailableSize)
{
    /// 用于获取磁盘剩余空间
    struct statfs diskInfo;

    statfs(szPath, &diskInfo);

    unsigned long long blocksize = diskInfo.f_bsize;	                 //每个block里包含的字节数
    unsigned long long totalsize = blocksize * diskInfo.f_blocks; 	     //总的字节数，f_blocks为block的数目

    printf(" Total_size = %llu B = %llu KB = %llu MB = %llu GB\n",
           totalsize, totalsize>>10, totalsize>>20, totalsize>>30);

    u32TotalSize = (totalsize >> 20);

    unsigned long long freeDisk  = diskInfo.f_bfree * blocksize;	    //剩余空间的大小
    unsigned long long availableDisk  = diskInfo.f_bavail * blocksize; 	//可用空间大小

    printf(" Disk_free = %llu MB = %llu GB\n Disk_available = %llu MB = %llu GB\n",
           freeDisk >> 20, freeDisk >> 30, availableDisk >> 20, availableDisk >> 30);

    u32AvailableSize =  (availableDisk >> 20);
}

int NVRReplayWgt::DeleteOldestFiles(char *FilePath,int iFilterFlag)
{
    std::list<string> lstFiles;

    GetAllFiles(FilePath, lstFiles);

    if(lstFiles.empty() || ((iFilterFlag == 1) && (lstFiles.size() <= 5)))
    {
        return -1;
    }

    lstFiles.sort();

    remove(lstFiles.front().data());

    return lstFiles.size();
}

void NVRReplayWgt::ManageDiskSpace()
{
    char szTFPath[256] = "/mnt/";

    uint32_t u32TotalSize = 0;
    uint32_t u32AvailableSize = 0;

    GetDiskSpace(szTFPath, u32TotalSize, u32AvailableSize);

    //
    if(u32TotalSize < 1024) //TF卡没挂上
    {
        return;
    }

    //空间不足，删除最老的文件
    while (u32AvailableSize < 5120)
    {
        char FilePath[256] = {0};


        sprintf(FilePath, "/mnt/video");
        DeleteOldestFiles(FilePath);
        sprintf(FilePath, "/mnt/map");
        DeleteOldestFiles(FilePath,1);
        sprintf(FilePath, "/mnt/log");
        DeleteOldestFiles(FilePath,1);

        GetDiskSpace(szTFPath, u32TotalSize, u32AvailableSize);
    }
}

//获取所有的文件名
void NVRReplayWgt::GetAllFiles(string path, list<string>& filenames)
{
    DIR *pDir;

    struct dirent* ptr;

    if(!(pDir = opendir(path.c_str())))
    {
        return;
    }

    while((ptr = readdir(pDir))!=0)
    {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
        {
            filenames.push_back(path + "/" + ptr->d_name);
        }
    }

    closedir(pDir);
}

void NVRReplayWgt::on_pbQJVideoRestore_clicked(bool checked)
{
    char cSendBuff[8000];
    memset(cSendBuff,0,8000);
    if(checked == true)
    {
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = 4;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 400;
        hsmsg.stVideoParam[0].u32Width  = 1270;
        hsmsg.stVideoParam[0].u32Height = 382;

        memcpy(cSendBuff,&hsmsg,sizeof(hsmsg));
        m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(hsmsg), m_dstRadarCtrlAddr, m_detPort );

        ui->pbQJVideoRestore->setText("放大");
    }
    else
    {
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = 4;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 100;
        hsmsg.stVideoParam[0].u32Width  = 1270;
        hsmsg.stVideoParam[0].u32Height = 982;

        memcpy(cSendBuff,&hsmsg,sizeof(hsmsg));
        m_pUdpSocketNVR->writeDatagram(cSendBuff,sizeof(hsmsg), m_dstRadarCtrlAddr, m_detPort );
        ui->pbQJVideoRestore->setText("还原");
    }
}

void NVRReplayWgt::on_ReplaySlider_sliderPressed()
{
//    QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;
//    QString strConfigFile = strTemp.left(strTemp.length()-4) + ".txt";
//    QFile replayConfigFile(strConfigFile);
//    if (!replayConfigFile.open(QFile::ReadOnly))
//    {
//        m_lCurrentReplayTotalFrame = 25 * 60 * 30;
//    }
//    else {
//        char cBuff[1024];
//        memset(cBuff,0,1024 * sizeof(char));
//        Replay_Config_File_Parameter stReplay_Config_File_Parameter;
//        memset(&stReplay_Config_File_Parameter,0,sizeof(stReplay_Config_File_Parameter));
//        replayConfigFile.read(cBuff,sizeof(stReplay_Config_File_Parameter));
//        memcpy(&stReplay_Config_File_Parameter,cBuff,sizeof(stReplay_Config_File_Parameter));
//        m_lCurrentReplayTotalFrame = stReplay_Config_File_Parameter.lReplayRecordFrameTotal;
//        if(m_lCurrentReplayTotalFrame == 0)
//        {
//            m_lCurrentReplayTotalFrame = 25 * 60 * 30;
//        }
//        //        replayConfigFile.readLine(ch, sizeof(ch));
//        //        QString strValue(ch);
//        //        m_lCurrentReplayTotalFrame = strValue.toULong();
//        replayConfigFile.close();
//    }

//    int iTimeMin = (int)(m_lCurrentReplayTotalFrame /60 / 25);
//    int iTimeSecond = (int)(m_lCurrentReplayTotalFrame /25 % 60);
//    QString strDisplayTime;
//    strDisplayTime.sprintf("/%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
//    qDebug() << "strDisplayTime：" << strDisplayTime;

//    ui->labReplayTotalTime->setText(strDisplayTime);
}

void NVRReplayWgt::on_ReplaySlider_actionTriggered(int action)
{
    if(!m_strCurrentSelVideoFile.isEmpty())
    {
        if(m_strSelCurrentFile != m_strCurrentSelVideoFile)
        {
            m_strSelCurrentFile =m_strCurrentSelVideoFile;
        }
        else
        {
            return;
        }
        QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;
        QString strConfigFile = strTemp.left(strTemp.length()-4) + ".txt";
        QFile replayConfigFile(strConfigFile);
        if (!replayConfigFile.open(QFile::ReadOnly))
        {
            m_lCurrentReplayTotalFrame = 25 * 60 * 30;
        }
        else {
            char cBuff[1024];
            memset(cBuff,0,1024 * sizeof(char));
            Replay_Config_File_Parameter stReplay_Config_File_Parameter;
            memset(&stReplay_Config_File_Parameter,0,sizeof(stReplay_Config_File_Parameter));
            replayConfigFile.read(cBuff,sizeof(stReplay_Config_File_Parameter));
            memcpy(&stReplay_Config_File_Parameter,cBuff,sizeof(stReplay_Config_File_Parameter));
            m_lCurrentReplayTotalFrame = stReplay_Config_File_Parameter.lReplayRecordFrameTotal;
            if(m_lCurrentReplayTotalFrame == 0)
            {
                m_lCurrentReplayTotalFrame = 25 * 60 * 30;
            }
            //        replayConfigFile.readLine(ch, sizeof(ch));
            //        QString strValue(ch);
            //        m_lCurrentReplayTotalFrame = strValue.toULong();
            replayConfigFile.close();
        }

        int iTimeMin = (int)(m_lCurrentReplayTotalFrame /60 / 25);
        int iTimeSecond = (int)(m_lCurrentReplayTotalFrame /25 % 60);
        QString strDisplayTime;
        strDisplayTime.sprintf("/%02d:%02d:%02d",0,iTimeMin,iTimeSecond);
        qDebug() << "strDisplayTime：" << strDisplayTime;

        ui->labReplayTotalTime->setText(strDisplayTime);
    }
}

void NVRReplayWgt::on_pbFileCpy_clicked()
{
    char szCmd[1024] = {0};

    m_strCurrentSelVideoFile = "";
    if(NULL != LastSelectitem)
    {
        m_strCurrentSelVideoFile = LastSelectitem->text(LastSelectIndex);

        if(m_bCurrentReplyState == false)
        {
            QString strTemp = VIDEO_FILE_PATH + m_strCurrentSelVideoFile;
            QString strCpFile = "echo \"cp " + strTemp.left(strTemp.length()-6) +"* /usb &\" >./cpcmd.sh";
            qDebug() << "strCpFile" << strCpFile;
            system(strCpFile.toStdString().c_str());
            system("chmod +x ./cpcmd.sh");
            system("./cpcmd.sh");
            system("sync");
            //QMessageBox::information(NULL, "提示", "拷贝已完成！", QMessageBox::Yes, QMessageBox::Yes);
        }
    }

//    for (int i = 0;i < VIDEO_CHANNEL_NUMBER;i++) {
//        if(m_rootTreeWidgetItem[i]->)

//         QString strTempName;
////         strTempName.sprintf("%d通道视频",i);
//         switch (i) {
//         case 0:
//         {
//             strTempName = "全景视频1";
//         }break;
//         case 1:
//         {
//             strTempName = "全景视频2";
//         }break;
//         case 2:
//         {
//             strTempName = "周视红外";
//         }break;
//         case 3:
//         {
//             strTempName = "周视可见光";
//         }break;
//         default:
//         {
//             strTempName = "其他";
//         }break;
//         }
//         m_rootTreeWidgetItem[i]->setText(0,strTempName);
//         ui->treeWidgetVideo->addTopLevelItem(m_rootTreeWidgetItem[i]);
//    }

}


void NVRReplayWgt::on_pbFileCpyMap_clicked()
{
    if(!m_strSelMapFileName.isEmpty())
    {
        QString strCpFile = "echo \"cp " + m_strSelMapFileName +" /usb &\" >./cpcmd.sh";
        qDebug() << "strCpFile" << strCpFile;
        system(strCpFile.toStdString().c_str());
        system("chmod +x ./cpcmd.sh");
        system("./cpcmd.sh");
        system("sync");
        //QMessageBox::information(NULL, "提示", "拷贝已完成！", QMessageBox::Yes, QMessageBox::Yes);

    }
}

void NVRReplayWgt::on_pbFileCpyLog_clicked()
{
//   ui->lWgtLogFile->currentItem()->text();
   if(!m_strSelLogFileName.isEmpty())
   {
       QString strCpFile = "echo \"cp " + m_strSelLogFileName +" /usb &\" >./cpcmd.sh";
       qDebug() << "strCpFile" << strCpFile;
       system(strCpFile.toStdString().c_str());
       system("chmod +x ./cpcmd.sh");
       system("./cpcmd.sh");
       system("sync");
       //QMessageBox::information(NULL, "提示", "拷贝已完成！", QMessageBox::Yes, QMessageBox::Yes);

   }
}

void NVRReplayWgt::on_lWgtLogFile_itemClicked(QListWidgetItem *item)
{
    QString strTempFileName = LOG_FILE_PATH +item->text();//+".log"
    qDebug() << "on_lWgtLogFile_itemClicked:strTempFileName" << strTempFileName;
    m_strSelLogFileName = strTempFileName;
}

void NVRReplayWgt::on_lWgtMapFile_itemClicked(QListWidgetItem *item)
{
    QString fileName = MAP_FILE_PATH + item->text();
    qDebug() << "on_lWgtLogFile_itemClicked:fileName" << fileName;
    m_strSelMapFileName = fileName;
}
