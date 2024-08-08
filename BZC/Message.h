#pragma once

#include "SocketManage.h"
#include "globalvar.h"
#include <QNetworkInterface>

class Message : public QObject
{
    Q_OBJECT
private:
    Message();

public:
    static Message *get_instance()
    {
        static Message *instance = new Message();
        return instance;
    }

    void start_socket();

    void disconnect_all_link();

    bool send_tcp_msg(QJsonObject &data, const QString &ip = "", int port = 0);
    bool send_udp_msg(const QJsonObject &data, const QString &ip = "", int port = 0);

    void get_mac_addrs();

    void init(QString strIp, int iPort, QString strMulticastGroupIp, int iMulticastGroupPort);

public slots:
    void slot_recv_data(const QString &id, const QJsonObject &data);

    void slot_link_state(bool normal);

signals:
    /**
     * @brief signal_video_data 视频相关的信号数据
     * @param id
     * @param data
     */
    void signal_video_data(const QString &id, const QJsonObject &data);

    /**
     * @brief signal_weibiao_data  微表相关信号数据
     * @param id
     * @param data
     */
    void signal_weibiao_data(const QString &id, const QJsonObject &data);

    /**
     * @brief signal_yuntai_ctrl_data 云台控制
     * @param id
     * @param data
     */
    void signal_yuntai_ctrl_data(const QString &id, const QJsonObject &data);

    /**
     * @brief signal_other_ctrl_data 各个设备的相关控制消息
     * @param id
     * @param data
     */
    void signal_other_ctrl_data(const QString &id, const QJsonObject &data);

    /**
     * @brief signal_status_data
     * @param id
     * @param data
     */
    void signal_status_data(const QString &id, const QJsonObject &data);

    void signal_link_state(bool normal);

    void signal_orientation_data(const QString &id, const QJsonObject &data);

    // cyt
    void signal_video_capture_response_data(const QString &id, const QJsonObject &data);
    void signal_log_response_data(const QString &id, const QJsonObject &data);

private:
    Socket_Host_Info m_tcp_host;

    Socket_Host_Info m_multicast_group_host;

    QString m_mac_addr;
};
