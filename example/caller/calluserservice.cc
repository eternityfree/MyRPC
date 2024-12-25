#include <iostream>
#include "myrpcApplication.h"
#include "user.pb.h"

int main(int argc, char **argv)
{
    // 整个程序启动后，想使用myrpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MyrpcApplication::Init(argc, argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MyrpcChannel());
    // rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;

    MyrpcController controller;
    // 发起rpc方法的调用 同步的rpc调用过程 MyrpcChannnel::callmethod
    stub.Login(&controller, &request, &response, nullptr);

    // 一次rpc调用完成，读调用的结果
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
    }
    else
    {
        if (response.result().errorcode() == 0)
        {
            std::cout << "rpc login response success:" << response.success() << std::endl;
        }
        else
        {
            std::cout << "rpc login response error:" << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}