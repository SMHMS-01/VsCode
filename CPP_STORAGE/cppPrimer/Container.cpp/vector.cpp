#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

void test()
{
    vector<string>::iterator it;
    string::iterator it2;
    vector<int>::const_iterator it3;
    string::const_iterator it4;

    const vector<int> cv;
    auto it5 = cv.rbegin(); //
    vector<int> c;
    auto it6 = c.crbegin(); //it6 defalut type is vector<int>::const_iterator
}
void test1()
{
    size_t index;
    unsigned index2;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *e = &arr[10];
    for (int *a = arr; a != e; ++a)
        cout << *a << ' ';
    // cout << sizeof(index) << sizeof(index2) << endl;
    cout << endl;

    //standard function libray
    int *beg = begin(arr);
    int *last = end(arr);
    for (; beg != last; ++beg)
        cout << *beg << ' ';
    cout << end(arr) - begin(arr) << endl;
}
void test2()
{
    int a[] = {9, 1, 2, 3};
    int b[] = {2, 3, 4, 5};

    int *p = &a[2];
    int *q = &a[3];
    p += q - p;
    // cout << *p << endl;

    //make array to initilaize vector
    int a2[] = {1, 2, 3, 4, 5};
    vector<int> vtr(begin(a2), end(a2));
}

//vector 的增长
void test2()
{
    //shrink_to_fit只适用于vector, string and deque
    //capacity and  reserve 只适用于vector and string
    //c.shrink_to_fit() 将capacity()减少为size()的大小,这只是一个请求，不代表真的会退还内存
    //c.capacity()  不重新分配内存的话，c可以保存多少元素
    //c.reserve(n)   分配至少能容纳n的内存空间
}
int main()
{
    SetConsoleOutputCP(65001);
    // test1();
    int a[] = {9, 1, 2, 3};
    int *p = &a[2];
    //内置数组下标类型是有符号型，可以处理负值，而容器下标则不可
    int k = p[-2];
    // cout << k << endl;
    // test2();
    test1();
    system("pause");
    return 0;
}
