#include <iostream>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include <vector>
#include <array>
#include <iterator>
using namespace std;

void test()
{
    vector<int> vec{0, 23, 5, 8, 90, 245, 666};
    int val = 66;
    auto result = find(vec.cbegin(), vec.cend(), val);
    cout << "The val is " << val << (result == vec.cend() ? " is not present" : " is present") << endl;

    std::array<int, 10> arr{0, 1, 2, 1, 2, 5, 2, 5, 6, 9};
    vector<int> vc;
    int i = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        vc.emplace_back(arr[i]);
        ++i;
    }
    int counts = count(vc.cbegin(), vc.cend(), 10);
    cout << "the 2 is " << counts << endl;
}
//只读算法
void Read()
{
    std::array<int, 10> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //前两个参数是迭代器范围，后面一个是和的初值
    int val = accumulate(a.cbegin(), a.cend(), 0); //在头文件numeric
    cout << val << endl;

    vector<string> vs{"Akemi", " Homura", " Sai", "Ko!"};
    //如果最后一个参数直接 " " 会错误，因为const char*没有定义 '+' 运算符，而string重载了 '+' 运算符
    string vs_ = accumulate(vs.cbegin(), vs.cend(), string(""));
    cout << vs_ << endl;

    vector<double> d{0, 12, 3, 4, 5, 6, 8.9, 24.4, 0.1, -2, 99.98653};
    vector<double>::value_type val_ = accumulate(d.cbegin(), d.cend(), 0.0000);
    cout << val_ << endl;
}

//操作两个序列的算法
void operation()
{
    std::array<int, 10> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 10> a2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> a3{0, 1, 2, 3, 4, 5, 6, 7, 9};
    bool b = equal(a.cbegin(), a.cend(), a3.cbegin());
    bool b1 = equal(a.cbegin(), a.cend(), a2.cbegin());
    cout << b << "-" << b1 << endl;
}

void write()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 9};
    fill(v.begin(), v.begin() + v.size() / 2, 99);
    for (const auto &a : v)
        cout << a << ends;

    cout << endl;

    vector<int> v2(20, 88);
    v2.reserve(20);
    fill_n(v2.begin(), v2.capacity(), 999);
    for (const auto &a : v2)
        cout << a << ends;
    cout << endl;
}

//插入迭代器
//保证算法有足够空间来容纳输出
void insertIterator()
{
    vector<int> v;
    auto it = back_inserter(v);
    *it = 42;
    fill_n(it, 10, 99);
    for (const auto &a : v)
        cout << a << ends;
    cout << endl;

    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a) / sizeof(a[0])];
    copy(begin(a), end(a), a2); //copy()返回的是尾后位置
    for (int *it = begin(a2); it != end(a2); it++)
        cout << *it << ends;

    cout << endl;
    //
    replace(begin(a), end(a), 2, 99);
    for (int *it = begin(a); it != end(a); it++)
        cout << *it << ends;

    cout << endl;
    //如果我们希望保留原序列不变，
    vector<int> vc;
    replace_copy(cbegin(a), cend(a), back_inserter(vc), 2, 99);
    for (auto it = vc.begin(); it != vc.end(); it++)
        cout << *it << ends;
    cout << endl;
}

bool shorter(const string &s1, const string &s2)
{
    return s1.size() > s2.size();
}
//排序与去重
void sort_and_unique()
{
    std::array<string, 10> as{"Ak", "emi", "Hom", "ra", "Sai", "Ko"};
    vector<string> vs{"Abandon", "breach", "Bbq", "Crfat", "draft", "draft"};
    fill(as.begin() + 6, as.end(), "----");

    //按字典排序
    sort(vs.begin(), vs.end());
    sort(as.begin(), as.end());
    for (const auto &s : as)
        cout << s << ends;

    cout << endl;
    for (const auto &s : vs)
        cout << s << ends;

    cout << endl;

    stable_sort(vs.begin(), vs.end(), shorter); //定制函数，请参考新的.cpp文件
    //unique并不真的删除重复元素,只是覆盖掉相邻的重复元素，使得不重复元素出现在序列的初始部分。
    //unique返回的迭代器指向最后一个不重复元素之后的位置。此位置之后的元素仍存在，但是未知其值。
    //为了真正的删除元素，必须要靠容器操作，因为算法并不会改变迭代器的大小！
    auto unique_back = unique(vs.begin(), vs.end());
    vs.erase(unique_back, vs.end());
    for (const auto &s : vs)
        cout << s << ends;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    Read();
    operation();
    write();
    insertIterator();
    sort_and_unique();
    system("pause");
    return 0;
}
