#include "search.hpp"

// 找到第一个大于或者等于k的元素的位置
int BinSearch(RecType R[], int n, KeyType k)
{
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (k <= R[mid].key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return high + 1;
}