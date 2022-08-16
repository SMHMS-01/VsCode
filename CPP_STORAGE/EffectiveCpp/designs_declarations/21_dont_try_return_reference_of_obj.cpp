#include <iostream>
#include <windows.h>

using namespace std;
//条款21：必须返回对象时，不要妄想返回对象的reference

//绝对不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个
//local static对象而有可能同时需要多个这样的对象。条款4已经为"在单线程环境中合理返回reference指向一个local static对象"提供了一份设计声明
class Ration
{
public:
    Ration(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}

private:
    int n, d;
    // friend const Ration &operator*(const Ration &lhs, const Ration &rhs)
    // {
    //     Ration result(lhs.n * rhs.n, lhs.d * rhs.n); //如果为了避免函数结束销毁对象而选择堆空间创建，那可能更糟糕！
    //     //你可能会想使用static，就像所有用上static对象的设计一样，这一个立刻会造成我们对多线程的疑虑。此外，如果有值判断，那更糟！
    //     return result;
    // };
    //最好的写法
    friend const Ration operator*(const Ration &lhs, const Ration &rhs)
    {
        return Ration(lhs.n * rhs.n, lhs.d * rhs.d);
    }
};

void test()
{
    Ration a(1, 2);
    Ration b(3, 5);
    Ration c = a * b; //如果返回值是reference类型，则会报错。
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
