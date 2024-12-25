#pragma once
#include "lockqueue.h"
#include <string>
#include <time.h>
#include <iostream>

enum LogLevel
{
    INFO,  // 普通信息
    ERROR, //  错误信息
};

// myrpc框架的日志系统
class Logger
{
public:
    //获取日志的单例
    static Logger& GetInstance();
    // 设置log级别
    void SetLogLevel(LogLevel level);
    // 写日志
    void Log(std::string msg);

private:
    int m_loglevel;                  // 记录日志级别
    LockQueue<std::string> m_lckQue; // 日志缓冲队列
    Logger();
    Logger(const Logger&)=delete;
    Logger(Logger&&)=delete;
};