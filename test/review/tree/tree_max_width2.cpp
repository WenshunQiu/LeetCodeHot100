#include <iostream>
#include <algorithm>
#include <queue>
#include "textbook/tree/tree.hpp"
using namespace std;
typedef pair<BTNode *, int> pairs;
// 求树最大的宽度
// 这里就包括了空节点
/*
每一层的宽度被定义为两个端点（该层最左和最右的非空节点，两端点间的null节点也计入长度）之间的长度。
示例 1:
输入:
           1
         /   \
        3     2
       / \     \
      5   3     9
输出: 4
解释: 最大值出现在树的第 3 层，宽度为 4 (5,3,null,9)。*/
// 找宽度可以将树映射在数组，然后求数组间某两个数(这里是最左边和最右边的节点)的宽度就可以了
// 使用pair来保存位置和节点
int maxWidth(BTNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    queue<pairs> q;
    q.push({root, 1});
    int size = 1;
    int maxwidth = 0;
    pairs rright = q.front();
    while (!q.empty())
    {
        pairs lleft = q.front();
        for (int i = 0; i < size; i++)
        {
            pairs temp = q.front();
            q.pop();
            if (temp.first->lchild != nullptr)
            {
                q.push({temp.first->lchild, temp.second * 2});
            }
            if (temp.first->rchild != nullptr)
            {
                q.push({temp.first->rchild, temp.second * 2 + 1});
            }
            rright = temp;
        }
        maxwidth = max(maxwidth, rright.second - lleft.second + 1);
        size = q.size();
    }
    return maxwidth;
}