#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
string longestCommonPrefix(vector<string> &strs)
{
    if (strs.size() <= 1)
        return strs.size() == 1 ? strs[0] : "\0";
    string s("");
    size_t sz = strs[0].size();
    for (int i = 1; i <= strs.size() - 1; ++i)
    {

        int j = 0;
        if (strs[i][0] != strs[0][0])
            return "";
        string p = "";

        while (strs[i] != "" && strs[i - 1] != "" && strs[i][j] != '\0' && strs[0][j] != '\0') // String[x][y]=='\0'对y进行边界检查
        {

            if (strs[i][j] != strs[0][j])
                break;
            else
            {
                p += strs[0][j];
                j++;
            }
        }
        if (p.size() <= sz && p != "")
        {
            s = p;
            sz = p.size();
        }
    }
    return s;
}
vector<int> twoSum(vector<int> &numbers, int target)
{
    int left = 0, right = numbers.size() - 1;
    while (left <= right)
    {
        if (numbers[left] + numbers[right] < target)
            left++;
        else if (numbers[left] + numbers[right] > target)
            right--;
        else
            break;
    }
    return vector<int>{left + 1, right + 1};
}
void moveZeroes(vector<int> &nums)
{
    for (int i = 0, nozero = 0; i < nums.size(); ++i)
    {
        if (nums[i] != 0)
        {
            if (nozero != i)
            {
                nums[nozero] = nums[i];
                nums[i] = 0;
            }
            nozero++;
        }
    }
}

int pow(int value, int n)
{
    int sum = 1;
    while (n != 0)
    {
        if (n & 1 == 1)
            sum *= value;
        value *= value;
        n = n >> 1;
    }
    return sum;
}
int main()
{
    SetConsoleOutputCP(65001);
    long n;
    int x = -1283;
    n = x % 10;
    cout << n << endl;
    cout << -1 % 10 << endl;
    cout << 1 % 10 << endl;
    string s("abcde");
    for (const char &c : s)
    {
        cout << c;
    }
    string a("");
    cout << (a == "" ? "yes" : "no") << endl;
    vector<string> strs{"flower", "flower", "flower", "flower"};

    cout << longestCommonPrefix(strs) << endl;
    cout << pow(2, 8) << endl;
    system("pause");
    return 0;
}
