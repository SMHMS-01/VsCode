#include <iostream>
#include <windows.h>

using namespace std;

//条款45:运用成员函数模板接受所有兼容类型
// 请使用member function templates  (成员函数模板)生成"可接受所有兼容类型"的函数
//如果你声明member templates用于"泛化copy构造"或者"泛化assignment操作",你还是需要声明正常的copy构造函数和copy assignment运算符

//Template And Generic Programming
class Top
{
};
class Middle : public Top
{
};
class Bottom : public Middle
{
};

template <typename T>
class SmartPtr
{
public:
    SmartPtr() = default;
    SmartPtr(T *realPtr) : heldPtr(realPtr) {}
    template <typename U>
    SmartPtr(const SmartPtr<U> &other) : heldPtr(other.get()) {}
    T *get() const { return heldPtr; }

    template <typename X>
    SmartPtr &operator=(SmartPtr<X> const &r)
    {
    }
    SmartPtr &operator=(SmartPtr const &r) {}

private:
    T *heldPtr;
};
template <typename T>
class Ptr
{
public:
    Ptr() = default;
    Ptr<T>(const Ptr &);
};
void test()
{
    Top *pt1 = new Middle;
    Top *pt2 = new Bottom;
    const Top *pct2 = pt1;
    SmartPtr<Top> p = SmartPtr<Middle>(new Middle);
    // SmartPtr<Bottom> pt2 = SmartPtr<Top>(new Top);//false: 子类转换为父类不可取
}
int main()

{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
