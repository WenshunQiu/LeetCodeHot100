#include <stdio.h>

#include <stdlib.h>

#define ERROR -1

#define OK 1

// 定义结点类型

typedef struct LNode
{

    int data;

    struct LNode *next;

} LNode, *LinkList;

// 不带头节点单链表的初始化

int ListInit(LinkList &L)
{

    L = NULL;

    return OK;
}

// 尾插法建立不带头结点的单链表

int LinkListCreat(LinkList &L)
{

    LNode *s, *r = L;

    int x;

    scanf("%d", &x);

    while (x != 9999)
    {

        s = (LNode *)malloc(sizeof(LNode));

        if (s == NULL)

            return ERROR;

        s->data = x;

        s->next = NULL;

        if (L == NULL)
        {

            L = s;

            r = s;
        }

        else
        {

            r->next = s;

            r = s;
        }

        scanf("%d", &x);
    }

    return OK;
}

// 递归算法实现删除单链表中所有值为x的结点

int del_x(LinkList &L, int x)
{
    if (!L)
    {
        return ERROR;
    }
    if (L->data == x)
    {

        LinkList tmp;
        tmp = L;
        L = L->next;
        delete tmp;
        del_x(L, x);
        return 0;
    }
    if (L->next)
    {
        if (L->next->data == x)
        {
            LinkList tmp;
            tmp = L->next;
            L->next = L->next->next; // 可能要改为nullptr
            delete tmp;
            del_x(L, x);
        }
        del_x(L->next, x);
        return OK;
    }
    return OK;
}

// 递归算法实现逆序打印单链表

int InversePrint(LinkList L)
{
    if (!L)
    {
        return ERROR;
    }
    if (L->next)
    {
        InversePrint(L->next);
        printf("%d ", L->data);
    }
    else
    {
        printf("%d ", L->data);
    }
    return OK;
}

int main()

{

    int x;

    LinkList L;

    ListInit(L);

    LinkListCreat(L);

    scanf("%d", &x);

    del_x(L, x);

    InversePrint(L);

    return 0;
}
