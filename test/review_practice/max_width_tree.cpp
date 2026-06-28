#include <iostream>
#include <queue>
#include <algorithm>
#include "textbook/tree/tree.hpp"
using namespace std;

int maxWidth(BTNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    queue<pair<BTNode *, int>> q;
    pair<BTNode *, int> temp = {nullptr, 0};
    q.push({root, 1});
    int howManyTreeThisLevel = 1;
    int maxWidth = 1;
    while (!q.empty())
    {
        maxWidth = max(maxWidth, q.back().second - q.front().second + 1);
        howManyTreeThisLevel = q.size();
        for (int i = 0; i < howManyTreeThisLevel; i++)
        {
            temp = q.front();
            q.pop();
            if (temp.first->lchild)
            {
                q.push({temp.first->lchild, temp.second * 2});
            }
            if (temp.first->rchild)
            {
                q.push({temp.first->rchild, temp.second * 2 + 1});
            }
        }
    }
    return maxWidth;
}