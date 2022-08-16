#include <iostream>
#include <windows.h>
#include <stdlib.h>

#define max ~(1 << (sizeof(int) * 8 - 1))

using namespace std;

int hashFunc(int key, int length);
int initHashTable(int *hashTable, int length);       //成功返回0，失败返回-1
int hashInsert(int *hashTable, int key, int length); //成功返回0，失败返回-1
static enum status { failture = -1,
                     success = 0 } flag;
int hashSearch(int *hashTable, int key, int length);
void test();

int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}

int initHashTable(int *hashTable, int length)
{
    if (!hashTable || length <= 0)
        throw length_error("it's empty!\n");
    for (int i = 0; i < length; i++)
        hashTable[i] = max;
    return 0;
}
int hashFunc(int key, int length)
{
    if (key == max || length <= 0)
        return -1;
    return key & (length % 37);
}

int hashInsert(int *hashTable, int key, int length)
{
    if (!hashTable || length <= 0)
        return -1;
    int hashAddr = hashFunc(key, length);
    if (hashAddr == -1)
        return -1;
    for (int idx = 0; idx != length; ++idx)
    {
        if (hashTable[idx] != max)
            hashAddr = (hashAddr + 1) % 12; // if collision
        else
            break;
    }
    if (max == hashTable[hashAddr])
    {
        hashTable[hashAddr] = key;
        return 0;
    }
    return -1;
}
void test()
{
    int arr[12] = {12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34};
    int *hashTable = new int[12]();
    int ret = initHashTable(hashTable, 12);
    if (-1 == ret)
        cout << "initHashTable fail!" << endl;

    cout << "哈希表待插入元素：";
    for (int idx = 0; idx != 12; ++idx)
    {
        cout << arr[idx] << " ";
        hashInsert(hashTable, arr[idx], 12);
    }
    cout << endl;

    cout << "哈希表：";
    for (int idx = 0; idx != 12; ++idx)
    {
        cout << hashTable[idx] << " ";
    }
    cout << endl;

    cout << "对应插入元素序列在哈希表查找元素：";
    for (int idx = 0; idx != 12; ++idx)
    {
        int ret = hashSearch(hashTable, arr[idx], 12);
        if (ret == -1 && flag == failture)
        {
            cout << "search " << arr[idx] << " fail" << endl;
        }
        cout << hashTable[ret] << " ";
    }
    cout << endl;
    cout << "查找1:" << endl;
    int rett = hashSearch(hashTable, 1, 12);
    if (rett == -1 && flag == failture)
    {
        cout << "search " << 1 << " fail" << endl;
        return;
    }
    cout << hashTable[rett] << endl;
}

int hashSearch(int *hashTable, int key, int length)
{
    flag = success;
    if (!hashTable || length <= 0)
    {
        flag = failture;
        return -1;
    }
    int hashAddr = hashFunc(key, length);
    while (key != hashTable[hashAddr])
    {
        hashAddr = (hashAddr + 1) % length;
        if (max == hashTable[hashAddr] || hashAddr == hashFunc(key, length)) //如果探测到下一个地址为空，还没有找到，或者循环找了一遍又回到最开始的hashAddr
        {
            flag = failture;
            return -1;
        }
    }
    return hashAddr;
}