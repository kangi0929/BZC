#include "interfacechange.h"
#include <QThread>

InterfaceChange::InterfaceChange()
{
    m_udp = new QUdpSocket();
}

InterfaceChange::~InterfaceChange()
{
    delete m_udp;
}

void InterfaceChange::change(ShowType st)
{
    switch(st)
    {
    case FirstPage:
    {
        break;
    }
    case QJ1ZoomIn:
    {
        //先显示全景的一路
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ1VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = QJ_HEIGHT;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }
        qDebug() << hsmsg.iInfoId << " " << hsmsg.videoNum << " " << hsmsg.videoChnIndex[0] << " "
        << hsmsg.stVideoParam[0].s32X << " " << hsmsg.stVideoParam[0].s32Y << " " << hsmsg.stVideoParam[0].u32Width
        << " " << hsmsg.stVideoParam[0].u32Height << " A";
        QThread::msleep(20);
        //然后再显示前面1600的部分
        //HIMSG_PARAM_S hsmsg;
       hsmsg.iInfoId = _QJ_Inter_;
       hsmsg.videoNum = 1;
       hsmsg.videoChnIndex[0] = QJ1VIDEO;
       hsmsg.stVideoParam[0].s32X      = 0;
       hsmsg.stVideoParam[0].s32Y      = 0;
       hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
       hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
       pHs                        = (char *)&hsmsg;
       len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
       if (len == -1)
       {
           qDebug() << "QJ1ZoomIn send Error";
       }

        qDebug() << hsmsg.iInfoId << " " << hsmsg.videoNum << " " << hsmsg.videoChnIndex[0] << " "
       << hsmsg.stVideoParam[0].s32X << " " << hsmsg.stVideoParam[0].s32Y << " " << hsmsg.stVideoParam[0].u32Width
       << " " << hsmsg.stVideoParam[0].u32Height << " B";

        break;
    }
    case QJ2ZoomIn:
    {
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ2VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = QJ_HEIGHT;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ2ZoomIn send Error";
        }

        //然后再显示前面1600的部分
        hsmsg.iInfoId = _QJ_Inter_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ2VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
        pHs                        = (char *)&hsmsg;
        len = m_udp->writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }

        break;
    }
    case SecondPage:
        break;
    }
}
