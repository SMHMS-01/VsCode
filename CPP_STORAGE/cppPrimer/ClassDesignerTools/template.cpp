#include <iostream>
#include <windows.h>
#include <type_traits>
using namespace std;

template <typename T, typename F = less<T>>
bool compare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2))
        return false;
    if (f(v2, v1))
        return true;
    return false;
}

class A
{
public:
    explicit A(size_t s) : sz(s) {}
    static inline bool A_compare(const A &a1, const A &a2) { return a1.sz <= a2.sz; }

private:
    size_t sz;
};

//显示模板实参
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

void test()
{
    bool i = compare(0.56, 0.45);
    cout << i << endl;
    bool j = compare('a', '#');
    cout << j << endl;
    A a1(21), a2(3);
    bool k = compare(a1, a2, A::A_compare);
    cout << k << endl;
    bool l = compare<int>(9, 10); //正常类型转换应用于显示指定的实参

    /*************************************************************************************************************/
    // auto val = sum<int>(10, 20);            //long int sum(long int, short);必须按照顺序，否则可能无法识别，或者更改模式，如下：
    // auto val2 = sum<int, int, int>(1, 0.9); //long sum(int,double);
}

//尾置返回类型与类型转换
template <typename T>
// auto fcn(T beg, T end) -> decltype(*beg) //尾置返回类型允许我们在参数列表之后声明返回类型
auto fcn(T beg, T end) -> typename remove_reference<decltype(*beg)>::type //褪去引用，返回元素值的拷贝
{
    return *beg;
}

//函数指针与实参推断
template <typename T>
inline bool compare_(const T &v1, const T &v2)
{
    return v1 < v2;
}
void test2()
{
    bool (*p1)(const int &, const int &) = compare_;
    void func(bool (*)(const string &, const string &));
    void func(bool (*)(const int &, const int &));
    // func(compare_<string>); //如果不加上<string>就无法识别调用哪一个
}

//  模板实参推断和引用
template <typename T>
void test3(T &&val) //传入右值（int）则T=int； 左值则T=int&
{
    T t = val;
    t = val + 10;
    if (t == val) //如果传入的是左值，那么一直会是true
        cout << "true" << endl;
}

template <typename T>
void test3(const T &val) //左值和const右值
{
    T t = val;
    t = val + 10;
    if (t != val)
        cout << boolalpha << false << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    test();
    test2();
    const int i = 99;
    test3(i);
    test3(99);
    system("pause");
    return 0;
}
