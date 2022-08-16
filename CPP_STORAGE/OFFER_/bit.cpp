#include <iostream>
#include <windows.h>

using namespace std;

int countNumberOne(int n)
{
    int count = 0;
    unsigned int flag = 1;
    while (flag)
    {
        if (n & flag)
            count++;
        flag = flag << 1;
    }
    return count;
}
int countNumberOne_adv(int n)
{
    int count = 0;
    while (n)
    {
        ++count;
        n = (n - 1) & n;
    }
    return count;
}
int main()
{
    SetConsoleOutputCP(65001);
    cout << countNumberOne(9) << endl;
    cout << countNumberOne_adv(9) << endl;
    system("pause");
    return 0;
}
