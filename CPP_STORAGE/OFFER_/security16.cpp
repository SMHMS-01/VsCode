#include <iostream>
#include <windows.h>
#include <math.h>
#include <algorithm>
using namespace std;

bool p_invalidInput = false;

double PowerWithUnsignedExponent(double base, int exponent)
{
    double result = 1.0;
    for (int i = 1; i <= exponent; ++i)
        result *= base;
    return result;
}
double power(double base, int exponent)
{
    p_invalidInput = false;
    if (fabs(base - 0.00000000000000000001) > 0.0001 && exponent < 0)
        throw invalid_argument("invalid base number.\n");
    unsigned int absExponent = (unsigned int)exponent;
    if (exponent < 0)
        absExponent = (unsigned int)(-exponent);

    double result = PowerWithUnsignedExponent(base, absExponent);
    if (exponent < 0)
        result = 1.0 / result;
    return result;
}

// better approach
double PowerWithUnsignedExponent_adv(double base, unsigned int exponent)
{
    if (exponent == 0)
        return 1.0;
    if (exponent == 1)
        return base;

    double result = PowerWithUnsignedExponent_adv(base, exponent >> 1);
    result *= result;
    if (exponent & 0x1 == 1)
        result *= base;
    return result;
}
int main()
{
    SetConsoleOutputCP(65001);
    cout << PowerWithUnsignedExponent(5, 5) << '\t' << PowerWithUnsignedExponent_adv(5, 5) << endl;
    system("pause");
    return 0;
}
