#include <iostream>
#include <windows.h>
#include <vector>
#include <typeinfo.h>
using namespace std;

void test()
{
    typedef int *array_int;
    using array_int_vector = std::vector<int>;
    array_int_vector a{0};
    const int a2 = 10;
    auto b = a2;
    b = 3;
    decltype(a2) c = 10;
    //c = 0; falut, this is difference between auto and decltype
}
void test_1()
{
    int i = 0, &j = i;
    decltype(i) a = i;
    decltype((i)) b = i;
    decltype(a = b) c = i;
    ++i;
    ++a;
    ++b;
    ++c;
    cout << i << " " << j << ' ' << a << ' ' << b << ' ' << c << endl;
}
int main()
{
    SetConsoleOutputCP(65001);
    int a;
    test_1();
    system("pause");
    return 0;
}
