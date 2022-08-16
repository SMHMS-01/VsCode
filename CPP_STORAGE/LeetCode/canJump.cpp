#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

    bool canJump(vector<int> &nums)
    {
        if (nums.size() == 0)
            return true;
        int maxReach = nums[0];
        for (int i = 0; maxReach && i < nums.size(); ++i)
        {
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach == nums.size())
                return true;
        }
        return false;
    }
int main()
{
    SetConsoleOutputCP(65001);
    vector<int> nums{2,3,1,1,4};
    cout << boolalpha << canJump(nums) << endl;
    system("pause");
    return 0;
}
