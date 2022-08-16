#include <iostream>
#include <windows.h>

using namespace std;

int maxProductAfterCutting(int length)
{
    if (length < 2)
        throw length_error("length is invalid.\n");
    if (length == 2)
        return 1;
    if (length == 3)
        return 2;

    int maximum = 0;
    int *products = new int[length + 1];
    for (int i = 0; i < 4; i++)
        products[i] = i;

    for (int i = 4; i <= length; ++i)
    {
        for (int j = 1; j <= i / 2; ++j)
        {
            maximum = 0;
            maximum = maximum > products[j] * products[i - j] ? maximum : products[i - j] * products[j];
            products[i] = maximum;
        }
    }
    maximum = products[length];
    delete[] products;
    return maximum;
}
int main()
{
    SetConsoleOutputCP(65001);
    cout << maxProductAfterCutting(10) << endl;
    system("pause");
    return 0;
}
