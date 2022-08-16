#include <iostream>
#include <time.h>
#include <windows.h>
#define ERROR 0
#define OK 0
using namespace std;
typedef int elemType;
typedef int status;
using namespace std;

typedef struct DulNode
{
    elemType data;
    struct DulNode *prior;
    struct DulNode *next;
} DulNode, *DuLinkList;

int length(DuLinkList *L)
{
    int j = 0;
    while ((*L)->next)
    {
        (*L) = (*L)->next;
        j++;
    }
    return j;
}
status listInsert(DuLinkList *L, int i, elemType e)
{
    int j;
    DuLinkList p, s;
    p = *L;
    j = 1;
    while (p->next && j <= i) //Traverse and index
    {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i)
        return ERROR;
    s = new DulNode;
    s->data = e;
    s->prior = p;
    s->next = p->next; //make the successor of p assign to the successor of s
    p->next->prior = s;
    p->next = s; //make s assign to the successor of p
    return OK;
}
status listDelete(DuLinkList *L, int i)
{
    int j;
    DuLinkList p;
    p = *L;
    j = 1;
    while (p->next && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i)
        return ERROR;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
    return OK;
}
void creatListTail(DuLinkList *L, int n)
{
    DuLinkList p, r;
    int i;
    srand(time(0));
    *L = new DulNode;
    r = *L;
    for (i = 0; i < n; i++)
    {
        p = new DulNode;
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}
void outputAllData(DuLinkList &L)
{
    DuLinkList p, q;
    p = L->next;
    while (p)
    {
        q = p->next;
        cout << p->data << endl;
        p = q;
    }
}
void test()
{
    DuLinkList *L = new DuLinkList;
    creatListTail(L, 10);
    outputAllData(*L);
    cout << endl;
    listInsert(L, 2, 9999);
    outputAllData(*L);
    cout << endl;
    listDelete(L, 2);
    outputAllData(*L);

    delete L;
}
int main()
{
    SetConsoleOutputCP(65001);
    test();
    system("pause");
    return 0;
}