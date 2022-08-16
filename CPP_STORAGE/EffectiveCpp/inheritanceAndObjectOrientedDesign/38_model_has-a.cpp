#include <iostream>
#include <windows.h>
#include <list>
#include <algorithm>
using namespace std;

//条款38:通过复合塑模出has-a或"根据某物实现出"

//复合的意义和public继承完全不同
//在应用域，复合意味has-a。在实现域，复合意味is-implemented-in-terms-of(根据某物实现出)
template <typename T>
class Set
{
public:
    bool member(const T &item) const;
    void insert(const T &item);
    void remove(const T &item);
    std::size_t size() const;

private:
    list<T> rep;
};

template <typename T>
inline bool Set<T>::member(const T &item) const
{
    return find(rep.begin(), rep.end(), item) != rep.end();
}

template <typename T>
inline void Set<T>::insert(const T &item)
{
    if (!member(item))
        rep.emplace_back(item);
}

template <typename T>
inline void Set<T>::remove(const T &item)
{
    typename list<T>::iterator it = find(rep.begin(), rep.end(), item);
    if (it != rep.end())
        rep.erase(it);
}

template <typename T>
inline size_t Set<T>::size() const { return rep.size(); }

void test()
{
    Set<int> s;
    s.insert(10);
    cout << s.size();
    s.remove(10);
    cout << s.size();
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
