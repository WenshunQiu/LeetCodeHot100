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
