#include <iostream>
#include <windows.h>
#include <bits.h>
using namespace std;

//固有的不可移植的特性
//位域、volatie限定符
void volatie_test()
{
    volatile int display_reqister; //该int值可能发生改变,display_reqister是一个volatile int 对象
    volatile string *curr_str;     //curr_str指向每一个volatile对象
    volatile int iax[10];          //iax每一个元素都是volatile

    volatile int v;
    int *volatile vip;           //一个指向int的volatile指针
    volatile int *ivp;           //一个指向volatile int的指针
    volatile int *volatile vivp; //一个指向volatile int的volatile 指针

    // int *ip = &v;//false: we must be choose a volatile pointer
    ivp = &v;
    vivp = &v;
}

//合成的拷贝对volatile对象无效
class Foo
{
public:
    Foo(const volatile Foo &); //

    Foo &operator=(volatile const Foo &);

    Foo &operator=(const volatile Foo &) volatile;
};

//链接指示：extern "C"
extern "C"
{
#include <string.h>
}
extern "C" void (*pf)(int); //指向一个C函数
void (*pf2)(int);           // 指向一个C++函数
// pf = pf2;/false: 类型不同
//有的C++编译器会接受这种赋值操作并将其作为语言的拓展，但是从严格意义上来说是非法的

//链接指示对整个声明都有效
//f1是一个C函数，它的形参是一个指向C函数的指针
extern "C" void f1(void (*)(int));
//如果我们希望给C++函数传递一个指向C函数的指针，则必须使用类型别名
extern "C" typedef void FC(int);
//f2是一个C++函数，该函数的形参是指向C函数的指针
void f2(FC *);

//导出C++函数到其他语言
//calc函数可以被C程序调用
extern "C" double calc(double dparm)
{ /*…………*/
}

int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
