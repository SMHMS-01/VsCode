#include <iostream>
#include <windows.h>
#include <ctime>
#define MAXSIZE 101
using namespace std;

typedef struct
{
    int arr[MAXSIZE + 1];
    int length;
} sqList;

void input(sqList *&L)
{
    int i;
    for (i = 1; i <= L->length; i++)
        cin >> L->arr[i];
}

void output(sqList *L)
{
    int i;
    for (i = 1; i <= L->length; i++)
        cout << L->arr[i] << ' ';
    cout << endl;
}

void initSqList(sqList *L, int length)
{
    if (length > MAXSIZE)
        exit(0);
    L->length = length;
    input(L);
}

void swap(sqList *L, int i, int j)
{
    L->arr[i] ^= L->arr[j];
    L->arr[j] ^= L->arr[i];
    L->arr[i] ^= L->arr[j];
}
// void swap(sqList *L, int i, int j)
// {
//     int temp = L->arr[j];
//     L->arr[j] = L->arr[i];
//     L->arr[i] = temp;
// }
void BubbleSort0(sqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
        for (j = i + 1; j <= L->length; j++)
            if (L->arr[i] > L->arr[j])
                swap(L, i, j);
}

void BubbleSort1(sqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
        for (j = L->length - 1; j >= i; j--)
            if (L->arr[j] > L->arr[j + 1])
                swap(L, j, j + 1);
}

void BubbleSort2(sqList *L)
{
    int i, j;
    bool flag = true;
    for (i = 1; i < L->length && flag; i++)
    {
        flag = false;
        for (j = L->length - 1; j >= i; j--)
            if (L->arr[j] > L->arr[j + 1])
            {
                swap(L, j, j + 1);
                flag = true;
            }
    }
}

void BubbleSortPro(sqList *L)
{
    int i, j;
    bool isSorted = true;
    int lastExchangeIndex = 0;
    int sortBorder = L->length;
    for (i = 1; i < L->length; i++)
    {
        isSorted = true;
        for (j = 1; j < sortBorder; j++)
        {
            if (L->arr[j] > L->arr[j + 1])
            {
                swap(L, j, j + 1);
                lastExchangeIndex = j;
                isSorted = false;
            }
        }
        sortBorder = lastExchangeIndex;
        if (isSorted)
            break;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    time_t c_start, c_end;
    sqList L;
    initSqList(&L, 10);
    // BubbleSort2(&L);
    c_start = clock();
    BubbleSortPro(&L);
    output(&L);
    c_end = clock();
    cout << "The current sort algorithm takes time is :" << difftime(c_end, c_start) << "ms" << endl;
    system("pause");
    return 0;
}