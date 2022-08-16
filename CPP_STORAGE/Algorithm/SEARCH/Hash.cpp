#include <iostream>
#include <windows.h>
#define SUCCESS 1
#define UNSUCCESS 0
#define MAXSIZE 999
#define OVERFLOW -1
#define ERROR -1
#define OK 1

using namespace std;
typedef bool status;
typedef int KeyType;
typedef struct
{
    KeyType key;
} RcdType;
typedef struct
{
    RcdType *rcd;//key value
    int size;//capacity
    int count;//number
    int *tag;//wether be occupied
} HashTable;

int hash_size[] = {11, 31, 61, 127, 251, 503};
int index = 0;

status initHashTable(HashTable &H, int size)
{

    H.rcd = new RcdType[size];
    H.tag = new int[size];
    if (H.rcd == NULL || H.tag == NULL)
        return OVERFLOW;
    KeyType maxNum = MAXSIZE;
    for (int i = 0; i < size; i++)
    {
        H.tag[i] = 0;
        H.rcd[i].key = maxNum;
    }
    H.size = size;
    H.count = 0;
    return OK;
}

int Hash(KeyType key, int m)
{
    return 3 * key % m;
}

void collision(int &p, int m)
{
    p = (p + 1) % m;
}
status searchHash(HashTable &H, KeyType key, int &p, int &c)
{
    p = Hash(key, H.size);
    int h = p;
    c = 0;
    while ((H.tag[p] == 1 && H.rcd[p].key != key) || H.tag[p] == -1)
    {
        collision(key, H.size);
        c++;
    }
    if (H.tag[p] == 1 && key == H.rcd[p].key)
        return SUCCESS;
    else
        return UNSUCCESS;
}

void printHash(HashTable H)
{
    int i;
    cout << "key: ";
    for (i = 0; i < H.size; i++)
        cout << H.rcd[i].key << ' ';
    cout << endl
         << "tag: ";
    for (i = 0; i < H.size; i++)
        cout << H.tag[i] << ' ';
    cout << endl
         << endl;
}

status insertHash(HashTable &H, KeyType key);

status recreatHash(HashTable &H)
{
    RcdType *orcd;
    int *otag, osize, i;
    orcd = H.rcd;
    otag = H.tag;
    osize = H.size;
    initHashTable(H, hash_size[index++]);
    for (i = 0; i < osize; i++)
        if (otag[i] == 1)
            insertHash(H, orcd[i].key);
    return OK;
}

status insertHash(HashTable &H, KeyType key)
{
    int p, c;
    if (searchHash(H, key, p, c) == UNSUCCESS)
        if (c * 1.0 / H.size < 0.5)
        {
            H.rcd[p].key = key;
            H.tag[p] = 1;
            H.count++;
            return SUCCESS;
        }
        else
            recreatHash(H);
    return UNSUCCESS;
}

status deleteHash(HashTable &H, KeyType key)
{
    int p, c;
    if (searchHash(H, key, p, c) == SUCCESS)
    {
        H.tag[p] = -1;
        H.count--;
        return SUCCESS;
    }
    else
        return UNSUCCESS;
}

int main()
{
    SetConsoleOutputCP(65001);
    cout << "Hash Table: \n";
    HashTable *H = new HashTable;
    int i, size = 11;
    KeyType array[8] = {22, 41, 53, 46, 30, 13, 12, 67};
    KeyType key;
    cout << "Initialize Hash Table\n";
    if (initHashTable(*H, hash_size[index++]) == OK)
        cout << "Initialzation is success!\n";

    cout << "Insert Hash Table\n";
    for (i = 0; i <= 7; i++)
    {
        key = array[i];
        insertHash(*H, key);
        printHash(*H);
    }

    cout << "Delete element with key is '12' in Hash Table\n";
    int p, c;
    if (!deleteHash(*H, 12))
    {
        cout << "Delete finished! Ate the same time, Hash Table is: ";
        printHash(*H);
    }

    cout << "Search element with key is '67' in Hash Table\n";
    if (searchHash(*H, 67, p, c) == SUCCESS)
        cout << "Successly search!\n";

    cout << "Insert again, test the recreation of Hash Table\n";
    KeyType array_two[8] = {27, 47, 57, 47, 37, 17, 93, 67};
    for (i = 0; i <= 7; i++)
    {
        key = array_two[i];
        insertHash(*H, key);
        printHash(*H);
    }
    delete H;
    H = NULL;
    system("pause");
    return 0;
}
