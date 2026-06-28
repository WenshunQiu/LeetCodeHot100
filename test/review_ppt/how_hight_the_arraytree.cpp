#include <iostream>
#include <queue>
#include "textbook/tree/tree.hpp"
using namespace std;
int getHight(char a[], int n, int index)
{
    if (index > n)
    {
        return 0;
    }
    int lhight = getHight(a, n, index * 2);
    int rhight = getHight(a, n, index * 2 + 1);
    return lhight > rhight ? lhight + 1 : rhight + 1;
}
int getHight(BTNode *root)
{
    if (!root)
    {
        return 0;
    }
    int lhight = getHight(root->lchild);
    int rhight = getHight(root->rchild);
    return lhight > rhight ? lhight + 1 : rhight + 1;
}
int main()
{
    char a[] = {'0', 'a', 'b', 'c', 'd'};
    printf("%d", getHight(a, 4, 1));
}