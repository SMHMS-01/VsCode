#include <iostream>
#include <windows.h>
#define MAXSIZE 101
using namespace std;
#ifdef MAXSIZE
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

int Partition(sqList *L, int low, int high)
{
    int pivotkey;
    pivotkey = L->arr[low];
    L->arr[0] = pivotkey; //当然也可以不用ARRAY[0]存储枢轴,总之得记录下枢纽（又称挖坑法——坑位）
    while (low != high)
    {
        while (low < high && L->arr[high] >= pivotkey)
            high--;
        if (low < high) // swap(L,low,high);
            L->arr[low] = L->arr[high];
        while (low < high && L->arr[low] <= pivotkey)
            low++;
        if (low < high) // swap(L,low,high);
            L->arr[high] = L->arr[low];
    }
    L->arr[low] = L->arr[0];
    return low;
}
void QSort(sqList *L, int low, int high)
{
    int pivot;

    if (low < high)
    {
        pivot = Partition(L, low, high);
        QSort(L, low, pivot - 1);
        QSort(L, pivot + 1, high);
    }
}
void QuickSort(sqList *L)
{
    QSort(L, 1, L->length);
}
void QuickSortOptimized_1(sqList *L);
void QuickSortOptimized_2(sqList *L); //即为目前所使用的，省去不必要的交换，借用ARRAY[0]，更改为赋值操作
void QuickSortOptimized_3(sqList *L);
void QuickSortOptimized_4(sqList *L);
int main()
{
    SetConsoleOutputCP(65001);
    sqList L;
    initSqList(&L, 10);
    QuickSortOptimized_4(&L);
    output(&L);
    system("pause");
    return 0;
}

// Optimized version 1
//优化选取枢轴Pivotkey
//三数取中（median-of-three）
int Partition1(sqList *L, int low, int high)
{
    int pivotkey;
    //
    int m = low + (high - low) / 2; //计算数组中间元素的下标
    if (L->arr[low] > L->arr[high]) //交换左右两端数据，保证左侧的更小
        swap(L, low, high);
    if (L->arr[m] > L->arr[high]) //交换中间与右端数据，保证中间较小
        swap(L, high, m);
    if (L->arr[m] > L->arr[low]) //交换左边与右边数据，保证中间更大（左边更小）
        swap(L, m, low);
    //此时L->arr[low] 已经是整个序列左右中三个关键字的中间值
    pivotkey = L->arr[low];

    while (low != high)
    {
        while (low < high && L->arr[high] >= pivotkey)
            high--;
        if (low < high)
            L->arr[low] = L->arr[high];
        while (low < high && L->arr[low] <= pivotkey)
            low++;
        if (low < high)
            L->arr[high] = L->arr[low];
    }
    L->arr[low] = pivotkey;
    return low;
}
void QSort1(sqList *L, int low, int high)
{
    int pivot;

    if (low < high && L)
    {
        pivot = Partition1(L, low, high);
        QSort1(L, low, pivot - 1);
        QSort1(L, pivot + 1, high);
    }
}
void QuickSortOptimized_1(sqList *L)
{
    QSort1(L, 1, L->length);
}

// Optimized Version 3
//优化小数组时的排序方案
const int MAX_LENGTH_INSERT_SORT = 7;
void InsertSort(sqList *L)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
    {
        if (L->arr[i] < L->arr[i - 1])
        {
            L->arr[0] = L->arr[i];
            for (j = i - 1; L->arr[j] > L->arr[0]; j--) //如果后面那一位大于前面那一位，则执行循环
                L->arr[j + 1] = L->arr[j];              //后移数组
            L->arr[j + 1] = L->arr[0];
        }
    }
}
void QSort3(sqList *L, int low, int high)
{
    int pivot;
    if ((high - low) > MAX_LENGTH_INSERT_SORT)
        if (low < high)
        {
            pivot = Partition(L, low, high);
            QSort3(L, low, pivot - 1);
            QSort3(L, pivot + 1, high);
        }
        else
            InsertSort(L); //简单排序中性能最好的是插入排序
}
void QuickSortOptimized_3(sqList *L)
{
    QSort3(L, 1, L->length);
}

// Optimized Version 4
//优化递归操作
//对QSort()施行尾递归优化
void QSort4(sqList *L, int low, int high)
{
    int pivot;
    if ((high - low) > MAX_LENGTH_INSERT_SORT)
        while (low < high)
        {
            pivot = Partition(L, low, high);
            QSort4(L, low, pivot - 1);
            low = pivot + 1; //尾递归思想 b
        }
    else
        InsertSort(L);
}
void QuickSortOptimized_4(sqList *L)
{
    QSort4(L, 1, L->length);
}
#endif