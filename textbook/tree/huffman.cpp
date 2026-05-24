#include <string>
#include <iostream>
#include "tree.hpp"
using namespace std;

HTNode *creatHTNode(HTNode ht[], int n0) // ht前n0个元素是叶子节点，n0到n0*2 - 1 个元素是节点
// 构建哈夫曼树，首先先初始化，再维护两个权值最小的节点的weight min1,min2和指针lnode rnode,找到后再在n0位置新建节点，并建立父母指向关系
{
    int k, lnode, rnode;
    double min1, min2;
    for (int i = 0; i < 2 * n0 - 1; i++) // 一定要进行初始化，有时候编译器为了方便会把结构放到有数据的内存上面！
    {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
    }
    for (int i = n0; i < 2 * n0 - 1; i++)
    {
        min1 = min2 = 32767; // 储存两个权值最小节点的weight
        lnode = rnode = -1;  // 储存两个权值最小的点的index
        for (int k = 0; k < i; k++)
        {
            if (ht[k].parent == -1)
            {
                if (ht[k].weight < min1)
                {
                    min2 = min1;
                    rnode = lnode;
                    min1 = ht[k].weight;
                    lnode = k;
                }
                else if (ht[k].weight < min2)
                {
                    min2 = ht[k].weight;
                    rnode = k;
                }
            }
        } // 找到两个权值最小的节点
        ht[i].weight = ht[lnode].weight + ht[rnode].weight;
        ht[i].lchild = lnode;
        ht[i].rchild = rnode;
        ht[lnode].parent = i;
        ht[rnode].parent = i;
    }
}
HTNode *init(string data, double weight[], int n0)
{
    HTNode *ht = (HTNode *)malloc((n0 * 2 - 1) * sizeof(HTNode));
    for (int i = 0; i < n0; i++)
    {
        ht[i].data = data[i];
        ht[i].weight = weight[i];
        ht[i].lchild = ht[i].rchild = ht[i].parent = -1;
    }
    return ht;
}

void CreatHCode(HTNode ht[], HCode hcd[], int n0) // 哈夫曼编码从后面构建，维护当前c以及父母节点f，还有一个指向编码开始位置的指针start
{
    int f, c; // f family c current
    HCode hc;
    for (int i = 0; i < n0; i++)
    {
        hc.start = n0; // 最大的编码一共有n0位
        c = i;
        f = ht[i].parent;
        while (f != -1) // 一直到根节点
        {
            if (ht[f].lchild == c)
            {
                hc.cd[hc.start--] = '0';
            }
            else
            {
                hc.cd[hc.start--] = '1';
            }
            c = f;
            f = ht[f].parent;
        }
        hc.start++; // 指向正确开始位置
        hcd[i] = hc;
    }
}
