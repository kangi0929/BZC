#ifndef WGTMAIN_H
#define WGTMAIN_H

#include <QWidget>
//#include "Player.h"
#include <QStandardItem>
#include "globalvar.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QItemSelectionModel>

#include "cytglobaltype.h"
#include "player.h"
#include <QUdpSocket>

namespace Ui
{
class QWgtMain;
}

class QWgtMain : public QWidget
{
    Q_OBJECT

public:
    explicit QWgtMain(QWidget *parent = nullptr);
    ~QWgtMain();

private:
    void InitControl();

signals:
    void signal_WgtMain_operateNo(int iOperateNo, int iParam0, int iParam1, int iParam2);
    void signalLog(LogInfo lg);

protected:
    void hideEvent(QHideEvent *event);

    void showEvent(QShowEvent *event);

private slots:

    void on_btn_up_pressed();

    void on_btn_up_released();

    void on_btn_down_pressed();

    void on_btn_down_released();

    void on_btn_left_pressed();

    void on_btn_left_released();

    void on_btn_right_pressed();

    void on_btn_right_released();

    void on_radio_low_clicked();

    void on_radio_mid_clicked();

    void on_radio_high_clicked();

    void slot_wgt_change(bool flag);

    void on_BtnFocusAdd_pressed();

    void on_BtnFocusAdd_released();

    void on_BtnFocusSub_pressed();

    void on_BtnFocusSub_released();

    void on_BtnZoomAdd_pressed();

    void on_BtnZoomAdd_released();

    void on_BtnZoomSub_pressed();

    void on_BtnZoomSub_released();

    void on_BtnInfraredFocusAdd_pressed();

    void on_BtnInfraredFocusAdd_released();

    void on_BtnInfraredFocusSub_pressed();

    void on_BtnInfraredFocusSub_released();

    void on_BtnInfraredZoomAdd_pressed();

    void on_BtnInfraredZoomAdd_released();

    void on_BtnInfraredZoomSub_pressed();

    void on_BtnInfraredZoomSub_released();

public:
    void setCameraPanSpeed(int iCameraSpeed, int iCameraPanSpeed);
    void setCameraPanAzimuthParam(int iAzimuth);
    void setCameraPanPitchParam(int iAzimuth);
    void setState(int device, int state);

private:
    QPlayer *m_QQj1Player;
    QPlayer *m_QQj2Player;

    QUdpSocket *m_udp;
    // QPlayer* m_QZsKjgPlayer;
    // QPlayer* m_QZsHwPlayer;

    // bool m_bShow = false;

private:
    QString m_urlOne = "192.168.0.10:8554";
    QString m_urlTwo = "192.168.0.10:8564";
    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;  // Item选择模型
    QJsonObject m_jsObj;
    //检测框信息存储
    QMap<int, DetectInfo *> m_mapDetect;
    QList<RectInfo *> m_rectplayerOne;
    QList<RectInfo *> m_rectplayerTwo;
    QMultiMap<int, int> m_mmap;
    //是否是微表来新数据后的第一次选择
    bool isFirstChooseFromNewTable = false;
    //实测调用theModel->removeRows函数会发送selectionChanged信号，所有这里要加个判断变量
    bool isRowsRemoved = false;
    void myInit();
    void initTable();
    //定时器用来清除过期的数据
    QTimer *m_timer;
    //控制微表刷新频率
    QTimer *m_timer2;

    //解析json对象, 并存入mapDetect中
    void parseDetectInfoJsObj(const QJsonObject &jsObj);
    template <class Key, class T> void clearQMap(QMap<Key, T> &map);
    //下面的两个函数分别利用m_mapDetect去做不同的工作
    void writeToTable();
    void drawRect();

signals:
    void sendRectToPlayerOne(QList<RectInfo *> &r1);
    void sendRectToPlayerTwo(QList<RectInfo *> &r2);

private slots:
    //微表项被选择的槽函数
    void on_updateSelection(const QItemSelection &selected, const QItemSelection &deselected);
    void showFocusedTarget();
    // signals : void signal_weibiao_data(const QString &id, const QJsonObject &data);
    void slots_weibiao_data(const QString &id, const QJsonObject &data);

    //更新m_mapDetect里项目的生存周期
    void updateMap();

    // void slotsReceiveJsObj();

    //警戒区
    void on_btn_add_1_clicked(bool checked);
    void on_btn_add_2_clicked(bool checked);
    //调转跟踪
    void on_btn_Trace_clicked(bool checked);
    //红外，可见光视频位置切换
    void on_btn_Change_clicked();

    void on_btn_debug_clicked(bool checked);
    void on_btn_record_clicked();

    //用来确定最新一次是在哪个全景上点击的
    void slot_getId(int id);

    //云台归零
    void on_btn_Zero_clicked();

    void on_btn_SetZero_clicked();

    void on_btn_JoyStick_reset_clicked();

    void on_btn_JoyStick_update_clicked();

private:
    int m_iCameraPanSpeed;
    int m_iCameraSpeed;
    // debug时区分是哪个全景
    int m_id = 0;

private:
    Ui::QWgtMain *ui;
};

#endif  // WGTMAIN_H
