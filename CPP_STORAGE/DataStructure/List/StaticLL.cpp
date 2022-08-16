#include <iostream>
#include <windows.h>
#include <time.h>
#define MAXSIZE 1000
#define OK 1
#define ERROR 0
using namespace std;
typedef int elemType;
typedef int status;

typedef struct
{
    elemType data;
    int cur;
} Component, staticLinkList[MAXSIZE];
status initList(staticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
    {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
    return OK;
}
int listLength(staticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i)
    {
        i = L[i].cur;
        j++;
    }
    return j;
}
int New_SLL(staticLinkList space) //simulate New, is apply for memory dynamically
{
    int i = space[0].cur;
    if (space[0].cur)
        space[0].cur = space[i].cur;
    return i;
}
status listInsert(staticLinkList L, int i, elemType e)
{
    int j, k, l;
    k = MAXSIZE - 1;
    if (i < 1 || i > listLength(L) + 1)
        return ERROR;
    j = New_SLL(L);
    if (j)
    {
        L[j].data = e;
        for (l = 1; l <= i - 1; l++) //traverse untill find will insert position
            k = L[k].cur;
        L[j].cur = L[k].cur; //put the front cursor of Ith element assign to cur of new element
        L[k].cur = j;        //An exchanging, put the cursor of new element assign to front of cur of Ith element
        return OK;
    }
    return ERROR;
}

void delete_SLL(staticLinkList space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}
status listDelete(staticLinkList L, int i)
{
    int j, k;
    if (i < 1 || i > listLength(L))
        return ERROR;
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++)
        k = L[k].cur;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    delete_SLL(L, j);
    return OK;
}
void outputList(staticLinkList L)
{
    int cur;
    cur = L[MAXSIZE - 1].cur;
    while (cur)
    {
        cout << L[cur].data << endl;
        cur = L[cur].cur;
    }
}
void test()
{
    staticLinkList L;
    initList(L);
    srand(time(0));
    for (int i = 1; i < 11; i++)
        listInsert(L, 1, i);
    outputList(L);
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}
