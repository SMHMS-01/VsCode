#include <iostream>
#include <windows.h>
using namespace std;

constexpr int INFINITY = INT_MAX;

inline int Min(int n, int m)
{
    return m < n ? m : n;
}
//二维数组DP路径
int uniquePaths(int m, int n)
{
    if (m <= 0 || n <= 0)
        return 0;

    m = n = 3; //本次指定3x3矩阵
    int arr[m][n] = {{1, 6, 1},
                     {1, 7, 1},
                     {4, 4, 1}};

    int **dp = new int *[m];
    for (int i = 0; i < m; ++i)
        dp[i] = new int[n];
        

    dp[0][0] = arr[0][0];
    for (int i = 1; i < m; ++i)
        dp[i][0] = dp[i - 1][0] + arr[i][0];
    for (int i = 1; i < n; ++i)
        dp[0][i] = dp[0][i - 1] + arr[0][i];

    for (int i = 1; i < m; ++i)
        for (int j = 1; j < n; ++j)
            dp[i][j] = Min(dp[i - 1][j], dp[i][j - 1]) + arr[i][j];
    return dp[m - 1][n - 1];
}
int main()
{
    SetConsoleOutputCP(65001);
    cout << uniquePaths(3, 3) << endl;
    cout << "INFINITE is " << INFINITE << endl;
    cout << "INFINITY is " << 0765 << endl;
    system("pause");
    return 0;
}
