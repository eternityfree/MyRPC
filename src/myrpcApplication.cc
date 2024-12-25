#include "myrpcApplication.h"
#include <iostream>
#include <string>
#include <unistd.h>


MyrpcConfig MyrpcApplication::m_config;

void ShowArgsHelp()
{
    std::cout << "format:command -i <configfile>" << std::endl;
}

void MyrpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while ((c = getopt(argc, argv, "i:")) != -1)  //参数i:表示如果是-i选项，则该选项后面必须有一个参数，即-i:xxx。
    {
        switch (c)
        {
        case 'i':                          //返回i，表示程序遇到了-i选项，并且这个选项后面跟了一个参数
            config_file = optarg;
            break;
        case '?':                          //返回?，表示用户输入了一个无效的选项
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':                           //表示选项后面需要参数，但是没给
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    //开始加载配置文件了 rpcserver_ip= rpcserver_port= zookeeper_ip= zookeeper_port=
    m_config.LoadConfigFile(config_file.c_str());

    // 调试信息
    // std::cout<<"rpcserverip:"<<m_config.Load("rpcserverip")<<std::endl;
    // std::cout<<"rpcserverport:"<<m_config.Load("rpcserverport")<<std::endl;
    // std::cout<<"zookeeperip:"<<m_config.Load("zookeeperip")<<std::endl;
    // std::cout<<"zookeeperport:"<<m_config.Load("zookeeperport")<<std::endl;
}
MyrpcApplication &MyrpcApplication::GetInstance()
{
    static MyrpcApplication app;
    return app;
}
MyrpcConfig& MyrpcApplication::GetMyrpcConfig()
{
    return m_config;
}