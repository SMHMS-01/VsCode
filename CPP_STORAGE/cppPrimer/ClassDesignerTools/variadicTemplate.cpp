#include <iostream>
#include <windows.h>
#include <tuple>
using namespace std;

//
template <typename T, typename... Args>
void foo(const T &t, const Args &...rest);

//sizeof...
template <typename... Args>
void g(Args... args)
{
    cout << sizeof...(Args) << endl; //类型参数的数目
    cout << sizeof...(args) << endl; //函数参数的数目
}

template <typename T, typename... Args>
//Args是一个模板参数包；rest是一个函数参数包
//Args表示零个或多个模板类型参数
//rest表示零个或多个函数参数
void foo(const T &t, const Args &...rest)
{
    cout << sizeof...(Args) << endl; //类型参数的数目
    cout << sizeof...(rest) << endl; //函数参数的数目
}

void test()
{
    int i = 0;
    double d = 3.14;
    string s("how bow now");
    //编译器实例化  void foo(const int&,const string&,const int&,const double&)
    foo(i, s, 42, d); //包中有三个参数
    //编译器实例化  void foo(const int&,const char[3]&,const double&)
    foo(i, "hi", d); //包中有两个参数
    //编译器实例化  void foo(const char[6]&)
    foo("akemi"); //空包
}

//编写可变参数函数模板

//用来终止递归并打印最后一个元素的函数
//此函数必须在可变参数版本的print定义之前声明
template <typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t; //包中最后一个元素之后不打印分隔符
}
//包中除了最后一个元素之外的其他元素都会调用这个版本的print
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args &...rest)
{
    os << t << ", ";           //打印第一个实参
    return print(os, rest...); //递归调用，打印其他实参
}

int main()
{
    SetConsoleOutputCP(65001);
    test();
    print(cout, 20, '#', '$', "akemi homura", 99.987);
    system("pause");
    return 0;
}
