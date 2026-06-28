#include <iostream>
#include "textbook/tree/tree.hpp"
using namespace std;
int num = 0;
void leafNum(BTNode *root)
{
    if (!root)
    {
        return;
    }
    if (root->lchild == nullptr && root->rchild == nullptr)
    {
        num++;
        return;
    }
    else
    {
        leafNum(root->lchild);
        leafNum(root->rchild);
    }
}