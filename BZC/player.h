#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include "cytglobaltype.h"
#include <QMenu>
#include <QAction>
#include <QTimer>

struct ZS_RECT
{
    QRect rect;
    int rect_id;
    bool isSelected;
    const static int MAX_NUM = 4;
};

class QPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit QPlayer(QWidget *parent = nullptr);
    ~QPlayer();
    void setAlarmArea(bool alm);
    void clear();
    void setPixmapSize(int width, int height);
    void setCamMoved(bool cam);
    void setRtspUrl(QString url);

    void setDebug(bool debug);
    QPoint getCurrnetPoint();

    void setScale();
signals:
    void lastQj(int id);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void drawRect();
    //为了防止绘图时出现重影
    void tmpClearInDrawing();
    //用于手绘矩形框的函数
    void drawAlarmRectangular(QRect &rect);
    //判断目标是不是在警戒区里
    bool isInAlarmArea(QRect &rect);

    //坐标转换，工具函数
    QPoint wgtToFrame(QPoint point);

    void clearPixmap();
    void clearZSVec();

    void drawScale();

public slots:
    void slotsReceiveRect(QList<RectInfo *> &listRect);
private slots:
    void slotsDelAlarmRect();

    void sltUpdate();

private:
    QList<RectInfo *> m_rectList;
    bool m_isDebug    = false;  //标定转台用的
    bool m_isCamMoved = false;  //调转跟踪
    bool m_isAlarmed  = false;
    QVector<ZS_RECT *> m_zsRectVec;
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isMouseLeftPressed = false;
    QPixmap *m_pixmap;
    bool m_isClear = false;
    QString m_rtspUrl;  //记录该视频来自哪个url
    QPoint m_currentPoint;

    //全景上添加角度坐标
    QPixmap *m_scale;
    const static int NUM = 19;  //水平方向刻度
    int m_degree[NUM];

    QTimer m_timerUpdate;


    //tmp
    int p = 0;
};

#endif  // PLAYER_H



