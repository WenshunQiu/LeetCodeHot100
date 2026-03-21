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

void PrintList(LinkList L) {
    LNode *p = L->next;
    if (p == NULL) {
        printf("空集\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void FreeList(LinkList *L) {
    LNode *p = *L, *q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    *L = NULL;
}

int IsExist(LinkList L, int x) {
    LNode *p = L->next;
    while (p != NULL) {
        if (p->data == x) return 1;
        p = p->next;
    }
    return 0;
}

void DiffSet_Unordered(LinkList A, LinkList B) {
    LNode *pre = A;
    LNode *pa = A->next;
    LNode *temp;

    while (pa != NULL) {
        if (IsExist(B, pa->data)) {
            pre->next = pa->next;
            temp = pa;
            pa = pa->next;
            free(temp);
        } else {
            pre = pa;
            pa = pa->next;
        }
    }
    FreeList(&B);
}

void DiffSet_Ordered(LinkList A, LinkList B) {
    LNode *pre = A;
    LNode *pa = A->next;
    LNode *pb = B->next;
    LNode *temp;

    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            pre = pa;
            pa = pa->next;
        } else if (pa->data == pb->data) {
            pre->next = pa->next;
            temp = pa;
            pa = pa->next;
            free(temp);
        } else {
            pb = pb->next;
        }
    }
    FreeList(&B);
}

int main() {
    printf("===== 无序列表差集测试 =====\n");
    int arrA1[] = {3, 1, 5, 2, 7};
    int arrB1[] = {2, 5, 8};
    LinkList A1, B1;
    InitList(&A1, arrA1, 5);
    InitList(&B1, arrB1, 3);
    printf("原集合A："); PrintList(A1);
    printf("原集合B："); PrintList(B1);
    DiffSet_Unordered(A1, B1);
    printf("差集A-B："); PrintList(A1);
    FreeList(&A1);

    printf("\n===== 有序列表差集测试 =====\n");
    int arrA2[] = {1, 3, 5, 7, 9};
    int arrB2[] = {3, 7, 8};
    LinkList A2, B2;
    InitList(&A2, arrA2, 5);
    InitList(&B2, arrB2, 3);
    printf("原集合A："); PrintList(A2);
    printf("原集合B："); PrintList(B2);
    DiffSet_Ordered(A2, B2);
    printf("差集A-B："); PrintList(A2);
    FreeList(&A2);

    return 0;
}