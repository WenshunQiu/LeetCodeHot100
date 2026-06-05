#include <iostream>
#include "sorttype.hpp"

void sift(RecType R[], int left, int right)
{
    int end = right;
    int lchild = left * 2;
    RecType tmp = R[left];
    while (left <= end)
    {
        if (left < end && R[lchild].data < R[lchild + 1].data)
        {
            lchild++; // 这里就变成右孩子了
        }
        if (tmp.data < R[lchild].data)
        {
            R[left] = R[lchild];
            // 继续往下找
            left = lchild;
            lchild = left * 2;
        }
        else
            break; // 完成构建返回
    }
    R[left] = tmp;
} // 这里只处理了从某个节点到其后面节点的树的维护，需要保证其后面的树已经被维护过了。
// 理解为给已经维护过的树加一个可能破坏结构的parent，然后对其整体进行维护
void swap(RecType &A, RecType &B)
{
    RecType tmp = A;
    A = B;
    B = tmp;
    free(&tmp);
}
void heapSort(RecType R[], int n)
{
    for (int i = n / 2; i >= 1; i--) // 这里保证了它是从最后一个节点开始的
    {
        sift(R, i, n);
    }
    for (int i = n; i >= 2; i--)
    {
        swap(R[1], R[i]);
        sift(R, 1, i - 1);
    }
}