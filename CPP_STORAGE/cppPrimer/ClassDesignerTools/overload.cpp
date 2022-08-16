#include <iostream>
#include <windows.h>

using namespace std;
class myArray
{

public:
    myArray(/* args */) : arr(nullptr), sz(0) {}
    myArray(int *a, size_t sz)
    {
        arr = new int[sz];
        for (int i = 0; i < sz; ++i)
            arr[i] = a[i];
        this->sz = sz;
    }
    myArray(const myArray &ma) : sz(ma.sz)
    {
        arr = new int[ma.sz];
        for (int i = 0; i < ma.sz; ++i)
            arr[i] = ma.arr[i];
    }
    myArray(myArray &&ma) noexcept : arr(ma.arr), sz(ma.sz)
    {
        ma.arr = nullptr;
        ma.sz = 0;
    }

    int &operator[](size_t n)
    {
        return arr[n];
    }
    const int &operator[](size_t n) const
    {
        return arr[n];
    }
    ~myArray() { delete[] arr; }

private:
    int *arr;
    size_t sz;
};
int main()
{
    SetConsoleOutputCP(65001);
    int a[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    myArray ma(a, 10);
    cout << ma[7] << endl;

    system("pause");
    return 0;
}
