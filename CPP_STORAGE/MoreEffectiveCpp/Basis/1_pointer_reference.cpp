#include <iostream>
#include <windows.h>

using namespace std;

//条款01：指针与引用的区别
void test()
{
    char *pc = 0;
    char &rc = *pc; //引用指向空，绝不该这样写
}

void printDouble(const double &rd)
{
    cout << rd; //不用检查，引用必定有指向
}
void printDouble(const double *pd)
{
    if (pd) //检查是否为空
        cout << *pd;
}

void test()
{
    string s1("Nancy");
    string s2("Clancy");
    string &rs = s1;  // rs 引用 s1
    string *ps = &s1; // ps 指向 s1
    rs = s2;          // rs 仍旧引用 s1,但是 s1 的值现在是"Clancy"
                      // ps 现在指向 s2;s1 没有改变
    ps = &s2;
}
// 总的来说，在以下情况下你应该使用指针，一是你考虑到存在不指向任何对象的可能（在 这种情况下，你能够设置指针为空），
// 二是你需要能够在不同的时刻指向不同的对象（在这 种情况下，你能改变指针的指向）。如果总是指向一个对象并且一旦指向一个对象后就不会改变指向，那么你应该使用引用。
// 还有一种情况，就是当你重载某个操作符时，你应该使用引用。最普通的例子是操作符 []。这个操作符典型的用法是返回一个目标对象，其能被赋值。
// 当你知道你必须指向一个对象并且不想改变其指向时，或者在重载操作符并为防止不必 要的语义误解时，你不应该使用指针。而在除此之外的其他情况下，则应使用指针。
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
