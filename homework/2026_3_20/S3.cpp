#include <iostream>
using namespace std;

typedef struct linkdList
{
    int data;
    linkdList *next;
};

int main()
{
    struct linkdList *head, *tail;
    head = new linkdList();
    head->next = NULL;
    tail = head;
    cin >> head->data;
    int value;
    while (cin >> value)
    {
        struct linkdList *temp;
        temp = new linkdList();
        temp->data = value;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        if (cin.get() == '\n')
            break;
    }
    int del;
    cin >> del;

    // 定位删除
    struct linkdList *edge;
    edge = head;
    while (edge != NULL)
    {
        if (edge->data >= del)
        {
            break;
        }
        edge = edge->next;
    }
    // 输出
    struct linkdList *cur;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
    while (edge != NULL)
    {
        cout << edge->data << " ";
        edge = edge->next;
    }

    return 0;
}
