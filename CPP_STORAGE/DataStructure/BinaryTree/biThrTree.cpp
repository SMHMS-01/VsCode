#include <iostream>
#include <windows.h>
#include <queue>
using namespace std;
//Binary Thread Tree some structure like double linked list
typedef std::string tElemType;

typedef enum
{
    link,  //link means a pointer point to left and right child
    thread //thread means a thread point to predecessor or successor
} pointerTag;
typedef struct biThrNode
{
    tElemType data;
    struct biThrNode *lchild, *rchild;
    pointerTag lTag;
    pointerTag rTag;

} biThrNode, *biThrTree;

biThrTree init(biThrTree &T)
{
    T = new biThrNode;
    T->lchild = NULL;
    T->rchild = NULL;
    T->lTag = thread;
    T->rTag = thread;
    return T;
}
int depth(biThrTree T)
{
    if (T == NULL)
        return 0;
    int m = depth(T->lchild);
    int n = depth(T->rchild);
    if (m > n)
        return m + 1;
    return n + 1;
}
int countNode(biThrTree T)
{
    return T == NULL ? 0 : countNode(T->lchild) + countNode(T->rchild) + 1;
}
int countNode_leaves(biThrTree T)
{
    if (T == 0)
        return 0;
    if (!T->lchild && !T->rchild)
        return 1;
    return countNode_leaves(T->lchild) + countNode_leaves(T->rchild);
}
void creat_tree(biThrTree *T)
{
    tElemType ch;
    cin >> ch;
    if (ch == "#")
        *T = NULL;
    else
    {
        (*T) = new biThrNode;
        if (!*T)
            exit(1);
        (*T)->data = ch;
        creat_tree(&(*T)->lchild);
        creat_tree(&(*T)->rchild);
    }
}
void InOrderTraverse(biThrTree &T)
{
    if (T == NULL)
        return;
    InOrderTraverse(T->lchild);
    cout << T->data << endl;
    InOrderTraverse(T->rchild);
}
static biThrTree pre = new biThrNode; //A global variable, used for record accessed node last time
void inThreading(biThrTree p)
{
    if (p == NULL)
        return;
    inThreading(p->lchild); //threadize
    if (!p->lchild)
    {
        p->lTag = thread;
        p->lchild = pre;
    }
    if (!pre->rchild && pre) // just make precusor  rchild point to successor when p->rchild
    {
        pre->rTag = thread;
        pre->rchild = p;
    }
    pre = p;
    inThreading(p->rchild);
}
void inOrderTraverse_Thr(biThrTree &T) // T point to head node
{
    biThrTree p = new biThrNode;
    p = T->lchild; //p point to root Node
    while (p != T)
    {
        while (p->lTag == link) //CYCLE UNTIL THE FIRST IN ORDER TRAVERSE NODE
            p = p->lchild;
        cout << p->data << endl;
        while (p->rTag == thread && p->rchild != T) //from the first in order traverse node to access its successor
        {
            p = p->rchild;
            cout << p->data << endl;
        }
        p = p->rchild; // To root
    }
}

void BinaryLevelOder(biThrTree *&root)
{
    std::queue<biThrNode *> Q;
    if (root)
        Q.push(*root);
    while (!Q.empty())
    {
        biThrNode *front = Q.front();
        Q.pop();
        cout << front->data;
        if (front->lchild)
            Q.push(front->lchild);
        if (front->rchild)
            Q.push(front->rchild);
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    biThrTree *T = new biThrTree;
    init(*T);
    creat_tree(T);
    InOrderTraverse(*T);
    inThreading(*T);
    inOrderTraverse_Thr(*T);
    delete T;
    T = NULL;
    system("pause");
    return 0;
}
