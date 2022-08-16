#include <iostream>
#include <windows.h>
using namespace std;

//条款47:请使用traits classes表现类型信息
//traits classes使得"类型相关信息"在编译期可用.它们以templates和"templates特化"完成实现.
//整合重载技术后,traits classes有可能在编译期对类型执行if...else测试.

//请参考<<STL源码剖析>>---Traits编程技法    @STL\iterator\source

template <typename T>
struct MyIter
{
    typedef T value_type;
    T *ptr;
    MyIter(T *p = 0) : ptr(p) {}
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
};
template <typename I>
typename I::value_type func(I ite) { return *ite; }
void test()
{
    MyIter<int> ite(new int(11));
    cout << func(ite);
}
/*
template <typename I>
struct Iterator_traits
{
    typedef typename I::iterator_category iterator_category;
    typedef typename I::value_type value_type;
    typedef typename I::difference_type difference_type;
    typedef typename I::pointer pointer;
    typedef typename I::reference reference;
};

template <typename I, typename T>
typename Iterator_traits<I>::difference_type count(I first, I last, const T &value)
{
    typename Iterator_traits<I>::difference_type n = 0;
    for (; first != last; ++first)
        if (*first == value)
            ++n;
    return n;
}
*/

//针对相应型别difference_type, traits的两个(针对原生指针而写的)特化版本如下:
template <typename I>
struct Iterator_traits
{
    typedef typename I::difference_type difference_type;
};

//针对原生指针而设计的偏特化版本
template <typename T>
struct Iterator_traits<T *>
{
    typedef ptrdiff_t difference_type;
};

//针对原生的pointer-to-const而设计的偏特化版
template <typename T>
struct Iterator_traits<const T *>
{
    typedef ptrdiff_t difference_type;
};
//现在,当我们需要任何迭代器I的difference type,可以这么写:   typename Iterator_traits<T>::difference_type

//迭代器相应类别之三:reference type
void ref()
{
    int *pi = new int(5);
    const int *pci = new int(9);
    *pi = 7; // 對mutable iterator 做提領動作時，獲得的應該是個左值，允許賦值。
    // *pci = 1; // 這個動作不允許，因為 pci 是個 constant iterator，
    // 提領 pci 所得結果，是個右值，不允許被賦值。
}

// 迭代器相應型別之四：pointer type
template <typename T>
struct Iterator_Traits
{
    typedef typename T::pointer pointer;
    typedef typename T::reference reference;
};
//针对原生指针而设计的偏特化版
template <typename T>
struct Iterator_Traits<T *>
{
    typedef T *pointer;
    typedef T &reference;
};
//针对原生的pointer-to-const而设计的偏特化版
template <typename T>
struct Iterator_Traits<const T *>
{
    typedef const T *pointer;
    typedef const T &reference;
};
int main()
{
    SetConsoleOutputCP(65001);
    test();
    cout << endl;
    system("pause");
    return 0;
}