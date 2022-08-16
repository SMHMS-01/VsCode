#include <iostream>
#include <windows.h>

using namespace std;
//条款26：尽可能延后变量定义式的出现时间
//尽可能延后变量定义式的出现时间，这样做可以增加程序的清晰度并改善程序效率。

const size_t n = 10;
class Widget
{
public:
    Widget() {}
    Widget(int i) : n(i) {}

private:
    int n;
};

static const size_t MinimumPasswordLength = 6;
string encryptPassword(const string &password)
{
    string encrypted; //如果抛出异常，那么encrypted没起到任何作用，而且你还需要承担它的构造和析构成本
    if (password.length() < MinimumPasswordLength)
        throw logic_error("Password is too short");
    //...string encrypted;//可放置在后
    return encrypted;
}

//A:
void test()
{
    Widget w;
    for (int i = 0; i < n; ++i)
        w = i;
}
//B:
void test2()
{
    for (int i = 0; i < n; ++i)
    {
        Widget w(i);
    }
}

//A:一个构造函数+一个析构函数+n个赋值操作
//B：n个构造函数+n个析构函数
//如果classes的一个赋值成本低于一组构造+析构成本，选A，尤其是n很大的时候；
//此外，做法A造成名称w的作用域（覆盖整个循环）比做法B更大，有时候那对程序的可理解性和易维护性造成冲突。
//因此，除非（1）你知道赋值成本比“构造+析构”成本低；（2）你正在维护代码中效率高度敏感的部分，否则选B。
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
