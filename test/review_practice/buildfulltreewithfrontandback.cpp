#include <iostream>
#include <vector>
#include "textbook/tree/tree.hpp"
using namespace std;
int findIndex(const vector<int> nums, int l, int r, int num)
{
    return 0;
}
// pre :[现在][左孩子][右孩子]
// post:[左孩子][右孩子][现在]
BTNode *build(const vector<int> &pre, const vector<int> post, int preL, int preR, int postL, int postR)
{
    if (preL > preR)
    {
        return nullptr;
    }
    int rootVal = pre[preL]; // 其实也可以用pre[post]
    BTNode *root = new BTNode(rootVal);
    if (preL == preR)
    {
        return root;
    }
    int leftRoot = pre[preL + 1];                          // 左子树的根节点;
    int leftIdx = findIndex(post, postL, postR, leftRoot); // 在后序遍历中找到左树的根节点下标
    int leftNum = leftIdx - postL + 1;                     // 左子树的节点个数
    root->lchild = build(pre, post, preL + 1, preL + leftNum, postL, leftIdx);
    root->rchild = build(pre, post, preL + leftNum + 1, preR, leftIdx + 1, postR - 1);
    return root;
    // 这个构建树好像和其他的也是很像的，只不过它只能构建出满二叉树，不然会有多棵树
}