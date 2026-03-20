#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

int main()
{ 
    int index = 0;
    scanf("%d", &index);
    Node *head = (Node*)malloc(sizeof(Node));
    Node *tail = head;
    if (!(scanf("%d", &(head->data))))
    {
        printf("Not Found\n");
        return 0;
    }
    head->next = NULL;
    int temp;
    int len = 1;
    while (scanf("%d", &temp) != EOF)
    {
        Node *t = (Node*)malloc(sizeof(Node));
        t->data = temp;
        tail->next = t;
        tail = t;
        tail->next = NULL;
        len++;
    }
    if ( index <= 0 || index > len)
    {
        printf("Not Found\n");
        return 0;
    }
    
    Node *p = head;
    for (int i = 0; i < len - index; i++)
    {
        p = p->next;
    }
    printf("%d\n", p->data);
    return 0;
}
