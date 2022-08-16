#include <iostream>
#include <windows.h>

using namespace std;

int MinInOrder(int *arr, int head, int rear);
int MinRotateArr(int *arr, int length)
{
    if (!arr || length <= 0)
        throw invalid_argument("invalid argument.\n");
    int pHead = 0;
    int pRear = length - 1;
    int pMid = pHead;

    while (arr[pHead] >= arr[pRear])
    {
        if (pRear - pHead == 1)
        {
            pMid = pRear;
            break;
        }
        pMid = (pHead + pRear) / 2;
        // if numbers of three pointer are same, u need inorder search
        if (arr[pMid] == arr[pHead] && arr[pMid] == arr[pRear])
            return MinInOrder(arr, pHead, pRear);
        if (arr[pMid] >= arr[pHead])
            pHead = pMid;
        else if (arr[pRear <= arr[pMid]])
            pRear = pMid;
    }

    return arr[pRear];
}
int MinInOrder(int *arr, int head, int rear)
{
    int result = arr[head];
    for (int i = head + 1; i <= rear; ++i)
        if (result > arr[i])
            result = arr[i];
    return result;
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
