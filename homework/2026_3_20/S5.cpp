#include <iostream>
using namespace std;

struct linkdList
{
    int data;
    linkdList *next;
    linkdList *prev;
};

void printList(linkdList *head);
void delList(linkdList *&head, int place);
void insertList(linkdList *&head, int place, int data);

int main()
{
    linkdList *head = nullptr;
    int choice;

    while (cin >> choice)
    {
        switch (choice)
        {
        case 0:
        {
            printList(head);
            cout << endl;
            break;
        }
        case 1:
        {
            int place, data;
            cin >> place >> data;
            insertList(head, place, data);
            break;
        }
        case 2:
        {
            int place;
            cin >> place;
            delList(head, place);
            break;
        }
        }
    }

    return 0;
}

void printList(linkdList *head)
{
    if (head == nullptr)
        return;

    linkdList *temp = head;
    do
    {
        cout << temp->data;
        temp = temp->next;
        if (temp != head)
            cout << " ";
    } while (temp != head);
}

void delList(linkdList *&head, int place)
{
    if (head == nullptr)
        return;

    // 只有一个结点
    if (head->next == head)
    {
        delete head;
        head = nullptr;
        return;
    }

    // 删除第1个位置
    if (place == 1)
    {
        linkdList *temp = head;
        linkdList *tail = head->prev;

        head = head->next;
        tail->next = head;
        head->prev = tail;

        delete temp;
        return;
    }

    linkdList *temp = head;
    for (int i = 1; i < place; i++)
    {
        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
}

void insertList(linkdList *&head, int place, int data)
{
    linkdList *newNode = new linkdList;
    newNode->data = data;

    // 空表
    if (head == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }

    // 插入到第1个位置
    if (place == 1)
    {
        linkdList *tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
        head = newNode;
        return;
    }

    linkdList *temp = head;
    for (int i = 1; i < place - 1; i++)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}