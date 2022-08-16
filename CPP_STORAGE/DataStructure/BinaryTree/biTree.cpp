#include <iostream>
#include <windows.h>
#include <stack>
typedef std::string tElemType;
using namespace std;
typedef struct biTNode
{
    tElemType data;
    struct biTNode *lchild, *rchild;
} BiTNode, *biTree;
void initBiTree(biTree *T) //the number of node is  (2^depth)-1, so you need input specific and accurate number
{
    tElemType ch;
    cin >> ch;
    if (ch == "#")
        *T = NULL;
    else
    {
        *T = new biTNode;
        if (!*T)
            exit(1);
        (*T)->data = ch;
        initBiTree(&(*T)->lchild);
        initBiTree(&(*T)->rchild);
    }
}
void PreOrderTraverse(biTree &T)
{
    if (T == NULL)
        return;
    cout << T->data << endl;
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void nonRecursionPreTraverse(biTree &T)
{
    stack<biTree> st1;
    while (T || !st1.empty())
    {
        while (T)
        {
            cout << T->data << endl;
            st1.push(T);
            T = T->lchild;
        }
        if (!st1.empty())
        {
            T = st1.top();
            st1.pop();
            T = T->rchild;
        }
    }
    cout << endl;
}
void InOrderTraverse(biTree T)
{
    if (T == NULL)
        return;
    InOrderTraverse(T->lchild);
    cout << T->data << endl;
    InOrderTraverse(T->rchild);
}
void nonRecursionInTraverse(biTree &T)
{
    stack<biTree> st1;
    while (T || !st1.empty())
    {
        while (T)
        {
            st1.push(T);
            T = T->lchild;
        }
        if (!st1.empty())
        {
            T = st1.top();
            cout << T->data << endl;
            st1.pop();
            T = T->rchild;
        }
    }
    cout << endl;
}
void PostOrderTraverse(biTree &T)
{
    if (T == NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    cout << T->data << endl;
}
void nonRecursionPostTraverse(biTree &T)
{
    stack<biTree> st1;

    cout << endl;
}
// 对二叉树T求叶子结点数目
int Leaves(biTree &T)
{
    if (NULL == T)
        return 0;
    if (NULL == T->lchild && NULL == T->rchild)
        return 1;
    return Leaves(T->lchild) + Leaves(T->rchild);
}
int Depth(biTree &p)
{
    int l = 0, r = 0;
    if (!p)
        return 0;
    else
    {
        l = Depth(p->lchild);
        r = Depth(p->rchild);
        return l > r ? l + 1 : r + 1;
    }
}
int countNodes(biTree &p)
{
    if (!p)
        return 0;
    else
        return countNodes(p->lchild) + countNodes(p->rchild) + 1;
}

//1 2 4 # # 5 # # 3 $ # # 6 # #
int main()
{
    SetConsoleOutputCP(65001);
    biTree T;
    initBiTree(&T);
    cout << "PreOrderTraverse: \n";
    // PreOrderTraverse(*T);
    nonRecursionPreTraverse(T);
    initBiTree(&T);
    cout << "InOrderTraverse: \n";
    // InOrderTraverse(T);
    nonRecursionInTraverse(T);
    initBiTree(&T);
    cout << "PostOrderTraverse: \n";
    PostOrderTraverse(T);
    // nonRecursionPostTraverse(T);
    cout << "the count of leaves is " << countNodes(T) << endl;
    delete T;
    T = NULL;
    system("pause");
    return 0;
}
