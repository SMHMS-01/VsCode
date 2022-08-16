#include <iostream>
#include <windows.h>
#include <random>
using namespace std;

typedef struct
{
   int arr[101];
   unsigned int size;
} Heap;

void swap(Heap *hp, int i, int j)
{
   hp->arr[i] ^= hp->arr[j];
   hp->arr[j] ^= hp->arr[i];
   hp->arr[i] ^= hp->arr[j];
}
int parent(int k)
{
   if (k == 0)
      throw out_of_range("该节点为根节点\n");
   return (k - 1) / 2;
}

int leftChild(int k)
{
   return k * 2 + 1;
}
int rightChild(int k)
{
   return k * 2 + 2;
}
void shiftUp(Heap *hp, int index)
{
   while (index > 0 && hp->arr[index] > hp->arr[parent(index)])
   {
      swap(hp, index, parent(index));
      index = parent(index);
   }
}

void shiftDown(Heap *hp, int index)
{
   int j;
   while (leftChild(index) < hp->size)
   {
      j = leftChild(index);
      if (rightChild(index) < hp->size && hp->arr[j] < hp->arr[rightChild(index)]) // 选举出左右节点最大的那个
         ++j;
      if (hp->arr[index] >= hp->arr[j])
         break; // 如果当前节点大于左右子节点，循环结束
      swap(hp, index, j);
      index = j;
   }
}

void insert(Heap *hp, int k)
{
   ++hp->size;
   hp->arr[hp->size - 1] = k;
   shiftUp(hp, hp->size - 1);
}

int extractMax(Heap *hp)
{
   int ret = hp->arr[0];
   swap(hp, 0, hp->size - 1);
   shiftDown(hp, 0);
   --hp->size;
   return ret;
}

void replace(Heap *hp, int val)
{
   hp->arr[0] = val;
   shiftDown(hp, 0);
}

void Heapify(Heap *hp)
{
   for (int i = parent(hp->size - 1); i >= 0; i--)
      shiftDown(hp, i);
}

void initHeap(Heap *hp, int arr[], int n)
{
   for (int i = 0; i < n; i++)
      insert(hp, arr[i]);
}

void output(Heap *hp)
{
   for (int i = 0; i < hp->size; i++)
      cout << hp->arr[i] << ' ';
   cout << endl;
}

void heapAdjust(Heap *hp, int index, int currentSize)
{
   int j;
   while (leftChild(index) < currentSize)
   {
      j = leftChild(index);
      if (rightChild(index) < currentSize && hp->arr[j] < hp->arr[rightChild(index)]) //该节点的有孩子的下标不超出范围&&如果左节点小于右节点
         ++j;
      if (hp->arr[index] > hp->arr[j]) //如果该节点的左/右孩子皆小于该节点
         break;
      swap(hp, index, j);
      index = j;
   }
}

void heapSort(Heap *hp)
{
   int i = hp->size - 1;
   for (; i > 0; i--)
   {
      swap(hp, 0, i);       //ROOT下到HP->ARR[0]
      heapAdjust(hp, 0, i); //调整
   }
}

bool isEmpty(Heap *hp)
{
   return hp->size == 0;
}

int main()
{
   SetConsoleOutputCP(65001);
   int array[39];
   default_random_engine e;
   uniform_int_distribution<int> u(1, 1000);
   for (int i = 0; i < 39; i++)
      array[i] = u(e);

   Heap hp;
   initHeap(&hp, array, 39);
   Heapify(&hp);
   replace(&hp, 100);
   // extractMax(&hp);
   heapSort(&hp);

   output(&hp);
   system("pause");
   return 0;
}
