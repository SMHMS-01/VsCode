#include <iostream>
#include <windows.h>
#include <stack>
#include <random>
using namespace std;
class stackWithMin
{
public:
    void push(int value)
    {
        real.push(value);
        if (minValue.empty())
            minValue.push(value);
        else
            minValue.push(value < minValue.top() ? value : minValue.top());
    }
    void pop()
    {
        real.pop();
        minValue.pop();
    }
    int top() { return real.top(); }
    int min() { return minValue.top(); }

private:
    stack<int> real;
    stack<int> minValue;
};

bool isPopOrder(const int *pPush, const int *pPop, const int nLength)
{
    bool bPossible = false;
    if (!pPush || !pPop || nLength <= 0)
        return false;
    const int *pNextPush = pPush;
    const int *pNextPop = pPop;
    stack<int> stackData;
    while (pNextPop - pPop < nLength)
    {
        //只要辅助栈还非空，并且辅助栈栈顶与压栈的当前移动地址不同，那就要继续遍历，直到压栈遍历
        while (stackData.empty() || stackData.top() != *pNextPop)
        {
            if (pNextPush - pPush == nLength)
                break;

            stackData.push(*pNextPush);
            pNextPush++; //把压栈除栈顶全部输出到辅助栈，并且进行地址记录
        }
        if (stackData.top() != *pNextPop)
            break;
        stackData.pop();
        pNextPop++;
    }
    if (stackData.empty() && pNextPop - pPop == nLength)
        bPossible = true;
    return bPossible;
}
int main()
{
    SetConsoleOutputCP(65001);
    stackWithMin *swm = new stackWithMin();
    static uniform_int_distribution<unsigned> u(67, 78);
    static default_random_engine e;
    for (int i = 0; i != 9; ++i)
    {
        swm->push(u(e));
        cout << swm->top() << '\t';
    }
    cout << endl
         << swm->min() << endl;

    delete swm;
    swm = nullptr;

    //*******************************************************
    stack<int> sL({1, 2, 3, 4, 5, 6});
    int *const p1 = &sL.top(), *p2 = &sL.top();
    size_t sz = sL.size();
    while (!sL.empty())
    {
        sL.pop();
        p2--;
    }

    cout << endl
         << "address of P1 is :" << p1 << '\t' << "address of P2 is :" << p2 << endl
         << "size:  " << sz << endl
         << "the difference between P1 and P2 is :" << p1 - p2 << endl;

    //*******************************************************

    int *a = new int[5]{1, 2, 3, 4, 5};
    int *b = new int[5]{4, 3, 5, 1, 2};
    cout << boolalpha << isPopOrder(a, b, 5) << endl;
    system("pause");
    return 0;
}
