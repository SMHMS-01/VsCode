#include <iostream>
#include <windows.h>

using namespace std;

//条款10：令operator=返回一个refere to *this

//例子,复制连锁形式：
void exm()
{
    int x, y, z;
    x = y = z = 15;
    //根据赋值采用的右结合律
    x = (y = (z = 15));
}
//为了实现"连锁赋值"，赋值操作符就必须返回一个reference指向操作符的左侧实参

class Widget
{
public:
    Widget &operator=(const Widget &rhs)
    {
        return *this;
    }
    //该协议适用于所有赋值运算形式
    Widget &operator+=(const Widget &rhs)
    {
        return *this;
    }
};
int main()
{
    SetConsoleOutputCP(65001);
    Widget w1, w2, w3;
    w1 = w2 = w3;
    w2 += w3 += w1;
    system("pause");
    return 0;
}
