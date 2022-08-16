#include <iostream>
#include <windows.h>

using namespace std;
int Min(int n, int m)
{
    return m < n ? m : n;
}
constexpr int INF = 65535;
void minimumCash(int n)
{
    int arr[n];
    arr[0] = 0;
    int cost;

    for (int i = 1; i <= n; ++i)
    {
        cost = INF;
        if (i - 1 >= 0)
            cost = Min(cost, arr[i - 1] + 1);
        if (i - 5 >= 0)
            cost = Min(cost, arr[i - 5] + 1);
        if (i - 11 >= 0)
            cost = Min(cost, arr[i - 11] + 1);
        arr[i] = cost;
        cout << "Arr[" << i << "] = " << arr[i] << endl;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    minimumCash(15);
    system("pause");
    return 0;
}
