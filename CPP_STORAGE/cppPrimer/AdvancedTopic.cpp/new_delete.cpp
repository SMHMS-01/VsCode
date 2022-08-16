#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

//operator new 接口和 operator delete接口
void test()
{
    //这些版本可能抛出异常
    void *operator new(size_t); //value_type传递储存指定类型对象所需的字节
    // void *operator new(size_t, void *);//此函数不允许重载！
    void *operator new[](size_t); //传递存储数组中所需元素的空间
    void operator delete(void *) noexcept;
    void operator delete[](void *) noexcept;

    //这些版本承诺不会抛出异常
    void *operator new(size_t, nothrow_t &) noexcept;
    void *operator new[](size_t, nothrow_t &) noexcept;
    void operator delete(void *, nothrow_t &) noexcept;
    void operator delete[](void *, nothrow_t &) noexcept;
}

//malloc和free函数
void *operator new(size_t size)
{
    if (void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}
void operator delete(void *mem) noexcept
{
    free(mem);
}
//定位new表达式、显式的析构函数调用
void test2()
{
    string *s = new string[2]{"akemi", "homura"};
    s->~basic_string(); //销毁对象，但不会释放内存
    cout << *s << " " + *(++s) << endl;
}
void test3()
{
    string *s1 = new string("hello");

    new (s1) string("jesus");
    s1->~basic_string();

    cout << *s1 << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    test2();
    test3();
    system("pause");
    return 0;
}
