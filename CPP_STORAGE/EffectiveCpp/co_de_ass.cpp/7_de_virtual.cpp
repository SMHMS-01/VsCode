#include <iostream>
#include <windows.h>

using namespace std;
//条款07：为多态基声明virtual析构函数
//因为动态数据类型的原因，声明为virtual函数，析构函数在调用的时候可以根据动态数据类型来释放和销毁资源，因此可有效避免数据破坏与内存泄漏.
//带有多态性质的base classes应该声明一个virtual析构函数。如果class带有任何virtual函数，它就应该拥有一个virtual析构函数；
//classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不该声明virtual析构函数（比如标准string和STL容器）；
class TimeKeeper
{
public:
    TimeKeeper() = default;
    virtual ~TimeKeeper() = default;
};
class AtomicClock : public TimeKeeper //原子钟
{
};
class WaterClock : public TimeKeeper //水钟
{
};
class WristWatch : public TimeKeeper //腕表
{
};

class SpecialString : public std::string
{
public:
    ~SpecialString() { cout << typeid(SpecialString).name() << "be called" << endl; }
};
void test()
{
    SpecialString *pss = new SpecialString;
    string *ps = pss;
    delete ps; //未有定义，现实中*ps的SpecialString资源会泄露，因为SpecialString析构函数没被调用
}

class AWOV
{
public:
    virtual ~AWOV() = 0;
};
AWOV::~AWOV() {} //AWOV的derived classes必须实现，纯虚函数（抽象类）只提供接口
//根据析构函数调用的规则最深层派生（most derived）到基类，编译器会在AWOV的derived classes的析构函数中创建一个对~AWOV的调用作用，所以你必须为这个函数提供定义；
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
