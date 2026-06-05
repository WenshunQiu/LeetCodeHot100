#include <iostream>
#include "sorttype.hpp"
int partition(RecType R[], int i, int j)
{
    RecType base = R[i];
    while (i < j) // 中间动过判断条件的 Ⅰ
    {
        while (i < j && R[j].data >= base.data)
        {
            j--; // Ⅰ
        }
        if (i < j) // 需要在后续操作中加入非法判断
        {
            R[i] = R[j];
            i++;
        }
        while (i < j && R[i].data <= base.data)
        {
            i++;
        }
        if (i < j)
        {
            R[j] = R[i];
            j--;
        }
    }
    R[i] = base;
    return i;
}

void quickSort(RecType R[], int left, int right)
{
    int i;
    if (left < right)
    {
        i = partition(R, left, right);
        quickSort(R, left, i - 1);
        quickSort(R, i + 1, right);
    }
}