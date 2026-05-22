#include "search.hpp"
int IdxSearch(IdxType I[], int b, RecType R[], int n, KeyType k)
{
    int s = (n + b - 1) / b; // 每一块元素的个数
    int low = 0;
    int high = b - 1;
    int mid;
    int i;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (k <= I[mid].key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    i = I[high + 1].link;
    while (i < I[high + 1].link + s && R[i].key != k) // 这里原文是i <= I[high+1].link + s - 1 &&...
    {
        i++;
    }
    if (i < I[high + 1].link + s) // 这里原文是i <= I[high + 1].link + s - 1
    {
        return i + 1;
    }
    else
    {

        return 0;
    }
}
