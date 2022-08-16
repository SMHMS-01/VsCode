#include <iostream>
#include <windows.h>

using namespace std;

//限定作用域的枚举类型
enum class open_modes
{
    input,
    output,
    append,
    assign,
    swap
};
enum struct programLanguage
{
    c,
    cpp,
    java,
    php,
    csharp
};

//不限定作用域的枚举类型
enum color
{
    red,
    yellow,
    purple,
    blue,
    black,
    white
};
//未命名的、不限定作用域的枚举类型
enum
{
    vc = 5,
    vb = 10,
    ve = 10
};
//set size
enum intVals : unsigned long long
{
    charType = 255,
    shortType = 65535,
    intType = shortType,
    longType = 4294967295UL,
    long_longType = 18446744073709551615ULL
};

void test()
{
    int i = color::red;
    int j = vc;
    // int k = open_modes::input;//false:限定作用域的枚举类型不会进行隐式转换
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
