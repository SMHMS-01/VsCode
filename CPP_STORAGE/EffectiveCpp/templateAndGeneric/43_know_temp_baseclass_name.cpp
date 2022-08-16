#include <iostream>
#include <windows.h>

using namespace std;

//43:学习处理模板化基类内的名称
//可在derived class template内通过"->"指涉base class templates内的成员名称,或藉由一个明白写出的"base class 资格修饰符"完成
class CompanyA
{
public:
    void sendClearText(const string &msg);
    void sendEncrypted(const string &msg);
};
class CompanyB
{
public:
    void sendClearText(const string &msg);
    void sendEncrypted(const string &msg);
};
class MsgInfo
{
};

template <typename Company>
class MsgSender
{
public:
    void sendClear(const MsgInfo &info)
    {
        string msg;
        Company c;
        c.senCleartext(msg);
    }
    void sendSecret(const MsgInfo &info)
    {
    }
};

template <typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo &info)
    {
        // sendClear(info); //false:调用base class函数:无法通过编译,因为不到LoggingMsgSender被具现化就无法确认Company是什么
    }
};

//为了让问题更具体化:
class CompanyZ
{
public:
    void sendEncrypted(const string &msg);
};
//全特化版:缺少某些功能
template <>
class MsgSender<CompanyZ>
{
public:
    void sendSecret(const MsgInfo &info);
};

template <typename Company>
class LOGGING_MSG_SENDER : public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo &info)
    {
        //sendClear(info);//如果company==companyZ,这个函数不存在. C++拒绝这个调用的原因:它知道base class template有可能被特化
        // 而那个特化版本可能不提供和一般性template相同的接口.因此它往往拒绝模板化基类内寻找继承而来的名称.

        //为了重投来过,我们必须有某种办法令C++"不进入templatized base classes观察"的行为失效.
        //有三个办法,第一是在base class函数调用动作之前加上"this->"
        this->sendClear(info);

        //第二种办法就是using
        //using MsgSender<Company>::sendClear
        //sendClear(info);//OK

        //第三种办法,明确指出被调用的函数位于base class内:这往往最不令人满意...这个会明确关闭virtual绑定行为
        //MsgSender<Company>::sendClear(info);
    }
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
