#include <bits/stdc++.h>
using namespace std;
/*
  Definition for a binary tree node.
  struct TreeNode
  {
      int val;
      TreeNode left;
      TreeNode right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode left, TreeNode right) : val(x), left(left), right(right) {}
  };
  */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 最长depth使用dfs，好像刚才那个也是用的dfs，只不过那边用多了几个dfs罢了，这里二叉树只需要dfs两次(左边和右边)
// dfs返回最长的一条边，在回溯的部分也是统计最长的长度
class Solution
{
public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        dfs(root);
        return maxDepth;
    }

private:
    int maxDepth = 0;
    int dfs(TreeNode *root)
    {
        if (!root)
            return 0;
        int maxLeftLen = dfs(root->left);
        int maxRightLen = dfs(root->right);
        maxDepth = max(maxDepth, maxLeftLen + maxRightLen );
        return max(maxRightLen + 1, maxLeftLen + 1);
    }
};