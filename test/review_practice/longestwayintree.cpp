#include <iostream>
#include <queue>
#include "textbook/tree/tree.hpp"
using namespace std;
int ans = 0;
int depth(BTNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int L = depth(root->lchild);
    int R = depth(root->rchild);
    ans = max(ans, L + R + 1);
    return max(L, R) + 1;
    // 和那个最长深度差不多，只是在每一次递归的时候都更新一下最大值就可以了：因为这个递归可以走到每一个节点，
    // 利用这个性质就可以求得每个节点作为头节点的时候的最大宽度了
}