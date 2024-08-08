#ifndef QCFGFILE_H
#define QCFGFILE_H

#include <string>

using namespace std;

class QCfgFile
{

private:
    QCfgFile();

public:
    static QCfgFile *GetInst();

    bool LoadFile();

    string GetQj1RtspUrl();

    string GetQj2RtspUrl();

    string GetZsKjgRtspUrl();

    string GetZsHwRtspUrl();

    string GetNVR_IP();

    string GetNVR_Port();

    string GetInterCommu_IP();

    string GetInterCommu_Port();

private:
    string GetCfgPath();

    string GetCurProcessName();

    //全景1 rtsp地址
    string m_strQj1RtspUrl = string("");

    //全景2 rtsp地址
    string m_strQj2RtspUrl = string("");

    //周视可见光rtsp地址
    string m_strZsKjgRtspUrl = string("");

    //周视红外rtsp地址
    string m_strZsHwRtspUrl = string("");

    // NVR通信IP
    string m_strNVR_IP = string("");
    // NVR通信Port
    string m_strNVR_Port = string("");

    //内部通信IP
    string m_strInterCommu_IP = string("");
    //内部通信Port
    string m_strInterCommu_Port = string("");

private:
    // static QCfgFile m_QCfgFile;
};

#endif  // QCFGFILE_H
