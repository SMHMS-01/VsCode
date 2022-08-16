#include <iostream>
#include <windows.h>
#include <functional>
#include <map>
using namespace std;

int add(int i, int j) { return i + j; }

struct divide
{
    int operator()(int i, int j) { return i / j; }
};
void test()
{
    auto mod = [](int i, int j)
    { return i % j; };

    function<int(int, int)> f1 = add;      //函数指针
    function<int(int, int)> f2 = divide(); //函数对象类的对象
    function<int(int, int)> f3 = [](int i, int j)
    { return i * j; }; //lambda
    cout << f1(2, 4) << ' ' << f2(4, 2) << ' ' << f3(4, 2) << endl;

    map<string, function<int(int, int)>> binpos = {{"+", add},
                                                   {"-", std::minus<int>()},
                                                   {"/", divide()},
                                                   {"*", [](int i, int j)
                                                    { return i * j; }},
                                                   {"%", mod}};
    cout << binpos["+"](10, 99)
         << endl;
}

int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
