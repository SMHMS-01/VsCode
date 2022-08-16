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

void SelectSort(sqList *L)
{
   int i, j, min;
   for (i = 1; i < L->length; i++)
   {
      min = i;
      for (j = 1 + i; j <= L->length; j++)
         if (L->arr[min] > L->arr[j])
            min = j;
      if (i != min)
         swap(L, i, min);
   }
}

void InsertSort(sqList *L)
{
   int i, j;
   for (i = 2; i <= L->length; i++)
   {
      if (L->arr[i] < L->arr[i - 1])
      {
         L->arr[0] = L->arr[i];
         for (j = i - 1; L->arr[j] > L->arr[0]; j--) //如果后面那一位大于前面那一位，则执行循环
            L->arr[j + 1] = L->arr[j];               //后移数组
         L->arr[j + 1] = L->arr[0];
      }
   }
}

void insertSort_(int *arr)
{
   int length = 0;
   int **pArr = &arr;
   while ((*pArr)++)
      length++;
   for (int i = 1; i < length; i++)
   {
      int insert = arr[i];
      int index = i - 1;
      while (index >= 0)
      {
         if (arr[index] > insert)
         {
            arr[index + 1] = arr[index];
            index--;
         }
         else
            break;
      }
      arr[index + 1] = insert;
   }
}
// optimiized version, just like straight insert sort
void ShellSort(sqList *L)
{
   int i, j;
   int increment = L->length;
   do
   {
      increment = increment / 3 + 1;
      for (i = increment + 1; i <= L->length; i++)
      {
         if (L->arr[i] < L->arr[i - increment])
         {
            L->arr[0] = L->arr[i];
            for (j = i - increment; j > 0 && L->arr[0] < L->arr[j]; j -= increment)
               L->arr[j + increment] = L->arr[j];
            L->arr[j + increment] = L->arr[0];
         }
      }
   } while (increment > 1);
}
int main()
{
   SetConsoleOutputCP(65001);
   time_t start, end;

   sqList L;
   initSqList(&L, 10);
   // SelectSort(&L);

   start = clock();
   // InsertSort(&L);
   ShellSort(&L);
   end = clock();
   cout << "The current search algorithm takes time is :" << difftime(end, start) << "ms" << endl;
   output(&L);
   system("pause");
   return 0;
}
