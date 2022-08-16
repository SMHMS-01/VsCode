#include <iostream>
#include <windows.h>
#define MAXSIZE 101
using namespace std;
typedef struct
{
    int arr[MAXSIZE];
    int size;
} sqList;

void swap(sqList *L, int i, int j)
{
    L->arr[i] ^= L->arr[j];
    L->arr[j] ^= L->arr[i];
    L->arr[i] ^= L->arr[j];
}

void input(sqList *&L)
{
    int i;
    for (i = 1; i <= L->size; i++)
        cin >> L->arr[i];
}

void output(sqList *L)
{
    int i;
    for (i = 1; i <= L->size; i++)
        cout << L->arr[i] << ' ';
    cout << endl;
}

void initSqList(sqList *L, int size)
{
    if (size > MAXSIZE)
        exit(0);
    L->size = size;
    input(L);
}

static void HeapAdjust(sqList *L, int cursor, int heapSize)
{
    int temp, j;
    temp = L->arr[cursor];

    for (j = 2 * cursor; j <= heapSize; j *= 2)
    {
        if (j < heapSize && L->arr[j] < L->arr[j + 1]) //if left is less than right
            ++j;
        if (temp >= L->arr[j]) //if temp(arr[cursor]) is better than left or right, don't need to exchange
            break;
        L->arr[cursor] = L->arr[j]; //exchange start
        cursor = j;                 //exchange index
    }
    L->arr[cursor] = temp; //exchang finished
}

static void HeapSort(sqList *L)
{
    int i = L->size / 2; //if statr from index-0, leftchild=2*index, rightchild=2*index+1
    for (; i > 0; i--)
        HeapAdjust(L, i, L->size);

    for (i = L->size; i > 1; i--)
    {
        swap(L, 1, i);           //the maxium is in index-1
        HeapAdjust(L, 1, i - 1); //adjust heap's structure without index-i(each exchanged finally)
    }
}

static void HeapMaxAdjust(sqList *L, int cursor, int heapSize)
{
    int temp, j;
    temp = L->arr[cursor];

    for (j = 2 * cursor; j <= heapSize; j *= 2)
    {
        if (j < heapSize && L->arr[j] > L->arr[j + 1])
            ++j;
        if (temp <= L->arr[j])
            break;
        L->arr[cursor] = L->arr[j];
        cursor = j;
    }
    L->arr[cursor] = temp;
}

static void HeapMaxSort(sqList *L)
{
    int i = L->size / 2;
    for (i; i > 0; i--)
        HeapMaxAdjust(L, i, L->size);

    for (i = L->size; i > 1; i--)
    {
        swap(L, 1, i);
        HeapMaxAdjust(L, 1, i - 1);
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    sqList L;
    initSqList(&L, 10);
    HeapSort(&L);
    output(&L);
    cout << "reversed: " << endl;
    HeapMaxSort(&L);
    output(&L);
    system("pause");
    return 0;
}
