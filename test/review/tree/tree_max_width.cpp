#include <iostream>
#include <queue>
#include <algorithm>
#include "textbook/tree/tree.hpp"
using namespace std;
// 这里是计算最多元素的行的元素个数
// 计算二叉树的最大宽度在另外的算法当中，可以看一下https://leetcode.cn/problems/maximum-width-of-binary-tree/

// 维护一个个数int，表示这一层的个数，这个可以从上一层得到
// 用for去循环它，将它的孩子push到queue里面
// 好像如果循环完了那么上一层在queue的就全部pop掉了
// 那就可以根据queue的大小来更新个数int了
// 同时也要用max来更新最大宽度

int maxWidth(BTNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    queue<BTNode *> q;
    q.push(root);
    int size = 1;
    int maxsize = 1;
    int floor = 0;
    while (!q.empty())
    {
        maxsize = max(size, (int)q.size());
        for (int i = 0; i < size; i++)
        {
            BTNode *temp = q.front();
            q.pop();
            if (temp->lchild != nullptr)
            {
                q.push(temp->lchild);
            }
            if (temp->rchild != nullptr)
            {
                q.push(temp->rchild);
            }
        }
        size = q.size();
        floor++;
    }
    return maxsize;
}