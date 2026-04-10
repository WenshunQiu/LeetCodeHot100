#include <iostream>
#include <iterator>
#include <ostream>
#include <stdio.h>

#include <stdlib.h>

// 函数结果状态代码

#define TRUE 1

#define FALSE 0

#define OK 1

#define ERROR 0

#define INFEASIBLE 0

typedef int Status;

typedef int ElemType;

// 定义结构体

typedef struct LNode

{

    ElemType data; // 数据域

    struct LNode *next; // 指针域

} LNode, *LinkList;

Status InitList(LinkList &L)

{

    int x, i;

    L = (LinkList)malloc(sizeof(LNode));

    if (L == NULL)

    {

        printf("memory malloc failure\n");

        return ERROR;
    }

    L->next = NULL;

    // 根据键盘值构造链表

    LinkList r;

    r = L;

    for (i = 0;; i++)

    {

        scanf("%d", &x);

        if (x == -1)

            break;

        LinkList p = (LinkList)malloc(sizeof(LNode));

        if (!p)

        {

            printf("initial failure\n");

            return ERROR;
        }

        p->data = x;

        p->next = NULL;

        r->next = p;

        r = p;
    }

    return OK;
}

void inverseprint(LinkList p)

{
    if (p->next)
    {
        inverseprint(p->next);
        std::cout << p->data << " ";
    }
    else
    {
        std::cout << p->data << " ";
    }
}

Status IsAscendOrder(LinkList L)

{
    if (L->next)
    {
        return L->data > L->next->data ? IsAscendOrder(L->next) : 0;
    }
    return 1;
}

int main()

{

    // 初始化链表

    LinkList L;

    if (InitList(L) == ERROR)

    {

        return 0;
    }

    inverseprint(L->next); // 对应第一行打印输出

    printf("\n");

    Status mystate = IsAscendOrder(L->next);

    if (mystate == OK)

        printf("is AscendOrder\n");

    else

        printf("not AscendOrder\n");

    return 0;
}
