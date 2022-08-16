#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
using namespace std;

template <typename T>
size_t LENGTH_ARRAY(const T &arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}
template <typename T>
size_t LENGTH_ARRAY(T &&arr)
{
    return sizeof(arr) / sizeof(arr[0]);
}

vector<int> twoSum(vector<int> &nums, int target)
{
    if (nums.size() < 2)
        return nums;
    vector<int> a;
    for (int i = 0; i < nums.size() - 1; ++i)
        for (int j = i + 1; j <= nums.size() - 1; ++j)
            if (nums[i] + nums[j] == target)
            {
                a.push_back(i);
                a.push_back(j);
                break;
            }
    return a;
}

int main()
{
    SetConsoleOutputCP(65001);
    string arr1[]{"a", "b", "c"};
    cout << LENGTH_ARRAY(arr1) << endl;
    constexpr int arr2[]{0, 1, 2, 3};
    cout << LENGTH_ARRAY(arr2) << endl;
    vector<int> a{3, 2, 4};
    vector<int> b(twoSum(a, 6));
    for (const auto &v : b)
        cout << v << ends;
    cout << endl;
    cout << 194208052043 % 7 + 1;
    system("pause");
    return 0;
}
