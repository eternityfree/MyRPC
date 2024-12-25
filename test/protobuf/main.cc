#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
{
    //protobuf用法1
    {
    // //封装了login请求对象数据
    // LoginRequest req;
    // req.set_name("zhang san");
    // req.set_pwd("123456");

    // //对象数据序列化成char*
    // std::string send_str;
    // if(req.SerializeToString(&send_str))
    // {
    //     std::cout<<send_str.c_str()<<std::endl;
    // }

    // //从send_str反序列化为一个login请求对象
    // LoginRequest reb;
    // if(reb.ParseFromString(send_str))
    // {
    //     std::cout<<reb.name()<<std::endl;
    //     std::cout<<reb.pwd()<<std::endl;
    // }
    }

    //protobuf用法2
    {
    GerFriendsList userlist;
    ReturnMessage *rp =userlist.mutable_ret();
    rp->set_errcode(0);
    rp->set_errmsg("");


    //添加第一个用户
    User* user1=userlist.add_userlist();
    user1->set_age(25);
    user1->set_name("lzy");
    user1->set_gender(User::MAN);

    //添加第二个用户
    User* user2=userlist.add_userlist();
    user2->set_age(25);
    user2->set_name("tlm");
    user2->set_gender(User::WOMAN);

    //获取列表元素个数
    std::cout<<userlist.userlist_size()<<std::endl;  //输出2

    }
    


    return 0;
}
