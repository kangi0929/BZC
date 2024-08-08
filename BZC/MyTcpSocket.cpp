#include "MyTcpSocket.h"
#include <QJsonDocument>
#include <QAbstractSocket>
#include "SocketManage.h"
#include "parse_json.h"

MyTcpSocket::MyTcpSocket(QObject *parent) : QTcpSocket(parent)
{
    setReadBufferSize(8 * 1024);

    m_auto_link_flag = true;

    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &MyTcpSocket::slot_timeout);

    connect(this, &QIODevice::readyRead, this, &MyTcpSocket::slot_socket_read_data);

    connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::slot_disconnected);

    connect(this, &MyTcpSocket::connected, this, &MyTcpSocket::slot_connected);
}

MyTcpSocket::~MyTcpSocket()
{

    if (m_timer->isActive())
    {
        set_auto_link(false);
        m_timer->stop();
    }
    disconect_host();
}

void MyTcpSocket::set_ip_port(const QString &ip, int port)
{
    m_ip_addr = ip;
    m_port    = port;
}

void MyTcpSocket::connect_host()
{
    disconect_host();

    connectToHost(m_ip_addr, m_port);
    // connectToHost("192.168.0.16", 8554);
    // connectToHost("192.168.0.16", 20002);

    waitForConnected(5 * 1000);

    if (QAbstractSocket::ConnectedState != this->state())
    {
        qWarning() << "ERROR: has not connected!";
        emit signal_socket_state(QAbstractSocket::UnconnectedState);
    }

    if (!m_timer->isActive())
    {
        m_timer->start(1 * 1000);
    }
}

bool MyTcpSocket::disconect_host()
{
    if (!this->isValid())
    {
        return true;
    }

    qDebug() << "Want to disconnect the host, current state:" << this->state();
    if (QAbstractSocket::UnconnectedState != this->state())
    {
        disconnectFromHost();
        waitForDisconnected();
        if (QAbstractSocket::UnconnectedState == this->state())
        {
            qWarning() << "ERROR: still not disconnected! state:" << this->state();
            return false;
        }
    }

    return true;
}

void MyTcpSocket::set_auto_link(bool flag)
{
    m_auto_link_flag = flag;
}

//发送消息
void MyTcpSocket::send_msg(const QString &ip, int port, const QJsonObject &data, bool heartbeat)
{
    if (port != m_port || ip != m_ip_addr)
    {
        return;
    }

    if (!this->isValid())
    {
        qWarning() << "This tcp link is not valid, ip" << m_ip_addr;
        return;
    }

    QJsonDocument document;
    document.setObject(data);
    QByteArray send_data = document.toJson(QJsonDocument::Compact);

    QByteArray data_block;
    data_block.resize(TCP_DATA_LEN_HEAD_SIZE);
    unsigned int data_len = send_data.size();

    if (!heartbeat)
    {
        // qDebug()<<"raw data len:"<< data_len << "json data info:" <<data;
    }

    //长度(4字节)+数据区
    memcpy(data_block.data(), &data_len, TCP_DATA_LEN_HEAD_SIZE);
    data_block.append(send_data);

    int send_length = this->write(data_block);

    bool result = (TCP_DATA_LEN_HEAD_SIZE + data_len == send_length) ? (true) : (false);
    if (result)
    {
        qDebug() << "send msg success:";
        // qDebug() << "send msg success:" << data_block;
    }
    qDebug() << "send length:" << send_length;
    return;
}

//收消息
void MyTcpSocket::slot_socket_read_data()
{
    //后续加载心跳报文机制
    //    QByteArray recv_data = this->readAll();
    //    qDebug() << "get data length:" << recv_data.length() << " server ip:" << m_ip_addr
    //             << "data:" << recv_data;
    //    //判断是否为心跳包，若是心跳包，需要把变量归零
    //    m_heartbeat_times = 0;

    //接收完数据后要发送信号通知socketManage对象的槽函数

    m_recv_data.append(this->readAll());

    //由于数据结构的中的保存数据长度是4个字节，不管是32位和是64位系统，数据长度的4个字段都在一个包里
    if (0 == m_pkg_len)
    {
        memcpy(&m_pkg_len, m_recv_data.data(), TCP_DATA_LEN_HEAD_SIZE);
        //大小端的调整
        m_pkg_len = ((m_pkg_len & 0x000000ff) << 24) | ((m_pkg_len & 0x0000ff00) << 8)
                    | ((m_pkg_len & 0x00ff0000) >> 8) | ((m_pkg_len & 0xff000000) >> 24);

        qDebug("The receive packet data length is %d.", m_pkg_len);
    }
    qDebug() << m_recv_data.length();

    //若接收到的数据超过了当前包的数据长度，需要进行数据包解析，并发送
    while (m_recv_data.length() >= (m_pkg_len + TCP_DATA_LEN_HEAD_SIZE))
    {
        // qDebug() << "******************************";
        // qDebug() << "tcpSocketrecv()   2";
        QByteArray pkg_data = m_recv_data;
        pkg_data.truncate(m_pkg_len + TCP_DATA_LEN_HEAD_SIZE);

        //去掉包头的 TCP_DATA_LEN_HEAD_SIZE 字节数据
        pkg_data.remove(0, TCP_DATA_LEN_HEAD_SIZE);

        //分发数据
        QJsonObject data_json;
        QString idValue;
        if (LES_Util_Json::parse_json(pkg_data, data_json)
            && LES_Util_Json::get_json_value_by_key(data_json, JSON_KEY_ID, idValue))
        {
            emit signal_recv_data(idValue, data_json);
        }
        else
        {
            qDebug() << "Cannot parse the json data.";
        }

        //去除掉已经分发的数据
        m_recv_data.remove(0, (m_pkg_len + TCP_DATA_LEN_HEAD_SIZE));

        //更新下一包数据的长度
        if (m_recv_data.length() >= TCP_DATA_LEN_HEAD_SIZE)
        {
            memcpy(&m_pkg_len, m_recv_data.data(), TCP_DATA_LEN_HEAD_SIZE);
        }
        else
        {
            m_pkg_len = 0;
        }
    }
    return;
}

void MyTcpSocket::slot_timeout()
{
    if (QAbstractSocket::UnconnectedState == this->state() && m_auto_link_flag)
    {
        qDebug() << "Try to connect the host.";
        connect_host();
    }

    //    m_heartbeat_times++;
    //    if(m_heartbeat_times > HEARTBEAT_TIMEOUT_MAX)
    //    {
    //        m_heartbeat_times = 0;
    //        //超时重连机制
    //        connect_host();
    //    }
}

void MyTcpSocket::slot_disconnected()
{
    qDebug() << "Has disconnect from the server. It's IP:" << m_ip_addr;
    emit signal_socket_state(QAbstractSocket::UnconnectedState);
}

void MyTcpSocket::slot_connected()
{
    emit signal_socket_state(QAbstractSocket::ConnectedState);
}
