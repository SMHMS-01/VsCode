#include <iostream>
#include <windows.h>
#include <queue>
using namespace std;

// Definition for a binary tree node.

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    TreeNode *mirrorTree(TreeNode *root)
    {
        //检查是否为空树
        if (!root)
            return nullptr;
        
        //由于是层序遍历，因此可以使用队列（或栈，压栈顺序与队列相反）储存节点数据
        queue<TreeNode *> que;
        que.push(root);

        //节点不为空则进行循环
        while (!que.empty())
        {
            //每次循环操作的节点
            TreeNode *tmp = que.front();
            //到该节点进行左右节点交换，则将其弹出队列
            que.pop();
            //确保弹出，循环继续
            if (tmp == NULL)
                continue;
            //左右子树交换
            swap(tmp->left, tmp->right);
            //边界检查与交换后的左右子树的压入队列操作
            if (tmp->left)
                que.push(tmp->left);
            if (tmp->right)
                que.push(tmp->right);
        }
        //返回根节点
        return root;
    }
};
int main()
{
    SetConsoleOutputCP(65001);
    system("pause");
    return 0;
}
