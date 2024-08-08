#include "mousemoveoptimize.h"
#include "cytglobaltype.h"

MouseMoveOptimize::MouseMoveOptimize(QObject *parent) : QObject(parent)
{
    m_udp = new QUdpSocket(this);
    m_udp->bind(QHostAddress("127.0.0.1"), 1234);
    connect(m_udp, &QUdpSocket::readyRead, this, &MouseMoveOptimize::sltRecivePos);
}

void MouseMoveOptimize::sltRecivePos()
{
    //get mouse pos;
    if (m_udp->hasPendingDatagrams())
    {
        qint64 size = m_udp->pendingDatagramSize();
        m_data.resize(size);
        m_udp->readDatagram(m_data.data(), m_data.size());
        auto pos = (CursorPos *)m_data.data();
        QCursor::setPos(pos->x, pos->y);
    }
}
