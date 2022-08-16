#include <iostream>
#include <windows.h>

using namespace std;

//48:认识template元编程
//Template meatprogramming (TMP，模板元编程)可将工作由运行期移向编译期，因而得以实现早期错误侦测和更高的执行效率；
//模板元编程的意思是：编程系统将会执行我们所写的代码，来生成新的代码。而这些新代码才真正实现了我们所期望的功能。元编程最大的特点在于：
//某些用户自定义的计算可以在编译期进行，二者通常能够在性能和接口简单性方面带来好处。

//TMP可被用来生成"基于政策选择组合"的客户定制代码，也可以用来避免生成对某些特殊类型并不适合的代码.

// TMP
//涉及模板函数具象化范例：
template <unsigned n>
struct Factorial
{
   enum
   {
      value = n * Factorial<n - 1>::value
   };
};
template <>
struct Factorial<0>
{
   enum
   {
      value = 1
   };
};

template <int N>
struct Fbi
{
   enum
   {
      Result = Fbi<N - 1>::Result + Fbi<N - 2>::Result
   };
};
template <>
struct Fbi<1>
{
   enum
   {
      Result = 1
   };
};
template <>
struct Fbi<0>
{
   enum
   {
      Result = 0
   };
};
int main()
{
   SetConsoleOutputCP(65001);
   cout << Factorial<5>::value << " " << Factorial<10>::value << endl;
   cout << Fbi<10>::Result << endl;
   system("pause");
   return 0;
}
