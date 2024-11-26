#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
{
    //封装了login请求对象数据
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    //对象数据序列化成char*
    std::string send_str;
    if(req.SerializeToString(&send_str))
    {
        std::cout<<send_str.c_str()<<std::endl;
    }

    //从send_str反序列化为一个login请求对象
    LoginRequest reb;
    if(reb.ParseFromString(send_str))
    {
        std::cout<<reb.name()<<std::endl;
        std::cout<<reb.pwd()<<std::endl;
    }
    return 0;
}
