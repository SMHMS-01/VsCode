#include <iostream>
#include <windows.h>
#include <iterator>
#include <limits>
using namespace std;

//自顶向下方法
int fib(int n, int *Mem);
int fibonaicc(int n)
{
    if (n <= 0)
        return n;
    int *Mem = new int[n + 1];
    for (int i = 0; i <= n; ++i)
        Mem[i] = -1;
    return fib(n, Mem);
}
int fib(int n, int *Mem)
{
    if (Mem[n] != -1)
        return Mem[n];
    if (n <= 2)
        Mem[n] = 1;
    else
        Mem[n] = fib(n - 1, Mem) + fib(n - 2, Mem);
    return Mem[n];
}

//自底向上
int FIB(int n)
{
    if (n <= 0)
        return n;
    int *Mem = new int[n + 1];
    Mem[0] = 0;
    Mem[1] = 1;
    for (int i = 2; i <= n; ++i)
        Mem[i] = Mem[i - 1] + Mem[i - 2];
    return Mem[n];
}
//自底向上advance
int FIB_ADVANCE(int n)
{
    if (n <= 1)
        return n;
    int Memo_i_2 = 0;
    int Memo_i_1 = 1;
    int Memo_i = 1;
    for (int i = 2; i <= n; ++i)
    {
        Memo_i = Memo_i_1 + Memo_i_2;
        Memo_i_2 = Memo_i_1;
        Memo_i_1 = Memo_i;
    }
    return Memo_i;
}

int main()
{
    SetConsoleOutputCP(65001);
    cout << fibonaicc(10) << endl;
    cout << FIB(10) << endl;
    
    cout << FIB_ADVANCE(10) << endl;
    system("pause");
    return 0;
}
