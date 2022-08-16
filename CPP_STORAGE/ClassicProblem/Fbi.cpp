#include <iostream>
#include <windows.h>
#define MAXSIZE 20
using namespace std;

int Fbi_recursion(int n)
{
    if (n <= 2)
        return n == 0 ? 0 : 1;
    return Fbi_recursion(n - 1) + Fbi_recursion(n - 2);
}

//tail recursion
int Fbi_tailRecursion(int n, int res, int ret)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 0;
    else if (n < 2)
        return res;
    else
        return Fbi_tailRecursion(n - 1, ret, res + ret);
}
int main()
{
    SetConsoleOutputCP(65001);
    int i;
    for (int i = 0; i < 10; i++)
        cout << Fbi_recursion(i) << " ";

    cout << endl;
    int res, ret;
    res = ret = 0;
    for (int i = 0; i < 11; i++)
        cout << Fbi_tailRecursion(i, 1, 1) << " ";
    // int a[20];
    // a[0] = 0;
    // a[1] = 1;
    // cout << a[0] << endl
    //      << a[1] << endl;
    // for (i = 2; i < 20; i++)
    // {
    //     a[i] = a[i - 1] + a[i - 2];
    //     cout << a[i] << endl;
    // }
    cout << system("pause");
    return 0;
}
