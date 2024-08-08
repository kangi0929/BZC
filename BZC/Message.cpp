#include "Message.h"
//#include "Sys_Conf.h"
//#include "uri_defines.h"
#include <QJsonObject>
#include "parse_json.h"
//#include "MyMessageBoxDlg.h"
#include "CfgFile.h"

Message::Message()
{
    //    init();
    connect(SocketManage::get_instance(), &SocketManage::signal_recv_data, this,
            &Message::slot_recv_data);

    connect(SocketManage::get_instance(), &SocketManage::signal_tcp_link_state, this,
            &Message::slot_link_state);
}

bool Message::send_tcp_msg(QJsonObject &data, const QString &ip, int port)
{
    //需要在所有的请求消息中添加 mac和device字段信息
    //    data.insert(JSON_KEY_DEVICE, Sys_Conf::get_instance()->get_device_name());
    //    data.insert(JSON_KEY_MAC, Sys_Conf::get_instance()->get_mac_addr());
    data.insert(JSON_KEY_MAC, m_mac_addr);
    if (ip.isEmpty() || 0 == port)
    {
        return SocketManage::get_instance()->send_tcp_msg(m_tcp_host.ip_addr, m_tcp_host.port, data);
    }
    else
    {
        return SocketManage::get_instance()->send_tcp_msg(ip, port, data);
    }
}

bool Message::send_udp_msg(const QJsonObject &data, const QString &ip, int port)
{
    return SocketManage::get_instance()->send_udp_msg(ip, port, data);
}

void Message::init(QString strIp, int iPort, QString strMulticastGroupIp, int iMulticastGroupPort)
{
    //获取TCP和组播的相关配置
    m_tcp_host.ip_addr = strIp;
    m_tcp_host.port    = iPort;

    m_multicast_group_host.ip_addr = strMulticastGroupIp;
    m_multicast_group_host.port    = iMulticastGroupPort;

    //    connect(SocketManage::get_instance(), &SocketManage::signal_recv_data, this,
    //            &Message::slot_recv_data);

    //    connect(SocketManage::get_instance(), &SocketManage::signal_tcp_link_state, this,
    //            &Message::slot_link_state);
}

void Message::start_socket()
{
    //目前用不到tcp了
    // SocketManage::get_instance()->start_tcp(m_tcp_host.ip_addr, m_tcp_host.port);

    SocketManage::get_instance()->start_udp(m_multicast_group_host.ip_addr,
                                            m_multicast_group_host.port, UDP_TYPE_GROUP);
}

void Message::disconnect_all_link()
{
    //目前先释放TCP的链路
    SocketManage::get_instance()->disconnet_tcp_socket();
}

void Message::slot_recv_data(const QString &id, const QJsonObject &data)
{
    //解析是否有result字段，若该字段为不成功，同一个给予错误提示。
    int ret_code = 0;
    QString mac_addr;
    if (LES_Util_Json::get_json_value_by_key(data, JSON_KEY_RESULT, ret_code)
        && LES_Util_Json::get_json_value_by_key(data, JSON_KEY_MAC, mac_addr))
    {
        //只有是本终端发送的请求，且返回值为不成功，才会给出相应的提示
        if (0 != ret_code && mac_addr == m_mac_addr)
        {
            QString msg;
            LES_Util_Json::get_json_value_by_key(data, JSON_KEY_MSG, msg);
            //            if(!MyMessageBoxDlg::get_instance()->is_show())
            //            {
            //                MyMessageBoxDlg::get_instance()->set_text(msg);
            //            }
            return;
        }
    }

    if (URI_TRACE_SET_MODE == id || URI_TRACE_GET_MODE == id || URI_TRACE_MANUAL == id
        || URI_TRACE_REPORT_STATUS == id)
    {
        emit signal_yuntai_ctrl_data(id, data);
    }
    else if (URI_TRACE_SET_POS == id || URI_TRACE_REPORT == id)
    {
        emit signal_video_data(id, data);
    }
    else if (URI_TARGET_REPORT == id)
    {
        emit signal_video_data(id, data);
        emit signal_weibiao_data(id, data);
    }
    else if (URI_BIT_REPORT == id)
    {
        emit signal_status_data(id, data);
    }

    else if (URI_PANORAMA_GET_ORIENTATION == id)
    {
        emit signal_orientation_data(id, data);
    }
    else if (NVR_SAVE_VIDEO_CAPTURE == id)
    {
        emit signal_video_capture_response_data(id, data);
    }
    else if (NVR_SAVE_LOG == id)
    {
        emit signal_log_response_data(id, data);
    }
}

void Message::slot_link_state(bool normal)
{
    emit signal_link_state(normal);
}

void Message::get_mac_addrs()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    for (int i = 0; i < nets.size(); i++)
    {
        if (nets[i].flags().testFlag(QNetworkInterface::IsUp)
            && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
            && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            m_mac_addr = nets[i].hardwareAddress();
            return;
            // qDebug() << "Local Mac Addr:" << m_mac_addr << "IP:" << nets[i].allAddresses();
        }
    }
}
