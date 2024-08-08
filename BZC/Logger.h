#ifndef LOGGER_H
#define LOGGER_H

#ifndef Q_DECL_EXPORT
#define Q_DECL_EXPORT __attribute__((visibility("default")))
#endif

#include <stddef.h>
#include <memory>
#include <functional>
#include "cytglobaltype.h"

enum LOG_LEVEL
{
    LL_TRACE = 0,
    LL_DEBUG,
    LL_INFO,
    LL_WARN,
    LL_ERROR,
    LL_CRITICAL,
    LL_OFF,
    n_levels
};

#define LOG_NAME "Device_log"
//#define LOG_PATH   "/mnt/log/"

#define LOG_CRITICAL    SPDLOG_LOGGER_CRITICAL

#define LOG_ERROR(NAME, ...)       Logger::LogError(NAME, __VA_ARGS__)
#define LOG_WARN(NAME, ...)        Logger::LogWarn(NAME, __VA_ARGS__)
#define LOG_INFO(NAME, ...)        Logger::LogInfo(NAME, __VA_ARGS__)
#define LOG_DEBUG(NAME, ...)       Logger::LogDebug(NAME, __VA_ARGS__)
#define LOG_TRACE(NAME, ...)       Logger::LogTrace(NAME, __VA_ARGS__)


class Q_DECL_EXPORT Logger
{

protected:

    Logger() = default;

    void *operator new(size_t){throw  nullptr;};

    void operator delete(void *){};

    void *operator new[](size_t){throw  nullptr;};

    void operator delete[](void *){};

public:

    typedef std::function<void(std::string, LOG_LEVEL, std::string,  uint32_t)> CallBack;

public:

    /*获得日志版本*/
    static std::string GetVersion();

    /*
    *初始化日志
    */
    static void InitLog(std::string logger_name, std::string filename,  LOG_LEVEL eLogLevel = LL_INFO) ;

    /*
    *设置日志级别
    */
    static void SetLevel(std::string logger_name, LOG_LEVEL eLevel);

    /*
     *写日志
     */
    static void LogError(std::string strName, std::string strLog, uint32_t Color = 0xffff0000);

    /*
     *写日志
     */
    static void LogWarn(std::string strName, std::string strLog, uint32_t Color = 0xffff0000);

    /*
     *写日志
     */
    static void LogInfo(std::string strName, std::string strLog, uint32_t Color = 0xffffffff);//ZZC20211014

    /*` q
     *写日志
     */
    static void LogDebug(std::string strName, std::string strLog, uint32_t Color = 0xffff0000);

    /*
     *写日志
     */
    static void LogTrace(std::string strName, std::string strLog, uint32_t Color = 0xffff0000);


    /*订阅日志*/
    static int SubLog(std::string strName, const CallBack &cbFun);


    /*取消订阅*/
    static int UnSubLog(std::string strName, int nLog);

    /*获得日志路径*/
    static std::string GetLogPath();


};

#endif // LOGGER_H
