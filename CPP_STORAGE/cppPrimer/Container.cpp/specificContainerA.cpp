#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
#include <numeric>
#include <iterator>
#include <functional>
#include <list>

using namespace std;

bool comp(const string &s1, const string &s2)
{
    return s1.compare(s2);
}
bool comp_int(const int &a, const int &b)
{
    return a <= b;
}
//特定容器算法
void specific_container()
{
    using namespace std::placeholders;
    list<string> l1{"Akemi", " Homura", " Sai", "Ko!"};
    list<string> l2{"she", "is", "me", "lovest", "one"};
    l1.merge(l2);
    if (!l1.empty())
        for_each(l1.cbegin(), l1.cend(), [=](const string &str)
                 { cout << str << ends; });

    cout << endl;
    if (l2.empty())
        cout << "list 2 is empty" << endl;
    else
        for_each(l2.cbegin(), l2.cend(), [](const string &str)
                 { cout << str << ends; });
    cout << endl;

    list<int> lst = {0, 4, 4, 8, 7568, 4, 243, 45, 6};
    list<int> lst_{21, 24, 66, 321, 11, 0, 164, 99};
    lst.merge(lst_, comp_int);
    //调用erase删除同一个值的连续拷贝
    lst.unique([=](int a, int b)
               { return a == b; });

    lst.remove(7568);
    if (!lst.empty())
        for_each(lst.cbegin(), lst.cend(), [=](const int &n)
                 { cout << n << ends; });
}
int main()
{
    SetConsoleOutputCP(65001);
    specific_container();
    system("pause");
    return 0;
}
