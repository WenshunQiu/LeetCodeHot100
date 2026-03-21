#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

void InitList(LinkList *L, int arr[], int n) {
    *L = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    LNode *tail = *L;
    for (int i = 0; i < n; i++) {
        LNode *newNode = (LNode *)malloc(sizeof(LNode));
        newNode->data = arr[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
}

void InsertBeforeMax(LinkList L, int x) {
    if (L == NULL || L->next == NULL) {
        printf("链表为空！\n");
        return;
    }

    LNode *p = L->next;
    int max = p->data;
    while (p != NULL) {
        if (p->data > max) {
            max = p->data;
        }
        p = p->next;
    }

    LNode *pre = L;
    p = L->next;
    while (p != NULL) {
        if (p->data == max) {
            break;
        }
        pre = p;
        p = p->next;
    }

    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = x;
    newNode->next = p;
    pre->next = newNode;
}

void PrintList(LinkList L) {
    LNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 7, 2, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    LinkList L;
    InitList(&L, arr, n);

    printf("原链表：");
    PrintList(L);

    int x = 9;
    InsertBeforeMax(L, x);

    printf("插入后：");
    PrintList(L);

    return 0;
}