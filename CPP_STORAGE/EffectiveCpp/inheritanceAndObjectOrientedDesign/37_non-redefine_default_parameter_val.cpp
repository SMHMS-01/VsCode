#include <iostream>
#include <windows.h>

using namespace std;

//条款37：绝不重新定义继承而来的缺省参数值
//绝对不要重新定义一个继承而来的缺省实现函数，因为缺省参数值都是静态绑定，而virtual函数——你唯一应该覆写的东西——却是动态绑定
class shape
{
public:
    enum ShapeColor
    {
        Red,
        Green,
        Blue
    };
    virtual void draw(ShapeColor color = Red) const = 0;
};

class rectangle : public shape
{
public:
    virtual void draw(ShapeColor color = Green) const; //如果color=Red造成代码重复和相依性
};
class ellipse : public shape
{
public:
    virtual void draw(ShapeColor color = Blue) const;
};
void test()
{
    shape *ps;
    shape *pr = new rectangle; // pr静态类型是shape，动态类型是rectangle
    shape *pe = new ellipse;   //逻辑同上
    pr->draw();                //你以为是调用的是rectangle::draw，实际上调用的是静态类型shape::draw，就算把pointer换成references也一样
}

//结局方案：替代设计
class bird
{
public:
    enum Color
    {
        Red,
        Blue,
        Green
    };
    // non-virtual函数绝不应该被dervied classes覆写
    int colorGet(Color color = Red) const
    {
        doColorGet(color);
        return 0;
    }

private:
    virtual void doColorGet(Color color = Blue) const = 0; //真正的函数实现在此处完成
};
class penguin : public bird
{
public:
private:
    virtual void doColorGet(Color color) const; //不需要指定缺省参数值
};
int main()
{
    SetConsoleOutputCP(65001);
    // test();
    system("pause");
    return 0;
}
