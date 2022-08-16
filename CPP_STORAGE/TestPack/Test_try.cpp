#include <iostream>
#include <windows.h>

using namespace std;

constexpr int64_t INFINITY = INT64_MAX;
constexpr unsigned FINITY = 0;

void test1()
{
    int a = INT_MAX;
    int b = 4;
    cout << a << "\ta + 1 = " << a + 1 << '\t' << (a << 2) << '\t' << (b >> 1) << endl;
    cout << "The INFINITY(64bits) is  " << INFINITY << flush << '\n'
         << b << endl;
    cout << FINITY << endl;
    unsigned a2 = 100, b2 = 10, c;
    if ((int)b2 - int(a2) < 0)
        c = a2 - b2;
    else
        c = b2 - a2;
    cout << c << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    test1();
    system("pause");
    return 0;
}
