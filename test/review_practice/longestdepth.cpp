#include <iostream>
#include <algorithm>
#include "textbook/tree/tree.hpp"
using namespace std;

int LongestDepth(BTNode *root)
{
    if (!root)
    {
        return 0;
    }
    int ldepth = root->lchild ? LongestDepth(root->lchild) : 0;
    int rdepth = root->rchild ? LongestDepth(root->rchild) : 0;
    return max(ldepth + 1, rdepth + 1);
}