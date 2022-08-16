#include <iostream>
#include <windows.h>

using namespace std;
//很重要的篇幅！
//条款25：考虑写出一个不抛出异常的swap函数p106

//首先，如果swap的缺省实现码对你的class或class template提供可接受的效率，你不需要额外做任何事。任何尝试置换(swap)那种对象的人都会获取缺省版本，而那将会有良好的运作
//其次，如果swap缺省实现版的效率不足（那几乎是意味你的class或template使用了某种pimpl手法），试着做以下事情：
//1.提供一个public swap成员函数，让它高效地置换你的两个对象值。这个函数绝不该抛出异常；
//2.在你的class或template所在的命名空间内提供一个non-member swap，并令他调用上述swap成员函数；
//3.如果你正在编写一个class而非class template，为你的class特化std::swap。并令它调用你的swap函数。
//最后，如果你调用swap，请确定包含一个using声明式，以便让std::swap在你的函数内曝光可见，然后不加任何namesapce修饰符，赤裸裸地调用swap。

//成员版swap绝不可抛出异常，因为那是swap的一个最好应用是帮助class（和class template）提供强烈的异常安全性保障。
//为用户定义类型进行std template全特化是好的，但千万不要尝试在std加入某些对std而言是全新的东西（std标准只对C++标准委员会所定义）。
class Widget
{
public:
    Widget(size_t size) : data(new int[size]), sz(size) {}
    void insert(int data)
    {
        static int i = 0;
        if (this->data)
            this->data[i++] = data;
    }
    int *getDataHeadAddress() { return data; }
    void swap(Widget &other)
    {
        using std::swap;
        swap(data, other.data);
    }
    void print()
    {
        for (int i = 0; i < sz; ++i)
            cout << data[i] << ' ';
    }

private:
    int *data;
    size_t sz;
};
namespace std
{
    template <>
    void swap<Widget>(Widget &a, Widget &b)
    {
        a.swap(b);
    }
} // namespace std
void test()
{
    Widget w1(2), w2(3);
    cout << "the address of w1 is: " << w1.getDataHeadAddress() << "\nthe address of w2 is:" << w2.getDataHeadAddress() << endl;
    w1.insert(10);
    w1.insert(88);
    w1.print();
    cout << endl;
    swap(w1, w2);
    cout << "the address of w1 is: " << w1.getDataHeadAddress() << "\nthe address of w2 is:" << w2.getDataHeadAddress() << endl;
    w2.print();
}
int main()

{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
