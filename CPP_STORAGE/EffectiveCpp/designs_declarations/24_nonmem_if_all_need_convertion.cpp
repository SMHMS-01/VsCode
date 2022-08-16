#include <iostream>
#include <windows.h>

using namespace std;

//条款24：若所有参数皆需类型转换，请为此采用non-member函数

//如果你需要为某个函数所有参数（包括被this指针所指的那个隐喻函数）进行类型转换，那么这个函数必是个non-member函数
class Ration
{
public:
    Ration(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {} //刻意允许int-to-Ration的implicit转换
    int numerator() const { return n; }
    int denominator() const { return d; }
    const Ration operator*(const Ration &rhs) const
    {
        return Ration(n * rhs.n, d * rhs.d);
    }

private:
    int n, d;

    friend const Ration operator*(const Ration &lhs, const Ration &rhs)
    {
        return Ration(lhs.n * rhs.n, lhs.d * rhs.d);
    }
};
const Ration operator*(const Ration &lhs, const Ration &rhs)
{
    return Ration(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}
void test()
{
    Ration a(1, 2);
    Ration b(3, 5);
    Ration c = a * b;
    c = c * a;
    c = c.operator*(2); //true: 2可隐式转换

    //false: 只有当参数被列于参数列内，这个参数才是隐式类型转换的合格选拔这。地位相当于"被调用的成员函数所隶属的那个对象"
    //即this对象——的那个隐喻函数，绝不是隐式转换的合格参与者。
    // c = 2.operator * (c);//false
    c = operator*(2, c); //true

    c = 2 * c; //true! non-member函数的作用，隐式转换fine
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
