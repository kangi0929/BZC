#ifndef MOUSEMOVEOPTIMIZE_H
#define MOUSEMOVEOPTIMIZE_H

#include <QObject>
#include <QUdpSocket>
#include <QCursor>

class MouseMoveOptimize : public QObject
{
    Q_OBJECT
public:
    explicit MouseMoveOptimize(QObject *parent = nullptr);
public slots:
    void sltRecivePos();
private:
    QUdpSocket *m_udp;
    QByteArray m_data;
};

#endif // MOUSEMOVEOPTIMIZE_H
