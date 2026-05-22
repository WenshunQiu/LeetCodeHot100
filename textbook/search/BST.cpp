#include "search.hpp"
#include <cstdlib>
BSTNode *SearchBST(BSTNode *bt, KeyType k)
{
    if (bt == nullptr || bt->key == k)
    {
        return bt;
    }
    if (k < bt->key)
    {
        SearchBST(bt->lchild, k);
    }
    else
    {
        SearchBST(bt->rchild, k);
    }
}
BSTNode *SearchBST1(BSTNode *bt, KeyType k)
{
    BSTNode *p = bt;
    while (p != nullptr)
    {
        if (p->key == k)
        {
            break;
        }
        else if (k < p->key)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }
    return p;
}

BSTNode *InsertBST(BSTNode *bt, KeyType k) // 这里没有处理存在相等元素的情况!
{
    if (bt == nullptr)
    {
        bt = (BSTNode *)malloc(sizeof(BSTNode));
        bt->key = k;
        bt->lchild = bt->rchild = nullptr;
    }
    if (k < bt->key)
    {
        bt->lchild = InsertBST(bt->lchild, k);
    }
    else // 如果相等也加到右子树，
    // 加上if (k > bt->key)后，如果相等就不执行任何操作，不加不减
    {
        bt->rchild = InsertBST(bt->rchild, k);
    }
    return bt;
}

BSTNode *CreatBST(KeyType a[], int n)
{
    BSTNode *bt = nullptr;
    for (int i = 0; i < n; i++)
    {
        bt = InsertBST(bt, a[i]);
    }
    return bt;
}

