#ifndef TCPMANAGE_H
#define TCPMANAGE_H

#include <QObject>
#include "MyTcpSocket.h"
#include "MyUdpSocket.h"

typedef QMap<QString, int> HOST_INFO;

class Socket_Host_Info
{
public:
    Socket_Host_Info() {}

    Socket_Host_Info(QString ip, int port_number)
    {
        ip_addr = ip;
        port    = port_number;
    }

    // key的比较
    bool operator==(const Socket_Host_Info &a) const
    {
        if (this->ip_addr == a.ip_addr && this->port == a.port)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator<(const Socket_Host_Info &a) const
    {
        if (port < a.port)
        {
            return true;
        }

        return (ip_addr.compare(a.ip_addr) < 0) ? (true) : (false);
    }

    QString ip_addr;
    int port;
};

class TcpSocketInfo
{
public:
    MyTcpSocket *tcp_socket = nullptr;
    QThread *thread         = nullptr;
};

class UdpSocketInfo
{
public:
    MyUdpSocket *udp_socket = nullptr;
    QThread *thread         = nullptr;
};

class SocketManage : public QObject
{
    Q_OBJECT
private:
    SocketManage();

public:
    static SocketManage *get_instance()
    {
        static SocketManage *instance = new SocketManage();
        return instance;
    }

    ~SocketManage();

    void start_tcp(const QString &ip, int port);

    void start_udp(const QString &ip, int port, MyUdpType type);

    void disconnet_tcp_socket();

    /**
     * @brief disconnet_spec_tcp_socket 断开指定IP的链路
     * @param socket_host 需要断链的IP地址和端口信息
     */
    void disconnet_spec_tcp_socket(const Socket_Host_Info &socket_host);

    /**
     * @brief send_msg 发送数据消息
     * @param dest_ip  目的IP
     * @param port
     * @param data     需要发送的数据
     */
    bool send_tcp_msg(const QString &dest_ip, int port, const QJsonObject &data);

    /**
     * @brief send_udp_msg
     * @param dest_ip
     * @param port
     * @param data
     * @return
     */
    bool send_udp_msg(const QString &dest_ip, int port, const QJsonObject &data);

public slots:
    //这里用于接收来自tcp和udp的信息
    void slot_recv_data(const QString &id, const QJsonObject &data);

    void slot_tcp_link_status(QAbstractSocket::SocketState state);

signals:
    void signal_recv_data(const QString &id, const QJsonObject &data);

    void signal_send_tcp_data(const QString &dest_ip, int port, const QJsonObject &data,
                              bool heartbeat);

    void signal_send_udp_data(const QString &dest_ip, int port, const QJsonObject &data,
                              bool heartbeat);

    void signal_tcp_link_state(bool normal);

private:
    QMap<Socket_Host_Info, TcpSocketInfo> m_tcp_socket;

    QMap<Socket_Host_Info, UdpSocketInfo> m_udp_socket;
};

#endif  // TCPMANAGE_H
