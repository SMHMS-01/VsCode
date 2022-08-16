#include <iostream>
#include <windows.h>
#include <math.h>
using namespace std;

int maxProductAfterCutting_greed(int length)
{
    if (length < 2)
        throw length_error("length is invalid.\n");
    if (length == 2)
        return 1;
    if (length == 3)
        return 2;

    int times0f3 = length / 3;
    if (length - times0f3 * 3 == 1)
        --times0f3;
    int times0f2 = (length - times0f3 * 3) / 2;
    return (int)pow(3, times0f3) * (int)pow(2, times0f2);
}

int main()
{
    SetConsoleOutputCP(65001);
    cout << maxProductAfterCutting_greed(10) << endl;
    system("pause");
    return 0;
}
