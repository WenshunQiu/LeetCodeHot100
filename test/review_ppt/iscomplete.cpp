#include <iostream>
#include <queue>
#include "textbook/tree/tree.hpp"
using namespace std;
int iscomplete(BTNode *root)
{
    if (!root)
    {
        return 1;
    }
    queue<BTNode *> q;
    q.push(root);
    int nomorenode = false;
    while (!q.empty())
    {
        BTNode *tmp;
        tmp = q.front();
        q.pop();
        if (tmp == nullptr)
        {
            nomorenode = true;
        }
        else
        {
            if (nomorenode)
            {
                return 0;
            }

            q.push(tmp->lchild);
            q.push(tmp->rchild);
        }
    }
    return 1;
}