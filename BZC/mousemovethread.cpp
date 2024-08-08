//#include "mousemovethread.h"
//#include <QDebug>

//MouseMoveThread::MouseMoveThread(QObject *parent) : QThread(parent) {}

//void MouseMoveThread::startMove()
//{
//    m_isRun = true;
//    hifb_test();
//    start();
//}

//void MouseMoveThread::stopMove()
//{
//    m_isRun = false;
//    wait(1000);
//    exit(0);
//}

//void MouseMoveThread::run()
//{
//    QPoint point;
//    while (m_isRun)
//    {
//        point = QCursor::pos();
//        set_mouse_pos(point.x(), point.y());
//        msleep(10);
//        // qDebug() << currentThreadId();
//    }
//}
