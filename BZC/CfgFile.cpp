#include "CfgFile.h"
#include "tinyxml2.h"
#include <unistd.h>

// tmp
#include <QString>
#include <QDebug>

#define PATH_LEN 256

// QCfgFile  QCfgFile::m_QCfgFile;

QCfgFile::QCfgFile()
{
    LoadFile();
}

QCfgFile *QCfgFile::GetInst()
{
    static QCfgFile *cfgFile = new QCfgFile();
    return cfgFile;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
bool QCfgFile::LoadFile()
{
    string strPath = GetCfgPath();
    // strPath += GetCurProcessName();
    // strPath += string("/");

    //目前配置文件在hs版上的路径是/root/Data/conf.xml
    strPath += string("conf.xml");

    tinyxml2::XMLDocument docXml;

    //
    tinyxml2::XMLError eRet = docXml.LoadFile(strPath.c_str());

    if (eRet != 0)
    {
        return false;
    }

    tinyxml2::XMLElement *root = docXml.RootElement();

    m_strQj1RtspUrl = root->FirstChildElement("quanjing1_rtsp_url")->GetText();

    m_strQj2RtspUrl = root->FirstChildElement("quanjing2_rtsp_url")->GetText();

    m_strZsKjgRtspUrl = root->FirstChildElement("zs_kjg_rtsp_url")->GetText();

    m_strZsHwRtspUrl = root->FirstChildElement("zs_hw_rtsp_url")->GetText();

    m_strNVR_IP = root->FirstChildElement("NVR_IP")->GetText();

    m_strNVR_Port = root->FirstChildElement("NVR_Port")->GetText();

    m_strInterCommu_IP = root->FirstChildElement("InterCommunication_IP")->GetText();

    m_strInterCommu_Port = root->FirstChildElement("InterCommunication_Port")->GetText();
    return true;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetQj1RtspUrl()
{
    return m_strQj1RtspUrl;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetQj2RtspUrl()
{
    return m_strQj2RtspUrl;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetZsKjgRtspUrl()
{
    return m_strZsKjgRtspUrl;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetZsHwRtspUrl()
{
    return m_strZsHwRtspUrl;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetCfgPath()
{
    string strPath;

    char szPath[PATH_LEN] = {0};

    getcwd(szPath, PATH_LEN);

    strPath.append(szPath);

    // int nIndex = strPath.find_last_of("/");
    // strPath = strPath.substr(0, nIndex);

    strPath.append("/Data/");

    //移植以后，设置开机自启动，这个路径可能要注意一下，到时候再看吧
    //等环境确定以后，可以直接写死
    return strPath;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetCurProcessName()
{
    char path[PATH_LEN];

    memset(path, 0, PATH_LEN);

    int rval = readlink("/proc/self/exe", path, sizeof(path));

    if (rval == -1)
    {
        return string("");
    }

    char *name = strrchr(path, '/');

    return string(name + 1);
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetNVR_IP()
{
    return m_strNVR_IP;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetNVR_Port()
{
    return m_strNVR_Port;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetInterCommu_IP()
{
    return m_strInterCommu_IP;
}

/**************************************************************************
 *函数名称:
 *函数输入:
 *函数输出:
 *返 回 值:
 *函数说明:
 **************************************************************************/
string QCfgFile::GetInterCommu_Port()
{
    return m_strInterCommu_Port;
}
