#include <iostream>
#include <windows.h>
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
void MSort(int SR[], int TR1[], int s, int t);
void Merge(int SR[], int TR[], int i, int m, int n);
void MergeSort(sqList *L)
{
    MSort(L->arr, L->arr, 1, L->length);
}

void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE];
    if (s == t)
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m + 1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; k++)
    {
        if (SR[i] < SR[j])
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if (i <= m)
    {
        for (l = 0; l < m - i; l++)
            TR[k + 1] = SR[i + 1];
    }
    if (j <= n)
    {
        for (l = 0; l <= n - j; l++)
            TR[k + 1] = SR[j + 1];
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    sqList L;
    initSqList(&L, 10);
    MergeSort(&L);
    output(&L);
    system("pause");
    return 0;
}
