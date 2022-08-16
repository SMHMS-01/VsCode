#include <iostream>
#include <windows.h>
#include <time.h>
#define ERROR 0
#define OK 0
using namespace std;
typedef int elemType;
typedef int status;
class Node
{
private:
    elemType data;
    Node *next;

public:
    typedef Node *linkList; //declare linkList
    Node(/* args */);
    ~Node();
    status getElem(linkList L, int i, elemType &e);    //the get of linkList
    status listInsert(linkList *L, int i, elemType e); //the insert of linkList
    status listDelete(linkList *L, int i, elemType e); //the delete of linkList
    void creatListHead(linkList *L, int n);            //the creation of linkList head
    void creatListTail(linkList *L, int n);
    status clearList(linkList *L); //
    int listLength(linkList *L);
    void outputAllData();
};
typedef Node *linkList;
Node::Node(/* args */)
{
}

Node::~Node()
{
}
status Node::getElem(linkList L, int i, elemType &e)
{
    int j;
    linkList p;  //state a pointer
    p = L->next; //pointer to the first Node of L
    j = 1;       //a counter
    while (p && j < i)
    {                //Traverse and index
        p = p->next; //make p pointer to the next Node
        ++j;
    }
    if (!p || j > i)
        return ERROR; //if Ith is no exist
    e = p->data;      //get data from Ith
    return e;
}
status Node::listInsert(linkList *L, int i, elemType e)
{
    int j;
    linkList p, s;
    p = *L;
    j = 1;
    while (p && j < i) //Traverse and index
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    s = new Node;
    s->data = e;
    s->next = p->next; //make the successor of p assign to the successor of s
    p->next = s;       //make s assign to the successor of p
    return OK;
}
status Node::listDelete(linkList *L, int i, elemType e)
{
    int j;
    linkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
    return OK;
}
void Node::creatListHead(linkList *L, int n)
{
    linkList p;
    int i;
    srand(time(0)); //initialize the random number seed
    *L = new Node;
    (*L)->next = NULL;
    for (i = 0; i < n; i++)
    {
        p = new Node;
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}
void Node::creatListTail(linkList *L, int n)
{
    linkList p, r;
    int i;
    srand(time(0));
    *L = new Node;
    r = *L;
    for (i = 0; i < n; i++)
    {
        p = new Node;
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}
status Node::clearList(linkList *L)
{
    linkList p, q;
    p = (*L)->next; //p pointer to the first Node
    while (p)
    {
        q = p->next; //q equal to the next of p
        delete p;
        p = q; //make p=q
    }
    (*L)->next = NULL; //head Node's pointer field is empty
    return OK;
}
int Node::listLength(linkList *L)
{
    int i = 0;
    while ((*L)->next)
    {
        (*L) = (*L)->next;
        i++;
    }
    return i;
}
void Node::outputAllData()
{
    linkList p, q;
    p = next;
    while (p)
    {
        q = p->next;
        cout << p->data << endl;
        p = q;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    linkList *linklist = new linkList;
    (*linklist)->creatListTail(linklist, 10);
    (*linklist)->outputAllData();
    cout << endl;
    // (*linklist)->listDelete(linklist, 2, 0);

    (*linklist)->listInsert(linklist, 2, 9999);
    (*linklist)->listDelete(linklist, 2, 9999);
    (*linklist)->outputAllData();
    cout << endl;
    // (*linklist)->clearList(linklist);
    // (*linklist)->outputAllData();
    elemType num = 0;
    cout << (*linklist)->getElem(*linklist, 2, num) << endl
         << "his length is " << (*linklist)->listLength(linklist);
    delete linklist;
    system("pause");
    return 0;
}
