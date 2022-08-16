#include <iostream>
#include <windows.h>

using namespace std;
typedef int elemType;
typedef bool status;
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

status Delete(BiTree *p);
status searchBST(BiTree &T, int key);

BiTree newNodeInit(elemType key)
{
    BiTree p = new BiTNode;
    p->data = key;
    p->rchild = p->lchild = NULL;
    return p;
}
BiTree insertBST(BiTree &p, elemType key)
{
    if (!p && !searchBST(p, key))
    {
        p = new BiTNode;
        if (p)
        {
            p->data = key;
            p->rchild = p->lchild = NULL;
        }
        else
        {
            cout << "the space is not enough!" << endl;
            exit(0);
        }
    }
    else if (key < p->data)
        p->lchild = insertBST(p->lchild, key);
    else if (key > p->data)
        p->rchild = insertBST(p->rchild, key);
    return p;
}

status searchBST(BiTree &T, int key)
{
    if (!T)
        return false;
    else if (key == T->data)
        return true;
    else if (T->data > key)
        return searchBST(T->lchild, key);
    else
        return searchBST(T->rchild, key);
}

status DeleteBST(BiTree *T, int key)
{
    if (!*T)
        return false;
    else
    {
        if (key == (*T)->data)
            return Delete(T);
        else if (key < (*T)->data)
            return DeleteBST(&(*T)->lchild, key);
        else
            return DeleteBST(&(*T)->rchild, key);
    }
}
status Delete(BiTree *p)
{
    BiTree q, s;
    if ((*p)->rchild == NULL)
    {
        q = *p;
        *p = (*p)->lchild;
        delete q;
    }
    else if ((*p)->lchild == NULL)
    {
        q = *p;
        *p = (*p)->rchild;
        delete q;
    }
    else
    {
        q = *p;
        s = (*p)->lchild;
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;//覆盖为前驱节点
        if (q != *p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;
        delete s;
    }
    return TRUE;
}
void inOrderTraverseBST(const BiTree &p)
{
    if (p)
    {
        inOrderTraverseBST(p->lchild);
        cout << "\t\tpCurrent->data: " << p->data
             << endl;
        if (p->lchild)
            cout << "leftchild: " << p->lchild->data << "\t\t\t";
        else
            cout << "leftchild: NULL\t\t\t";
        if (p->rchild)
            cout << "rightchild: " << p->rchild->data;
        else
            cout << "rightchild: NULL";
        cout << endl
             << endl;
        inOrderTraverseBST(p->rchild);
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    BiTree p = NULL;
    int arr[] = {0, 3, 5, 12, 13, 7, 8, 2, 6, 4, 11, 23, 23};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        p = insertBST(p, arr[i]);
    inOrderTraverseBST(p);
    DeleteBST(&p, 5);
    DeleteBST(&p, 7);
    insertBST(p, 7);
    inOrderTraverseBST(p);
    delete p;
    p = NULL;
    system("pause");
    return 0;
}
