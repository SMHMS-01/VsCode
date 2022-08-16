#include <iostream>
#include <windows.h>

using namespace std;

template <typename T>
int getRows(const T &array)
{
    return sizeof(array) / sizeof(array[0]);
}
template <typename T>
int getCols(const T &array)
{
    return sizeof(array[0]) / sizeof(array[0][0]);
}
void sparseArray()
{

    //creat a Two-Dimensional array 11*11
    //0 means no pawn, 1 means black pawn, 2 means blue pawn
    int chessArr1[11][11] = {0};
    chessArr1[1][2] = 1;
    chessArr1[2][1] = 2;
    chessArr1[2][2] = 1;
    chessArr1[3][5] = 99;
    //output original Two-dimensional array'
    for (int i = 0; i < getRows(chessArr1); i++)
    {
        for (int j = 0; j < getCols(chessArr1); j++)
            cout << chessArr1[i][j] << '\t';
        cout << endl;
    }

    //sparseArray's constructure
    //sum used for statistics data that are not zero
    int sum = 0;
    for (int i = 0; i < getRows(chessArr1); i++)
    {
        for (int j = 0; j < getCols(chessArr1); j++)
        {
            if (chessArr1[i][j] != 0)
                sum++;
        }
    }
    cout << "the number of no zeroData is " << sum << endl;

    //creat sparseArray
    int **spareArray = new int *[sum + 1];
    for (int i = 0; i < sum + 1; i++)
        spareArray[i] = new int[3];

    spareArray[0][0] = getRows(chessArr1);
    spareArray[0][1] = getCols(chessArr1);
    spareArray[0][2] = sum;

    //find exact data and save march elements to spareArray
    int count = 0; //used for record the sequence of non-zeroData
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (chessArr1[i][j] != 0)
            {
                count++;
                spareArray[count][0] = i;
                spareArray[count][1] = j;
                spareArray[count][2] = chessArr1[i][j];
            }
        }
    }
    cout << endl
         << "spareArray~~~" << endl;
    for (int i = 0; i < sum + 1; i++)
    {
        cout << spareArray[i][0] << '\t' << spareArray[i][1] << '\t' << spareArray[i][2] << endl;
    }

    cout << endl
         << "Next is sparseArray to Two-dimensional array~~~";
    //replace
    int hang = spareArray[0][0];
    int lie = spareArray[0][1];
    int **original = new int *[hang];

    for (int i = 0; i < hang; i++)
        original[i] = new int[lie];

    for (int i = 0; i < hang; i++)
    {
        for (int j = 0; j < lie; j++)
            original[i][j] = 0;
    }

    for (int i = 1; i < sum + 1; i++)
        original[spareArray[i][0]][spareArray[i][1]] = spareArray[i][2];

    cout << endl;
    cout << " the original after restore" << endl;
    for (int i = 0; i < hang; i++)
    {
        for (int j = 0; j < lie; j++)
        {
            cout << original[i][j] << "\t";
        }
        cout << endl;
    }

    //delete
    for (int i = 0; i < sum + 1; i++)
        delete[] spareArray[i];
    delete[] spareArray;

    for (int i = 0; i < hang; i++)
        delete[] original[i];

    delete[] original;
}
int main()
{
    SetConsoleOutputCP(65001);
    sparseArray();
    system("pause");
    return 0;
}
