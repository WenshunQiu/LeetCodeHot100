#include "tree.hpp"

// 初始化的时候，每个节点的父节点是自己
void MAKE_SET(UFSTree s[], int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        s[i].rank = 0;
        s[i].parent = i;
    }
}

// 并查集的查找与路径压缩
int Find(UFSTree S[], int x)
{
    if (S[x].parent != x)
    {
        S[x].parent = Find(S, S[x].parent);
    }
    return S[x].parent;
}

int Find1(UFSTree S[], int x)
{
    int root = x;
    while (S[root].parent != root) // 找到root
    {
        root = S[root].parent;
    }
    int closestparent = x;
    while (closestparent != root) // 路径压缩
    {
        int tmp = S[closestparent].parent;
        S[closestparent].parent = root;
        closestparent = tmp;
    }
    return root;
}

void Union(UFSTree S[], int x, int y)
{
    int rootx = Find(S, x);
    int rooty = Find(S, y);
    if (rootx == rooty)
    {
        return;
    }
    if (S[rootx].rank > S[rooty].rank)
    {
        S[rooty].parent = rootx;
    }
    else
    {
        S[rootx].parent = rooty;
        if (S[rootx].rank == S[rooty].rank)
        {
            S[rooty].rank++;
        }
    }
}