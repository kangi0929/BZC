#ifndef QJZOOMAREA_H
#define QJZOOMAREA_H

#include <QWidget>
#include "cytglobaltype.h"
#include <QUdpSocket>

class QjZoomArea : public QWidget
{
    Q_OBJECT
private:
    QPoint m_startPoint;
    QPoint m_endPoint;

    QString m_tag;
    QUdpSocket m_udp;

    bool m_isQj1Zoomed;
    bool m_isQj2Zoomed;

    int m_posX;

    //放大功能是否开启
    bool m_zoomFunc;

public:
    static const QString QJ1;
    static const QString QJ2;
    static const double widthScale;
    static const double heightScale;

    explicit QjZoomArea(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void setTag(QString tag);
    QString getTag();
    void setStartX(int posX);
    int getStartX();

    void setZoomFunc(bool zoom);

    void restore();

    //点击返回首页按钮，执行的，防止在全景里点击放大出现问题。
    void restoreInit();

signals:

};

#endif // QJZOOMAREA_H
