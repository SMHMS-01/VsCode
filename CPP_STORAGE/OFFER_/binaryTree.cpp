#include <iostream>
#include <windows.h>
#include <exception>
#include <cmath>

using namespace std;
typedef int dataType;
struct BinaryTreeNode
{
    dataType value;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
};
BinaryTreeNode *ReConstructBinaryTree(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder)
{
    int rootValue = startInorder[0];
    BinaryTreeNode *root = new BinaryTreeNode();
    root->value = rootValue;
    root->left = root->right = nullptr;

    if (startPreorder == endPreorder)
    {
        if (startInorder == endInorder && *startPreorder == *startInorder)
            return root;
        else
            throw std::invalid_argument("Invalid input!\n");
    }

    int *rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue) // search root node where list into inOrderTraverse
        ++rootInorder;

    if (rootInorder == endInorder && *rootInorder != rootValue) // double checking && maybe that can't be searched
        throw std::invalid_argument("Invalid input!\n");

    int left_length = rootInorder - startInorder;
    int *leftPreOrderEnd = startPreorder + left_length;

    if (left_length > 0)
    {
        root->left = ReConstructBinaryTree(startPreorder + 1, leftPreOrderEnd, startInorder, rootInorder + 1);
    }

    if (left_length < endPreorder - startPreorder)
    {
        root->right = ReConstructBinaryTree(leftPreOrderEnd + 1, endPreorder, rootInorder + 1, endInorder);
    }
    return root;
}

void MirrorRecurively(BinaryTreeNode *pRoot)
{
    if (!pRoot || !pRoot->left || !pRoot->right)
        return;
    BinaryTreeNode *pTemp = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = pTemp;
    if (pRoot->left)
        MirrorRecurively(pRoot->left);
    if (pRoot->right)
        MirrorRecurively(pRoot->right);
}

template <class T>
bool Equal(T num1, T num2)
{
    if (num1 - num2 == 0)
        return true;
    else
        return false;
}
template <>
bool Equal(double num1, double num2)
{
    if (fabs(num1 - num2) < 0.000000000000001)
        return true;
    else
        return false;
}
bool DoesTree1HaveTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    if (!pRoot1)
        return false;
    if (!pRoot2)
        return true;
    if (Equal(pRoot1->value, pRoot2->value))
        return DoesTree1HaveTree2(pRoot1->left, pRoot2->left) && DoesTree1HaveTree2(pRoot1->right, pRoot2->right);
    return false;
}

bool HasSubTree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    bool result = false;

    if (pRoot1 && pRoot2)
    {
        if (Equal(pRoot1->value, pRoot2->value))
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        if (!result)
            result = HasSubTree(pRoot1->left, pRoot2);
        if (!result)
            result = HasSubTree(pRoot1->right, pRoot2);
    }
    return result;
}

//
bool isSymmetrical(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    if (!pRoot1 && !pRoot2)
        return true;
    if (!pRoot1 || !pRoot2)
        return false;
    if (pRoot1->value != pRoot2->value)
        return false;
    return isSymmetrical(pRoot1->left, pRoot2->right) && isSymmetrical(pRoot1->right, pRoot2->left);
}
bool isSymmetrical(BinaryTreeNode *pRoot)
{
    return isSymmetrical(pRoot, pRoot);
}
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
