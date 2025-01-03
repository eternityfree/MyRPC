#include "logger.h"

// 获取日志的单例
Logger &Logger::GetInstance()
{
    static Logger logger;
    return logger;
}
// 设置log级别
void Logger::SetLogLevel(LogLevel level)
{
    m_loglevel = level;
}
// 写日志,把日志信息写入lockqueue缓冲区当中
void Logger::Log(std::string msg)
{
    m_lckQue.Push(msg);
}
Logger::Logger()
{
    // 启动专门的写日志线程
    std::thread writeLogTask([&]()
                             {
                                 for (;;)
                                 {
                                     // 获取当前的日期，然后取日志信息，写入相应的日志文件当中
                                     time_t now = time(nullptr);
                                     tm *nowtm = localtime(&now);

                                     char file_name[128];
                                     sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year + 1900, nowtm->tm_mon + 1, nowtm->tm_mday);

                                     FILE *pf = fopen(file_name, "a+");
                                     if (pf == nullptr)
                                     {
                                         std::cout << "logger file: " << file_name << " open error!"<<std::endl;
                                         exit(EXIT_FAILURE);
                                     }

                                     std::string msg=m_lckQue.Pop();
                                     char time_buf[128]={0};
                                     sprintf(time_buf,"%d:%d:%d=> [%s] ",nowtm->tm_hour,nowtm->tm_min,nowtm->tm_sec,(m_loglevel==INFO?"INFO":"ERROR"));
                                     msg.insert(0,time_buf);
                                     msg.append("\n");

                                     fputs(msg.c_str(),pf);
                                     fclose(pf);
                                 } });
    // 设置分离线程，守护线程
    writeLogTask.detach();
}

// 定义宏
#define LOG_INFO(logmsgformat, ...)                     \
    do                                                  \
    {                                                   \
        Logger &logger = Logger::GetInstance();         \
        logger.SetLogLevel(INFO);                       \
        CHAR C[1024] = {0};                             \
        snprintf(C, 1024, logmsgformat, ##__VA_ARGS__); \
        Logger.Log(c);                                  \
    } while (0);

#define LOG_ERROR(logmsgformat, ...)                    \
    do                                                  \
    {                                                   \
        Logger &logger = Logger::GetInstance();         \
        logger.SetLogLevel(ERROR);                      \
        CHAR C[1024] = {0};                             \
        snprintf(C, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(C);                                  \
    } while (0)
