#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>
#include <initializer_list>
using namespace std;

void error_msg(error_code e, initializer_list<string> i1);
void test()
{
    //含有可变形参的函数
    //该对象中的元素永远都是常量
    initializer_list<string> lls;
    error_code e;
    string expect = "expect", actual = "actual";
    if (expect != actual)
        error_msg(e, {"function", "okay", expect, actual});
}
void error_msg(error_code e, initializer_list<string> i1)
{
    cout << e.message() << " ";
    for (const auto &elem : i1)
        cout << elem << ' ';
    cout << endl;
}

//转发
void f(int v1, int &v2)
{
    cout << v1 << " " << ++v2 << endl;
}
void g(int &&v1, int &v2)
{
    cout << v1 << " " << v2 << endl;
}
template <typename T, typename F1, typename F2>
void fcn(T t, F1 &&f1, F2 &&f2)
{
    f(f2, f1);
}
void fcnCalled()
{
    int i, j = 0;
    f(42, j);      //改变了j的值
    fcn(f, j, 42); //没有改变j的值，因为传递是j的拷贝，j的拷贝的引用++而不会改变j自身
    fcn(g, i, 42);
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    fcnCalled();
    string s("abcde");
    new (&s) string("i love jk");
    s.~basic_string();
    cout << s << endl;
    string *a = new string("Homura");
    a->~basic_string();
    cout << *a << endl;
    system("pause");
    return 0;
}
