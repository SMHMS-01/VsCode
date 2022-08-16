#include <iostream>
#include <windows.h>
#include <forward_list>
#include <deque>
#include <list>
#include <vector>
#include <array>
using namespace std;

//将一个容器初始化位另一个容器的拷贝
void test()
{
    list<string> author = {"folyd", "jason", "kmp"};
    vector<const char *> articles{"a", "an", "the"};

    list<int> l1;
    vector<double> v1(l1.begin(), l1.end());

    list<string> list2(author);
    // deque<string> authList(author); false: the container type doesn't match
    //vector<string> words(articles); false: data type doesn't match

    //true: const char* can be converted to string
    vector<string> word(articles.begin(), articles.end());
    forward_list<string> words(articles.begin(), articles.end());
}

//array container
void array()
{
    //array have fixed size
    std::array<int, 10> a1; //std::array<dataType,size_type>
    std::array<int, 10>::size_type i;
    int dig[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int cpy[10]=dig; false: 我们并不能对内置数组类型进行拷贝或对象赋值操作
    std::array<int, 10> a2 = a1; //true
}

//容器的赋值(仅顺序容器)与交换
void assign_swap()
{
    std::array<int, 10> a1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 10> a2 = {0};
    a2 = a1;
    a1 = {0};
    swap(a1, a2); //a1.swap(a2);            swap()通常比拷贝元素快得多
    for (const auto &s : a1)
        cout << s << ends;
    cout << endl;
    //assign()  该操作不适用于array和关联容器
    vector<int> v1{0, 1, 2}, v2(3, 0);
    v2.assign(5, 9);
    v1.assign(v2.begin(), v2.end());
    for (const auto &s : v2)
        cout << s << ends;
    cout << endl;
    for (const auto &s : v1)
        cout << s << ends;
    cout << endl;

    list<string> l1{"a", "b", "d"};
    vector<string> v{"123", "456"};
    l1.insert(l1.end(), "c");
    l1.insert(--l1.end(), v.end() - 1, v.end());
    for (const auto &s : l1)
        cout
            << s << ends;
}

void forward_list_()
{
    forward_list<int> fl{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int>::iterator prev = fl.before_begin(); //首前元素
    auto curr = fl.begin();                               //第一个元素
    while (curr != fl.end())
    {
        if (*curr % 2 == 0)
            curr = fl.erase_after(prev); //delete element in front of prev
        else
        {
            prev = curr;
            ++curr;
        }
    }
    for (const auto &i : fl)
        cout << i << ends;
}
int main()
{
    SetConsoleOutputCP(65001);
    // test();
    // assign_swap();
    forward_list_();
    system("pause");
    return 0;
}
