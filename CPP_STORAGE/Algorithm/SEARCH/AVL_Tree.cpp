#include <iostream>
#include <windows.h>

using namespace std;

// typedef enum balanceFactor
// {
//     LH,
//     EH,
//     RH
// };
typedef int elemType;
typedef bool status;
typedef struct BiTNode
{
    elemType data;   
    // int bf; //balance factor
    struct BiTNode *lchild, *rchild;
    int height;
} BiTNode, *BiTree;

int maxDepth(BiTree &p)
{
    if (!p)
        return 0;
    int max = 0, maxL = 0, maxR = 0;
    if (p->lchild)
        maxL = maxDepth(p->lchild);
    if (p->rchild)
        maxR = maxDepth(p->rchild);
    max = maxL > maxR ? maxL + 1 : maxR + 1;
    return max;
}
status searchAVL(BiTree &p, elemType data)
{
    if (!p)
        return false;
    else if (data == p->data)
        return true;
    else if (data < p->data)
        return searchAVL(p->lchild, data);
    else
        return searchAVL(p->rchild, data);
}
int getHeight(BiTree &p)
{
    if (!p)
        return 0;
    return p->height;
}
int getBalanceFactor(BiTree &p)
{
    if (!p)
        return 0;
    else
        return getHeight(p->lchild) - getHeight(p->rchild);
}
BiTree right_rotate(BiTree &p)
{
    BiTree L;
    L = p->lchild;
    p->lchild = L->rchild;
    L->rchild = p;
    p = L;
    p->height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;
    // L->height = max(getHeight(L->lchild), getHeight(L->rchild)) + 1;
    return p;
}

BiTree left_rotate(BiTree &p)
{
    BiTree R;
    R = p->rchild;
    p->rchild = R->lchild;
    R->lchild = p;
    p = R;
    p->height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;
    // R->height = max(getHeight(R->lchild), getHeight(R->rchild)) + 1;
    return p;
}

BiTree RL_rotate(BiTree &p)
{
    p = right_rotate(p);
    return left_rotate(p);
}
BiTree LR_rotate(BiTree &p)
{
    p = left_rotate(p);
    return right_rotate(p);
}

BiTree insertAVL(BiTree &T, elemType data)
{
    if (!T && !searchAVL(T, data)) //not found
    {
        T = new BiTNode;
        if (T)
        {
            T->data = data;
            T->rchild = T->lchild = NULL;
            T->height = 0;
        }
        else
        {
            cout << "the space is not enough!" << endl;
            exit(0);
        }
    }
    else if (data < T->data)
    {
        T->lchild = insertAVL(T->lchild, data);
        if (getBalanceFactor(T) > 1)
        {
            if (getBalanceFactor(T->lchild) > 0)
                T = right_rotate(T);
            else if (getBalanceFactor(T->lchild) < 0)
                T = LR_rotate(T);
        }
    }
    else if (data > T->data)
    {
        T->rchild = insertAVL(T->rchild, data);
        if (getBalanceFactor(T) < -1)
        {
            if (getBalanceFactor(T->rchild) < 0)
                T = left_rotate(T);
            else if (getBalanceFactor(T->rchild) > 0)
                T = RL_rotate(T);
        }
    }
    else
        cout << "the Node-" << data << " existed in AVL_tree\n";

    T->height = max(getHeight(T->lchild), getHeight(T->rchild)) + 1;
    return T;
}
BiTree addAVL(BiTree &p, elemType data)
{
    if (!p && !searchAVL(p, data)) //not found
    {
        p = new BiTNode;
        if (p)
        {
            p->data = data;
            p->rchild = p->lchild = NULL;
            p->height = 0;
        }
        else
        {
            cout << "the space is not enough!" << endl;
            exit(0);
        }
    }
    if (data < p->data)
        p->lchild = addAVL(p->lchild, data);
    else if (data > p->data)
        p->rchild = addAVL(p->rchild, data);

    p->height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;

    int bf = getBalanceFactor(p);
    if (bf > 1 && getBalanceFactor(p->lchild) > 0)
        return right_rotate(p);
    else if (bf < -1 && getBalanceFactor(p->rchild) < 0)
        return left_rotate(p);
    else if (bf > 1 && getBalanceFactor(p->lchild) < 0)
        return LR_rotate(p);
    else if (bf < -1 && getBalanceFactor(p->rchild) > 0)
        return RL_rotate(p);
    return p;
}

BiTree eraseAVL(BiTree &p, const elemType &data)
{
    if (!p)
        return NULL;
    if (data == p->data)
    {
        if (!p->lchild)
        {
            BiTree tmp = p;
            p = p->rchild;
            delete tmp;
            tmp = NULL;
            return p;
        }
        else if (!p->lchild)
        {
            BiTree tmp = p;
            p = p->lchild;
            delete tmp;
            tmp = NULL;
            return p;
        }
        else
        {
            BiTree tmp = p->rchild;
            while (tmp->lchild)
                tmp = tmp->lchild;
            p->data = tmp->data;
            // p->rchild = eraseAVL(p->rchild, tmp->data);
            // delete tmp;
            // tmp = NULL;
            if (p != tmp)
                p->rchild = tmp->lchild;
            else
                p->lchild = tmp->lchild;
            delete tmp;
        }
    }
    else if (p->data < data)
        p->rchild = eraseAVL(p->rchild, data);
    else
        p->lchild = eraseAVL(p->lchild, data);
    p->height = max(getHeight(p->lchild), getHeight(p->rchild)) + 1;
    if (getBalanceFactor(p) > 1)
    {
        if (getBalanceFactor(p->lchild)) //getHeight(p->lchild->lchild) > getHeight(p->lchild->rchild)
            p = LR_rotate(p);
        else
            p = right_rotate(p);
    }
    else if (getBalanceFactor(p) < -1)
    {
        if (getBalanceFactor(p->rchild) > 0) //OR getHeight(p->rchild->rchild) > getHeight(p->rchild->lchild)
            p = right_rotate(p);
        else
            p = RL_rotate(p);
    }
    return p;
}
void inOrderTraverseAVL(const BiTree &p)
{
    if (p)
    {
        inOrderTraverseAVL(p->lchild);
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
        inOrderTraverseAVL(p->rchild);
    }
}
void clearAVL(BiTree &p)
{
    if (p)
    {
        clearAVL(p->lchild);
        clearAVL(p->rchild);
        delete p;
        p = NULL;
    }
}
int main()
{
    SetConsoleOutputCP(65001);
    BiTree p = NULL;
    int arr[] = {0, 3, 5, 12, 13, 7, 8, 2, 6, 4, 11, 23, 23};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        p = insertAVL(p, arr[i]); // Or call function-addAVL()
    eraseAVL(p, arr[2]);
    inOrderTraverseAVL(p);
    cout << getHeight(p) << " : " << maxDepth(p) << endl;
    // delete p;
    // p = NULL;
    clearAVL(p);
    inOrderTraverseAVL(p);
    system("pause");
    return 0;
}
