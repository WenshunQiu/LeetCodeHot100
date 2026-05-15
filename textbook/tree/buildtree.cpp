#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "tree.hpp"
using namespace std;
// 前序 中 左 右
// 中序 左 中 右
// 后序 左 右 中
// 前序和后续是可以确定父母节点的，也就是中间节点

BTNode *CreateBT1(char *pre, char *in, int n) // n 为二叉树的节点个数
{
    // 思路：从前序中获取到中间节点，然后在中序中分割为左右节点来递归
    BTNode *b;
    char *p; // 指向分割的节点位置
    int k;
    if (n <= 0)
    {
        return nullptr;
    }
    b = (BTNode *)malloc(sizeof(BTNode));
    b->data = *pre;
    for (p = in; p < in + n; p++) // 找到分割节点的位置，但是这里为什么是n?
    {
        if (*p == *pre)
        {
            break;
        }
    }
    k = p - in; // 左子树的个数
    b->lchild = CreateBT1(pre + 1, in, k);
    b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1); // 个数减一是因为现在已经构建好一个节点了
}

BTNode *CreateBT2(char *post, char *in, int n) // 后序和中序来构建二叉树
{
    BTNode *b;
    char r, *p;
    int k;
    if (n <= 0)
    {
        return NULL;
    }
    r = *(post + n - 1); // 至于为什么需要减一，可以举一个例子来理解，也可根据左闭右开原则来理解
    // 找到中间节点
    b = (BTNode *)malloc(sizeof(BTNode));
    b->data = r; // 构建当前节点
    for (p = in; p < in + n; p++)
    {
        if (*p == r)
        {
            break;
        }
    } // 在中序中找到分割位置
    k = p - in; // 左子树的个数，下面的内容和上面的CreateBT1相同
    b->lchild = CreateBT2(post, in, k);
    b->rchild = CreateBT2(post + k, p + 1, n - k - 1);
    return b;
}
int main()
{
    char post[10], in[10];
    cin >> post >> in;
    BTNode *root = CreateBT2(post, in, strlen(post));
    return 0;
}
