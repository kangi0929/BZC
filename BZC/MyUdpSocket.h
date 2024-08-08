#pragma once
#include <QUdpSocket>
#include "globalvar.h"

enum MyUdpType
{
    UDP_TYPE_SERVER = 0,
    UDP_TYPE_CLIENT,
    UDP_TYPE_GROUP,
};

class MyUdpSocket : public QUdpSocket
{
    Q_OBJECT
public:
    MyUdpSocket(QObject *parent = nullptr);

    ~MyUdpSocket();

    void set_host_info(const QString &ip, int port);

    void init(MyUdpType type);

public slots:
    bool send_msg(const QString &ip, int port, const QJsonObject &data);

private slots:
    void slot_data_recv();

signals:
    void signal_recv_data(const QString &id, const QJsonObject &data);

private:
    void init_server();

    void init_client();

    void init_multicast_group();

private:
    QString m_ip_addr;
    int m_port;
    bool m_multicast_group;
    MyUdpType m_type;
};
