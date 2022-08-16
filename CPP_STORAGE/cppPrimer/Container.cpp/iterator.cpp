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

//再探迭代器
//1.插入迭代器（insert iterator):这些迭代器被绑定在一个容器上，可以向容器插入元素；
//2.流迭代器（stream iterator）：这些迭代器被绑定在输入或输出流上，可以用来遍历所关联的IO流；
//3.反向迭代器（reverse iterator）：这些迭代器向后而不是向前移动。除了forward_list以外的容器都有反向迭代器；
//4.移动迭代器（move iterator）：这些专用迭代器不是拷贝其中的元素，而是移动他们。

void insertIterator()
{
    list<int> l1{95, 62, 11, 23, 54, 12, 68, 99, 65, 14};
    list<int> l2, l3;
    copy(l1.cbegin(), l1.cend(), inserter(l2, l2.begin()));

    replace_copy_if(
        l2.cbegin(), l2.cend(), inserter(l3, l3.begin()), [](int n)
        { return n > 50; },
        0);
    for_each(l2.cbegin(), l2.cend(), [](int i)
             { cout << i << ends; });
    cout << endl;
    for_each(l3.cbegin(), l3.cend(), [](int i)
             { cout << i << ends; });
    cout << endl;
}

void streamIterator()
{
    vector<int> vec;
    istream_iterator<int> int_it(cin);
    istream_iterator<int> end;
    while (int_it != end)
    {
        vec.emplace_back(*int_it++);
    }
}

void reverseIterator()
{
    vector<string> v{"Akemi", " Homura", " Sai", "Ko!"};
    for_each(v.crbegin(), v.crend(), [=](const string &str)
             { cout << str << ends; });
    cout << endl;
    const char c[] = "Akemi Homura Sai Ko, she is me lovest one.";
    auto it = find(crbegin(c), crend(c), ',');
    cout << string(crbegin(c), it) << endl;     //如果这么写则会倒序输出
    cout << string(it.base(), cend(c)) << endl; //base()成员函数会把it转换成一个普通迭代器
    cout << string(cbegin(c), it.base()) << endl;
}

//P369
int main()
{
    SetConsoleOutputCP(65001);
    insertIterator();
    // streamIterator();
    reverseIterator();
    system("pause");
    return 0;
}
