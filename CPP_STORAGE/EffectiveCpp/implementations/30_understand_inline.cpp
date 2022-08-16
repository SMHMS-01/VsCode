#include <iostream>
#include <windows.h>

using namespace std;

//条款30：透彻了解inlining的里里外外
//将大多数inlining限制在小型、被频繁调用的函数身上。这便可使得日后的调试过程和二进制升级更容易，也可以使潜在的代码膨胀问题最小化，使程序的速度提升最大化。
//不要只因为function templates出现在头文件，就将他们声明为inline.

//注意：
//1.inline不能包括复杂的控制语句，如循环语句和switch语句；
//2.只将规模很小的(一般5个语句以下)而是使用频繁的函数声明为内联函数。
class Temp
{

public:
   //隐式inline
   Temp(int amount) : amount(amount) {}
   void print_amount() const { cout << amount << endl; }
   int doubleVal();

private:
   int amount;
};
//显示inline
inline int Temp::doubleVal()
{
   return amount *= 2;
}
int main()
{
   SetConsoleOutputCP(65001);
   system("pause");
   return 0;
}
