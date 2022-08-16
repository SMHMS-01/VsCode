#include <iostream>
#include <windows.h>

using namespace std;

//条款05：了解C++默认编写并调用了哪些函数
class Empty
{
public:
    Empty() = default;                            //default构造函数
    Empty(const Empty &rhs) = default;            //copy构造函数
    ~Empty() = default;                           //析构函数
    Empty &operator=(const Empty &rhs) = default; //copy assignment操作符
};
void test()
{
    //只有这些函数被需要（被调用），他们才会默默地被创建出来。下面代码造成上述每一个函数被编译器产出：
    Empty e1;
    Empty e2(e1);
    e1 = e2;
}
template <typename T>
class NameObject
{
public:
    NameObject(const string &name, const T &value);
    NameObject &operator=(const NameObject &nb);

private:
    string nameValue;
    T objectValue;
};
template <typename T>
NameObject<T>::NameObject(const string &name, const T &value) : nameValue(name), objectValue(value) {}

template <typename T>
NameObject<T> &NameObject<T>::operator=(const NameObject &nb)
{
    new (&nameValue) string(nb.nameValue);
    objectValue = nb.objectValue;
    return *this;
}
void test2()
{
    string newDog("Persephone");
    string oldDog("Satch");
    NameObject<int> p(newDog, 2);
    NameObject<int> s(oldDog, 10);
    // p = s; //false: you need creat assignment operator
    p = s; //true:创建赋值运算符后
}
//编译器可以暗自为class创建default构造函数、copy构造函数、copy assignment操作符，以及析构函数
//如果不想用编译器自动生成的函数，就该明确拒绝，参考条款06.
int main()
{
    SetConsoleOutputCP(65001);
    test2();
    system("pause");
    return 0;
}
