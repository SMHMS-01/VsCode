#include <iostream>
#include <windows.h>

using namespace std;

//条款53：不要忽略编译器的警告
//严肃对待编译器发出的警告信息，努力在你的编译器的最高（最严苛）警告级别下争取"无任何警告"的荣誉
//不要过度依赖编译器的报警能力，因为不同的编译器对待事情的态度并不相同。一旦移植到另一个编译器上，你原本依赖的警告信息有可能消失
class B
{
public:
    virtual void f() const { cout << "i am base" << endl; }
};
class D : public B
{
public:
    virtual void f() /*const*/ { cout << "i am derived" << endl; } //没有被重新声明，而是遮掩了base版
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
