#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
#include <numeric>
#include <iterator>
#include <functional>
using namespace std;

bool sizeStandrad(const string &str)
{
    return str.size() < 6;
}
void test()
{
    vector<string> v{"Abandon", "breach", "Bbq", "Crfat", "draft", "draft"};
    partition(v.begin(), v.end(), sizeStandrad);
    for (const auto &s : v)
        cout << s << ends;
    cout << endl;
}

//lambda
//[capture list](parameter list) -> return type {function body}
void lambda()
{
    auto f = []
    { return 42; };
    cout << f() << endl;
    vector<string> v{"Abandon", "breach", "Bbq", "Crfat", "draft", "draft"};
    vector<string>::size_type sz = 5;
    //一个lambda只有在捕获列表中捕获一个他所在的函数的局部变量，才能在函数体中使用该函数
    //我想起了QT
    partition(v.begin(), v.end(), [sz](const string &str)
              { return str.size() < sz; });

    for (const auto &s : v)
        cout
            << s << ends;
    cout << endl;

    auto iter = find_if(v.cbegin(), v.cend(), [](const string &str)
                        { return str.size() >= 6; });
    cout << *iter << endl;

    //捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和它所在函数之外声明的名称
    for_each(v.cbegin(), v.cend(), [](const string &str)
             { cout << str << ends; });

    cout << endl;
}

void lambda2()
{
    unsigned short i = 99;
    auto z = [&i]() mutable
    { return ++i; };
    i = 0;
    auto j = z();
    cout << j << endl;

    //隐式捕获&可变lambda
    vector<string> v{"Abandon", "breach", "Bbq", "Crfat", "draft", "draft"};
    for_each(v.begin(), v.end(), [&](const string &str) mutable
             { cout << "***" + str << ends; });

    transform(v.begin(), v.end(), v.begin(), [=](const string &str)
              { return str.size() < 4 ? "###" : str; });
    cout << endl;
    for_each(v.begin(), v.end(), [=](const string &str) mutable
             { cout << str << ends; });
    cout << endl;
}

bool check_size(const string &str, string::size_type sz)
{
    return str.size() >= sz;
}
bool shorter(const string &s1, const string &s2)
{
    return s1 <= s2;
}
//parameter bind
void bind()
{
    using namespace std::placeholders; //注意bind占位符命名空间的调用
    // using std::placeholders::_1;
    vector<string> v{"Abandon", "breach", "Bbq", "Crfat", "draft", "draft"};
    vector<int>::size_type sz = 5;
    auto it = find_if(v.cbegin(), v.cend(), bind(check_size, _1, sz));
    cout << *it << ' ' << *(++it) << endl;
    sort(v.begin(), v.end(), shorter);
    sort(v.begin(), v.end(), bind(shorter, _2, _1)); //用bind()重排参数顺序，上个函数调用为shorter(A,B),而此次更改了顺序，为shorter(B,A)
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    lambda();
    lambda2();
    bind();
    +system("pause");
    return 0;
}
