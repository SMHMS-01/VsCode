#include <iostream>
#include <windows.h>

using namespace std;

// iterator 源碼完整重列
struct Input_iterator_tag
{
};
struct Output_iterator_tag
{
};
struct Forward_iterator_tag : public Input_iterator_tag
{
};
struct Bidirectional_iterator_tag : public Forward_iterator_tag
{
};
struct Random_access_iterator_tag : public Bidirectional_iterator_tag
{
};

//迭代器类别
template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T *, typename Reference = T &>
struct Iterator
{
    typedef Category Iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

//萃取机
template <typename Iterator>
struct Iterator_traits
{
    typedef typename Iterator::Iterator_category Iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

//针对原生指针而设计的traits偏特化版
template <typename T>
struct Iterator_traits<T *>
{
    typedef random_access_iterator_tag Iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};

//针对原生pointer-to-const而设计的traits偏特化版
template <typename T>
struct Iterator_traits<const T *>
{
    typedef random_access_iterator_tag Iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
};

//这个函数式可以方便地决定某个迭代器的类型
template <typename Iterator>
inline typename Iterator_traits<Iterator>::Iterator_category Iterator_category(const Iterator &)
{
    typedef typename Iterator_traits<Iterator>::Iterator_category category;
    return category();
}

// 這個函式可以很方便地決定某個迭代器的 distance type
template <typename Iterator>
inline typename Iterator_traits<Iterator>::difference_type *distance_type(const Iterator &)
{
    return static_cast<typename Iterator_traits<Iterator>::difference_type *>(0);
}

// 這個函式可以很方便地決定某個迭代器的 value type
template <typename Iterator>
inline typename Iterator_traits<Iterator>::value_type *value_type(const Iterator &)
{
    return static_cast<typename Iterator_traits<Iterator>::value_type *>(0);
}

// 以下是整組 distance 函式
template <typename InputIterator>
inline typename Iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last,
                                                                          input_iterator_tag)
{
    typename Iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

template <typename RandomAccessIterator>
inline typename Iterator_traits<RandomAccessIterator>::difference_type _distance(RandomAccessIterator first, RandomAccessIterator last,
                                                                                 Random_access_iterator_tag)
{
    return last - first;
}

template <typename InputIterator>
inline typename Iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
{
    typedef typename Iterator_traits<InputIterator>::Iterator_category category;
    return _distance(first, last, category());
}

// 以下是整組 advance 函式
template <typename InputIterator, typename Distance>
inline void _advance(InputIterator &i, Distance n, Input_iterator_tag)
{
    while (n--)
        ++i;
}

template <typename BidirectionalIterator, typename Distance>
inline void _advance(BidirectionalIterator &i, Distance n, Bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--)
            ++i;
    else
        while (n++)
            --i;
}

template <typename RandomAccessIterator, typename Distance>
inline void _advance(RandomAccessIterator &i, Distance n, Random_access_iterator_tag)
{
    i += n;
}

template <typename InputIterator, typename Distance>
inline void advance(InputIterator &i, Distance n)
{
    _advance(i, n, Iterator_category(i));
}

void test()
{
    Iterator_traits<int *>::pointer p;
    int p2 = 999;
    p = &p2;
    cout << *p << endl;
    cout << typeid(distance_type(p)).name() << endl;
    cout << typeid(value_type(p)).name() << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
