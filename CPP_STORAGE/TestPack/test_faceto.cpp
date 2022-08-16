#include <iostream>
#include <windows.h>

using namespace std;

boolean duplicate(int numbers[], int length, int *duplication)
{
    if (numbers == NULL || length < 1)
        return false;
    for (int i = 0; i < length; ++i)
        return numbers[i] < 0 || length - 1 < numbers[i] ? false : true;
    for (int i = 0; i < length; ++i)
    {
        while (numbers[i] != i)
        {
            if (numbers[i] == numbers[numbers[i]])
            {
                *duplication = numbers[i];
                return true;
            }

            // swap
            int tmp = numbers[i];
            numbers[i] = numbers[tmp];
            numbers[tmp] = tmp;
        }
    }
    return false;
}

boolean findNumInMatrix(int *matrix, int rows, int columns, int number)
{
    bool search = false;
    if (matrix != NULL && columns > 0)
    {
        int row = 0;
        int col = columns - 1;
        while (row < rows && col >= 0)
        {
            if (matrix[row * columns + col] == number)
            {
                search = true;
                break;
            }
            else if (matrix[row * columns + col] > number)
                --col;
            else
                ++row;
        }
    }
    return false;
}

int judge()
{
    char str1[] = "hello world";
    char str2[] = "hello world";
    char *str3 = "hello world";
    char *str4 = "hello world";

    if (str1 == str2)
        cout << "strl and slr2 ar samc.\n";
    else
        cout << "strl and str2 arc not samc.\n";

    // pointer are point to the same address
    if (str3 == str4)
        cout << "str3 and str4 are same";
    else
        cout << "str3 a nd slr4 are not same.\n";
    return 0;
}
int main()
{
    SetConsoleOutputCP(65001);
    judge();
    system("pause");
    return 0;
}
