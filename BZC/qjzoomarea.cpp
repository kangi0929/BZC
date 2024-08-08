#include "qjzoomarea.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QThread>

const QString QjZoomArea::QJ1 = "Qj1";
const QString QjZoomArea::QJ2 = "Qj2";
const double QjZoomArea::widthScale = (1.0 * VIDEO_WIDTH / QJ_WIDTH);
const double QjZoomArea::heightScale = (1.0 * VIDEO_HEIGHT / QJ_HEIGHT);

QjZoomArea::QjZoomArea(QWidget *parent) : QWidget(parent)
{
    m_startPoint.setX(0);
    m_startPoint.setY(0);
    m_endPoint.setX(0);
    m_endPoint.setY(0);

    m_isQj1Zoomed = false;
    m_isQj2Zoomed = false;

    m_zoomFunc = false;
}

void QjZoomArea::mousePressEvent(QMouseEvent *event)
{
    if (m_zoomFunc)
    {
        if (event->button() == Qt::LeftButton)
        {
            if (getTag() == QjZoomArea::QJ1)
            {
                if (!m_isQj1Zoomed)
                {
                    m_startPoint = event->pos();
                    m_endPoint = event->pos();
                    m_isQj1Zoomed = true;
                }
                else
                {
                    QMessageBox::warning(this, "非法", "只能放大一次！");
                }
            }

            if (getTag() == QjZoomArea::QJ2)
            {
                if (!m_isQj2Zoomed)
                {
                    m_startPoint = event->pos();
                    m_endPoint = event->pos();
                    m_isQj2Zoomed = true;
                }
                else
                {
                    QMessageBox::warning(this, "非法", "只能放大一次！");

                }
            }
        }
    }
}

void QjZoomArea::mouseMoveEvent(QMouseEvent *event)
{
    if (m_zoomFunc)
    {
        if (event->button() == Qt::LeftButton)
        {
            m_endPoint = event->pos();
            update();
        }
    }
}

void QjZoomArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_zoomFunc)
    {
        if (event->button() == Qt::LeftButton)
        {
            int width = m_endPoint.x() - m_startPoint.x();
            int height = m_endPoint.y() - m_startPoint.y();
            if (width > 0 && height > 0)
            {
                if (getTag() == QjZoomArea::QJ1)
                {
                    //qDebug() << "from qj1";
                    HIMSG_PARAM_S hsmsg;
                    hsmsg.iInfoId                   = _QJ_Inter_;//放大
                    hsmsg.videoNum                  = 1;
                    hsmsg.videoChnIndex[0]          = QJ1VIDEO;
                    hsmsg.stVideoParam[0].s32X      = m_startPoint.x() + m_posX;
                    hsmsg.stVideoParam[0].s32Y      = m_startPoint.y() * heightScale;
//                    hsmsg.stVideoParam[0].u32Width  = width * widthScale;
//                    hsmsg.stVideoParam[0].u32Height = height * heightScale;
                    hsmsg.stVideoParam[0].u32Width  = width;
                    hsmsg.stVideoParam[0].u32Height = height * heightScale;

                    auto pHs                        = (char *)&hsmsg;
                    auto len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
                    if (len == -1)
                    {
                        qDebug() << "send Error";
                    }
                }
                else if(getTag() == QjZoomArea::QJ2)
                {
                    //qDebug() << "from qj2";

                    HIMSG_PARAM_S hsmsg;
                    hsmsg.iInfoId                   = _QJ_Inter_;//放大
                    hsmsg.videoNum                  = 1;
                    hsmsg.videoChnIndex[0]          = QJ2VIDEO;
                    hsmsg.stVideoParam[0].s32X      = m_startPoint.x() + m_posX;
                    hsmsg.stVideoParam[0].s32Y      = m_startPoint.y() * heightScale;
                    hsmsg.stVideoParam[0].u32Width  = width;
                    hsmsg.stVideoParam[0].u32Height = height * heightScale;
                    auto pHs                        = (char *)&hsmsg;
                    auto len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
                    if (len == -1)
                    {
                        qDebug() << "send Error";
                    }
                }
            }


            m_endPoint = m_startPoint;
            update();
        }
    }
}

void QjZoomArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    int width = m_endPoint.x() - m_startPoint.x();
    int height = m_endPoint.y() - m_startPoint.y();
    //qDebug() << width << "  " << height;
    if(width > 0 && height > 0)
    {
        //qDebug() << "drawing....";
        painter.drawRect(m_startPoint.x(), m_startPoint.y(), width, height);
    }
}

void QjZoomArea::setTag(QString tag)
{
    m_tag = tag;
}

QString QjZoomArea::getTag()
{
    return m_tag;
}

void QjZoomArea::setStartX(int posX)
{
    m_posX = posX;
}

int QjZoomArea::getStartX()
{
    return m_posX;
}

void QjZoomArea::setZoomFunc(bool zoom)
{
    m_zoomFunc = zoom;
}

void QjZoomArea::restore()
{
    if (getTag() == QjZoomArea::QJ1)
    {
        m_isQj1Zoomed = false;

        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_Inter_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ1VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }

    }
    else if(getTag() == QjZoomArea::QJ2)
    {
        m_isQj2Zoomed = false;

        //qDebug() << "from qj2";
        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_Inter_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ2VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }

    }
}

void QjZoomArea::restoreInit()
{
    //if (getTag() == QjZoomArea::QJ1)
    //{
        m_isQj1Zoomed = false;

        HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_RESTORE_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ1VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
        auto pHs                        = (char *)&hsmsg;
        auto len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }

        QThread::msleep(20);

    //}
   // else if(getTag() == QjZoomArea::QJ2)
    //{
        m_isQj2Zoomed = false;

        //qDebug() << "from qj2";
        //HIMSG_PARAM_S hsmsg;
        hsmsg.iInfoId = _QJ_RESTORE_;
        hsmsg.videoNum = 1;
        hsmsg.videoChnIndex[0] = QJ2VIDEO;
        hsmsg.stVideoParam[0].s32X      = 0;
        hsmsg.stVideoParam[0].s32Y      = 0;
        hsmsg.stVideoParam[0].u32Width  = QJ_WIDTH;
        hsmsg.stVideoParam[0].u32Height = VIDEO_HEIGHT;
        pHs                        = (char *)&hsmsg;
        len = m_udp.writeDatagram(pHs, sizeof(hsmsg), QHostAddress("127.0.0.1"), 8888);
        if (len == -1)
        {
            qDebug() << "QJ1ZoomIn send Error";
        }

   // }
}



