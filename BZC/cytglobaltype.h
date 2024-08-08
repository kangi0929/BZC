#ifndef CYTGLOBALTYPE_H
#define CYTGLOBALTYPE_H
#include <QString>
#include <QDateTime>
struct DetectInfo
{
    QString panorama_ip;
    int orientation;
    int area_id;
    int type;
    int target_id;
    int order_no;
    int x_pos;
    int y_pos;
    int width;
    int high;
    int lifeTime = 20;
};

struct RectInfo
{
    QString panorama_ip;
    int target_id;
    int x_pos;
    int y_pos;
    int width;
    int high;
    bool isSelected = false;
};

//视频流输出位置控制结构体
enum
{
    QJ1VIDEO = 0,  //全景1
    QJ2VIDEO,      //全景2
    HWVIDEO,       //红外
    KJGVIDEO,      //可见光
};

#define VIDEO_FILE_PATH "/mnt/video/"
#define MAP_FILE_PATH   "/mnt/map/"
#define LOG_FILE_PATH   "/mnt/log/"

#define REPLAY_CURRENT_POSE                 1001
#define REPLAY_COMPLETE                     1002
#define RECORD_CHANGE                       1003

//四路视频
#define VIDEO_PARAMETER_SETTING_FUNCTION    2001
#define REPLAY_CONTRL_FUNCITON              2002
#define APP_EXIT                            2003
//隐藏三路,显示一路
#define _QJ_    2004
//显示视频帧内的某一块(放大)
#define _QJ_Inter_ 2005
//
#define _QJ_RESTORE_ 2006

#define NVR_NET_PORT 6666


//视频图像尺寸
#define VIDEO_WIDTH 3840
#define VIDEO_HEIGHT 2160
//全景显示尺寸
#define QJ_WIDTH 1600
#define QJ_HEIGHT 1144

#define VIDEO_NUM 4
typedef struct hiRECT_S
{
    int s32X;
    int s32Y;
    int u32Width;
    int u32Height;
} RECT_S;
typedef struct hiMsg_PARAM
{
    int iInfoId;
    int videoNum;                    //当前页面视频个数
    int videoChnIndex[VIDEO_NUM];    //视频索引数组
    RECT_S stVideoParam[VIDEO_NUM];  //视频位置参数数组
    char     cURL_Name[1024];
    long lCurrentReplayPos;
    int iReplayState;//1:开始播放 2:暂停 3:继续播放 4：快放 5：慢放 6:停止
    long lSelReplyStartPos;//选时回放开始位置
} HIMSG_PARAM_S;

typedef struct _Replay_Config_File_Parameter
{
  long lReplayRecordFrameTotal;
}Replay_Config_File_Parameter;

//
//    int s32VideoNum;
//    int s32VideoChnIndex[IPC_VIDEO_NUM];
//    hisiRECT stVideoParam[IPC_VIDEO_NUM];
//    int iCurrentReplayPos;
//    int iReplayState;//1:开始播放 2:暂停 3:继续播放 4：快放 5：慢放

//日志信息
struct LogInfo
{
    QString id       = "/nvr/save_log";
    int logType      = 1;
    QString device   = "";
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    int level;
    QString mac;
    int type;
    QString operationCode;  //具体的操作名称
    int status;             //成功0或失败1
    QString info;           //一般填写操作失败的原因
    QString detail;         //??
};

struct CursorPos
{
    int x;
    int y;
};

enum ShowType
{
    FirstPage = 0,
    QJ1ZoomIn,
    QJ2ZoomIn,
    SecondPage
};

#endif  // CYTGLOBALTYPE_H
