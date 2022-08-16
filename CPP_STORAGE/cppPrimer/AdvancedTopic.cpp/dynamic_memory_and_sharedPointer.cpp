#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>
using namespace std;

void test_shared()
{
    shared_ptr<string> p1;
    string str = "hello";
    p1 = make_shared<string>(str);
    shared_ptr<vector<int>> p2;
    p2 = make_shared<vector<int>>(10, 30);
    cout << *p1 << endl;
    for (int i = 0; i < (*p2).size(); ++i)
        cout << (*p2).at(i) << ends;
    cout << endl;
}
void test()
{
    int *a = new int(1000);
    cout << *a << endl;
    auto q1 = make_shared<int>(42), q2 = make_shared<int>(100);
    q2 = q1;
    cout << *q1 << endl;
    cout << (q2 == nullptr ? -1 : 1);
    cout << endl;

    shared_ptr<int> p(new int(42));
    int *q = p.get();
    {
        shared_ptr<int>(q);
    }
    int foo = *p;
    cout << foo << endl;
}

void allocatorF()
{

    allocator<string> alloc; //可以分配string的allocate对象
    alloc.allocate(4);       //分配4个未初始化的sting
}
int main()
{
    SetConsoleOutputCP(65001);
    test_shared();
    test();
    system("pause");
    return 0;
}
