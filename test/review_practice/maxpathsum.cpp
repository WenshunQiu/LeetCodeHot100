#include <iostream>
#include "textbook/tree/tree.hpp"
using namespace std;

int maxpathsum = 0;

int calpathsum(BTNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int lbestpath = max(calpathsum(root->lchild), 0);
    int rbestpath = max(calpathsum(root->rchild), 0);
    maxpathsum = max(maxpathsum, rbestpath + lbestpath + root->data);
    return max(lbestpath, rbestpath) + root->data;
}