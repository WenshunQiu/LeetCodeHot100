#include <bits/stdc++.h>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 采用双重递归，第一重来决定哪个为头节点，第二重来决定怎么走路径
// 第一重递归只需要简单递归即可
// 第二重递归需要传入当前路径的长度，检查加上自己后是否满足题目要求，然后继续递归(因为可能有负数)
class Solution
{
public:
    int pathSum(TreeNode *root, int targetSum)
    {
        this->targetSum = targetSum;
        dfs1(root);
        return count;
    }

private:
    int count = 0;
    int targetSum = 0;
    void dfs1(TreeNode *root)
    {
        if (!root)
            return;
        dfs2(root, 0);
        dfs1(root->left);
        dfs1(root->right);
    }
    void dfs2(TreeNode *root, long sum)
    {
        if (!root)
            return;
        sum = sum + root->val;
        if (sum == targetSum)
            count++;
        dfs2(root->left, sum);
        dfs2(root->right, sum);
        return;
    }
};