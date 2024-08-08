#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H
#include <QTcpSocket>
#include <QTimer>
#include "globalvar.h"

#define HEARTBEAT_TIMEOUT_MAX  15
#define TCP_DATA_LEN_HEAD_SIZE 4

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket(QObject *parent = nullptr);

    ~MyTcpSocket();

    void set_ip_port(const QString &ip, int port);

    void connect_host();

    bool disconect_host();

    void set_auto_link(bool flag);

signals:
    void signal_socket_state(SocketState status);

    void signal_recv_data(const QString &id, const QJsonObject &data);

public slots:
    void send_msg(const QString &ip, int port, const QJsonObject &data, bool heartbeat);
private slots:
    void slot_socket_read_data();

    void slot_timeout();

    void slot_disconnected();

    void slot_connected();

private:
    QString m_ip_addr;

    int m_port;

    bool m_auto_link_flag;

    QTimer *m_timer;  //定时器，每隔一段时间发送心跳字节

    unsigned int m_heartbeat_times;

    unsigned int m_pkg_len;  //当前数据包的总长度
    QByteArray m_recv_data;  //当前接收数据的信息
};

#endif  // TCP_SOCKET_H
