#include <iostream>
#include <windows.h>

using namespace std;

//条款46:需要类型转换时请为模板定义非成员函数@条款24
//template实参推导过程中并不考虑采纳"通过构造函数而发生的"隐式类型转换.
//当我们编写一个class template, 而它所提供之"与此template相关的"函数支持"所有参数之隐式类型转换"时,请将那些函数定义为"class template内部的friend函数"
template <typename T>
class Ration
{
    friend const Ration operator*(const Ration &lhs, const Ration &rhs)
    {
        return Ration(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator()); //如果定义在类外则编译失败
    }

public:
    Ration(const T &numerator = 0, const T &denominator = 1) : n(numerator), d(denominator) {} //刻意允许int-to-Ration的implicit转换
    T numerator() const { return n; }
    T denominator() const { return d; }
    const Ration operator*(const Ration &rhs) const
    {
        return Ration(n * rhs.n, d * rhs.d);
    }

private:
    T n, d;
};

void test()
{
    Ration<int> a(1, 2);
    Ration<int> b(3, 5);
    Ration<int> c = a * b;
    c = c * a;
    c = c.operator*(2);
    c = c * 2;
    c = 2 * c;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
