#include "SocketManage.h"
#include <QThread>

SocketManage::SocketManage() {}

SocketManage::~SocketManage()
{
    disconnet_tcp_socket();
}

void SocketManage::start_tcp(const QString &ip, int port)
{
    Socket_Host_Info socket_host(ip, port);
    auto it = m_tcp_socket.find(socket_host);
    //说明这个ip和port已经有了
    if (it != m_tcp_socket.end())
    {
        if (it.value().thread != nullptr)
        {
            //需要停止线程
            it.value().thread->quit();
        }

        it.value().thread->deleteLater();
        it.value().tcp_socket->deleteLater();

        // disconnect()
    }

    TcpSocketInfo tcp_socket_info;
    tcp_socket_info.thread     = new QThread;
    tcp_socket_info.tcp_socket = new MyTcpSocket;

    //发
    connect(this, &SocketManage::signal_send_tcp_data, tcp_socket_info.tcp_socket,
            &MyTcpSocket::send_msg);

    //收
    connect(tcp_socket_info.tcp_socket, &MyTcpSocket::signal_recv_data, this,
            &SocketManage::slot_recv_data);

    connect(tcp_socket_info.tcp_socket, &MyTcpSocket::signal_socket_state,
            SocketManage::get_instance(), &SocketManage::slot_tcp_link_status,
            Qt::ConnectionType::QueuedConnection);

    tcp_socket_info.tcp_socket->set_ip_port(ip, port);
    tcp_socket_info.tcp_socket->connect_host();
    m_tcp_socket[socket_host] = tcp_socket_info;
    tcp_socket_info.tcp_socket->moveToThread(tcp_socket_info.thread);
    tcp_socket_info.thread->start();
    return;
}

void SocketManage::start_udp(const QString &ip, int port, MyUdpType type)
{
    Socket_Host_Info socket_host(ip, port);
    auto it = m_udp_socket.find(socket_host);
    //说明这个ip和port已经有了
    if (it != m_udp_socket.end())
    {
        if (it.value().thread != nullptr)
        {
            //需要停止线程
            it.value().thread->quit();
        }

        it.value().thread->deleteLater();
        it.value().udp_socket->deleteLater();
    }

    UdpSocketInfo udp_socket_info;
    udp_socket_info.thread     = new QThread;
    udp_socket_info.udp_socket = new MyUdpSocket;
    udp_socket_info.udp_socket->set_host_info(ip, port);
    udp_socket_info.udp_socket->init(type);

    //收
    connect(udp_socket_info.udp_socket, &MyUdpSocket::signal_recv_data, this,
            &SocketManage::slot_recv_data);

    //发
    connect(this, &SocketManage::signal_send_udp_data, udp_socket_info.udp_socket,
            &MyUdpSocket::send_msg);

    m_udp_socket[socket_host] = udp_socket_info;
    udp_socket_info.udp_socket->moveToThread(udp_socket_info.thread);
    udp_socket_info.thread->start();
}

void SocketManage::disconnet_tcp_socket()
{
    m_tcp_socket.clear();
}

void SocketManage::disconnet_spec_tcp_socket(const Socket_Host_Info &socket_host)
{
    auto it = m_tcp_socket.find(socket_host);
    if (it != m_tcp_socket.end())
    {
        //把断链自动重连设置关闭
        it.value().tcp_socket->set_auto_link(false);

        if (it.value().tcp_socket != nullptr)
        {
            it.value().tcp_socket->disconect_host();
        }

        if (it.value().thread != nullptr)
        {
            //需要停止线程
            it.value().thread->quit();
        }
    }
}

bool SocketManage::send_tcp_msg(const QString &dest_ip, int port, const QJsonObject &data)
{
    Socket_Host_Info socket_host(dest_ip, port);
    auto it = m_tcp_socket.find(socket_host);
    if (it != m_tcp_socket.end() && it.value().tcp_socket->isValid())
    {
        emit signal_send_tcp_data(dest_ip, port, data, false);
        return true;
    }
    else
    {
        return false;
    }
}

bool SocketManage::send_udp_msg(const QString &dest_ip, int port, const QJsonObject &data)
{
    Socket_Host_Info socket_host(dest_ip, port);
    auto it = m_udp_socket.find(socket_host);
    // qDebug() << m_udp_socket.firstKey().ip_addr << "  " << m_udp_socket.firstKey().port;
    if (it != m_udp_socket.end())
    {
        emit signal_send_udp_data(dest_ip, port, data, false);
        return true;
    }
    else
    {
        return false;
    }
}

void SocketManage::slot_recv_data(const QString &id, const QJsonObject &data)
{
    emit signal_recv_data(id, data);
}

void SocketManage::slot_tcp_link_status(QAbstractSocket::SocketState state)
{
    if (0 == m_tcp_socket.size())
    {
        return;
    }
    //遍历所有tcp链路状态
    bool link_normal = true;
    for (auto it = m_tcp_socket.begin(); it != m_tcp_socket.end(); it++)
    {
        if (QAbstractSocket::ConnectedState != it.value().tcp_socket->state())
        {
            link_normal = false;
            break;
        }
    }

    emit signal_tcp_link_state(link_normal);
}
