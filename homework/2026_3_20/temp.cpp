#include <stdio.h>
#include <stdlib.h>
struct table
{
    int a;
    struct table *next;
};
typedef struct table node;
int main()
{
    int n;
    scanf("%d", &n);
    printf("\n");
    int c[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &c[i]);
    }
    node *head = (node*)malloc(sizeof(node));
    head->next = NULL;
    node *tail = head;
    for (int j = 0; j < n; j++)
    {
        node *p = (node*)malloc(sizeof(node));
        p->a = c[j];
        p->next = NULL;
        tail->next = p;
        tail = p;
    }

    if (n > 0)
    {
        node *prev = head;
        node *cur = head->next;
        node *max_prev = head;
        node *max_node = head->next;
        int max_val = cur->a;

        while (cur)
        {
            if (cur->a >= max_val)
            {
                max_val = cur->a;
                max_prev = prev;
                max_node = cur;
            }
            prev = cur;
            cur = cur->next;
        }

        if (max_node != tail)
        {
            max_prev->next = max_node->next;
            tail->next = max_node;
            max_node->next = NULL;
            tail = max_node;
        }
    }

    node *p = head->next;
    while (p)
    {
        printf("%d\n", p->a);
        p = p->next;
    }

    return 0;
}