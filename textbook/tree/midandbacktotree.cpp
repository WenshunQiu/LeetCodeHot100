#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "tree.hpp"
using namespace std;

BTNode *CreateBT2(char *post, char *in, int n)
{
    BTNode *b;
    char r, *p;
    int k;
    if (n <= 0)
    {
        return NULL;
    }
    r = *(post + n - 1);
    b = (BTNode *)malloc(sizeof(BTNode));
    b->data = r;
    for (p = in; p < in + n; p++)
    {
        if (*p == r)
        {
            break;
        }
    }
    k = p - in;
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
