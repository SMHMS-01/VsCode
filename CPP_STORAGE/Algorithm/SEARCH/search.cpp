#include <iostream>
#include <windows.h>

using namespace std;
//ORDINAL TABLE SEARCH

//Approximate reasoning for ordinal squence
int Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;
    while (low <= high)
    {
        mid = (low + high) / 2;
        //OPTIMIZATION ALGORITHM: Interpolation Search , SUITABLE FOR ODEDERED SEARCH
        //MIDDLE=LOW+(HIGH-LOW)*(KEY-ARRAY[LOW])/(ARRAY[HIGH]-ARRAY[LOW])
        if (key < a[mid])
            high = mid - 1; //the high bit is back by one
        else if (key > a[mid])
            low = mid + 1; //the low bit is advanced by one
        else
            return mid;
    }
    return 0;
}

//the array of Fibonacci sequence
const int Fibonacci_arr[10] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 1;
    high = n;
    k = 0;
    while (n > Fibonacci_arr[k] - 1)
        k++;
    for (i = n; i < Fibonacci_arr[k] - 1; i++)
        a[i] = a[n];
    while (low <= high)
    {
        mid = low + Fibonacci_arr[k - 1] - 1;
        if (key < a[mid])
        {
            high = mid - 1;
            --k;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            if (mid <= n)
                return mid;
            else
                return n;
        }
    }
    return 0;
}
int main()
{
    SetConsoleOutputCP(65001);
    int arr[] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
    // cout << Binary_Search(arr, 9, 99) << endl;
    cout << Fibonacci_Search(arr, 10, 59) << endl;
    system("pause");
    return 0;
}
