#include <iostream>
#include <windows.h>

using namespace std;

template <typename T>
size_t Length(T *t, size_t size)
{
    t = new T[size];
    T *a = t;
    T *b = a + size;
    return ptrdiff_t(b - a);
}
int lengthOfLIS(int *nums, size_t size)
{
    auto len = Length(nums, size);
    if (len == 0)
        return 0;
    int *dp = new int[len];
    dp[0] = 1;
    int maxans = dp[0];
    for (int i = 1; i < len; ++i)
    {
        dp[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] < nums[i])
                dp[i] = max(dp[i], dp[j] + 1);
            maxans = max(maxans, dp[i]);
        }
    }
    return maxans;
}
int main()
{
    SetConsoleOutputCP(65001);
    int arr[]{0, 4, 3, 2, 1, 5, 6, 7, 8, 9, 2, 3, 4, 51, 34, 34, 34, 34, 24, 100};
    cout << lengthOfLIS(arr, 20) << endl;
    system("pause");
    return 0;
}