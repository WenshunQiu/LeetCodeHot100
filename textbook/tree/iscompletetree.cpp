#include <iostream>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 判断是否为完全二叉树
// 完全二叉树：除了最后一层，其他层都是满的；并且最后一层的元素全部靠左
// 思路，逐层遍历，遇到空之后后面只能为空
bool isCompleteTree(TreeNode *root)
{
    if (root == nullptr)
    {
        return true;
    }

    queue<TreeNode *> q;
    q.push(root);
    bool foundNull = false;

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        if (node == nullptr)
        {
            foundNull = true;
        }
        else
        {

            if (foundNull)
            {
                return false;
            }

            q.push(node->left);
            q.push(node->right);
        }
    }

    return true;
}
