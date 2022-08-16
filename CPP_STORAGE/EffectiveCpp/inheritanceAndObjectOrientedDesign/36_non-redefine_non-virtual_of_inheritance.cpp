#include <iostream>
#include <windows.h>

using namespace std;

//条款36：绝不重新定义继承而来的non-virtual函数

//non-virtual的不变性和凌驾特异性的性质就决定了不该重更新定义它
//参考条款7
class Base
{
public:
    void mf();
};
class Derived : public Base
{
public:
    void mf();
};

void test()
{
    Derived d;
    //virtual的动态类型和non-virtual的静态类型的不同之处！
    Base *b = &d;     //调用Base::mf
    Derived *d2 = &d; //调用Derived::mf
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
