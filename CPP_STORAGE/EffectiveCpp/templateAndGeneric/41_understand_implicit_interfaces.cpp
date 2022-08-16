#include <iostream>
#include <windows.h>

using namespace std;

//条款41：了解隐式接口和编译期多态

//Templates及泛型编程的世界，与面向对象有根本上的不同。在此世界中显示接口和运行期多态仍然存在，但重要性降低。反倒是隐式接口和编译期多态移到前头了

class Widget
{
public:
    //显示接口：由函数的签名式(函数名称、参数类型、返回类型)组成
    Widget() = default;
    Widget(const Widget &) = default;
    ~Widget() = default;
    virtual size_t size() const { return sz; }
    virtual void normalize() {}
    void swap(Widget &other)
    {
        using std::swap;
        swap(sz, other.sz);
    }
    bool operator!=(int a) { return true; }

private:
    size_t sz = 0;
};

//隐式接口
//隐式转换的核心是：表达式的有效性
// 1.类和模板都支持接口和多态
//2.对类而言接口是显式的,以函数签名为中心;多态则是通过虚函数发生于运行期;
//3.对template参数而言,接口是隐式的,奠基于有效表达式,多态则通过template具现化和函数重新解析发生于编译期
int someNastWidget = 0;
template <typename T>
void doProcessing(T &w)
{
    if (w.size() > 10 && w != someNastWidget)
    {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    Widget w;
    doProcessing(w);
    system("pause");
    return 0;
}
