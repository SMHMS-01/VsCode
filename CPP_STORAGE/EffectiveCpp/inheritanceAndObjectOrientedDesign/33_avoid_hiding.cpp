#include <iostream>
#include <windows.h>

using namespace std;

//条款33：避免遮掩继承而来的名称
//derived class内的名称会遮掩base classes内的名称。在public 继承下从来没有人会希望如此。
//为了让被遮掩的名称再见天日，可使用using声明式或转交函数。

class Base
{
public:
   virtual void mf1() = 0;
   virtual void mf1(int);
   virtual void mf2();
   void mf3();
   void mf3(double);

private:
   int x;
};

class Derived : public Base
{
public:
   using Base::mf1;
   using Base::mf3; //让Base class内名为mf1和mf3的所有东西在Derived作用域内都可见(并且public)
   virtual void mf1();
   void mf3();
   void mf4();
};

class Derived2 : private Base
{
public:
   virtual void mf1() { Base::mf1(); } //转交函数(暗自成为inline)
   //inline转交函数的另一个用途是为那些不支持using声明式的老旧编译器另辟蹊径，将继承而来的名称汇入derived class作用域内。
};
void test()
{
   Derived d;
   int x;
   d.mf1(); //ok: call Derived::mf1
   // d.mf1(x); //error: Derived::mf1遮掩了Base::mf1，添加using Base::mf1；就可以了
   d.mf2(); //ok: call Base::mf2
   d.mf3(); //ok: call Derived::mf3
   // d.mf3(x); //error: Derived::mf3遮掩了Base::mf3

   Derived2 d2;
   d2.mf1();
   // d2.mf1(x);//false:   Base::mf1被遮掩
}
int main()
{
   SetConsoleOutputCP(65001);
   test();
   system("pause");
   return 0;
}
