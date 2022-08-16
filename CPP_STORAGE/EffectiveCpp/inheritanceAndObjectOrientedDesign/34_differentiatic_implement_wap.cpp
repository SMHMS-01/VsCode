#include <iostream>
#include <windows.h>

using namespace std;

//条款34：区分接口继承和实现继承
//接口继承和实现继承不同。在public继承之下，derived classes总是继承base class的接口。

class shape
{
public:
    shape() = default;
    //声明一个pure virtual函数的目的是为了让derived classes只继承其接口
    virtual void draw() const = 0;
    //声明impure virtual函数的目的，是让derived classes继承该函数的接口和缺省实现
    virtual void error(const string &msg);
    //声明non-virtual函数的目的是为了令derived classes继承函数的接口及一份强制性实现
    //其代表的意义是不变性(invariant)、凌驾特异性(specialization)，所以他绝不应该在dervied class中被重新定义。
    int objectID() const;
};
class RectAngle : public shape
{
public:
    RectAngle() = default;
    virtual void draw() const {}
};
class Ellipse1 : public shape
{
public:
    Ellipse1() = default;
    virtual void draw() const {}
};
void test()
{
    // shape *ps = new shape;//false: shape is obstract function
    shape *ps = new RectAngle;
    shape *ps2 = new Ellipse1;
    ps->draw();
    ps2->draw();
    ps->shape::draw();
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
