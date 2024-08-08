#include "Logger.h"
#include <map>
#include <list>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/fmt/bin_to_hex.h"


namespace  QLog{
    #define  LOG_VERSION "1.8.2"
    static std::map<std::string, std::map<int, std::shared_ptr<Logger::CallBack> > >g_mapLogger;
    std::mutex mtx_log;
}

/*
 *
*/
std::string Logger::GetVersion()
{
    return  std::string(LOG_VERSION);
}

/*
 *
 */
void Logger::InitLog(std::string logger_name, std::string filename, LOG_LEVEL eLogLevel)
{
    if(spdlog::get(logger_name) != nullptr)
    {
        return;
    }

    spdlog::level::level_enum eLevel = static_cast< spdlog::level::level_enum>(eLogLevel);

    spdlog::set_level(eLevel);

    spdlog::set_pattern("[%H:%M:%S.%e] [%l] %v");

    std::string strPath = GetLogPath();

    strPath += filename;

    auto logger = spdlog::daily_logger_mt(logger_name, strPath, 0, 0);

    spdlog::flush_on(spdlog::level::info);//spdlog::level::err

    //输出日志版本
    logger->info(std::string("日志版本:") + LOG_VERSION);
}

/*
*设置日志级别
*/
void Logger::SetLevel(std::string logger_name, LOG_LEVEL eLevel)
{
    spdlog::level::level_enum eLogLevel = static_cast< spdlog::level::level_enum>(eLevel);
    spdlog::get(logger_name).get()->set_level(eLogLevel);
}

/*
 *写日志 错误
 */
void Logger::LogError(std::string strName, std::string strLog, uint32_t Color )
{
    spdlog::get(strName)->error(strLog);

    std::lock_guard<std::mutex> lock(QLog::mtx_log);
    if(QLog::g_mapLogger.find(strName) != QLog::g_mapLogger.end())
    {
        for(auto it = QLog::g_mapLogger[strName].begin();  it !=  QLog::g_mapLogger[strName].end(); ++it)
        {
            (*it->second.get())(strName,  LL_ERROR, strLog, Color);
        }
    }   
}


/*
 *写日志 警告
 */
void Logger::LogWarn(std::string strName, std::string strLog, uint32_t Color)
{
    spdlog::get(strName)->warn(strLog);

    std::lock_guard<std::mutex> lock(QLog::mtx_log);

    if(QLog::g_mapLogger.find(strName) != QLog::g_mapLogger.end())
    {
        for(auto it = QLog::g_mapLogger[strName].begin();  it !=  QLog::g_mapLogger[strName].end(); ++it)
        {
            (*it->second.get())(strName,  LL_WARN, strLog, Color);
        }
    }
}

/*
 *写日志 信息
 */
void Logger::LogInfo(std::string strName, std::string strLog, uint32_t Color)
{
    spdlog::get(strName)->info(strLog);

    std::lock_guard<std::mutex> lock(QLog::mtx_log);
    if(QLog::g_mapLogger.find(strName) != QLog::g_mapLogger.end())
    {
        for(auto it = QLog::g_mapLogger[strName].begin();  it !=  QLog::g_mapLogger[strName].end(); ++it)
        {
            (*it->second.get())(strName,  LL_INFO,  strLog, Color);
        }
    }
}

/*
 *写日志 调试
 */
void Logger::LogDebug(std::string strName, std::string strLog, uint32_t Color)
{
    spdlog::get(strName)->debug(strLog);

    std::lock_guard<std::mutex> lock(QLog::mtx_log);

    if(QLog::g_mapLogger.find(strName) != QLog::g_mapLogger.end())
    {
        for(auto it = QLog::g_mapLogger[strName].begin();  it !=  QLog::g_mapLogger[strName].end(); ++it)
        {
            (*it->second.get())(strName,  LL_DEBUG,  strLog, Color);
        }
    }
}

/*
 *写日志 trace
 */
void Logger::LogTrace(std::string strName, std::string strLog, uint32_t Color)
{
    spdlog::get(strName)->trace(strLog);

    std::lock_guard<std::mutex> lock(QLog::mtx_log);

    if(QLog::g_mapLogger.find(strName) != QLog::g_mapLogger.end())
    {
        for(auto it = QLog::g_mapLogger[strName].begin();  it !=  QLog::g_mapLogger[strName].end(); ++it)
        {
            (*it->second.get())(strName, LL_TRACE, strLog, Color);
        }
    }
}

/*
*订阅日志
*/
int Logger::SubLog(std::string strName, const CallBack &cbFun)
{
    int nLog = 0;

    std::lock_guard<std::mutex> lock(QLog::mtx_log);

    auto it = QLog::g_mapLogger.find(strName);

    if(it == QLog::g_mapLogger.end())
    {
        nLog = 1;
    }

    else
    {
        nLog = it->second.size() + 1;
    }

    QLog::g_mapLogger[strName].emplace(nLog, std::make_shared<CallBack>(cbFun));

    return nLog;
}

/*
*取消订阅
*/
int Logger::UnSubLog(std::string strName, int nLog)
{
    std::lock_guard<std::mutex> lock(QLog::mtx_log);

    auto it = QLog::g_mapLogger.find(strName);

    if(it == QLog::g_mapLogger.end())
    {
        return 0;
    }
    auto it2 = it->second.find(nLog);

    if(it2 == it->second.end())
    {
        return 0;
    }

    it->second.erase(nLog);

    return  nLog;
}

/*获得日志文件路径*/
std::string Logger::GetLogPath()
{
    std::string strPath("");

//    char szpath[256] = {0};

//    getcwd(szpath, 256);

//    strPath.append(szpath);

//    int nIndex = strPath.find_last_of("/");

//    strPath = strPath.substr(0, nIndex);

//    strPath.append("/Logs/");

    strPath.append(LOG_FILE_PATH);

    return strPath;
}
