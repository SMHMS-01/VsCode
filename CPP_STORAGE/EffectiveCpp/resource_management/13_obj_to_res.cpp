#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;

//条款13：以对象管理资源
//两个关键想法：
//1.获得资源后立刻放进管理对象
//2.管理对象应用析构函数确保资源被释放
class A
{
public:
   inline static A *creatA()
   {
      static A *a;
      return a;
   }

private:
   A *a;
};
void f()
{
   A *a = A::creatA();
   //我们必须负责销毁对象，但是由于各种原因，如过早的return语句、break、goto和continue等导致delete被忽略，最终内存泄漏...

   delete a;
}
//为了保证creatA()返回的资源总是被释放，我们需要把资源放在对象内，当控制流离开f，该对象的析构函数会自动释放哪些资源。
//许多资源被动态分布于heap内而后被用于单一区块或函数内，他们应该在控制流离开那个区块或函数内时被释放。
//标准库提供的auto_ptr正是针对这种形势而设计的产品。
//auto_ptr避免了下函数潜在的资源泄漏的可能性
//但是此处shared_ptr更加，原因:复习智能指针篇,重点在于强调"以对象管理资源"
void f2()
{
   shared_ptr<A> pA(A::creatA()); //auto_ptr的析构函数会自动删除pA
}
int main()
{
   SetConsoleOutputCP(65001);
   system("pause");
   return 0;
}
