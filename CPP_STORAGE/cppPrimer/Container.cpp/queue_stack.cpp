#include <iostream>
#include <windows.h>
#include <stack>
#include <queue>
#include <time.h>
using namespace std;

//容器适配器
void test()
{
    stack<int> intStack;
    for (size_t ix = 0; ix != 10; ++ix)
        intStack.push(ix);
    while (!intStack.empty())
    {
        stack<int>::value_type val = intStack.top();
        intStack.pop();
    }
}

void test_()
{
    priority_queue<int> intQueue;
    srand(time(0));
    for (size_t iq = 0; iq != 10; ++iq)
        intQueue.emplace(rand() % 100 + 1);
    while (!intQueue.empty())
    {
        priority_queue<int>::value_type val = intQueue.top();
        cout << val << ends;
        intQueue.pop();
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    test_();
    system("pause");
    return 0;
}
