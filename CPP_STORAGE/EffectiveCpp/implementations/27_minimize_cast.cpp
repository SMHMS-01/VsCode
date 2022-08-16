#include <iostream>
#include <windows.h>
#include <vector>
#include <memory>
using namespace std;

//条款27：尽量少做转型动作
//如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast，如果有个设计需要转型动作，试着发展无需转型的替代设计。
//如果转型是必要的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，而不需将转型放进他们的代码内。
//宁可使用C++-style(新式)转型，不要使用技术转型。前者很容易辨识出来，而且也比较有着分门别类的职掌。

class windows
{
public:
    virtual void onResize() {}
};
class specialWindows : public windows
{
public:
    virtual void onResize()
    {
        static_cast<windows>(*this).onResize(); //derived onResize()实现代码：将*this转换为windows，然后调用其onResize()，实际不行
        //实际上，上述代码并非你预期中的"这段程序将*this转换为windows，对函数onResize的调用也因此调用了windows::onResize"。
        //但是它调用的并不是当前对象上的函数，而是稍早转型动作所建立的一个"*this对象之base class成分"的暂时副本对象身上的onReszie！
        //如果onResize修改了对象内容，当前对象并没被改动，改动的是副本。如果SpecialWindows::onResize内如果也修改对象，那就是真的被改动了。
        //这会使当前对象进入"伤残"状态：其base class成分的更改没有被落实，而derived class的成分的更改倒落实了。

        //正确写法
        //拿掉转型动作
        windows::onResize();
    }
};

//dynamic_cast探讨
//dyna_cast无论是空间还是时间成本都是很高的，尽可能避免使用
//之所以需要dynamic_cast，通常是因为你想在一个你认定的derived class对象身上执行derived class操作函数，但你的手上却只有一个"指向base"的pointer
//或reference，你只能靠它们处理对象，有两个一般性做法可避免此问题：
//第一、使用容器并在其中存储直接指向derived class对象的指针(通常是智能指针，用对象管理内存),如此便消除了"通过base class接口处理对象"的需要。
//案例：
class Window
{
public:
    virtual void resize() {}
};
class SpecialWindow : public Window
{
public:
    virtual void resize() { Window::resize(); }
    void blink();
};

typedef std::vector<shared_ptr<Window>> VPW;
void test()
{
    VPW winPtrs;
    for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
    {
        if (SpecialWindow *psw = dynamic_cast<SpecialWindow *>(iter->get()))
            psw->blink();
    }
}

//应该改成
typedef std::vector<shared_ptr<SpecialWindow>> VPSW;
void test2()
{
    VPSW winPtrs;
    for (VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
        (*iter)->blink();
}

//另一种做法就是在base class内提供virtual函数做你想对各个window派生类做的事。即函数声明于base calss内并提供一份"什么也没做"的缺省实现代码
//参考条款34：区分接口继承和实现继承
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
