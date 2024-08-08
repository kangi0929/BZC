#include "player.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPaintEvent>
#include "parse_json.h"
#include "Message.h"

QPlayer::QPlayer(QWidget *parent) : QWidget(parent)
{
    m_pixmap = new QPixmap(this->width(), this->height());
    m_pixmap->fill(Qt::transparent);

//    connect(&m_timerUpdate, &QTimer::timeout, this, &QPlayer::sltUpdate);
//    m_timerUpdate.start(500);
}

QPlayer::~QPlayer()
{
    delete m_pixmap;
}

void QPlayer::setAlarmArea(bool alm)
{
    m_isAlarmed = alm;
}

void QPlayer::clear()
{
    //clearPixmap();
    clearZSVec();
    m_isClear = true;
    update();
    //repaint();
}

//小转大
QPoint QPlayer::wgtToFrame(QPoint point)
{
    int x = point.x() * (1.0 * 1920 / 1600);
    int y = point.y() * (1.0 * 1080 / 310);
    return QPoint(x, y);
}

void QPlayer::mousePressEvent(QMouseEvent *event)
{
    if (m_isDebug)
    {
        m_currentPoint = event->pos();  // wgt的局部坐标
        if (m_rtspUrl == "rtsp://192.168.0.10:8554/video")
        {
            emit lastQj(1);
        }
        else if (m_rtspUrl == "rtsp://192.168.0.10:8564/video")
        {
            emit lastQj(2);
        }
        update();
        //repaint();
    }
    else
    {
        if (event->button() == Qt::LeftButton)
        {
            //绘制警戒区
            if (m_isAlarmed && !m_isCamMoved)
            {
                if (m_zsRectVec.size() == ZS_RECT::MAX_NUM)
                {
                    QMessageBox::information(NULL, "告警", "警戒区最大数量为4!");
                }
                else
                {
                    m_startPoint         = event->pos();
                    m_endPoint           = event->pos();
                    m_isMouseLeftPressed = true;
                }
            }

            //调转跟踪
            if (m_isCamMoved)
            {
                QPoint curPoint = wgtToFrame(event->pos());
                QJsonObject json;
                json.insert(JSON_KEY_ID, "api/panorama/get_orientation");  // ID
                QString ipPort;
                //通过m_rtsp_url来判断到底是来自哪个全景
                if (m_rtspUrl == "rtsp://192.168.0.10:8554/video")
                {
                    ipPort = m_rtspUrl.left(24);
                    ipPort = ipPort.right(17);
                    json.insert(JSON_PANORAMA_IP, ipPort);
                }
                else if (m_rtspUrl == "rtsp://192.168.0.10:8564/video")
                {
                    ipPort = m_rtspUrl.left(24);
                    ipPort = ipPort.right(17);
                    json.insert(JSON_PANORAMA_IP, ipPort);
                }
                json.insert(JSON_X_POS, curPoint.x());
                json.insert(JSON_Y_POS, curPoint.y());
                // qDebug() << "*&*&*&*&*&*&*    " << ipPort;

                Message::get_instance()->send_udp_msg(json, "192.168.0.10", 20002);
            }
        }
        //删除警戒框
        else if (event->button() == Qt::RightButton && m_isAlarmed)  //在警戒区开启的时候，右键才有用
        {
            for (int i = 0; i < m_zsRectVec.size(); ++i)
            {
                //如果右键的位置在警戒框里，则创建右键菜单
                if (m_zsRectVec.at(i)->rect.contains(event->pos()))
                {
                    m_zsRectVec.at(i)->isSelected = true;
                    QMenu *menu                   = new QMenu(this);
                    auto del                      = new QAction("删除", menu);
                    connect(del, &QAction::triggered, this, &QPlayer::slotsDelAlarmRect);
                    menu->addAction(del);
                    if (menu->exec(event->globalPos()) == 0)
                    {
                        //说明没有点击删除项，该警戒区不需要被删除
                        m_zsRectVec.at(i)->isSelected = false;
                    }

                    delete menu;
                    break;
                }
            }
        }
    }
}

void QPlayer::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDebug)
    {
    }
    else
    {
        if (m_isMouseLeftPressed)
        {
            if (event->buttons() & Qt::LeftButton)
            {
                m_endPoint = event->pos();
                update();
                //repaint();
            }
        }
    }
}

void QPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDebug)
    {
    }
    else
    {
        if (event->button() == Qt::LeftButton && m_isAlarmed && m_isMouseLeftPressed)
        {
            m_isMouseLeftPressed = false;
            m_endPoint           = event->pos();
            QRect rect(m_startPoint, m_endPoint);
            if (qAbs(rect.width()) > 3 && qAbs(rect.height()) > 3)
            {
                ZS_RECT *zs    = new ZS_RECT;
                zs->rect       = rect;
                zs->isSelected = false;
                m_zsRectVec.append(zs);
            }
        }
    }
}

//int temp[10] = {1000, 800, 300, 500, 587, 982, 654, 432, 892, 434};
//int posbuf[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
//int postemp = 0;


void QPlayer::paintEvent(QPaintEvent *event)
{
    if (m_isDebug)
    {
        QPainter painter(this);
        QPainter pp(m_pixmap);
        pp.setPen(QPen(Qt::red, 3, Qt::SolidLine));
        QRect rect2(QPoint(m_currentPoint.x() - 3, m_currentPoint.y() - 3),
                    QPoint(m_currentPoint.x() + 3, m_currentPoint.y() + 3));
        pp.drawEllipse(rect2);
        painter.drawPixmap(0, 0, *m_pixmap);
    }
    else
    {
        drawRect();
        QPainter painter(this);

        //drawScale();
        //painter.drawPixmap(0, 0, *m_scale);

        //画标尺
        QPen pen;
        pen.setColor(QColor(19, 168, 95));
        painter.setPen(pen);
        for (int i = 0; i < NUM; ++i)
        {
            QRect rect(i*88-6, 285, 50, 50);
            painter.drawText(rect, QString::number(m_degree[i])+"°");
            painter.drawLine(i*88, 300, i*88, 310);
        }


        //可以手动绘制矩形框了
        if (m_isAlarmed || m_isClear)
        {
            // if-else 针对当前正在画的这一次警戒区框
            if (m_isMouseLeftPressed)
            {
                //tmpClearInDrawing();
                QRect rect2(m_startPoint, m_endPoint);
                QPen pen(Qt::yellow, 2, Qt::DashLine);
                painter.setPen(pen);
                painter.drawRect(rect2);
                //drawAlarmRectangular(rect2);
            }
            else
            {
                //tmpClearInDrawing();
            }
            //

            for (int i = 0; i < m_zsRectVec.size(); ++i)
            {
                QPen pen(Qt::yellow, 2, Qt::DashLine);
                painter.setPen(pen);
                painter.drawRect(m_zsRectVec.at(i)->rect);
                //drawAlarmRectangular(m_zsRectVec.at(i)->rect);
            }
            //painter.drawPixmap(event->rect(), *m_pixmap);
            m_isClear = false;
        }
    }
}

void QPlayer::showEvent(QShowEvent *event)
{
    m_scale = new QPixmap(width(), height());
    m_scale->fill(Qt::transparent);
}

//画检测框
void QPlayer::drawRect()
{
    QPainter painter(this);
    QPen pen;
    for (int i = 0; i < m_rectList.size(); ++i)
    {
        // 1920*1080 --> 1600*310
        int x      = m_rectList.at(i)->x_pos * (1.0 * 1600 / 1920);
        int y      = m_rectList.at(i)->y_pos * (1.0 * 310 / 1080);
        int width  = m_rectList.at(i)->width * (1.0 * 1600 / 1920);
        int height = m_rectList.at(i)->high * (1.0 * 310 / 1080);
        QRect rect(x, y, width, height);

        if (isInAlarmArea(rect))
        {
            QPen pen;
            pen.setWidth(4);
            pen.setColor(Qt::red);
            painter.setPen(pen);
        }
        //        else if (m_rectList.at(i)->isSelected)
        //        {
        //            pen.setWidth(6);
        //            pen.setColor(Qt::yellow);
        //            painter.setPen(pen);
        //        }
        else
        {
            pen.setWidth(2);
            pen.setColor(Qt::green);
            painter.setPen(pen);
        }

        painter.drawRect(rect);

        //再加一个target_id文字信息
        QFont font = painter.font();
        //font.setFamily("");
        font.setPixelSize(15);
        font.setBold(true);
        pen.setColor(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setFont(font);
        painter.drawText(rect.x(), rect.y(), "id(批号) : " + QString::number(m_rectList.at(i)->target_id));
    }
}

bool QPlayer::isInAlarmArea(QRect &rect)
{
    int left   = rect.left();
    int right  = rect.right();
    int top    = rect.top();
    int bottom = rect.bottom();

    for (int i = 0; i < m_zsRectVec.size(); ++i)
    {
//        qDebug() << "*****************";
//        qDebug() << m_zsRectVec.value(i)->rect.left() << " " << m_zsRectVec.value(i)->rect.right()
//                 << " " << m_zsRectVec.value(i)->rect.top() << " " << m_zsRectVec.value(i)->rect.bottom();
//        qDebug() << m_zsRectVec.value(i)->rect.x() << " " << m_zsRectVec.value(i)->rect.width()
//                 << " " << m_zsRectVec.value(i)->rect.y() << " " << m_zsRectVec.value(i)->rect.height();
//        qDebug() << "*****************";
//        qDebug() << m_zsRectVec.value(i)->rect.isEmpty() << " "
//                 << m_zsRectVec.value(i)->rect.isValid();

        int alarmLeft = qMin(m_zsRectVec.value(i)->rect.left(), m_zsRectVec.value(i)->rect.right());
        int alarmRight = qMax(m_zsRectVec.value(i)->rect.left(), m_zsRectVec.value(i)->rect.right());
        int alarmTop = qMin(m_zsRectVec.value(i)->rect.top(), m_zsRectVec.value(i)->rect.bottom());
        int alarmBottom = qMax(m_zsRectVec.value(i)->rect.top(), m_zsRectVec.value(i)->rect.bottom());

        if (alarmLeft < left && alarmRight > left
            && alarmTop < bottom && alarmBottom > top)
        {
            return true;
        }
        if (alarmLeft < right && alarmRight > right
            && alarmTop < bottom && alarmBottom > top)
        {
            return true;
        }
        if (alarmTop < top && alarmBottom > top
            && alarmLeft < right && alarmRight > left)
        {
            return true;
        }
        if (alarmTop < bottom && alarmBottom > bottom
            && alarmLeft < right && alarmRight > left)
        {
            return true;
        }
        if (alarmLeft > left && alarmRight < right
            && alarmTop > top && alarmBottom < bottom)
        {
            return true;
        }

//        if (m_zsRectVec.value(i)->rect.left() < left && m_zsRectVec.value(i)->rect.right() > left
//            && m_zsRectVec.value(i)->rect.top() < bottom && m_zsRectVec.value(i)->rect.bottom() > top)
//        {
//            return true;
//        }
//        if (m_zsRectVec.value(i)->rect.left() < right && m_zsRectVec.value(i)->rect.right() > right
//            && m_zsRectVec.value(i)->rect.top() < bottom && m_zsRectVec.value(i)->rect.bottom() > top)
//        {
//            return true;
//        }
//        if (m_zsRectVec.value(i)->rect.top() < top && m_zsRectVec.value(i)->rect.bottom() > top
//            && m_zsRectVec.value(i)->rect.left() < right && m_zsRectVec.value(i)->rect.right() > left)
//        {
//            return true;
//        }
//        if (m_zsRectVec.value(i)->rect.top() < bottom && m_zsRectVec.value(i)->rect.bottom() > bottom
//            && m_zsRectVec.value(i)->rect.left() < right && m_zsRectVec.value(i)->rect.right() > left)
//        {
//            return true;
//        }
//        if (m_zsRectVec.value(i)->rect.left() > left && m_zsRectVec.value(i)->rect.right() < right
//            && m_zsRectVec.value(i)->rect.top() > top && m_zsRectVec.value(i)->rect.bottom() < bottom)
//        {
//            return true;
//        }
    }
    return false;
}

void QPlayer::slotsReceiveRect(QList<RectInfo *> &listRect)
{
    m_rectList = listRect;
    update();
    //qDebug() << m_rtspUrl << " " << m_rectList.size();
    //repaint();
}

void QPlayer::slotsDelAlarmRect()
{
    for (int i = 0; i < m_zsRectVec.size(); ++i)
    {
        if (m_zsRectVec.at(i)->isSelected)
        {
            auto rec = m_zsRectVec.takeAt(i);
            delete rec;
            break;
        }
    }
    update();
    //repaint();
}

void QPlayer::sltUpdate()
{

}

void QPlayer::tmpClearInDrawing()
{
    m_pixmap->fill(Qt::transparent);

}

void QPlayer::drawAlarmRectangular(QRect &rect)
{
    QPainter painter(m_pixmap);
    QPen pen(Qt::yellow, 2, Qt::DashLine);
    painter.setPen(pen);
    painter.drawRect(rect);
}

void QPlayer::clearPixmap()
{
    m_pixmap->fill(Qt::transparent);
    m_startPoint = m_endPoint = QPoint(0, 0);
}

void QPlayer::clearZSVec()
{
    while (m_zsRectVec.size() != 0)
    {
        delete m_zsRectVec.at(0);
        m_zsRectVec.removeAt(0);
    }
}

void QPlayer::drawScale()
{
    QPainter painter(m_scale);
    QPen pen;
    pen.setColor(QColor(26, 226, 128));
    painter.setPen(pen);
    for (int i = 0; i < NUM; ++i)
    {
        QRect rect(i*88-6, 285, 50, 50);
        painter.drawText(rect, QString::number(m_degree[i])+"°");
        painter.drawLine(i*88, 300, i*88, 310);
    }
}

void QPlayer::setPixmapSize(int width, int height)
{
    *m_pixmap = m_pixmap->scaled(width, height);
}

void QPlayer::setCamMoved(bool cam)
{
    m_isCamMoved = cam;
}

void QPlayer::setRtspUrl(QString url)
{
    m_rtspUrl = url;
}

void QPlayer::setDebug(bool debug)
{
    m_isDebug = debug;
}
QPoint QPlayer::getCurrnetPoint()
{
    return wgtToFrame(m_currentPoint);
}

void QPlayer::setScale()
{
    QFile inFile("./Data/scale.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "scale.txt文件打开失败!";
    }
    char ch[10];
    inFile.readLine(ch, sizeof(ch));
    QString str(ch);
    int index = str.toInt() - 1;
    if (m_rtspUrl == "rtsp://192.168.0.10:8554/video")
    {
        int start = 0;//0度
        int end = 350;
        //int gp = 180 / (NUM + 1);
        for (int i = index; i < NUM; ++i)
        {
            m_degree[i] = start;
            start += 10;
        }
        for (int i = index - 1; i >= 0; --i)
        {
            m_degree[i] = end;
            end -= 10;
        }
    }
    else if(m_rtspUrl == "rtsp://192.168.0.10:8564/video")
    {
        int start = (NUM - index - 1) * 10;
        for (int i  = 0; i < NUM; ++i)
        {
            m_degree[i] = start;
            start += 10;
        }
    }
}
