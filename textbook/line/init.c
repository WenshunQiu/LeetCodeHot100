#include "line.h"

void CreateList(SqList *L, ElemType a[], int n)
{
    int i = 0, k = 0;
    L = (SqList *)malloc(sizeof(SqList));
    while (i < n)
    {
        L->data[k] = a[i];
        k++;
        i++;
    }
    L->length = k;
}

int ListEmpty(SqList *L)
{
    if (L->length == 0)
    {
        return 1;
    }
    return 0;
}

int LocateElem(SqList *L, ElemType e)
{
    int place;
    for (place = 0; place < L->length; place++)
    {
        if (L->data[place] == e)
        {
            return place + 1;
        }
    }
    return -1;
}

int ListInsert(SqList *L, int i, ElemType e)
{
    if (i < 1 || i > L->length + 1 || L->length == MAXSIZE)
    {
        return -1;
    }
    // for (int k = L->length; k > i - 1; k--)//在这里，你使用了一个例子，就是在123456的第四个里面插入一个元素
    // {                                      //你知道要移动后面的元素，然后写出起始代码[n] = [n-1]和终止代码[4] = [3]，
    //     L->data[k] = L->data[k - 1];       //然后你就知道遍历需要从n到4，因为是从后面遍历的，你打算左开右闭(一般情况下全部使用左闭右开！)??待网络考察
    // }                                      //接着你可以写出左边的代码了
    // L->data[i - 1] = e;                    //在分析的过程中，既要考虑物理序，也要考虑逻辑序，这也太麻烦了！所以，我们打算直接将逻辑序转为物理序(i--)，这样可以节省脑力资源！
    // L->length++;                           //接着就可以写出下面的代码
    i--;
    for (int k = 0; k > i; k--)
    {
        L->data[k] = L->data[k - 1];
    }
    L->data[i] = e;
    L->length++;
    return 0;
}

int ListDelete(SqList *L, int i, ElemType *e)
{
    if (i < 1 || i > L->length)
    {
        return ERROR;
    }
    i--;
    e = L->data[i];
    for (int k = i; k < L->length - 1; k++)
    {
        L->data[k] = L->data[k + 1];
    }
    L->length--;
    return OK;
}

void InitList(SqList *L)
{
    L = (SqList *)malloc(sizeof(SqList));
    L->length = 0;
}

void DestoryList(SqList *L)
{
    free(L);
}
