#include <iostream>
typedef struct linkNode
{
    int data;
    linkNode *next;
    linkNode(int a)
    {
        data = a;
        next = nullptr;
    }
} linkNode;

void makeLinkedList(linkNode *&head)
{
    int n;
    scanf("%d", &n);
    if (n == 0)
    {
        head = nullptr;
        return;
    }
    int data;
    scanf("%d", &data);
    linkNode *_head = new linkNode(data);
    linkNode *temp = _head;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &data);
        temp->next = new linkNode(data);
        temp = temp->next;
    }
    head = _head;
    return;
}
void merge(linkNode *&head, int low, int mid, int high)
{
    int oldlow = low;
    linkNode *store = new linkNode(-1);
    linkNode *storeHead = store;
    linkNode *lowP = head;
    linkNode *midP = head;
    linkNode *highP = head;
    linkNode *start = nullptr;
    for (int i = 0; i < low; i++)
    {
        start = lowP;
        lowP = lowP->next;
    }
    for (int i = 0; i < mid; i++)
    {
        midP = midP->next;
    }
    midP = midP->next;
    for (int i = 0; i < high; i++)
    {
        highP = highP->next;
    }
    int j = mid + 1;
    while (low <= mid && j <= high)
    {
        if (lowP->data <= midP->data)
        {
            store->next = new linkNode(lowP->data);
            store = store->next;
            lowP = lowP->next;
            low++;
        }
        else
        {
            store->next = new linkNode(midP->data);
            store = store->next;
            midP = midP->next;
            j++;
        }
    }
    while (low <= mid)
    {
        store->next = new linkNode(lowP->data);
        store = store->next;
        lowP = lowP->next;
        low++;
    }
    while (j <= high)
    {
        store->next = new linkNode(midP->data);
        store = store->next;
        midP = midP->next;
        j++;
    }
    store->next = highP->next;
    if (oldlow == 0)
        head = storeHead->next;
    else
        start->next = storeHead->next;
    // 还没有内存处理呢
}
void mergeSortDC(linkNode *&head, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSortDC(head, low, mid);
        mergeSortDC(head, mid + 1, high);
        merge(head, low, mid, high);
    }
}
int linkedListLenth(linkNode *head)
{
    if (head == nullptr)
    {
        return -1;
    }
    linkNode *p = head;
    int count = 0;
    while (p != nullptr)
    {
        p = p->next;
        count++;
    }
    return count;
}
void printLinkedList(linkNode *head)
{
    linkNode *p = head;
    while (p != nullptr)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
int main()
{
    linkNode *head;
    makeLinkedList(head); // 创建链表
    int len = linkedListLenth(head);
    if (len == -1)
    {
        return 0;
    }
    mergeSortDC(head, 0, len - 1);
    printLinkedList(head);
}