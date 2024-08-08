#include "MyUdpSocket.h"
#include "parse_json.h"
//#include "uri_defines.h"

MyUdpSocket::MyUdpSocket(QObject *parent) : QUdpSocket(parent) {}

MyUdpSocket::~MyUdpSocket() {}

void MyUdpSocket::set_host_info(const QString &ip, int port)
{
    m_ip_addr = ip;
    m_port    = port;
}

void MyUdpSocket::init(MyUdpType type)
{
    m_type = type;
    switch (m_type)
    {
        case UDP_TYPE_SERVER:
            init_server();
            break;
        case UDP_TYPE_CLIENT:
            init_client();
            break;
        case UDP_TYPE_GROUP:
            init_multicast_group();
            break;
        default:
            break;
    }

    return;
}

void MyUdpSocket::init_server()
{
    bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);
    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::slot_data_recv);
}

void MyUdpSocket::init_client()
{
    setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);
    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::slot_data_recv);
}

void MyUdpSocket::init_multicast_group()
{
    bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 8);
    joinMulticastGroup(QHostAddress(m_ip_addr));
    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::slot_data_recv);
}

bool MyUdpSocket::send_msg(const QString &ip, int port, const QJsonObject &data)
{
    if (port != m_port || ip != m_ip_addr)
    {
        return true;
    }
    QJsonDocument document;
    document.setObject(data);
    QByteArray send_data = document.toJson(QJsonDocument::Compact);
    return (send_data.size()
            == writeDatagram(send_data.data(), send_data.size(), QHostAddress(m_ip_addr), m_port))
               ? (true)
               : (false);
}

void MyUdpSocket::slot_data_recv()
{
    QByteArray data;
    data.resize(pendingDatagramSize());
    readDatagram(data.data(), data.size());

    QString id;
    QJsonObject recv_json;

    //清楚尾部垃圾数据
    QString str = QString(data);
    data        = str.toLocal8Bit();

    if (data.size() && LES_Util_Json::parse_json(data, recv_json)
        && LES_Util_Json::get_json_value_by_key(recv_json, JSON_KEY_ID, id))
    {
        emit signal_recv_data(id, recv_json);
    }
    else
    {
        qDebug() << "get data something error";
    }
}
